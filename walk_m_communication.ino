// Communication


char test;

const byte numBytes = 32;
char receivedBytes[numBytes];
byte numReceived = 0;



const int numChar = 4;
String function;
char functionNrChar[numChar];
int functionNr;
char functionValueChar[numChar];
int functionValue;
char dump;

//void communication() {
    
//}

void recvBytesWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rb;
   //Serial.println("recvBytesWithStartEndMarkers");
    while (Serial1.available() > 0 && newData == false) {
        rb = Serial1.read();
        //Serial.println("Inne i while");
        if (recvInProgress == true) {
            if (rb != endMarker) {          
                receivedBytes[ndx] = rb;
                Serial.print("ndxif : ");
                Serial.println(ndx);
                ndx++;
                if (ndx >= numBytes) {
                  Serial.println("för lång");
                    ndx = numBytes - 1;
                    
                Serial.print("ndx: ");
                  Serial.println(ndx);
                }
            }
            else {
                receivedBytes[ndx] = '>'; // terminate the string but keep the endMarker
                recvInProgress = false;
                numReceived = ndx;  // save the number for use when printing
                ndx = 0;
                newData = true;
                Serial.print("rb:");
                  Serial.println(rb);
            }
        }

        else if (rb == startMarker) {
            recvInProgress = true;
        }
        else{
          dump=Serial.read();
        }
        
    }
}

void sortArray() {
  
  byte pos;
  byte Nrpos;
  memset(functionNr,'\0',numChar);
  memset(functionValue,'\0',numChar); 
  
  function = "";
  //Serial.println(1);
  //Serial.print(receivedBytes[0]);
  //Serial.print(receivedBytes[1]);
  //Serial.print(receivedBytes[2]);
  //Serial.println(receivedBytes[3]);
  Nrpos=0;
  pos=0;
  while(receivedBytes[pos] != ','){
     function += receivedBytes[pos];
     pos++;
   //  Serial.println("hej");
  }
  
  pos++;
  if (receivedBytes[pos] == ' '){//fångar bara whitespace efter ,
    pos++;  
  }
  while(receivedBytes[pos] != ','){
    functionNrChar[Nrpos] = receivedBytes[pos];
    Nrpos++;
    pos++;
    //Serial.println("Hej 2");
  }
  // Om Nrpos = 0 => ERROR!
  
  pos++;
  if (receivedBytes[pos] == ' '){
    pos++;  
  }
  
  Nrpos = 0;
  while(receivedBytes[pos] != '>'){
    functionValueChar[Nrpos] = receivedBytes[pos];
    Nrpos++;
    pos++;
   // Serial.println("Hej 3");
  }
  functionNr = atoi(&functionNrChar[0]);
  functionValue = atoi(&functionValueChar[0]);
/*
  Serial.println(function);
  Serial.println(functionNr);
  Serial.println(functionValue);
  */
  
  
}

void showNewData() {
        Serial.print("This just in (HEX values)... ");
        for (byte n = 0; n < numReceived; n++) {
            Serial.print(receivedBytes[n]);
            Serial.print(' ');
        }
        Serial.println();
        

       Serial.print("This is the function; ");
       Serial.println(function);
       
       Serial.print("This is the function Nr: ");
       Serial.println(functionNr);

       Serial.print("This is the function Value: ");
       Serial.println(functionValue);

       
       
    
}



String chooseCommand(){
  int var; // initiate variable for switch case
  static String retString = "Command: " + function + ", nr: " + functionNr + ", value: " + functionValue;
  showNewData();
  if(function == ("walk") ||function == ("WALK") ||function == ("Walk")){
    if(functionNr == 1){
      walk_1(functionValue);
      return retString;
      }
    else if (functionNr == 2){
      walk_2(functionValue);
      return retString;
      }
    else if (functionNr == 3){
        walk_3(functionValue);
        return retString;
      }
    else{
      retString = "Invalid functionNr";
      }
  }
  else if(function=="servo"){
    servoLock();
    delay(5000);
    servoUnLock();
    return retString;
  }
  else if(function=="init"){
    initiateLegs();
    return retString;
  }

  else if(function = ("movelegout" || "MOVELEGOUT" || "MoveLegOut" || "movelegOut" || "moveLegout" || "Movelegout")){ // Different combination of leg out
    if(functionNr == 1){
      MoveLeg(legs1, "out", functionValue);
      return retString;
    }
    else if (functionNr == 2){
      MoveLeg(legs2, "out", functionValue);
      return retString;
    }
    else if (functionNr == 3){
      MoveLeg(legs3, "out", functionValue);
      return retString;
    }
    else if (functionNr == 4){
      MoveLeg(legs4, "out", functionValue);
      return retString;
    }
    else if (functionNr == (14 || 41)){
      MoveLeg(legs14, "out", functionValue);
      return retString;
    }
    else if (functionNr == (13 || 31)){
      MoveLeg(legs13, "out", functionValue);
      return retString;
    }
    else if (functionNr == (12 || 21)){
      MoveLeg(legs12, "out", functionValue);
      return retString;
    }
    else if (functionNr == (23 || 32)){
      MoveLeg(legs23, "out", functionValue);
      return retString;
    }
    else if (functionNr == (24 || 42)){
      MoveLeg(legs24, "out", functionValue);
      return retString;
    }
    else if (functionNr == (34 || 43)){
      MoveLeg(legs34, "out", functionValue);
      return retString;
    }
    else if (functionNr == (1234)){
      MoveLeg(legs1234, "out", functionValue);
      return retString;
    }
    
    else{
      retString = "Invalid function Value";
      return retString; 
    }
  }


    
  else if(function = ("movelegin" || "MOVELEGIN" || "MoveLegIn" || "movelegIn" || "moveLegin" || "Movelegin")){ // Different combination of leg out
    if(functionNr == 1){
      MoveLeg(legs1, "in", functionValue);
      return retString;
    }
    else if (functionNr == 2){
      MoveLeg(legs2, "in", functionValue);
      return retString;
    }
    else if (functionNr == 3){
      MoveLeg(legs3, "in", functionValue);
      return retString;
    }
    else if (functionNr == 4){
      MoveLeg(legs4, "in", functionValue);
      return retString;
    }
    else if (functionNr == (14 || 41)){
      MoveLeg(legs14, "in", functionValue);
      return retString;
    }
    else if (functionNr == (13 || 31)){
      MoveLeg(legs13, "in", functionValue);
      return retString;
    }
    else if (functionNr == (12 || 21)){
      MoveLeg(legs12, "in", functionValue);
      return retString;
    }
    else if (functionNr == (23 || 32)){
      MoveLeg(legs23, "in", functionValue);
      return retString;
    }
    else if (functionNr == (24 || 42)){
      MoveLeg(legs24, "in", functionValue);
      return retString;
    }
    else if (functionNr == (34 || 43)){
      MoveLeg(legs34, "in", functionValue);
      return retString;
    }
    else if (functionNr == (1234)){
      MoveLeg(legs1234, "in", functionValue);
      return retString;
    }
    
    else{
      retString = "Invalid function Value";
      return retString; 
    }
  }


    else if (function = ("rotateforward" || "ROTATEFORWARD" || "RotateForward" || "rotateForward" || "Rotateforward")){ // Rotate forward for different combinations of the legs
      if(functionNr == 1){
//      rotateForward1(functionValue);
      return retString;
    }
    else if (functionNr == 2){
//      rotateForward2(functionValue);
      return retString;
    }
    else if (functionNr == 3){
//      rotateForward3(functionValue);
      return retString;
    }
    else if (functionNr == 4){
//      rotateForward4(functionValue);
      return retString;
    }
    else if (functionNr == (14 || 41)){
      rotateForward14(functionValue);
      return retString;
    }
    else if (functionNr == (13 || 31)){
      rotateForward13(functionValue);
      return retString;
    }
    else if (functionNr == (12 || 21)){
      rotateForward14(functionValue);
      return retString;
    }
    else if (functionNr == (23 || 32)){
      rotateForward23(functionValue);
      return retString;
    }
    else if (functionNr == (24 || 42)){
      rotateForward24(functionValue);
      return retString;
    }
    else if (functionNr == (34 || 43)){
//      rotateForward34(functionValue);
      return retString;
    }
    else{
      retString = "Invalid function Value";
      return retString; 
    }
  }
  
  else if (function = ("rotatebackward" || "ROTATEBACKWARD" || "RotateBackward" || "rotateBackward" || "Rotatebackward")){ // Rotate forward for different combinations of the legs
      if(functionNr == 1){
//      rotateBackward1(functionValue);
      return retString;
    }
    else if (functionNr == 2){
//      rotateBackward2(functionValue);
      return retString;
    }
    else if (functionNr == 3){
//      rotateBackward3(functionValue);
      return retString;
    }
    else if (functionNr == 4){
//      rotateBackward4(functionValue);
      return retString;
    }
    else if (functionNr == (14 || 41)){
      rotateBackward14(functionValue);
      return retString;
    }
    else if (functionNr == (13 || 31)){
//      rotateBackward13(functionValue);
      return retString;
    }
    else if (functionNr == (12 || 21)){
//      rotateBackward12(functionValue);
      return retString;
    }
    else if (functionNr == (23 || 32)){
//      rotateBackward23(functionValue);
      return retString;
    }
    else if (functionNr == (24 || 42)){
//      rotateBackward24(functionValue);
      return retString;
    }
    else if (functionNr == (34 || 43)){
//      rotateBackward34(functionValue);
      return retString;
    }
     else{
      retString = "Invalid function Value";
      return retString; 
    }
  }
  
      
  else {
    retString = "Invalid Function";
      return retString;
    }


}

 
