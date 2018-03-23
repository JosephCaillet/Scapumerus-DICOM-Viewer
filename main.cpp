//-------------------------------------------------------------------------------------------------------------------
/*!	\brief	Application used to validate the Glenoid fitting process
*	\file	main.cpp
*	\author	Imascap
*///-----------------------------------------------------------------------------------------------------------------

/*---- Internal Includes ----*/
#include "ApplicationData.h"
#include "Widget.h"

/*---- QT Includes ----*/
#include <QApplication>


//-----------------------------------------------------------------------------------------------------------------
int main(int p_argc, char* p_argv[])
//-----------------------------------------------------------------------------------------------------------------
{
	QApplication app(p_argc, p_argv);

	//Create main widget
	Widget widget;
	widget.show();

	//Launch events loop
	app.exec();

	//Kill data
	ApplicationData::getInstance()->kill();

	return 0;
}