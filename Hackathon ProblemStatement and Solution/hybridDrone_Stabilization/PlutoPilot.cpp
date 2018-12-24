// Do not remove the include below
#include "PlutoPilot.h"
#include "Print.h"
#include "Control.h"
#include "Flight.h"
#include "Motor.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))
int constrain(int amt, int low, int high)
{
   if (amt < low)
        return low;
   else if (amt > high)
        return high;
   else
        return amt;
}

//Generate PWM Values
int generatePWM(int amt)
{

   amt= ABS(amt);

   amt=1000+(amt*2);

   return amt;
}

int16_t desiredHeading = 0; // Desired Heading
int16_t heading_error = 0;  // Heading error
int16_t k=10;       		// Correction factor of heading

int16_t M3_Value;           // speed of Right Motor
int16_t M2_Value;			// speed of Left Motor

int16_t M2_Valuef;			// final Speed of left motor
int16_t M3_Valuef;			// final Speed of right motor

int16_t Roll_value = 0;			// Roll value of plutoX
int16_t Th_Value = 0;			// Throttle value of plutoX

//The setup function is called once at Pluto's hardware startup
void plutoInit()
{
// Add your hardware initialization code here
}

//The function is called once before plutoPilot when you activate Developer Mode
void onPilotStart()
{
  // do your one time stuffs here
	Control.disableFlightStatus(true); //Disable the default LED behaviour
	desiredHeading = Flight.getAngle(AG_YAW);
}



// The loop function is called in an endless loop
void plutoPilot()
{

//Add your repeated code here

	if(!Control.isArmed())
	{

	if(ABS(Control.getRcData(RC_ROLL)-1500)<30)
	{ //If no RC Input is given Auto-Stabilizes the Pluto to original heading

		heading_error = desiredHeading - Flight.getAngle(AG_YAW);

		if(heading_error>180)
			 heading_error=heading_error-360;
		else if(heading_error<-180)
			 heading_error=heading_error+360;

		Roll_value=1500 +k*heading_error;

	 }
	 else{//otherwise set current heading as a target heading
	          Roll_value = Control.getRcData(RC_ROLL);  //Reads the Roll value from controller
	          desiredHeading = Flight.getAngle(AG_YAW); 		//Sets current heading to target heading
		 }

     Th_Value = Control.getRcData(RC_THROTTLE); //Reads the Throttle value from controller

	 //Weighted addition of throttle and roll value
	 M3_Value = (Th_Value-1500)-(Roll_value-1500)/3;
	 M3_Value = constrain(M3_Value, -500, 500);
	 M2_Value = (Th_Value-1500)+(Roll_value-1500)/3;
	 M2_Value = constrain(M2_Value, -500, 500);


     //Set the motor direction
	 if(M2_Value<0)
		 Motor.setDirection(M2, BACKWARD);
     else
	    Motor.setDirection(M2, FORWARD);

	 if(M3_Value<0)
		Motor.setDirection(M3, BACKWARD);
	 else
		 Motor.setDirection(M3, FORWARD);

	//Get the PWM value for each motor
	M2_Valuef = generatePWM(M2_Value);
	M3_Valuef = generatePWM(M3_Value);

	//Set the Motor speed
	Motor.set(M3,M3_Valuef);
	Motor.set(M2,M2_Valuef);
	Print.monitor("M2:", M2_Valuef);
	Print.monitor("M3:", M3_Valuef );

	}
	else
	{
		// fly mode
		Motor.set(M2, 1000);
		Motor.set(M3, 1000);
	}


}



//The function is called once after plutoPilot when you deactivate Developer Mode
void onPilotFinish()
{

// do your cleanup stuffs here
	 Control.disableFlightStatus(false); //Enable the default LED behaviour
	 Motor.set(M2, 1000);
	 Motor.set(M3, 1000);
}




