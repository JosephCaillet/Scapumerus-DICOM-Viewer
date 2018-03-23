#pragma once


/*---- ITK Includes ----*/
#include <itkImage.h>

/*---- QT Includes ----*/
#include <QList>
#include <QString>
#include <QDebug>
#include <QWidget>

/*---- VTK Includes ----*/
#include <vtkImageData.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

//Define image type
typedef itk::Image<signed short, 2> ShortImageType;
typedef itk::Image<unsigned char, 2> UCharImageType;


//-------------------------------------------------------------------------------------------------------------------
/*!	\class	ApplicationData
*	\brief	Stored the application data using SingletonPattern
*
*	\note	Copy constructor and assignment operator are purposely not implemented.
*	
*	\file	ApplicationData.h
*///-----------------------------------------------------------------------------------------------------------------
class ApplicationData : protected QObject
{
	Q_OBJECT

	public:
		typedef itk::Image<short , 2> UShortImageType;
		typedef itk::Image<int, 2> IntImageType;

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Get instance: if NULL create it	
		*///-----------------------------------------------------------------------------------------------------------------
		static ApplicationData * getInstance()
		{
			//Create instance
			if (!m_instance)
				m_instance = new ApplicationData();
			return m_instance;
		}

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Kill the instance if already created	
		*///-----------------------------------------------------------------------------------------------------------------
		static void kill()
		{
			//Delete instance
			if (m_instance)
			{
				delete m_instance;
				m_instance = nullptr;
			}
		}

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Method to load a directory
			\return	true if load success, false otherwise
		*///-----------------------------------------------------------------------------------------------------------------
		bool loadDirectory(const QString & p_dirPath);

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Method to segment the data
		*///-----------------------------------------------------------------------------------------------------------------
		void segmentData();

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Method to count object per slices in data
		*///-----------------------------------------------------------------------------------------------------------------
		void countObjectInSlices();

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Method to save 3d models to a directory
		*///-----------------------------------------------------------------------------------------------------------------
		void save3dModels(const QString directorySavePath);

		//! Getters
		vtkPolyData * getScapula() const { return m_scapula; }
		vtkPolyData * getHumerus() const { return m_humerus; }

		vtkSmartPointer<vtkImageData> getRawVTKData() const { return m_rawVTKData; }

		QString getLastOpenedPath() const { return m_openingPath; }
		QString getLastSaveddPath() const { return m_savingPath != nullptr ? m_savingPath : m_openingPath; }

		unsigned int getSliceNumber() const { return m_dimensionZ; }
		unsigned int getSliceWidth() const { return m_dimensionX; }
		unsigned int getSliceHeight() const { return m_dimensionY; }

		QList<int> getLabeledCounter() const { return m_rawImagesLabelerCounter; }

	signals:
		void progressStarted() const;
		void progressNewStep(const QString stepName, const int subStepsNumber) const;
		void progressUpdate(const int currentSubStep) const;
		void progressStopped() const;

	private:
		static ApplicationData *m_instance;
		
		//! The path to the current processed directory
		QString m_openingPath;// = "../Data/Patient021/Segmented";
		//! The path to the last directory used to save 3d models
		QString m_savingPath = nullptr;
		//! The spacing for the loaded scan
		//doubles
		double m_spacingZ, m_spacingX, m_spacingY;
		//! The dimensions of the loaded scan
		unsigned int m_dimensionX, m_dimensionY, m_dimensionZ;
		

		//! Store the raw images
		QList<ShortImageType::Pointer> m_rawImages;

		//! Count number of object per slice;
		QList<int> m_rawImagesLabelerCounter;

		//! Store raw VTK data
		vtkSmartPointer<vtkImageData> m_rawVTKData;

		//! The raw data in VTK format
		vtkPolyData * m_scapula, * m_humerus;

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Method to segment the data depending on lower and higher threshold
		*///-----------------------------------------------------------------------------------------------------------------
		vtkPolyData * segmentData(const int p_lowerThreshold, const int p_upperThreshold) const;

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Constructor
		*///-----------------------------------------------------------------------------------------------------------------
		ApplicationData();

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Destructor
		*///-----------------------------------------------------------------------------------------------------------------
		virtual ~ApplicationData();
		
		ApplicationData( const ApplicationData & );					//! Purposely not implemented
		ApplicationData & operator=(const ApplicationData & );		//! Purposely not implemented

};