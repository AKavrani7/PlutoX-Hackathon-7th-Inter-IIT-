// Do not remove the include below
#include "PlutoPilot.h"
#include "Peripheral.h"
#include "Print.h"
#include "Led.h"
#include "Control.h"
#include "Althold.h"


int16_t sensorValue14;
int16_t someThresholdValue = 200;

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
	ADC.Init(Pin14);
}



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

	sensorValue14 = ADC.Read(Pin14)*340/4096;

	Print.monitor("Gas Sensor Value", sensorValue14);
	Print.monitor("\n");

	if(sensorValue14 > someThresholdValue)
	{
		Print.monitor("Do Something");
		Print.monitor("\n");
		Control.arm();
		Althold.setRelativeAltholdHeight(200);
	}
	else
	{
		Print.monitor("Situation is under Control");
		Print.monitor("\n");
		Control.setCommand(COMMAND_LAND);
		Control.disArm();
	}

}

//The function is called once after plutoPilot when you deactivate Developer Mode
void onPilotFinish()
{

// do your cleanup stuffs here
	Control.disableFlightStatus(false);
}
