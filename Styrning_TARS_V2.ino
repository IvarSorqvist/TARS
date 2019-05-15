  //Include libraries
  #include<Servo.h>
  #include<Wire.h>
  #include <avr/wdt.h> // Watchdog for avoiding hangups

  
// Include classes
  #include "Leg.h" // Leg
  #include "Sensor.h" //Sensor

  

// Define pins
  // Motor leg 1
  #define PUL_L1 9  // purple
  #define DIR_L1 10 // brown
  #define ENA_L1 11 // blue

   // Motor leg 3
  #define PUL_L3 8 // purple
  #define DIR_L3 7 // brown
  #define ENA_L3 6 // blue

   // Motor leg 4
  #define PUL_L4 3 // purple 
  #define DIR_L4 4 // brown
  #define ENA_L4 5 // blue
  

  // Motor lead screw leg 1
  #define PUL_LS1 45  // purple
  #define DIR_LS1 46  // brown
  #define ENA_LS1 47  // blue
  

  // Motor lead screw leg 2
  #define PUL_LS2 42 // purple
  #define DIR_LS2 43 // brown
  #define ENA_LS2 44 // blue

  // Motor lead screw leg 3
  #define PUL_LS3 39 // purple
  #define DIR_LS3 40 // brown
  #define ENA_LS3 41 // blue

  // Motor lead screw leg 4
  #define PUL_LS4 36 // purple
  #define DIR_LS4 37 // brown
  #define ENA_LS4 38 // blue


  // Accelerometer adresschange, low=0x68 high=0x69
  #define AD0_1 24  
  #define AD0_2 25  
  #define AD0_3 26
  #define AD0_4 27

  // Endswitch pins, high=endswitch reached, low=no contact
  #define END_SWITCH_1 30
  #define END_SWITCH_2 31
  #define END_SWITCH_3 32
  #define END_SWITCH_4 33
  
  //Gyro clock
  #define SCK 51 // Set clock gyro leg 2 and 3


  //Servo 
  #define SERVO 12
 
 
// This value is predefined from at the motors drivers
  int microsec_screw  = 1250; //testat oss fram till dessa värden, lät bäst
  int microsec_axle = 1500;//315 //Denna får testas fram old = 700
  
 
  // Messages
  String setupready = "Setup done";

//Bluetooth constants
  int BT_in;
  int BT_walk;
  int BT_steps;


 //Creating for instances of Sensor class, used with sens1.getAngle();
  Sensor sens1=Sensor(AD0_1);
  Sensor sens2=Sensor(AD0_2);
  Sensor sens3=Sensor(AD0_3);
  Sensor sens4=Sensor(AD0_4);
  

// Creating four leg objects with initiating varibles
//skapar 4 ben som ställer in dessa pinnar för resp. ben
/*
  Leg leg1 = Leg(PUL_L1,DIR_L1,ENA_L1, PUL_LS1, DIR_LS1, ENA_LS1, AD0_1, microsec_screw, microsec_axle); 
  Leg leg2 = Leg(PUL_L1,DIR_L1,ENA_L1, PUL_LS2, DIR_LS2, ENA_LS2, AD0_2, microsec_screw, microsec_axle);
  Leg leg3 = Leg(PUL_L3,DIR_L3,ENA_L3, PUL_LS3, DIR_LS3, ENA_LS3, AD0_3, microsec_screw, microsec_axle);
  Leg leg4 = Leg(PUL_L4,DIR_L4,ENA_L4, PUL_LS4, DIR_LS4, ENA_LS4, AD0_4, microsec_screw, microsec_axle);
*/

  Leg leg1 = Leg(PUL_L1,DIR_L1,ENA_L1, PUL_LS1, DIR_LS1, ENA_LS1, END_SWITCH_1, microsec_screw, microsec_axle); 
  Leg leg2 = Leg(PUL_L1,DIR_L1,ENA_L1, PUL_LS2, DIR_LS2, ENA_LS2, END_SWITCH_2, microsec_screw, microsec_axle);
  Leg leg3 = Leg(PUL_L3,DIR_L3,ENA_L3, PUL_LS3, DIR_LS3, ENA_LS3, END_SWITCH_3, microsec_screw, microsec_axle);
  Leg leg4 = Leg(PUL_L4,DIR_L4,ENA_L4, PUL_LS4, DIR_LS4, ENA_LS4, END_SWITCH_4, microsec_screw, microsec_axle);



 Leg legs1[] = {leg1};
 Leg legs2[] = {leg2};
 Leg legs3[] = {leg3};
 Leg legs4[] = {leg4};
 
 Leg legs12[] = {leg1,leg2};
 Leg legs13[] = {leg1,leg3};
 Leg legs14[] = {leg1,leg4};
 
 Leg legs23[] = {leg2,leg3};
 Leg legs24[] = {leg2,leg4};

 Leg legs34[] = {leg3,leg4};
 
 
 Leg legs1234[] = {leg1,leg2,leg3,leg4};
 Servo myServo;


void setup() {
  
  
  /*
  digitalWrite(DIR_L1,LOW);
  digitalWrite(ENA_L1,HIGH);

  digitalWrite(DIR_L3,LOW);
  digitalWrite(ENA_L3,HIGH);

  digitalWrite(DIR_L4,LOW);
  digitalWrite(ENA_L4,HIGH);
*/
  // setup motors lead screw
  // Foot 1
  pinMode (PUL_LS1, OUTPUT);
  pinMode (DIR_LS1, OUTPUT);
  pinMode (ENA_LS1, OUTPUT);

  //Foot 2 
  pinMode (PUL_LS2, OUTPUT);
  pinMode (DIR_LS2, OUTPUT);
  pinMode (ENA_LS2, OUTPUT);

  // Foot 3
  pinMode (PUL_LS3, OUTPUT);
  pinMode (DIR_LS3, OUTPUT);
  pinMode (ENA_LS3, OUTPUT);

  //Foot 4
  pinMode (PUL_LS4, OUTPUT);
  pinMode (DIR_LS4, OUTPUT);
  pinMode (ENA_LS4, OUTPUT);
  

  // Setup motors legs
  // Leg 1 
  pinMode (PUL_L1, OUTPUT);
  pinMode (DIR_L1, OUTPUT);
  pinMode (ENA_L1, OUTPUT);

  // Leg 3
  pinMode (PUL_L3, OUTPUT);
  pinMode (DIR_L3, OUTPUT);
  pinMode (ENA_L3, OUTPUT);

  // Leg 4
  pinMode (PUL_L4, OUTPUT);
  pinMode (DIR_L4, OUTPUT);
  pinMode (ENA_L4, OUTPUT);

  pinMode(AD0_1,OUTPUT);
  pinMode(AD0_2,OUTPUT);
  pinMode(AD0_3,OUTPUT);
  pinMode(AD0_4,OUTPUT);

  pinMode(END_SWITCH_1,INPUT_PULLUP);//removes the problem with the value floating, rewired the switch to ground, 1 open, 0 closed switch
  pinMode(END_SWITCH_2,INPUT_PULLUP);
  pinMode(END_SWITCH_3,INPUT_PULLUP);
  pinMode(END_SWITCH_4,INPUT_PULLUP);

 // pinMode(SERVO, OUTPUT);
 myServo.attach(SERVO);
  myServo.write(90);


  
  // Turn on the motors
  
  digitalWrite(ENA_LS1,HIGH);
  digitalWrite(ENA_L1,HIGH);

  digitalWrite(ENA_LS2,HIGH);

  digitalWrite(ENA_LS3,HIGH);
  digitalWrite(ENA_L3,HIGH);

  digitalWrite(ENA_LS4,HIGH);
  digitalWrite(ENA_L4,HIGH);




  // setup communication
  Serial1.begin(9600); // setup communication with USB with 9600 ???
  Serial.begin(9600); // setup communication with Buetooth with 9600 ???
  
  Serial1.println(setupready);

  Serial.println(setupready);
 


  //Setup gyro
  /* .  Oändlig loop?? kommer aldrig in till main med denna funktionen
  Wire.begin();//start sequence for i2c mpu6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  
  Wire.beginTransmission(0x69);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
*/

}
