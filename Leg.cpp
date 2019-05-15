#include "Arduino.h"
#include "Leg.h"

  Leg::Leg(int PUL_rot, int DIR_rot, int ENA_rot, int PUL_lead, int DIR_lead, int ENA_lead, int endSwitch,int microsec_screw, int microsec_axle ){//int chipSelect
    this->PUL_rot = PUL_rot;
    this->DIR_rot = DIR_rot;
    this->ENA_rot = ENA_rot;
    this->PUL_lead = PUL_lead;
    this->DIR_lead = DIR_lead;
    this->ENA_lead = ENA_lead;
    //this->chipSelect = chipSelect;
    this->endSwitch = endSwitch;
    this->microsec_screw = microsec_screw;
    this->microsec_axle = microsec_axle;

    //Sensor acc=Sensor(chipSelect);
  
   
  }
  void Leg::pushOut(){ //pushes out foot one microsec 
    
        digitalWrite(DIR_lead,LOW);
        
        delayMicroseconds(microsec_screw); // Konstigt med att den ligger innan, testa med efter.
        digitalWrite(PUL_lead,HIGH);
        digitalWrite(PUL_lead,LOW);
  }

  void Leg::pushIn(){ //pushes in foot one microsec 
    
        digitalWrite(DIR_lead,HIGH);

        delayMicroseconds(microsec_screw);
        digitalWrite(PUL_lead,HIGH);
        digitalWrite(PUL_lead,LOW);
        
  }

  void Leg::resetLegLocation(){
    while(digitalRead(endSwitch)!=0){
        digitalWrite(DIR_lead,HIGH);
        delayMicroseconds(microsec_screw);
        digitalWrite(PUL_lead,HIGH);
        digitalWrite(PUL_lead,LOW);
    }
        
  }

  void Leg::rotateForward(){ //Rotates leg clockwise one microsec 
        digitalWrite(DIR_rot,LOW);
        
        delayMicroseconds(microsec_axle);
        digitalWrite(PUL_rot, HIGH);
        delayMicroseconds(microsec_axle);
        digitalWrite(PUL_rot, LOW);
   
        
  }

  void Leg::rotateBackward(){ //Rotates leg counterclockwise one microsec
        digitalWrite(DIR_rot,HIGH);

        delayMicroseconds(microsec_axle); 
        digitalWrite(PUL_rot,HIGH); 
        delayMicroseconds(microsec_axle);
        digitalWrite(PUL_rot,LOW);
        
  }


void Leg::rotateForwardHighSpeed(){ //Rotates leg clockwise one microsec 
        digitalWrite(DIR_rot,LOW);
        
        delayMicroseconds(1400);
        digitalWrite(PUL_rot, HIGH);
        delayMicroseconds(1400);
        digitalWrite(PUL_rot, LOW);
   
        
  }

  void Leg::rotateBackwardHighSpeed(){ //Rotates leg counterclockwise one microsec
        digitalWrite(DIR_rot,HIGH);

        delayMicroseconds(1400); 
        digitalWrite(PUL_rot,HIGH); 
        delayMicroseconds(1400);
        digitalWrite(PUL_rot,LOW);
        
  }



 
