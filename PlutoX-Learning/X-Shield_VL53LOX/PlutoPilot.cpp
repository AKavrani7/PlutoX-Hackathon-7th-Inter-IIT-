// Do not remove the include below
#include "PlutoPilot.h"
#include "Xshield.h"
#include "Control.h"
#include "Led.h"

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
	Xshield.init();
}



//The function is called once before plutoPilot when you activate Developer Mode
void onPilotStart()
{
  // do your one time stuffs here
	Control.disableExternalRC(RC_ROLL);
	Xshield.startRanging();
	Control.disableFlightStatus(true);
	ledOp(L_MID, OFF);
	ledOp(L_LEFT, OFF);
	ledOp(L_RIGHT, OFF);
}


// The loop function is called in an endless loop
void plutoPilot()
{

//Add your repeated code here

	if(Xshield.getRange(RIGHT) < 200)
	{
		Control.setRC(RC_ROLL, 1000);
		ledOp(L_RIGHT, ON);
		ledOp(L_LEFT, OFF);
	}
	else if(Xshield.getRange(LEFT) < 200)
	{
		Control.setRC(RC_ROLL, 2000);
		ledOp(L_RIGHT, OFF);
		ledOp(L_LEFT, ON);
	}
}



//The function is called once after plutoPilot when you deactivate Developer Mode
void onPilotFinish()
{

// do your cleanup stuffs here
	Control.enableAllExternalRC();
	Xshield.stopRanging();
	Control.disableFlightStatus(false);

}




