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

const unsigned int BUZZ_PIN=4;

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

  pinMode(BUZZ_PIN, OUTPUT);

  Serial.begin(BAUD_RATE);

  
  Serial.setTimeout(200); //default = 1000ms
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



//Serial.println(c);
unsigned char i, j ;
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
int amount = 0;

 if(left_distance < 20 || right_distance<20 || front_distance<20 || rear_distance<20 ){
     Car.Brake(); 
     car_speed=50;
     amount=50;
        for (i = 0; i <80; i++) // When a frequency sound
      {
        digitalWrite (BUZZ_PIN, HIGH) ; //send tone
        delay (1) ;
        digitalWrite (BUZZ_PIN, LOW) ; //no tone
        delay (1) ;
      }
   }else if(left_distance < 30 || right_distance<30 || front_distance<30 || rear_distance<30 ){
     car_speed=100;
     amount = 100;
     for (i = 0; i <80; i++) // When a frequency sound
      {
        digitalWrite (BUZZ_PIN, HIGH) ; //send tone
        delay (2) ;
        digitalWrite (BUZZ_PIN, LOW) ; //no tone
        delay (2) ;
      }
    
   }else if(left_distance < 50 || right_distance<50 || front_distance<50 || rear_distance<50 ){
    car_speed=250;
     amount = 200;
     for (i = 0; i <80; i++) // When a frequency sound
      {
        digitalWrite (BUZZ_PIN, HIGH) ; //send tone
        delay (3) ;
        digitalWrite (BUZZ_PIN, LOW) ; //no tone
        delay (3) ;
      }
    
   }




  
  String input = "";



   Serial.println(direction);

  if (Serial.available() > 0){
    //int input = Serial.read() -'0';
    //input = Serial.readStringUntil(';');
    input = Serial.readString();
    input.trim(); //remove white space

  
    direction = input.charAt(0);



    if(input.equals("Fb")){
        if(front_distance > 10)
          Car.Backward(200);
          direction='b';
    }
    
    if(input.equals("Bb")){
        if(rear_distance > 10)
          Car.Forward(200);
          direction='b';

    }
    
    if(input.equals("Rb")){
        if(left_distance > 10)
           Car.Left(200); 
          direction='b';

    }
    
    if(input.equals("Lb")){
        if(right_distance > 10)
          Car.Right(200);
          direction='b';

    }
    
  }
  

    //Serial.println(direction);
    switch(direction){
      case 'F':
      if(front_distance > 10)
        Car.Backward();
        break;
      case 'B':
       if(rear_distance > 10)
        Car.Forward();
        break;
      case 'L':
       if(right_distance > 10)
          Car.Left();        
        break;
      case 'R':
       if(left_distance > 10)
          Car.Right();
        break;
      default:
          Car.Brake(); 
        break;
    }
  //  direction = 'b';


 
}
