#include "AlphaBot.h"

#define DEBUG 1
const unsigned int TRIG_PIN_REAR=13;
const unsigned int ECHO_PIN_REAR=12;

const unsigned int TRIG_PIN_FRONT=11;
const unsigned int ECHO_PIN_FRONT=10;

const unsigned int TRIG_PIN_LEFT=9;
const unsigned int ECHO_PIN_LEFT=8;


const unsigned int TRIG_PIN_RIGHT=3;
const unsigned int ECHO_PIN_RIGHT=2;





const unsigned int BAUD_RATE=9600;
float distance_forward = 0;
float distance_backwards = 0;
float distance_left = 0;
float distance_right = 0;
char direction = 'b';
char action = 'b';
int car_speed = 250;

AlphaBot Car = AlphaBot();




void setup() {
  

  
  pinMode(TRIG_PIN_REAR, OUTPUT);
  pinMode(ECHO_PIN_REAR, INPUT);

  
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);


    
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);

    
  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);

  
  Serial.begin(BAUD_RATE);

  
  Serial.setTimeout(100); //default = 1000ms
  Car.SetSpeed(car_speed);  //Speed: 0-255 ?
  
}



/**
 * Inputs possíveis:
 * s = stop program (exit 0)
 * b = break (stop moving)
 * F = Forward
 * B = Backwards
 * L = Left
 * R = Right
 * u = more speed (5 intervals, min:5 max:255)
 * d = less speed (5 intervals, min:5 max:255)
 * 
 */
void loop() {

  unsigned long duration= 0;
/**-------------------**/
  digitalWrite(TRIG_PIN_REAR, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_REAR, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_REAR, LOW);
  

 duration = pulseIn(ECHO_PIN_REAR, HIGH);
 int rear_distance= duration/29/2;

 if(DEBUG)
   if(duration==0){
    //Serial.println("Warning: no pulse from sensor REAR");
     }else{
       // Serial.println(rear_distance);
    
    }

/**-------------------**/
  duration = 0 ;
  digitalWrite(TRIG_PIN_FRONT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_FRONT, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_FRONT, LOW);
  

 duration= pulseIn(ECHO_PIN_FRONT, HIGH);
 int front_distance= duration * 0.034 / 2;

 if(DEBUG)
   if(duration==0){
     Serial.println("Warning: no pulse from sensor FRONT");
     }else{
    //  Serial.println(front_distance);

    }

/**-------------------**/

 /**-------------------**/

  digitalWrite(TRIG_PIN_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  

 duration= pulseIn(ECHO_PIN_RIGHT, HIGH);
 int right_distance=  duration * 0.034 / 2;

 if(DEBUG)
   if(duration==0){
     Serial.println("Warning: no pulse from sensor RIGHT");
     }else{
       //Serial.println(right_distance);
    }

/**-------------------**/



 /**-------------------**/

  digitalWrite(TRIG_PIN_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, LOW);
  

 duration= pulseIn(ECHO_PIN_LEFT, HIGH);
 int left_distance= duration/29/2;

 if(DEBUG)
   if(duration==0){
     Serial.println("Warning: no pulse from sensor LEFT");
     }else{
        //Serial.println(left_distance);
    }


/**-------------------**/



  
  String input = "";





  if (Serial.available() > 0){
    //int input = Serial.read() -'0';
    //input = Serial.readStringUntil(';');
    input = Serial.readString();
    input.trim(); //remove white space

    //if(input.equals("F") || input.equals("B") || input.equals("L") || input.equals("R") || input.equals("b") ){
      direction = input.charAt(0);
    //}
    
    
  }
   if(left_distance < 30 || right_distance<30 || front_distance<30 || rear_distance<30 ){
     Car.Brake(); 
   }

    //Serial.println(direction);
    switch(direction){
      case 'F':
      if(front_distance > 30)
        Car.Backward();
        break;
      case 'B':
       if(rear_distance > 30)
        Car.Forward();
        break;
      case 'L':
       if(right_distance > 30)
          Car.Left();        
        break;
      case 'R':
       if(left_distance > 30)
          Car.Right();
        break;
      default:
             Car.Brake(); 
        break;
    }
  //  direction = 'b';


 
}
