//-------------------------------------------------------------------------------------------------------------------
/*!	\brief 	Implementation of class Widget
*	\file	Widget.cpp
*///-----------------------------------------------------------------------------------------------------------------

#include "Widget.h"

/*---- Internal Includes ----*/
#include "ApplicationData.h"
#include "View2D.h"
#include "View3D.h"

/*---- QT Includes ----*/
#include <QFileDialog>
#include <QDebug>
#include <QHBoxLayout>
#include <QtWidgets/QMessageBox>

//-----------------------------------------------------------------------------------------------------------------
Widget::Widget(QWidget * p_parent) : QWidget(p_parent)
//-----------------------------------------------------------------------------------------------------------------
{
	m_ui.setupUi(this);

	//Hide view
	m_ui.segmentButton->setDisabled(true);
	m_ui.view2D->hide();
	m_ui.view3D->hide();
	m_ui.progressBar->hide();

	//Connect signals and slots for Load button
	connect(m_ui.loadButton, SIGNAL(clicked()), this, SLOT(slotSelectDir()));
	connect(m_ui.saveButton, SIGNAL(clicked()), this, SLOT(slotSave3dModels()));
	connect(m_ui.segmentButton, SIGNAL(clicked()), this, SLOT(slotSegmentData()));
	connect(m_ui.countButton, SIGNAL(clicked()), this, SLOT(coutObjectInSlice()));
	connect(m_ui.colorsButton, SIGNAL(toggled(bool)), m_ui.view3D, SLOT(slotEnableColors(bool)));
	connect(m_ui.invertBgColorButton, SIGNAL(toggled(bool)), m_ui.view3D, SLOT(slotInvertBackgroundColor()));

	auto data = ApplicationData::getInstance();
	connect(data, SIGNAL(progressStarted()), this, SLOT(slotProgressStarted()));
	connect(data, SIGNAL(progressStopped()), this, SLOT(slotProgressStopped()));
	connect(data, SIGNAL(progressNewStep(QString, int)), this, SLOT(slotProgressNewStep(QString, int)));
	connect(data, SIGNAL(progressUpdate(int)), m_ui.progressBar , SLOT(setValue(int)));

	setFixedWidth(1200);
}

//-----------------------------------------------------------------------------------------------------------------
Widget::~Widget()
//-----------------------------------------------------------------------------------------------------------------
{
}

//-----------------------------------------------------------------------------------------------------------------
void Widget::slotSelectDir()
//-----------------------------------------------------------------------------------------------------------------
{
	const QString dirPath = QFileDialog::getExistingDirectory(this, "Open DICOM image directory", ApplicationData::getInstance()->getLastOpenedPath());
	if(dirPath != "")
	{
		m_ui.segmentButton->setDisabled(true);
		m_ui.saveButton->setDisabled(true);
		m_ui.view2D->hide();
		m_ui.view3D->hide();
		update();

		//Load directory
		if(!ApplicationData::getInstance()->loadDirectory(dirPath))
		{
			QMessageBox::critical(this, "Error opening DICOM folder", "Selected folder does not contains any DICOM image file.");
			return;
		}

		//Connect signals and slots for Segment button
		m_ui.segmentButton->setDisabled(false);
		m_ui.countButton->setEnabled(true);

		m_ui.view2D->initData();

		//Show view2D and view3D
		m_ui.view2D->show();
	}
}

//-----------------------------------------------------------------------------------------------------------------
void Widget::slotSegmentData()
//-----------------------------------------------------------------------------------------------------------------
{
	//Disconnect segment button
	m_ui.segmentButton->setDisabled(true);
	m_ui.colorsButton->setDisabled(false);
	m_ui.invertBgColorButton->setDisabled(false);
	m_ui.saveButton->setDisabled(false);

	//Segment data
	ApplicationData::getInstance()->segmentData();

	//Init view3D
	m_ui.view3D->initData();
	m_ui.view3D->show();
}

//-----------------------------------------------------------------------------------------------------------------
void Widget::slotSave3dModels()
//-----------------------------------------------------------------------------------------------------------------
{
	const QString dirPath = QFileDialog::getExistingDirectory(this, "Save 3d models in directory", ApplicationData::getInstance()->getLastSaveddPath());
	if(dirPath != "")
	{
		ApplicationData::getInstance()->save3dModels(dirPath);
	}
}

//-----------------------------------------------------------------------------------------------------------------
void Widget::coutObjectInSlice()
//-----------------------------------------------------------------------------------------------------------------
{
	ApplicationData::getInstance()->countObjectInSlices();
	m_ui.countButton->setEnabled(false);
	m_ui.view2D->displaySliceObjectCounter();
}

//-----------------------------------------------------------------------------------------------------------------
void Widget::slotProgressStarted()
//-----------------------------------------------------------------------------------------------------------------
{
	m_ui.progressBar->show();
}

//-----------------------------------------------------------------------------------------------------------------
void Widget::slotProgressStopped()
//-----------------------------------------------------------------------------------------------------------------
{
	m_ui.progressBar->hide();
}

//-----------------------------------------------------------------------------------------------------------------
void Widget::slotProgressNewStep(QString stepName, int subStepsNumber)
//-----------------------------------------------------------------------------------------------------------------
{
	m_ui.progressBar->setFormat(stepName + " %v/%m (%p%)");
	m_ui.progressBar->setValue(0);
	m_ui.progressBar->setMaximum(subStepsNumber);
}