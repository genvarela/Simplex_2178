#include "Main.h"

/*
	main program will create an App class object and run it, once its done it will
	delete it
*/
int main(void)
{
	AppClass* pApp = new AppClass(); //create an AppClas object
	pApp->Run(); //Run the app this will return the execution control once the main loop is done
	if (pApp) //if the app allocated space, delete it
	{
		delete pApp;
		pApp = nullptr;
	}
	return 0;
}