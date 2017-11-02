//====================--- I N N E R B R E E D F X ---====================//
// Project; Animatronic Macaw (Base Code)                                 //
// Description: http://www.innerbreed.co.uk                              //
// Version: V2.0                                                         //
// Start Date: 16/08/17                                                  //
// Last Edit Date: 01/11/17                                              //
// Developer/s: Jonny Poole (aka Innerbreed)                             // 
//                                                                       //
// FEATURES:                                                             //
// Smoothed servo movements with variable Bézier Curve Trajectory        //
//  low pass FILTER to apply jointed compliance.                         //
//=======================================================================//

//----------------
// LIBRARY (Include)
// Metro, by Thomas Ouellet Fredericks,
#include <Metro.h>   // http://www.arduino.cc/playground/Code/Metro 
#include <Servo.h>

//----------------
// SERVO NAMES (Defined)
Servo Beak;              // Open close the beak
Servo Beak_Shift;        // Move beak forward and back
Servo Head_Turn;         // Turn head left and right
Servo Head_Rotate;       // Tilt head side to side
Servo Neck_XShift;       // Lift neck up and down
Servo Body_ZShift;       // Tilt body side to side
Servo Body_XShift;       // Lift body up and down
Servo Step;              // Move legs (Walking)
Servo Gantry;            // Move body (Walking)

//----------------
// INITIAL SERVO POSITION (Center)
int Start_Pos = 1500;

//----------------
// SERVO RANGE (pwm)
int min = 1000;
int max = 2000;
int Random_value = random(min, max); 
long time;

//----------------
// GANTRY SERVO END POINTS (Set as required)
int Middel = 1550;
int Right  = 1240;
int Left   = 1760;

//----------------
// STEPPING COMMAND (Hoekens Linkage)
int Step_Left  = 1800;
int Step_Right = 1200;

//----------------  
// SOLENOID NAMES (Eyes)
int blink = A3;

//---------------- 
// FILTER (Smooth servo movements)
int Servo_Value;                          // Servo_Value
int Servo_Value_Smooth;                   // Servo_Value to be smoothed
int FilterVal = random(0.01, 1.0);        // Random Value Range from (0.01 = Full Filter ~ 1.0 = No Filter)
float Apply_Filter = FilterVal;           // 0.01 ~ 1.0 (Low pass Filter) (1 = no filter)
int Bezier_curve = 3500;                  // Duration of the interval in miliseconds (can be set to random)
Metro intervaller = Metro (Bezier_curve); // Metro uses the built-in timer (either fixed or tempo-relative)

//==========================================
// CODE EXECUTION
//------------------------------------------
// SETUP (Run once)
void setup() {
   time = random(1000, 10000);        // Time Range from 1-10 sec
   pinMode(blink, OUTPUT);

 { 
// Attached servos
     //Beak.attach(4); 
     //Beak_Shift.attach(5); 
     //Head_Turn.attach(6); 
     //Head_Rotate.attach(7); 
     //Neck_XShift.attach(10; 
     //Body_ZShift.attach(11; 
     //Body_XShift.attach(12; 
     Step.attach(8); 
     Gantry.attach(9); 
     
// Center all servos upon power up
     Beak,Beak_Shift,Head_Turn,Head_Rotate,Neck_XShift,Body_ZShift,Body_XShift.write(Start_Pos); 
     Step,Gantry.write(Middel);
                                   
  delay(150);                
 
  }
}
//------------------------------------------
// LOOP (Run forever)
void loop() {
  digitalWrite(blink, LOW);  // Close eye
  delay(500);               // 0.5 sec delay
  digitalWrite(blink, HIGH); // Open eye

    //Call up loop routines
     Macaw();                // Macaw routine 
     Walking();              // Walking routine

  delay(15);                 // Wait for random time before loop

} //End Loop

//---------------- Sequence ----------------
// MACAW routine                              
// Servo movements eased with low pass filter 
void Macaw() {                                
  if (intervaller.check() == 1) {                      // Check built-in timer is returned to start
     Servo_Value = (Random_value);                     // Calculate a new random position between 1000 and 2000 values
     intervaller.interval(random(min, max));           // Resets interval with a new random Bézier Curve Trajectory  
} // Smooth the Trajectory Value              
     Servo_Value_Smooth = Servo_Value_Smooth * (1.0-Apply_Filter) + Servo_Value * Apply_Filter; 
     
     Head_Rotate.write(Servo_Value_Smooth);            // Assign new position to the servo with filter applied
  delay(1000);                                         // Delay to make the servo move
     Neck_XShift.write(Servo_Value_Smooth);
  delay(250);
     Body_XShift.write(Servo_Value_Smooth);
  
} // End Loop

//---------------- Sequence ----------------
// WALKING routine
// Servo movements eased by design (SW5513-4MA Sailwinch Servo)
void Walking() {
     
     Step.write(Step_Right);                                
     Gantry.write(Right);                      
  delay(10000);                                    
     
     Step.write(Step_Left);
     Gantry.write(Left);                        
  delay(10000);
    
     Step.write(Step_Right);
     Gantry.write(Right);                      
  delay(10000);                              
     
     Step.write(Step_Left); 
     Gantry.write(Left);                   
} // End Loop
 
