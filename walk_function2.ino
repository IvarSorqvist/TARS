

 // Initiates constants
  int gearScrew = 1; 
  int gearAxle = 27;
  int angleAxle = 10; //reference angle
  int screwLength = 3;  //linear displacesment of leadscrew (mm) 
  int screwConstant = 24*screwLength; // constant to give accurate height
  int microstep = 1;


  int angleAxleOneDegree = 2; 

  int legsstart = 10; // 10 mm out to start linear actuator.

  boolean newData = false;

void loop() {
//communication();
//Serial.println("Inne i communication");
    //wdt_enable(WDTO_2S);
    recvBytesWithStartEndMarkers();
    //wdt_reset();
    if(newData == true){
    //showNewData();
    //wdt_enable(WDTO_1S);
    sortArray();
    //wdt_reset();


    String newCommand = chooseCommand();
    
    Serial.println(newCommand);
    newData = false;
    
    }
    
}


void MoveLeg(Leg ben[], String dir ,byte actuateLength){
 for(int i = 0; i < microstep*gearScrew*actuateLength; i++){
   for(int j = 0; j < (sizeof(ben) / sizeof(ben[0])); j++){
     if(dir == "out"){
       ben[j].pushOut();
     }
     else if(dir == "in"){
       ben[j].pushIn();
     }
   }
 }
}


// All functions is for rotating the legs anti-clockwise or legsforward
        

void rotateForward14(byte rotateAngle){
  for (int i=0; i < microstep*gearAxle*rotateAngle; i++){ //Rotate legs forward to reference angle
    leg1.rotateForward();
    leg4.rotateBackward();
  }
}

void rotateForward23(byte rotateAngle){
  for (int i=0; i < microstep*gearAxle*rotateAngle; i++){ //Rotate legs forward to reference angle
    leg1.rotateBackward();
    leg4.rotateForward();
  }
}

void rotateForward13(byte rotateAngle){
  for (int i=0; i < microstep*gearAxle*rotateAngle; i++){ //Rotate legs forward to reference angle
    leg1.rotateBackward();
    leg3.rotateForward();
    leg4.rotateBackward();
  }
}

void rotateForward24(byte rotateAngle){
  for (int i=0; i < microstep*gearAxle*rotateAngle; i++){ //Rotate legs forward to reference angle
    leg1.rotateBackward();
    leg3.rotateForward();
    leg4.rotateBackward();
  }
}


// Functions for rotating BACKWARD

void rotateBackward14(int rotateAngle){
  for (int i=0; i < microstep*gearAxle*rotateAngle; i++){ //Rotate legs forward to reference angle
              leg1.rotateBackward();
              leg4.rotateForward();
           }
}

       
void rotateForwardImpact(){
  while(!sens1.impact()&&!sens4.impact()){ //Rotate legs forward to reference angle
    leg1.rotateForward();
    leg4.rotateBackward();
  }
  sens1.resetImpact();
  sens4.resetImpact();
  
}


void initiateLegs(){
 
  int initHight=10;
 for(int i=0; i<(microstep*gearScrew*24*initHight); i++){
        leg1.pushOut();
        leg2.pushOut();
        leg3.pushOut(); 
        leg4.pushOut();
      }
  
  while(digitalRead(END_SWITCH_1) ||digitalRead(END_SWITCH_2) ||digitalRead(END_SWITCH_3) ||digitalRead(END_SWITCH_4 )){
    if(digitalRead(END_SWITCH_1)){
      leg1.pushIn();
    }
    if(digitalRead(END_SWITCH_2)){
      leg2.pushIn();
    }
    if(digitalRead(END_SWITCH_3)){
      leg3.pushIn();
    }
    if(digitalRead(END_SWITCH_4)){
      leg4.pushIn();
    }
  }
}


       





//--------------Walk 1 ----------------

void walk_1(byte steps){
    int hight=4;
    int hight2=18;
    int myangle=17;
   // servoLock();
    
  for(int j=0; j<steps;j++){
      Serial.println(j);
    for(int i=0; i<(microstep*gearScrew*hight*24); i++){
      leg1.pushOut();
         leg4.pushOut();
    }
    for(int i=0; i<(microstep*gearAxle*myangle); i++){
      leg1.rotateForward();
      leg4.rotateBackward();
    }
    delay(1700);
  
    for(int i=0; i<(microstep*gearScrew*hight2*24); i++){
      leg1.pushOut();
         leg4.pushOut();
    }
  int outCounter=0;
for(int i = 0; i < max(microstep*gearScrew*24*(hight+hight2), microstep*gearAxle*myangle); i++){
      if(i <= microstep*gearScrew*24*(hight+hight2) ){
       leg1.pushIn();
       leg4.pushIn();
      }
      if(i <=  microstep*gearAxle*(myangle)){
         leg1.rotateBackward();
         leg4.rotateForward();
      }

      if(i>microstep*gearScrew*24*(hight+hight2)/6.0&&i<=microstep*gearScrew*24*(hight+hight2)*4/5.0){
        outCounter++;
        leg2.pushOut();
        leg3.pushOut();

      }
    }
    delay(500);
       for(int i=0; i<outCounter;i++){
        leg2.pushIn();
        leg3.pushIn();
      
    }


    }
    //servoUnLock();
}



//walk_1

//---------------Walk 2 ---------------
void walk_2(byte steps){
    int hight=4;
    int hight2=18;
    int myangle=17;
    //servoLock();
    
      int outCounter14 = 0;//för att skjuta in lika mycket som trycktes ut
      int outCounter23 = 0; 
   
      for(int j=0; j<steps;j++){

        outCounter14 = 0;//för att skjuta in lika mycket som trycktes ut
        outCounter23 =0; 
        
          for(int i=0; i<(microstep*gearScrew*hight*24); i++){
            leg1.pushOut();
            leg4.pushOut();
            outCounter14++;
          }//14 ut
          
          for(int i=0; i<(microstep*gearAxle*myangle); i++){
            leg1.rotateForward();
            leg4.rotateBackward();
          }//vrid 12, 34
          delay(1700);//vänta på fall
    
          for(int i=0; i<(microstep*gearScrew*hight2*24); i++){
            leg1.pushOut();
            leg4.pushOut();
            outCounter14++;
          }//14 ut för att skifta tyngdpkt
          
          for(int i = 0; i < max(microstep*gearScrew*24*(hight+hight2), microstep*gearAxle*myangle); i++){
            if(i <= microstep*gearScrew*24*(hight+hight2)){
              leg1.pushIn();
              leg4.pushIn();
              outCounter14--;
            }
            if(i <=  microstep*gearAxle*myangle){
              leg1.rotateBackward();
              leg4.rotateForward();
            }
            if(i>microstep*gearScrew*24*(hight+hight2)/6.0&&i<=microstep*gearScrew*24*(hight+hight2)*3/5.0){
              outCounter23++;
              leg2.pushOut();
              leg3.pushOut();
            }
          } //vrid tillbaka, sänk 14,höj 23
          
          for(int i=0; i<(microstep*gearAxle*myangle); i++){
            leg1.rotateBackward();
            leg4.rotateForward();
          }
          
          delay(1700); //fortsätt att vrida
      
          for(int i=0; i<(microstep*gearScrew*hight2*24); i++){
            leg2.pushOut();
            leg3.pushOut();
            outCounter23++;
          } //23 ut för att skifta tybgdpkt
          
         for(int i = 0; i < max(microstep*gearScrew*24*(hight+hight2), microstep*gearAxle*myangle); i++){
            if(i <= microstep*gearScrew*24*(hight+hight2)){
              leg2.pushIn();
              leg3.pushIn();
              outCounter23--;
            }
            if(i <=  microstep*gearAxle*myangle+1){
              leg1.rotateForward();
              leg4.rotateBackward();
            }
            if(i > microstep*gearScrew*24*(hight+hight2)/6.0 && i <= microstep*gearScrew*24*(hight+hight2)*4/5.0){
              outCounter14++;
              leg1.pushOut(); 
              leg4.pushOut();
            }
          } //vrid tillbaka, sänk 23,höj 14

        delay(500);

        for(int i = 0 ; i< outCounter14 ; i++ ){
          leg1.pushIn();
          leg4.pushIn();
        }

        for(int i = 0 ; i< outCounter23 ; i++){
            leg2.pushIn();
            leg3.pushIn();
        }
        
        //leg1.resetLegLocation();
        //leg2.resetLegLocation();
        //leg3.resetLegLocation();
        //leg4.resetLegLocation();
        
    }
    //servoUnLock();
}
// --------------Walk 3 ---------------
void walk_3(int steps){
  //TODO fixxa Servot
  
  int hight=8;
  int hight2=14;
  int myangle=16;
    
  for(int j=0; j<steps;j++){
    Serial.println(j);
    for(int i=0; i<(microstep*gearScrew*hight*24); i++){
      
      leg3.pushOut();
      leg1.pushOut();
    }
    for(int i=0; i<(microstep*gearAxle*myangle); i++){
      
      leg3.rotateBackwardHighSpeed();
      leg1.rotateForwardHighSpeed();
      leg4.rotateForwardHighSpeed();
    }
    delay(3000);
  
    for(int i=0; i<(microstep*gearScrew*hight2*24); i++){
      leg1.pushOut();
      leg3.pushOut();
    }
    int outCounter=0;
    for(int i = 0; i < max(microstep*gearScrew*24*(hight+hight2), microstep*gearAxle*myangle); i++){
      if(i <= microstep*gearScrew*24*(hight+hight2) ){
         leg1.pushIn();
         leg3.pushIn();
        }
        if(i <=  microstep*gearAxle*myangle){
           leg3.rotateForwardHighSpeed();
           leg1.rotateBackwardHighSpeed();
           leg4.rotateBackwardHighSpeed();
        }
  
        if(i>microstep*gearScrew*24*(hight+hight2)/15.0&&i<=microstep*gearScrew*24*(hight+hight2)*5/6.0){
          outCounter++;
          leg2.pushOut();
          leg4.pushOut();
  
        }
      }
      delay(500);
      for(int i=0; i<outCounter;i++){
        leg2.pushIn();
        leg4.pushIn(); 
      }
    }
}//walk3

void testServo(int servoPos,int tid){
  myServo.write(servoPos);
  delay(tid*5);
  myServo.write(90);
}
void servoLock(){
  myServo.write(70);
  delay(450);
  myServo.write(90);  
}

void servoUnLock(){
  myServo.write(110);
  delay(450);
  myServo.write(90);  
}
