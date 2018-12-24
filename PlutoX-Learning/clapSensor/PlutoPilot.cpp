// Do not remove the include below
#include "PlutoPilot.h"
#include "Control.h"
#include "Peripheral.h"
#include "Led.h"
#include "Print.h"
#include "Althold.h"

int16_t sensorValue4;
int16_t thresholdValue = 15;


//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
	ADC.Init(Pin4);
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

	sensorValue4 = ADC.Read(Pin4)*340/4096;

	Print.monitor("SensorValue4: ", sensorValue4);
	Print.monitor("\n");

	if(sensorValue4 > thresholdValue)
	{
		ledOp(L_LEFT, ON);
		ledOp(L_RIGHT, OFF);

		Control.arm();
		Althold.setRelativeAltholdHeight(200);
	}


}



//The function is called once after plutoPilot when you deactivate Developer Mode
void onPilotFinish()
{

// do your cleanup stuffs here
	Control.disableFlightStatus(false);

}




