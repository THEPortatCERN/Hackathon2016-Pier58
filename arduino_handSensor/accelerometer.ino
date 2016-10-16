#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include <math.h>
/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper
functions.
  
   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).
  
   Connections (For default I2C)
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 5V DC
   Connect GROUND to common ground

   History
   =======
   2014/JULY/25  - First version (KTOWN)
*/
  
/* Assign a unique base ID for this sensor */
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(1000);  // Use I2C, ID #1000


/* Or, use Hardware SPI:
  SCK -> SPI CLK
  SDA -> SPI MOSI
  G_SDO + XM_SDO -> tied together to SPI MISO
  then select any two pins for the two CS lines:
*/

#define LSM9DS0_XM_CS 10
#define LSM9DS0_GYRO_CS 9
//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(LSM9DS0_XM_CS, LSM9DS0_GYRO_CS,
1000);

/* Or, use Software SPI:
  G_SDO + XM_SDO -> tied together to the MISO pin!
  then select any pins for the SPI lines, and the two CS pins above
*/

#define LSM9DS0_SCLK 13
#define LSM9DS0_MISO 12
#define LSM9DS0_MOSI 11

int duration = 83.375*2;
int scale[] = {
  0, 2, 4, 7, 9
};

//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0(LSM9DS0_SCLK, LSM9DS0_MISO,
LSM9DS0_MOSI, LSM9DS0_XM_CS, LSM9DS0_GYRO_CS, 1000);


/**************************************************************************
/
/*
    Displays some basic information on this sensor from the unified
    sensor API sensor_t type (see Adafruit_Sensor for more information)
*/
/**************************************************************************
/
void displaySensorDetails(void)
{
  sensor_t accel, mag, gyro, temp;
  
  lsm.getSensor(&accel, &mag, &gyro, &temp);
  
  //Serial.println(F("------------------------------------"));
  //Serial.print  (F("Sensor:       ")); Serial.println(accel.name);
  //Serial.print  (F("Driver Ver:   ")); Serial.println(accel.version);
  //Serial.print  (F("Unique ID:    ")); Serial.println(accel.sensor_id);
  //Serial.print  (F("Max Value:    ")); Serial.print(accel.max_value);
Serial.println(F(" m/s^2"));
  //Serial.print  (F("Min Value:    ")); Serial.print(accel.min_value);
Serial.println(F(" m/s^2"));
  //Serial.print  (F("Resolution:   ")); Serial.print(accel.resolution);
Serial.println(F(" m/s^2"));
  //Serial.println(F("------------------------------------"));
  //Serial.println(F(""));

  //Serial.println(F("------------------------------------"));
  //Serial.print  (F("Sensor:       ")); Serial.println(mag.name);
  //Serial.print  (F("Driver Ver:   ")); Serial.println(mag.version);
  //Serial.print  (F("Unique ID:    ")); Serial.println(mag.sensor_id);
  //Serial.print  (F("Max Value:    ")); Serial.print(mag.max_value);
Serial.println(F(" uT"));
  //Serial.print  (F("Min Value:    ")); Serial.print(mag.min_value);
Serial.println(F(" uT"));
  //Serial.print  (F("Resolution:   ")); Serial.print(mag.resolution);
Serial.println(F(" uT"));
  //Serial.println(F("------------------------------------"));
  //Serial.println(F(""));
  /*
  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(gyro.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(gyro.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(gyro.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(gyro.max_value);
Serial.println(F(" rad/s"));
  Serial.print  (F("Min Value:    ")); Serial.print(gyro.min_value);
Serial.println(F(" rad/s"));
  Serial.print  (F("Resolution:   ")); Serial.print(gyro.resolution);
Serial.println(F(" rad/s"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));

  Serial.println(F("------------------------------------"));
  Serial.print  (F("Sensor:       ")); Serial.println(temp.name);
  Serial.print  (F("Driver Ver:   ")); Serial.println(temp.version);
  Serial.print  (F("Unique ID:    ")); Serial.println(temp.sensor_id);
  Serial.print  (F("Max Value:    ")); Serial.print(temp.max_value);
Serial.println(F(" C"));
  Serial.print  (F("Min Value:    ")); Serial.print(temp.min_value);
Serial.println(F(" C"));
  Serial.print  (F("Resolution:   ")); Serial.print(temp.resolution);
Serial.println(F(" C"));
  Serial.println(F("------------------------------------"));
  Serial.println(F(""));
  */
  delay(500);
}

/**************************************************************************
/
/*
    Configures the gain and integration time for the TSL2561
*/
/**************************************************************************
/
void configureSensor(void)
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}

/**************************************************************************
/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************
/
void setup(void)
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial
console opens
#endif
  Serial.begin(9600);
  //Serial.println(F("LSM9DS0 9DOF Sensor Test")); Serial.println("");
  
  /* Initialise the sensor */
  if(!lsm.begin())
  {
    /* There was a problem detecting the LSM9DS0 ... check your
connections */
    //Serial.print(F("Ooops, no LSM9DS0 detected ... Check your wiring or
I2C ADDR!"));
    while(1);
  }
  //Serial.println(F("Found LSM9DS0 9DOF"));
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* Setup the sensor gain and integration time */
  configureSensor();
  
  /* We're ready to go! */
  //Serial.println("");
}

/**************************************************************************
/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************
/
void loop(void)
{  
  /* Get a new sensor event */
  sensors_event_t accel, mag, gyro, temp;

  lsm.getEvent(&accel, &mag, &gyro, &temp);
  float kangle=180.0f/3.14;
  // print out accelleration data
  //Serial.print("Accel X: ");
  float acc_x=accel.acceleration.x;
  //Serial.print(acc_x); Serial.print(" ");
  float acc_y=accel.acceleration.y;
  //Serial.print("  \tY: "); Serial.print(acc_y);Serial.print(" ");
  float acc_z=accel.acceleration.z;
  //Serial.print("  \tZ: "); Serial.print(acc_z);     Serial.println("
\tm/s^2");
float  
avg=(float)sqrt((((float)acc_x)*((float)acc_x))+(((float)acc_y)*((float)acc
_y))+(((float)acc_z)*((float)acc_z)));
float   roll_acc=(asin((acc_y)/avg))*kangle;
       //if (roll_acc<=-90)
       //roll_acc=roll_acc+((90+roll_acc));
       //if (roll_acc>=90)
       //roll_acc=roll_acc-((90-roll_acc));
            
float  pitch_acc=(asin((acc_x)/avg))*kangle;
//float  yaw_acc=(asin((acc_z)/avg))*kangle;

//Serial.print("  \troll_acc: "); Serial.print(roll_acc);
//Serial.print("  \tpitch_acc: "); Serial.print(pitch_acc);
//Serial.print("  \tyaw_acc: "); Serial.print(yaw_acc);
  
  
  
  // print out magnetometer data
  //Serial.print("Magn. X: ");
float  mag_x=mag.magnetic.x;
  //Serial.print(mag_x); Serial.print(" ");
  //Serial.print("  \tY: ");
float mag_y=mag.magnetic.y;
// Serial.print(mag_y);       Serial.print(" ");
  //Serial.print("  \tZ: ");
float  mag_z=mag.magnetic.z;
// Serial.print(mag_z);     Serial.println("  \tgauss");
         float   a=(mag_y*cos(roll_acc/kangle));
         float   b=(mag_z*sin(roll_acc/kangle));
         float   Yh=a-b;
         float  
Xh=mag_x*cos(pitch_acc/kangle)+mag_y*sin(roll_acc/kangle)*sin(pitch_acc/kan
gle)+mag_z*cos(roll_acc/kangle)*sin(pitch_acc/kangle);
         float   dir=atan(Yh/Xh)*(kangle);
                if(Xh>0&&Yh>0)
                                dir=-180+dir;
                if(Xh>0&&Yh<0)
                                dir=180+dir;
          
          
            //Serial.print(dir);
            
  // print out gyroscopic data
  /*Serial.print("Gyro  X: ");
  float gyro_x=gyro.gyro.x;
  Serial.print(gyro_x); Serial.print(" ");
  Serial.print("  \tY: ");
  float gyro_y=gyro.gyro.y;
  Serial.print(gyro_y);  Serial.print(" ");
  Serial.print("  \tZ: ");
  float gyro_z=gyro.gyro.z;
  Serial.print(gyro_z);     Serial.println("  \tdps");*/
  // print out temperature data
//  Serial.print("Temp: "); Serial.print(temp.temperature);
Serial.println(" *C");

  //Serial.println("**********************\n");
  

  //delay(250);


//////SONIFICATION

int note1 = map(roll_acc, -90,90, 36, 96);
int duration1 = map(pitch_acc, -50,50, 100, 1000);
    int n=note1/12;
    n=n*12;
    int r=note1%12;
    int dist=r-scale[0];
    int index=0;
    int i=1;
    while ((i<5) && (r-scale[i]>=0)){
      if (r-scale[i]<dist) {
        dist=r-scale[i];
        index=i;
      }
      i++;
    }
    note1=n+scale[index];
    
    //Serial.println(note);
    noteOn(0x90, note1, 0x45); delay(duration1);
    noteOn(0x90, note1, 0x00); delay(100);

}


void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
