

/*
 while (Serial.available() == 0){ //Waits until choice has been made 
  }
  
  BT_walk = Serial1.parseInt(); //Reads which walk style     
     */

void readSerialComputer(){
  while(Serial.available() == 0){
    Serial.println("Waiting");
    delay(1000);
  }
  
  int Leg = Serial.parseInt();
  Serial.println(Leg);
  testLegAxis(Leg);
   
  Serial.println("Eureka");

}

void testLegAxis(int Leg){

  if (Leg = 4){
    for (int i=0; i<50; i++){
     leg4.rotateForward();
   }

   delay(3000);

   for (int i = 0; i < 50; i++){
     leg4.rotateBackward();
  }
  }
}

void testActuatingLeg(int Leg){

    if (Leg = 1){
      for (int i=0; i < 50; i++){
        leg1.pushOut();
      }
      delay(3000);
      for (int i=0; i < 50; i++){
        leg1.pushIn();
      }
    }
    else if (Leg = 2){
      for (int i=0; i < 50; i++){
        leg2.pushOut();
      }
      delay(3000);
      for (int i=0; i < 50; i++){
        leg2.pushIn();
      }
    }
    else if (Leg = 3){
      for (int i=0; i < 50; i++){
        leg3.pushOut();
      }
      delay(3000);
      for (int i=0; i < 50; i++){
        leg3.pushIn();
      }
    }
    else if (Leg = 4){
      for (int i=0; i < 50; i++){
        leg4.pushOut();
      }
      delay(3000);
      for (int i=0; i < 50; i++){
        leg4.pushIn();
      }
    }
    else{
      Serial.print("Error in testActuatingLeg");
      }
}


void testSensors(){
  Serial.print("1: ");
  Serial.print(sens1.getAngle());
  Serial.print(",impact: ");
  Serial.println(sens1.impact());
  
  Serial.print(",2: ");
  Serial.print(sens2.getAngle());
  Serial.print(",impact: ");
  Serial.println(sens2.impact());
  
  Serial.print(",3: ");
  Serial.print(sens3.getAngle());
  Serial.print(",impact: ");
  Serial.println(sens3.impact());
  
  Serial.print(",4: ");
  Serial.print(sens4.getAngle());
  Serial.print(",impact: ");
  Serial.println(sens4.impact());
}

void testEndSwitch(){

  
  while(true){
  Serial.print("endSwitches   1: ");
  Serial.print(digitalRead(END_SWITCH_1));
  
  Serial.print("  2: ");
  Serial.print(digitalRead(END_SWITCH_2));
  
  Serial.print("  3: ");
  Serial.print(digitalRead(END_SWITCH_3));
  
  Serial.print("  4: ");
  Serial.println(digitalRead(END_SWITCH_4));
  delay(100);
  }
}

void testInitiate(){
  int init2=10;
  
  for(int i=0; i<(24*init2); i++){
    leg2.pushOut();
  }
  while(digitalRead(END_SWITCH_2)){
    leg2.pushIn();
  }
  
}
