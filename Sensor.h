
class Sensor{

    int selectchip;
    int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
    double acx, acy,acz;
    double ax,ay,az;
    double degree1_1,degree2_1,degree3_1,degree4_1,degree5_1;
    double degree1_2,degree2_2,degree3_2,degree4_2,degree5_2;//can be used to make a mean value to make the measurment more stable
    double degree1_3,degree2_3,degree3_3,degree4_3,degree5_3;
    int port;
    bool impacted;
  
public: 

  // list of all functions in cpp file
  Sensor(int selectchip);
  double readDataI2C();
  double getAngle();
  bool impact();
  bool resetImpact();
 
};
