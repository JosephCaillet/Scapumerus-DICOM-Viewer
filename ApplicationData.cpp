//-------------------------------------------------------------------------------------------------------------------
/*!	\brief 	Implementation of class ApplicationData
*	\file	ApplicationData.cpp
*///-----------------------------------------------------------------------------------------------------------------

#include "ApplicationData.h"

/*---- ITK Includes ----*/

/*---- QT Includes ----*/
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QStringList>

/*---- VTK Includes ----*/
#include <vtkImageFlip.h>
#include <vtkPointData.h>
#include <vtkShortArray.h>
#include <vtkUnsignedCharArray.h>
#include <itkImageFileReader.h>
#include <itkGDCMImageIO.h>
#include <itkImageRegionConstIterator.h>
#include <itkBinaryThresholdImageFilter.h>
#include <vtkMarchingCubes.h>
#include <vtkDecimatePro.h>
#include <vtkSTLWriter.h>
#include <vtkBooleanOperationPolyDataFilter.h>
#include <itkConnectedComponentImageFilter.h>
#include <itkRelabelComponentImageFilter.h>

//Initialize static variable
ApplicationData * ApplicationData::m_instance = 0;

//-----------------------------------------------------------------------------------------------------------------
ApplicationData::ApplicationData() : QObject(),
		m_scapula(vtkPolyData::New()), m_humerus(vtkPolyData::New())
//-----------------------------------------------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------------------------------------------
ApplicationData::~ApplicationData()
//-----------------------------------------------------------------------------------------------------------------
{
	m_scapula->Delete();
	m_humerus->Delete();
}

//-----------------------------------------------------------------------------------------------------------------
bool ApplicationData::loadDirectory(const QString & p_dirPath)
//-----------------------------------------------------------------------------------------------------------------
{
	emit progressStarted();

	//reset previous saved state
	m_rawImages.clear();
	m_rawImagesLabelerCounter.clear();

	//Save path
	m_openingPath = p_dirPath;

	//List files in a directory
	QDir dir(p_dirPath);

	//Create the list of string to store files path
	QStringList filesList;

	//Set the appropriate filter (we only want Files) and sorting procedure (by name).
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable);
	dir.setSorting(QDir::Name);

	//List all files
	const QFileInfoList list = dir.entryInfoList();
	emit progressNewStep("Listing files", list.size());

	for (int i = 0 ; i < list.size() ; ++i)
	{
		//Check if it is a readable file
		if ( (list[i].isFile()) && (list[i].isReadable()) )
			filesList.push_back(list[i].absoluteFilePath());
		emit progressUpdate(i + 1);
	}

	qDebug() << filesList.size();
	//filesList contains all the files found in the directory

	//Read Dicom Image
	emit progressNewStep("Reading DICOM image files", filesList.size());

	double positionZ = 0.;
	for(int i = 0 ; i < filesList.size() ; ++i)
	{
		//try to read the ITK file and save the image
//		qDebug() << "Reading image " << i + 1 << "with path:" << filesList[i];

		itk::ImageFileReader<UShortImageType>::Pointer reader = itk::ImageFileReader<UShortImageType>::New();
		itk::GDCMImageIO::Pointer gdcmImageIO = itk::GDCMImageIO::New();

		try
		{
			reader->SetFileName(filesList[i].toStdString().c_str());
			reader->SetImageIO(gdcmImageIO);
			reader->Update();
			m_rawImages.append(reader->GetOutput());

			//For the first two images, we get the image position (0020, 0032).
			//From the difference, we compute the spacingZ
			if(i <= 1)
			{
				std::string currentPosition;
				gdcmImageIO->GetValueFromTag(std::string("0020|0032"), currentPosition);
				const double currentPositionZ = QString(currentPosition.c_str()).trimmed().split("\\").last().toDouble();
				qDebug() << QString(currentPosition.c_str()) << positionZ;
				if(i == 1)
				{
					m_spacingZ = currentPositionZ - positionZ;
				}
				else positionZ = currentPositionZ;
			}

		}
		//catch error in case we try to read a non dicom file
		catch(...)
		{
			qDebug() << "Skipping not valid DICOM image file: " << filesList[i].toStdString().c_str();
		}
		emit progressUpdate(i + 1);
	}

	//if no DICOM image found, returning false
	if(m_rawImages.size() == 0)
	{
		emit progressStopped();
		return false;
	}


	emit progressNewStep("Computing metadatas", 1);
	//Get dimensionX/Y
	m_dimensionX = m_rawImages.first()->GetLargestPossibleRegion().GetSize()[0];
	m_dimensionY = m_rawImages.first()->GetLargestPossibleRegion().GetSize()[1];

	//Get spacing X/Y
	m_spacingX = m_rawImages.first()->GetSpacing()[0];
	m_spacingY = m_rawImages.first()->GetSpacing()[1];

	//Get dimensionZ
	m_dimensionZ = m_rawImages.size();

	qDebug() << "dim x" << m_dimensionX;
	qDebug() << "dim y" << m_dimensionY;
	qDebug() << "dim z" << m_dimensionZ;
	qDebug() << "spa x" << m_spacingX;
	qDebug() << "spa y" << m_spacingY;
	qDebug() << "spa z" << m_spacingZ;

	emit progressUpdate(1);

	//Build the vtkImageData containing the raw volume
	emit progressNewStep("Building raw volume", m_rawImages.size());
	m_rawVTKData = vtkSmartPointer<vtkImageData>::New();

	m_rawVTKData->SetDimensions(m_dimensionX, m_dimensionY, m_dimensionZ);
	m_rawVTKData->SetSpacing(m_spacingX, m_spacingY, m_spacingZ);
	m_rawVTKData->SetOrigin(0, 0, 0);
	m_rawVTKData->SetExtent(0, m_dimensionX - 1, 0, m_dimensionY - 1, 0, m_dimensionZ - 1);

	//Create scalars to fill the vtkImageData
	vtkSmartPointer<vtkShortArray> scalars = vtkSmartPointer<vtkShortArray>::New();
	scalars->SetNumberOfValues(m_dimensionX * m_dimensionY * m_dimensionZ);

	int offset  = 0;
	//Iterate over all images and fill the scalars
 	for(int z = 0 ; z < m_rawImages.size() ; ++z)
	{
		//Create const iterator on each image
		auto image = m_rawImages[z];
		itk::ImageRegionConstIterator<UShortImageType> globalIterator(image, image->GetLargestPossibleRegion());
		globalIterator.GoToBegin();
		//In the while, set the value of each pixel to the scalars using offset
		while(! globalIterator.IsAtEnd())
		{
			scalars->SetValue(offset, globalIterator.Get());
			offset++;
			++globalIterator;
		}
		emit progressUpdate(z + 1);
	}
	
	m_rawVTKData->GetPointData()->SetScalars(scalars);


	//Flip image along Y to respect difference of referentiel between ITK/VTK display
	emit progressNewStep("Flipping along Y axes", 1);
	vtkSmartPointer<vtkImageFlip> flipper = vtkSmartPointer<vtkImageFlip>::New();
	flipper->SetFilteredAxis(1);//car l'origine n'est pas la même dans itk et vtk
	flipper->SetInputData(m_rawVTKData);
	flipper->Update();
	m_rawVTKData = flipper->GetOutput();

	emit progressUpdate(1);

	emit progressStopped();
	return true;
}

//-----------------------------------------------------------------------------------------------------------------
void ApplicationData::segmentData()
//-----------------------------------------------------------------------------------------------------------------
{
	emit progressStarted();

	//Segment from 1 to 2 for Scapula
	m_scapula->Delete();
	m_scapula = segmentData(2, 2);
	int scapulaSize = m_scapula->GetPointData()->GetScalars()->GetSize();

	emit progressStopped();

	//Segment from 0 to 1 for Humerus
	emit progressStarted();

	m_humerus->Delete();
	m_humerus = segmentData(1, 1);
	int humerusSize = m_humerus->GetPointData()->GetScalars()->GetSize();

	//In DICOM images, sometimes scapula and humerus have their color inverted.
	//As the scapula is usually bigger than humerus, we invert them using their size (in point number)
	if(scapulaSize < humerusSize)
	{
		vtkPolyData* temp = m_scapula;
		m_scapula = m_humerus;
		m_humerus = temp;
	}

	emit progressStopped();
}

//-----------------------------------------------------------------------------------------------------------------
void ApplicationData::countObjectInSlices()
//-----------------------------------------------------------------------------------------------------------------
{
	emit progressStarted();
	emit progressNewStep("Labeling slices", m_rawImages.size());
	for(int z = 0 ; z < m_rawImages.size() ; ++z)
	{
		//Create const iterator on each image
		auto image = m_rawImages[z];
		itk::ImageRegionConstIterator<UShortImageType> globalIterator(image, image->GetLargestPossibleRegion());

		itk::BinaryThresholdImageFilter<UShortImageType, UCharImageType>::Pointer thresholder =
				itk::BinaryThresholdImageFilter<UShortImageType, UCharImageType>::New();

		thresholder->SetInput(image);
		thresholder->SetLowerThreshold(1);
		thresholder->SetUpperThreshold(2);
		thresholder->SetInsideValue(255);
		thresholder->SetOutsideValue(0);
		thresholder->Update();

		//Labelize the image
		itk::ConnectedComponentImageFilter<UCharImageType, IntImageType>::Pointer labeler =
				itk::ConnectedComponentImageFilter<UCharImageType, IntImageType>::New();
		labeler->SetInput(thresholder->GetOutput());
		labeler->Update();

		//Relabelize the image to get info about the group of found pixels
		itk::RelabelComponentImageFilter<IntImageType, UCharImageType>::Pointer relabeler =
				itk::RelabelComponentImageFilter<IntImageType, UCharImageType>::New();
		relabeler->SetInput(labeler->GetOutput());
		relabeler->SetMinimumObjectSize(100);
		relabeler->Update();

		m_rawImagesLabelerCounter.append(relabeler->GetNumberOfObjects());

		emit progressUpdate(z + 1);
	}
	emit progressStopped();
}

void ApplicationData::save3dModels(const QString directorySavePath)
{
	m_savingPath = directorySavePath;
	emit progressStarted();
	emit progressNewStep("Saving 3d model of humerus scapula both", 4);
	vtkSmartPointer<vtkSTLWriter> writer = vtkSmartPointer<vtkSTLWriter>::New();

	writer->SetInputData(m_humerus);
	writer->SetFileName((directorySavePath + "/meshHumerus.stl").toStdString().c_str());
	writer->Write();
	emit progressUpdate(1);

	writer->SetInputData(m_scapula);
	writer->SetFileName((directorySavePath + "/meshScapula.stl").toStdString().c_str());
	writer->Write();
	emit progressUpdate(2);

	//Merging both scapula and humerus in one model
	vtkSmartPointer<vtkBooleanOperationPolyDataFilter> booleanFilter =
			vtkSmartPointer<vtkBooleanOperationPolyDataFilter>::New();
	booleanFilter->SetInputData(0, m_scapula);
	booleanFilter->SetInputData(1, m_humerus);
	booleanFilter->SetOperationToUnion();
	booleanFilter->Update();
	emit progressUpdate(3);

	writer->SetInputData(booleanFilter->GetOutput());
	writer->SetFileName((directorySavePath + "/meshHumerusScapula.stl").toStdString().c_str());
	writer->Write();
	emit progressUpdate(4);

	emit progressStopped();
}

//-----------------------------------------------------------------------------------------------------------------
vtkPolyData * ApplicationData::segmentData(const int p_lowerThreshold, const int p_upperThreshold) const
//-----------------------------------------------------------------------------------------------------------------
{
	QList<UCharImageType::Pointer> binaryImages;
	binaryImages.clear();

	//Apply threshold on each raw images
	emit progressNewStep("Applying 2d threshold", m_rawImages.size());

	//Same as ITKReader with itk::BinaryThresholdImageFilter
	//See Exo6 ITK
	itk::BinaryThresholdImageFilter<ShortImageType, UCharImageType>::Pointer thresholder =
			itk::BinaryThresholdImageFilter<ShortImageType, UCharImageType>::New();
	for(int i = 0 ; i < m_rawImages.size() ; ++i)
	{
		thresholder->SetInput(m_rawImages[i]);
		thresholder->SetLowerThreshold(p_lowerThreshold);
		thresholder->SetUpperThreshold(p_upperThreshold);
		thresholder->SetInsideValue(255);
		thresholder->SetOutsideValue(0);
		thresholder->Update();
		binaryImages.append(thresholder->GetOutput());
		thresholder->GetOutput()->DisconnectPipeline();//cleaning thresholder input (to avoid allocating a new one ech loop iteration

		emit progressUpdate(i + 1);
	}

	//Build Image Data for input of marching cubes
	emit progressNewStep("Building 3d model: creating scalars", binaryImages.size());

	vtkSmartPointer<vtkImageData> marchingCubesRawVTKData =
		vtkSmartPointer<vtkImageData>::New();

	marchingCubesRawVTKData->SetDimensions(m_dimensionX, m_dimensionY, m_dimensionZ);
	marchingCubesRawVTKData->SetSpacing(m_spacingX, m_spacingY, m_spacingZ);
	marchingCubesRawVTKData->SetOrigin(0, 0, 0);
	marchingCubesRawVTKData->SetExtent(0, m_dimensionX - 1, 0, m_dimensionY - 1, 0, m_dimensionZ - 1);

	//Create scalars to fill the vtkImageData
	vtkSmartPointer<vtkShortArray> scalars = vtkSmartPointer<vtkShortArray>::New();
	scalars->SetNumberOfValues(m_dimensionX * m_dimensionY * m_dimensionZ);

	int offset  = 0;
	//Iterate over all images and fill the scalars
	//for on binary images
	for(int z = 0 ; z < binaryImages.size() ; ++z)
	{
		//Same as before with m_rawImages and m_rawData
		auto image = binaryImages[z];
		itk::ImageRegionConstIterator<UCharImageType> globalIterator(image, image->GetLargestPossibleRegion());
		globalIterator.GoToBegin();
		while(! globalIterator.IsAtEnd())
		{
			scalars->SetValue(offset, globalIterator.Get());
			offset++;
			++globalIterator;
		}
		emit progressUpdate(z + 1);
	}

	//computing 3d model from 2d slices
	marchingCubesRawVTKData->GetPointData()->SetScalars(scalars);

	//Apply the marching cubes
	emit progressNewStep("Building 3d model: applying marching cubes", 1);

	//vtkMarchingCubes
	//See Exo12 VTK
	vtkSmartPointer<vtkMarchingCubes> marchingcubes =
			vtkSmartPointer<vtkMarchingCubes>::New();
	marchingcubes->SetInputData(marchingCubesRawVTKData);
	marchingcubes->SetValue(0, 1);
	marchingcubes->Update();//création d'un mesh en 3d à partir des img 3d
	emit progressUpdate(1);

	qDebug() << "Before decimater:" << marchingcubes->GetOutput()->GetNumberOfPoints();

	//Reducing point number
	emit progressNewStep("Building 3d model: applying decimater", 1);
	vtkSmartPointer<vtkDecimatePro> decimater =
			vtkSmartPointer<vtkDecimatePro>::New();
	decimater->SetInputData(marchingcubes->GetOutput());
	decimater->SetTargetReduction(0.7);
	decimater->Update();//supression du maximum de triagle coplanaire (ds le meme plan)

	qDebug() << "After decimater: " << decimater->GetOutput()->GetNumberOfPoints();
	emit progressUpdate(1);

	//Return resulting mesh after copy
	vtkPolyData * mesh = vtkPolyData::New();
	mesh->DeepCopy(decimater->GetOutput());

	emit progressStopped();

	return mesh;
}
