//-------------------------------------------------------------------------------------------------------------------
/*!	\brief 	Implementation of class View2D
*	\file	View2D.cpp
*///-----------------------------------------------------------------------------------------------------------------

#include "View2D.h"

/*---- Internal Includes ----*/
#include "ApplicationData.h"

/*---- VTK Includes ----*/
#include <vtkActor2D.h>
#include <vtkRenderWindow.h>
#include <QDebug>
//-----------------------------------------------------------------------------------------------------------------
View2D::View2D(QWidget * p_parent)
: QWidget(p_parent), m_renderer(vtkSmartPointer<vtkRenderer>::New()), m_viewer(vtkSmartPointer<vtkImageViewer>::New())
//-----------------------------------------------------------------------------------------------------------------
{
	m_ui.setupUi(this);
	m_ui.lcdNumber->display(1);
}

//-----------------------------------------------------------------------------------------------------------------
View2D::~View2D()
//-----------------------------------------------------------------------------------------------------------------
{
	//Not necessary to delete children View2D, Qt will do it automatically
}

//-----------------------------------------------------------------------------------------------------------------
void View2D::initData()
//-----------------------------------------------------------------------------------------------------------------
{
	//reset
	m_ui.objectCounterLcdNumber->display(-1);
	m_ui.objectCounterLcdNumber->setDisabled(true);

	//Add renderer
	m_ui.view->GetRenderWindow()->RemoveRenderer(m_renderer);
	m_renderer = m_renderer.New();
	m_ui.view->GetRenderWindow()->AddRenderer(m_renderer);

	//Set input to viewer
	m_viewer->SetInputData(ApplicationData::getInstance()->getRawVTKData());
	m_ui.view->setMinimumSize(ApplicationData::getInstance()->getSliceWidth(), ApplicationData::getInstance()->getSliceHeight());

	setFixedWidth(ApplicationData::getInstance()->getSliceWidth());
	//Add actor to the renderer
	m_renderer->AddActor2D(m_viewer->GetActor2D());

	//Init slider
	m_ui.slider->setRange(1, ApplicationData::getInstance()->getSliceNumber());

	//Connect slider to 2D view
	connect(m_ui.slider, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateSlice(int)));

	//Connect slider to LCD number
	connect(m_ui.slider, SIGNAL(valueChanged(int)), m_ui.lcdNumber, SLOT(display(int)));

	//Update color
	double range[2];
	ApplicationData::getInstance()->getRawVTKData()->GetScalarRange(range);

	m_viewer->SetColorWindow(range[1] - range[0] );
	m_viewer->SetColorLevel( (range[1]+range[0])/2 );

	//Set Z Slice and update view
	m_ui.slider->setValue(1);
}

//-----------------------------------------------------------------------------------------------------------------
void View2D::slotUpdateSlice(const int p_value)
//-----------------------------------------------------------------------------------------------------------------
{
	m_viewer->SetZSlice(p_value - 1);
	m_ui.view->setMinimumSize(ApplicationData::getInstance()->getSliceWidth(), ApplicationData::getInstance()->getSliceHeight());
	m_ui.view->update();

	auto counters = ApplicationData::getInstance()->getLabeledCounter();
	if(m_ui.objectCounterLcdNumber->isEnabled())
	{
		m_ui.objectCounterLcdNumber->display(counters[p_value - 1]);
	}
}

//-----------------------------------------------------------------------------------------------------------------
void View2D::displaySliceObjectCounter()
//-----------------------------------------------------------------------------------------------------------------
{
	auto counters = ApplicationData::getInstance()->getLabeledCounter();
	m_ui.objectCounterLcdNumber->setDisabled(false);
	m_ui.objectCounterLcdNumber->display(counters[m_ui.slider->value() - 1]);
}