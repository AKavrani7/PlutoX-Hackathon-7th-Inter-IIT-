
// Do not remove the include below
#include "PlutoPilot.h"
#include "Control.h"
#include "Print.h"
#include "Led.h"
#include "Motor.h"
#include "App.h"
#include "Angle.h"



int16_t m1m2value;
int16_t m3m4value;
int16_t throttleValue;
int16_t rollValue;

int16_t checkRange(int16_t amt)
{
	if(amt < -500) return -500;
	else if(amt > 500) return 500;

	return amt;
}

int16_t generatePWM(int16_t amt)
{
	if(amt<0) amt = -1*amt;

	return 1000 + amt*2;
}

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here

}



//The function is called once before plutoPilot when you activate Developer Mode
void onPilotStart()
{
  // do your one time stuffs here

	Control.disableFlightStatus(true);
	throttleValue = 0;
	rollValue = 0;
	ledOp(L_LEFT, OFF);
	ledOp(L_RIGHT,OFF);
	ledOp(L_MID,OFF);

}

// The loop function is called in an endless loop
void plutoPilot()
{

//Add your repeated code here

	throttleValue = Control.getRC(RC_THROTTLE);
	rollValue = Control.getRC(RC_ROLL);

	m1m2value = (throttleValue-1500) + (rollValue -1500)/2; ///
	m3m4value = (throttleValue-1500) - (rollValue -1500)/2; ///

	m1m2value = checkRange(m1m2value);
	m3m4value = checkRange(m3m4value);

	if(m1m2value > 0)
	{
		Motor.setDirection(M1, FORWARD);
		Motor.setDirection(M2, FORWARD);
	}
	else
	{
		Motor.setDirection(M1, BACKWARD);
		Motor.setDirection(M2, BACKWARD);
	}

	if(m3m4value > 0)
	{
		Motor.setDirection(M3, FORWARD);
		Motor.setDirection(M4, FORWARD);
	}
	else
	{
		Motor.setDirection(M3, BACKWARD);
		Motor.setDirection(M4, BACKWARD);
	}

	Motor.set(M1,generatePWM(m1m2value));
	Motor.set(M2,generatePWM(m1m2value));

	Motor.set(M3, generatePWM(m3m4value));
	Motor.set(M4, generatePWM(m3m4value));
}



//The function is called once after plutoPilot when you deactivate Developer Mode
void onPilotFinish()
{

// do your cleanup stuffs here

	Control.disableFlightStatus(false);
	Motor.set(M1, 1000);
	Motor.set(M2, 1000);
 	Motor.set(M3, 1000);
 	Motor.set(M4, 1000);

}



