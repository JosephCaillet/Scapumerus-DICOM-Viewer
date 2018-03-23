//-------------------------------------------------------------------------------------------------------------------
/*!	\brief 	Implementation of class View3D
*	\file	View3D.cpp
*///-----------------------------------------------------------------------------------------------------------------

#include "View3D.h"

/*---- Internal Includes ----*/
#include "ApplicationData.h"

/*---- VTK Includes ----*/
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>

#include <QDebug>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

//-----------------------------------------------------------------------------------------------------------------
View3D::View3D(QWidget * p_parent)
: QVTKWidget(p_parent), m_renderer(vtkSmartPointer<vtkRenderer>::New())
//-----------------------------------------------------------------------------------------------------------------
{
	m_ui.setupUi(this);
}

//-----------------------------------------------------------------------------------------------------------------
View3D::~View3D()
//-----------------------------------------------------------------------------------------------------------------
{
	//Not necessary to delete children View3D, Qt will do it automatically
}

//-----------------------------------------------------------------------------------------------------------------
void View3D::initData()
//-----------------------------------------------------------------------------------------------------------------
{
	//Add renderer
	m_ui.view->GetRenderWindow()->RemoveRenderer(m_renderer);
	m_renderer = m_renderer->New();//renderer reset between image to clean actors and all related stuff
	m_ui.view->GetRenderWindow()->AddRenderer(m_renderer);

	m_renderer->SetBackground(backGroundColor, backGroundColor, backGroundColor);

	//Render
	m_renderer->Render();
	m_ui.view->update();

	//Create mapper for scapula
	//Use ScalarVisibilityOff() on mapper
	vtkSmartPointer<vtkPolyDataMapper> scapulaMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	scapulaMapper->SetInputData(ApplicationData::getInstance()->getScapula());
	scapulaMapper->ScalarVisibilityOff();

	//Create actor for scapula
	scapulaActor = vtkSmartPointer<vtkActor>::New();
	scapulaActor->SetMapper(scapulaMapper);

	//Create mapper for humerus
	//Use ScalarVisibilityOff() on mapper
	vtkSmartPointer<vtkPolyDataMapper> humerusMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
	humerusMapper->SetInputData(ApplicationData::getInstance()->getHumerus());
	humerusMapper->ScalarVisibilityOff();

	//Create actor for humerus
	humerusActor = vtkSmartPointer<vtkActor>::New();
	humerusActor->SetMapper(humerusMapper);

	slotEnableColors(colorEnabled);

	//setup text not working :(
//	vtkSmartPointer<vtkTextActor> humerusTextActor =
//			vtkSmartPointer<vtkTextActor>::New();
//	humerusTextActor->SetInput("Humerus");
//	humerusTextActor->SetPosition2(20, 20);
//	humerusTextActor->GetTextProperty()->SetFontSize(24);
//	humerusTextActor->GetTextProperty()->SetColor(0.5, 0.5, 1);
//
//	vtkSmartPointer<vtkTextActor> scapulaTextActor =
//			vtkSmartPointer<vtkTextActor>::New();
//	scapulaTextActor->SetInput("Scapula");
//	scapulaTextActor->GetTextProperty()->SetFontSize(24);
//	scapulaTextActor->GetTextProperty()->SetColor(1, 0.5, 0.5);
//	scapulaTextActor->SetPosition(20, 20);
//	scapulaTextActor->SetTextScaleMode(40);

	//Add actors
	m_renderer->AddActor(scapulaActor);
	m_renderer->AddActor(humerusActor);
//	m_renderer->AddActor2D(scapulaTextActor);
//	m_renderer->AddActor2D(humerusTextActor);
}

//-----------------------------------------------------------------------------------------------------------------
void View3D::slotEnableColors(bool enabled)
//-----------------------------------------------------------------------------------------------------------------
{
	colorEnabled = enabled;
	if(enabled)
	{
		humerusActor->GetProperty()->SetColor(0.5, 0.5, 1);
		scapulaActor->GetProperty()->SetColor(1, 0.5, 0.5);
	}
	else
	{
		humerusActor->GetProperty()->SetColor(0.87, 0.83, 0.69);
		scapulaActor->GetProperty()->SetColor(0.87, 0.83, 0.69);
	}
	//Render
	m_renderer->Render();
	m_ui.view->update();

}//-----------------------------------------------------------------------------------------------------------------
void View3D::slotInvertBackgroundColor()
//-----------------------------------------------------------------------------------------------------------------
{
	backGroundColor = !backGroundColor;

	m_renderer->SetBackground(backGroundColor, backGroundColor, backGroundColor);
	//Render
	m_renderer->Render();
	m_ui.view->update();
}

//-----------------------------------------------------------------------------------------------------------------
void View3D::show()
//-----------------------------------------------------------------------------------------------------------------
{
	QWidget::show();
	m_ui.view->update();
	m_renderer->Render();
	m_renderer->ResetCamera();
}
