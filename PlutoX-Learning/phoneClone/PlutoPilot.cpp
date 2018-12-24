// Do not remove the include below
#include "PlutoPilot.h"
#include "Print.h"
#include "Control.h"
#include "Led.h"
#include "App.h"

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
}


int phoneAlignment = 0;


//The function is called once before plutoPilot when you activate Developer Mode
void onPilotStart()
{
  // do your one time stuffs here
  Control.disableFlightStatus(true);
}



// The loop function is called in an endless loop
void plutoPilot()
{

//Add your repeated code here
	phoneAlignment = 90 + App.getAppHeading();

	if(phoneAlignment>360)
		phoneAlignment = phoneAlignment - 360;

	Print.monitor("phoneAlignment: ", phoneAlignment);
	Print.monitor("\n");

	Control.setHeading(phoneAlignment);
}



//The function is called once after plutoPilot when you deactivate Developer Mode
void onPilotFinish()
{

// do your cleanup stuffs here
	Control.disableFlightStatus(true);
}
