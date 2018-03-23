#pragma once


/*---- VTK Includes ----*/
#include <vtkImageViewer.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <QtCore/QArgument>
#include <QtWidgets/QWidget>


#include "ui_View2D.h"

//-------------------------------------------------------------------------------------------------------------------
/*!	\class	View2D
*	\brief	View2D
*
*	\note	Copy constructor and assignment operator are purposely not implemented.
*	
*	\file	View2D.h
*///-----------------------------------------------------------------------------------------------------------------
class View2D : public QWidget
{
	Q_OBJECT
	public:
		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Constructor	
		*///-----------------------------------------------------------------------------------------------------------------
		View2D(QWidget * p_parent = NULL);

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Destructor	
		*///-----------------------------------------------------------------------------------------------------------------
		~View2D();

		//-------------------------------------------------------------------------------------------------------------------
		/*!	\brief	Init data
		*///-----------------------------------------------------------------------------------------------------------------
		void initData();


		View2D( const View2D & ) = delete;					//! Purposely deleted
		View2D & operator=(const View2D & ) = delete;		//! Purposely deleted
		void displaySliceObjectCounter();

	public slots:
		void slotUpdateSlice(const int p_value);

	private:
		vtkSmartPointer<vtkRenderer> m_renderer;
		vtkSmartPointer<vtkImageViewer> m_viewer;
		Ui::View2D m_ui;

		
};
