
class Leg{

    int PUL_rot;
    int DIR_rot;
    int ENA_rot;
    int PUL_lead;
    int DIR_lead;
    int ENA_lead;
    //int chipSelect;
    int endSwitch;
    int microsec_screw;
    int microsec_axle;
    //Sensor acc;
    double angle;

public: 

  // list of all functions in cpp file
  Leg(int PUL_rot, int DIR_rot, int ENA1_rot, int PUL_lead, int DIR_lead, int ENA_lead, int chipsSelect,int microsec_screw, int microsec_axle);
  void pushOut();
  void pushIn();
  void rotateForward();
  void rotateBackward();
  
  void rotateForwardHighSpeed();
  void rotateBackwardHighSpeed();
  
  void resetLegLocation();
  double getAngle();  
  
};
