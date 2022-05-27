#include "AlphaBot.h"
#include "pitches.h"


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
int r = 0;
AlphaBot Car = AlphaBot();


void imperialmarch(){
  
    
    // change this to make the song slower or faster
  int tempo = 120;
  
  // change this to whichever pin you want to use
  int buzzer = 11;
  
  // notes of the moledy followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {
  
  // Dart Vader theme (Imperial March) - Star wars 
  // Score available at https://musescore.com/user/202909/scores/1141521
  // The tenor saxophone part was used
  
  NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
  NOTE_A4,-4, NOTE_A4,-4, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_A4,16, NOTE_F4,8, REST,8,
  NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,

  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,//4
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,

  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16, //7 
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,

  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,//9
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZ_PIN, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(BUZZ_PIN);
 
}
}




    
    
void pulodagaita(){
    
    // change this to make the song slower or faster
    int tempo = 100;
    
    
    // notes of the moledy followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    int melody[] = {
      
      // Pulo da gaita - Auto da Compadecida 
      // Score available at https://musescore.com/user/196039/scores/250206
      
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,2,
      
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,8,
      NOTE_C4,2,
    
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,2,
    
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,8,
      NOTE_C4,16, NOTE_D5,8, NOTE_D5,16, NOTE_D5,16, NOTE_D5,8, NOTE_D5,16,
    
      NOTE_D5,16, NOTE_D5,8, NOTE_D5,16, NOTE_C5,8, NOTE_E5,-8,
      NOTE_C5,8, NOTE_C5,16, NOTE_E5,16, NOTE_E5,8, NOTE_C5,16,
      NOTE_F5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,-8,
      NOTE_C5,8, NOTE_D5,16, NOTE_E5,16, NOTE_D5,8, NOTE_C5,16,
    
      NOTE_F5,8, NOTE_F5,8, NOTE_A5,8, NOTE_G5,-8,//21
      NOTE_G5,8, NOTE_C5,16, NOTE_C5,16, NOTE_C5,8, NOTE_C5,16,
      NOTE_F5,-8, NOTE_E5,16, NOTE_D5,8, NOTE_C5,4,
      NOTE_C5,16, NOTE_C5,16, NOTE_C5,16, NOTE_C5,16,
    
      NOTE_F5,8, NOTE_F5,16, NOTE_A5,8, NOTE_G5,-8,//25
      NOTE_G5,8, NOTE_C5,16, NOTE_C5,16, NOTE_C5,8, NOTE_C5,16,
      NOTE_F5,16, NOTE_E5,8, NOTE_D5,16, NOTE_C5,8, NOTE_E5,-8,
      NOTE_C5,8, NOTE_D5,16, NOTE_E5,16, NOTE_D5,8, NOTE_C5,16,
     
      NOTE_F5,8, NOTE_F5,16, NOTE_A5,8, NOTE_G5,-8,//29
      NOTE_G5,8, NOTE_C5,16, NOTE_C5,16, NOTE_C5,8, NOTE_C5,16,
      NOTE_F5,8, NOTE_E5,16, NOTE_D5,8, NOTE_C5,8,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
    
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,2,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
    
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,-2,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
    
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
      NOTE_G4,2,
      NOTE_C5,4, NOTE_G4,8, NOTE_AS4,4, NOTE_A4,8,
    
      NOTE_G4,16, NOTE_C4,8, NOTE_C4,16, NOTE_G4,16, NOTE_G4,8, NOTE_G4,16,
      NOTE_F4,8, NOTE_E4,8, NOTE_D4,8, NOTE_C4,-2,
      NOTE_C4,16, NOTE_C4,8, NOTE_C4,16, NOTE_E4,16, NOTE_E4,8, NOTE_E4,16,
      NOTE_F4,16, NOTE_F4,8, NOTE_F4,16, NOTE_FS4,16, NOTE_FS4,8, NOTE_FS4,16,
    
      NOTE_G4,8, REST,8, NOTE_AS4,8, NOTE_C5,1,
      
      
    
    };
    
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    
    // this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;
    
    int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZ_PIN, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(BUZZ_PIN);
 
}
}

void zeldatheme(){






int tempo=88; 

// change this to whichever pin you want to use

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=169
  
  NOTE_AS4,-2,  NOTE_F4,8,  NOTE_F4,8,  NOTE_AS4,8,//1
  NOTE_GS4,16,  NOTE_FS4,16,  NOTE_GS4,-2,
  NOTE_AS4,-2,  NOTE_FS4,8,  NOTE_FS4,8,  NOTE_AS4,8,
  NOTE_A4,16,  NOTE_G4,16,  NOTE_A4,-2,
  REST,1, 

  NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//7
  NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
  NOTE_AS5,-2,  NOTE_AS5,8,  NOTE_AS5,8,  NOTE_GS5,8,  NOTE_FS5,16,
  NOTE_GS5,-8,  NOTE_FS5,16,  NOTE_F5,2,  NOTE_F5,4, 

  NOTE_DS5,-8, NOTE_F5,16, NOTE_FS5,2, NOTE_F5,8, NOTE_DS5,8, //11
  NOTE_CS5,-8, NOTE_DS5,16, NOTE_F5,2, NOTE_DS5,8, NOTE_CS5,8,
  NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
  NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8,

  NOTE_AS4,4,  NOTE_F4,-4,  NOTE_AS4,8,  NOTE_AS4,16,  NOTE_C5,16, NOTE_D5,16, NOTE_DS5,16,//15
  NOTE_F5,2,  NOTE_F5,8,  NOTE_F5,8,  NOTE_F5,8,  NOTE_FS5,16, NOTE_GS5,16,
  NOTE_AS5,-2, NOTE_CS6,4,
  NOTE_C6,4, NOTE_A5,2, NOTE_F5,4,
  NOTE_FS5,-2, NOTE_AS5,4,
  NOTE_A5,4, NOTE_F5,2, NOTE_F5,4,

  NOTE_FS5,-2, NOTE_AS5,4,
  NOTE_A5,4, NOTE_F5,2, NOTE_D5,4,
  NOTE_DS5,-2, NOTE_FS5,4,
  NOTE_F5,4, NOTE_CS5,2, NOTE_AS4,4,
  NOTE_C5,-8, NOTE_D5,16, NOTE_E5,2, NOTE_G5,8, 
  NOTE_F5,16, NOTE_F4,16, NOTE_F4,16, NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,16,NOTE_F4,8, NOTE_F4,16,NOTE_F4,8
  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes=sizeof(melody)/sizeof(melody[0])/2; 

// this calculates the duration of a whole note in ms (60s/tempo)*4 beats
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;


  // iterate over the notes of the melody. 
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(BUZZ_PIN, melody[thisNote], noteDuration*0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
    
    // stop the waveform generation before the next note.
    noTone(BUZZ_PIN);
  }
  
}


  

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
    
   }




  
  String input = "";



   Serial.println(direction);

  if (Serial.available() > 0){
    //int input = Serial.read() -'0';
    //input = Serial.readStringUntil(';');
    input = Serial.readString();
    input.trim(); //remove white space

    direction = input.charAt(0);
    if(direction=='A'){
      direction='b';
      if(r==0){
          imperialmarch(); 
      }else if(r==1){
          zeldatheme();
          r=0;
      }
        
    }
    
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
      Serial.println("aqui");
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
