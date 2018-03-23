#pragma once


/*---- VTK Includes ----*/
#include <QVTKWidget.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include "ui_View3D.h"

//-------------------------------------------------------------------------------------------------------------------
/*!	\class	View3D
*	\brief	View3D
*
*	\note	Copy constructor and assignment operator are purposely not implemented.
*	
*	\file	View3D.h
*///-----------------------------------------------------------------------------------------------------------------
class View3D : public QVTKWidget
{
	Q_OBJECT
	public:
		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Constructor	
		*///-----------------------------------------------------------------------------------------------------------------
		View3D(QWidget * p_parent = NULL);

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Destructor	
		*///-----------------------------------------------------------------------------------------------------------------
		~View3D();

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Init data
		*///-----------------------------------------------------------------------------------------------------------------
		void initData();

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Show widget
		*///-----------------------------------------------------------------------------------------------------------------
		void show();

		View3D( const View3D & ) = delete;					//! Purposely deleted
		View3D & operator=(const View3D & ) = delete;		//! Purposely deleted
		
	private:
		vtkSmartPointer<vtkRenderer> m_renderer;
		Ui::View3D m_ui;
		vtkSmartPointer<vtkActor> humerusActor;
		vtkSmartPointer<vtkActor> scapulaActor;
		bool colorEnabled = false;
		double backGroundColor = 0;

	private slots:
		void slotEnableColors(const bool enabled);
		void slotInvertBackgroundColor();
		
};