#include <Arduino.h>
//#include <SPI.h>
#include<Wire.h>
#include "Sensor.h"

//https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf 

Sensor::Sensor(int selectchip){

   this->selectchip = selectchip;
   
}

// Sensor constants
 double alpha = 0.5; 
 int accAngle = 0;
 double sumA=0;

//Acceleration
double Sensor::readDataI2C(){// read acceleometer sensordata from i2c adress 0x69 mpu6050 

  Wire.beginTransmission(0x69);
  Wire.write(0x3B);  //Börjar läsa på accelerometer adressen se register map document.
  Wire.endTransmission(false);
  Wire.requestFrom(0x69,6,true); //sensor address, how many bytes (uses 2 per reading), something
  AcX=Wire.read()<<8|Wire.read(); //Läs bit 7-15 byt register och läs bit 0-7
  AcY=Wire.read()<<8|Wire.read();  
  AcZ=Wire.read()<<8|Wire.read(); // can be removed and Wire.requestFrom(0x69,6,true); can be replaced with Wire.requestFrom(0x69,4,true); to make more efficient

  Wire.endTransmission();

  ay=AcY/16384.0;// kan dela alla med 16384 för att det ska vara typ 1 g used now to make it a float 
  ax=AcX/16384.0; 
  az=AcZ/16384.0;// can be removed
  double degree=atan(ay/ax)*180/PI;
  
  return degree;
}




double Sensor::getAngle(){

  digitalWrite(selectchip, HIGH); //flyttar från 68 till 69 när vi vill läsa
  double newDegree;

  newDegree=readDataI2C(); //reads angle
  delay(10);//can probably be lowered

  if (accAngle == 0){
    accAngle = newDegree;
    }

    accAngle = newDegree * alpha + (1-alpha)*accAngle; //Exponential smoothing 
  
    digitalWrite(selectchip, LOW);

    return accAngle ;
        
}//getangle      

bool Sensor::impact(){

  sumA=sqrt(ax*ax+ay*ay+az*az);
  if(sumA>3){//helt godtyckligt satt 
    impacted=true;
  }
  
  return impacted;
}

bool Sensor::resetImpact(){
  impacted=false;
  return impacted;
}
  
