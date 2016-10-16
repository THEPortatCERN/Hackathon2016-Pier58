/*
Developed by: SoPhy Team - Pier58 THE Port Hackathon@CERN
Date: 16/10/2016
*/

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            9

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

//End of the light library definition

//These are the 5 values sensors
int sensorPin1 = A0; // select the input pin for the potentiometer
int sensorPin2 = A1; // select the input pin for the potentiometer
int sensorPin3 = A2; // select the input pin for the potentiometer
int sensorPin4 = A3; // select the input pin for the potentiometer
int sensorPin5 = A4; // select the input pin for the potentiometer
int sensorPin6 = A5; // select the input pin for the potentiometer

//These are the initial values from the 5 finger-sensors
int initial_sensor1Value=0;
int initial_sensor2Value=0;
int initial_sensor3Value=0;
int initial_sensor4Value=0;
int initial_sensor5Value=0;
int initial_sensor6Value=0;

//Variables to store the 5 finger-sensors value coming from the sensors
int sensor1Value = 0; 
long sensor2Value = 0; 
int sensor3Value = 0; 
int sensor4Value = 0; 
int sensor5Value = 0;
int sensor6Value = 0;

//Variables to store the value coming from the ball sensor 
//int sensor6Value = 0; 

//This is the average value from 5 finger-sensors
int averageValue = 0;

//The delay value in ms which provides us the value between the previous value and the new one
int duration = 100;

//Array of ints which represents the "notes" values from the pentatonic scale
int scale[] = {0, 2, 4, 7, 9};

//This functions represents the reset when the user press the reset-button
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
//end of the light library

  // initialize serial communications at 9600 bps:
  digitalWrite(A0, HIGH);       // turn on pullup resistors
  digitalWrite(A1, HIGH);       // turn on pullup resistors
  digitalWrite(A2, HIGH);       // turn on pullup resistors
  digitalWrite(A3, HIGH);       // turn on pullup resistors
  digitalWrite(A4, HIGH);       // turn on pullup resistors
  digitalWrite(A5, HIGH);       // turn on pullup resistors

  Serial.begin(9600);
}

//This is the main project
void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  int led_color =  map(abs(sensor2Value), 200,350, 0, 255);
  
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(led_color,255-led_color,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }

//end of the light library
      
  // Read the corresponding value from the  sensors:
  // The ones from the 5 finger-sensors
  sensor1Value = analogRead(sensorPin1);
  sensor2Value =0;
  for (int i;i<100;i++){
    sensor2Value = sensor2Value+analogRead(sensorPin2);
  }
  sensor2Value= sensor2Value/100;
  sensor3Value = analogRead(sensorPin3);
  sensor4Value = analogRead(sensorPin4);
  sensor5Value = analogRead(sensorPin5);
  sensor6Value = analogRead(sensorPin6);

  //To calculate the average of the 5 finger-sensors values, it has to be 1*Sensor1+2*Sensor2+3*Sensor3+4*Sensor4+5*Sensor5 divided by
  //15, which is the sum of 1+2+3+4+5.
  //averageValue = ((1*sensor1Value)+(2*sensor2Value)+(3*sensor3Value)+(4*sensor4Value)+(5*sensor5Value))/(15);
  averageValue = ((sensor1Value)+(sensor2Value)+(sensor3Value)+(sensor4Value)+(sensor5Value))/(5);
    

  //Mapping of the sensors values average 
  //The map_avgSensors is the pitch.
  int map_avgSensors = map(abs(averageValue), 130,350, 90, 36);

    int n=map_avgSensors/12;
    n=n*12;
    int r=map_avgSensors%12;
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
    map_avgSensors=n+scale[index];

  
  //noteOn(0x95, map_avgSensors, 0x45); delay(200);
  //noteOn(0x95, map_avgSensors, 0x00); delay(100);


  //Mapping of the sensor values average with the duration
  //The duration is the times between all the notes
  //50 is the min value for example when you crash the car or there is a flatline. 100 is ms)
  int map_avgDuration = map(abs(averageValue), 160,330, 50, 750);
  int map_velocity = map(abs(sensor6Value), 995,1005, 20, 127);

  int duration_time = 50;
  noteOn(0x96, map_avgSensors, map_velocity); delay(map_avgDuration);
  noteOn(0x96, map_avgSensors, 0x00); delay(duration_time);
  //Serial.println(sensor6Value);

}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

