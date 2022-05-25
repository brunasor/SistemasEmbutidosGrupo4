#include "AlphaBot.h"

#define DEBUG 0

//Pinos
int ECHO_F = 18;
int TRIG_F = 19;
/*
int ECHO_B = 0;
int TRIG_B = 0;
int ECHO_L = 0;
int TRIG_L = 0;
int ECHO_R = 0;
int TRIG_R = 0;
*/

float distance_forward = 0;
float distance_backwards = 0;
float distance_left = 0;
float distance_right = 0;

char direction = 'b';
int car_speed = 100;

AlphaBot Car = AlphaBot();

void ultrasonic_config(){
  pinMode(ECHO_F, INPUT);                   // Define the ultrasonic echo input pin
  pinMode(TRIG_F, OUTPUT);                  // Define the ultrasonic trigger input pin
  /*
  pinMode(ECHO_B, INPUT);
  pinMode(TRIG_B, OUTPUT);
  pinMode(ECHO_L, INPUT);
  pinMode(TRIG_L, OUTPUT);
  pinMode(ECHO_R, INPUT);
  pinMode(TRIG_R, OUTPUT);*/
}

void distance_test_forward(){               // Measure the distance
  digitalWrite(TRIG_F, LOW);                // set trig pin low 2μs
  delayMicroseconds(2);
  digitalWrite(TRIG_F, HIGH);               // set trig pin 10μs , at last 10us 
  delayMicroseconds(10);
  digitalWrite(TRIG_F, LOW);                // set trig pin low
  float Fdistance = pulseIn(ECHO_F, HIGH);  // Read echo pin high level time(us)
  
  Fdistance = Fdistance / 58;                
  //Y m =（X s * 344）/ 2; 
  //X s =（ 2 * Y m）/ 344;
  //X s = 0.0058 * Y m;
  //cm = us /58

  if(DEBUG){
    Serial.print("Distance_Forward=");            //output distance (Unit: cm)
    Serial.print(Fdistance);
    Serial.println("cm");
  }
  distance_forward = Fdistance;
}
/*
void distance_test_backwards(){
  digitalWrite(TRIG_B, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_B, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_B, LOW);
  float Fdistance = pulseIn(ECHO_B, HIGH);
  
  Fdistance = Fdistance / 58;  

  distance_backwards = Fdistance;
}  
void distance_test_left(){
  digitalWrite(TRIG_L, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_L, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_L, LOW);
  float Fdistance = pulseIn(ECHO_L, HIGH);
  
  Fdistance = Fdistance / 58;  

  distance_left = Fdistance;
}
void distance_test_right(){
  digitalWrite(TRIG_R, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_R, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_R, LOW);
  float Fdistance = pulseIn(ECHO_R, HIGH);
  
  Fdistance = Fdistance / 58;  

  distance_right = Fdistance;
}  
*/



void setup() {
  ultrasonic_config();
  Serial.begin(9600);
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
  if(DEBUG)
    Serial.println("_START_");
  
  String input = "";



  distance_test_forward();
  //distance_test_backwards();
  //distance_test_left();
  //distance_test_right();





  if (Serial.available() > 0){
    //int input = Serial.read() -'0';
    //input = Serial.readStringUntil(';');
    input = Serial.readString();
    input.trim(); //remove white space

    if(input.equals("F") || input.equals("B") || input.equals("L") || input.equals("R")){
      direction = input.charAt(0);
    }
    
    if(DEBUG){
      Serial.println("INPUT=" + input);
    }    
  }


  if(input.equals("s")){
    Serial.println("STOPPING");
    exit(0);
  }

  if(input.equals("b")){
    Car.Brake();
    direction = 'b';
  }else if(input.equals("u") && car_speed < 255){
    car_speed += 5;
    Car.SetSpeed(car_speed);
  }else if(input.equals("d") && car_speed > 5){
    car_speed -= 5;
    Car.SetSpeed(car_speed);
  }else{
    switch(direction){
      case 'F':
        if(distance_forward > 5)  // Unit: cm  (variar com velocidade?)
          Car.Forward(100);
        break;
      case 'B':
        //if(distance_backwards > 5)  // Unit: cm  (variar com velocidade?)
          Car.Backward(100);
        break;
      case 'L':
        //if(distance_left > 5)
          Car.Left(100);
        break;
      case 'R':
        //if(distance_right > 5)
          Car.Right(100);
        break;
      default:
        break;
    }
  }

  if(DEBUG)
    Serial.println("_END_");
  
  //delay(1000);
}
