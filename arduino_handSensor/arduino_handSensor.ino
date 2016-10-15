//These are the 5 values sensors
int sensorPin1 = A0; // select the input pin for the potentiometer
int sensorPin2 = A1; // select the input pin for the potentiometer
int sensorPin3 = A2; // select the input pin for the potentiometer
int sensorPin4 = A3; // select the input pin for the potentiometer
int sensorPin5 = A4; // select the input pin for the potentiometer

//These are the initial values from the 5 finger-sensors
int initial_sensor1Value=0;
int initial_sensor2Value=0;
int initial_sensor3Value=0;
int initial_sensor4Value=0;
int initial_sensor5Value=0;

//This is the sixth sensor which corresponds to the ball one
int sensorPin6 = A5; // select the input pin for the potentiometer

//This is for the ball one
int initial_sensor6Value=0;

//These are the deviation values from the finger-sensors
int deviation1;
int deviation2;
int deviation3;
int deviation4;
int deviation5;

int ledPin = 13; // select the pin for the LED

//Variables to store the 5 finger-sensors value coming from the sensors
int sensor1Value = 0; 
int sensor2Value = 0; 
int sensor3Value = 0; 
int sensor4Value = 0; 
int sensor5Value = 0;

//Variables to store the value coming from the ball sensor 
int sensor6Value = 0; 

//This is the average value from 5 finger-sensors
int averageValue = 0;

//The delay value in ms which provides us the value between the previous value and the new one
int duration = 100;

//Array of ints which represents the "notes" values from the pentatonic scale
int scale[] = {0, 2, 4, 7, 9};

//This functions represents the reset when the user press the reset-button
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  //Reading the sensors and saving the data in the initial sensors
  initial_sensor1Value = (int) (analogRead(sensorPin1));
  initial_sensor2Value = (int) (analogRead(sensorPin2));
  initial_sensor3Value = (int) (analogRead(sensorPin3));
  initial_sensor4Value = (int) (analogRead(sensorPin4));
  initial_sensor5Value = (int) (analogRead(sensorPin5));
  initial_sensor6Value = (int) (analogRead(sensorPin6));//<-This one is for the ball!
  //And we display them on the screen.
  Serial.print("Initial sensor1Value=");
  Serial.println(initial_sensor1Value);
  Serial.print("Initial sensor2Value=");
  Serial.println(initial_sensor2Value);
  Serial.print("Initial sensor3Value=");
  Serial.println(initial_sensor3Value);
  Serial.print("Initial sensor4Value=");
  Serial.println(initial_sensor4Value);
  Serial.print("Initial sensor5Value=");
  Serial.println(initial_sensor5Value);
  //This one is to display the ball one
  Serial.print("Initial sensor6Value=");
  Serial.println(initial_sensor6Value);
}

//This is the main project
void loop() {
  // Read the corresponding value from the  sensors:
  // The ones from the 5 finger-sensors
  sensor1Value = analogRead(sensorPin1);
  sensor2Value = analogRead(sensorPin2);
  sensor3Value = analogRead(sensorPin3);
  sensor4Value = analogRead(sensorPin4);
  sensor5Value = analogRead(sensorPin5);
  //This is the one from the ball
  sensor6Value = analogRead(sensorPin6);
  //Serial.println(sensor1Value); <- From Domenico

  //first sensor
  if ((sensor1Value<(initial_sensor1Value*0.97)) || (sensor1Value>(initial_sensor1Value*1.03)))
  {
    deviation1=(int)(initial_sensor1Value-sensor1Value);

    int perc_deviation1=(int) (deviation1*100/initial_sensor1Value);
    //Serial.print("deviation1(%)=");<- From Domenico
    //Serial.println(perc_deviation1);<- From Domenico
    int note1 = map(abs(perc_deviation1), 0,30, 36, 60);
    //if (perc_deviation1<0){ duration=200;}<- From Domenico
    //Serial.println(sensor1Value);<- From Domenico
    //Serial.println(note);<- From Domenico
    // mapping to pentatonic scale<- From Domenico
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

    //Serial.println(note);<- From Domenico
    noteOn(0x90, note1, 0x45); delay(duration);
    noteOn(0x90, note1, 0x00); delay(duration);
  }

  //second sensor
  if ((sensor2Value<(initial_sensor2Value*0.97)) || (sensor2Value>(initial_sensor2Value*1.03)))
  {
    deviation2=(int)(initial_sensor2Value-sensor2Value);

    int perc_deviation2=(int) (deviation2*100/initial_sensor2Value);
    int note2 = map(abs(perc_deviation2), 0,30, 72, 96);

    int n=note2/12;
    n=n*12;
    int r=note2%12;
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
    note2=n+scale[index];

    noteOn(0x91, note2, 0x45); delay(duration);
    noteOn(0x91, note2, 0x00); delay(duration);
  }

  //Third sensor
  if ((sensor3Value<(initial_sensor3Value*0.97)) || (sensor3Value>(initial_sensor3Value*1.03)))
  {
    deviation3=(int)(initial_sensor3Value-sensor3Value);

    int perc_deviation3=(int) (deviation3*100/initial_sensor3Value);
    int note3 = map(abs(perc_deviation3), 0,30, 36, 60);

    int n=note3/12;
    n=n*12;
    int r=note3%12;
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
    note3=n+scale[index];

    noteOn(0x92, note3, 0x45); delay(duration);
    noteOn(0x92, note3, 0x00); delay(duration);
  }

  //Fourth sensor
  if ((sensor4Value<(initial_sensor4Value*0.97)) || (sensor4Value>(initial_sensor4Value*1.03)))
  {
    deviation4=(int)(initial_sensor4Value-sensor4Value);

    int perc_deviation4=(int) (deviation4*100/initial_sensor4Value);
    int note4 = map(abs(perc_deviation4), 0,30, 36, 60);

    int n=note4/12;
    n=n*12;
    int r=note4%12;
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
    note4=n+scale[index];

    noteOn(0x93, note4, 0x45); delay(duration);
    noteOn(0x93, note4, 0x00); delay(duration);
  }

  //Fifth sensor
  if ((sensor5Value<(initial_sensor5Value*0.97)) || (sensor5Value>(initial_sensor5Value*1.03)))
  {
    deviation5=(int)(initial_sensor5Value-sensor5Value);

    int perc_deviation5=(int) (deviation5*100/initial_sensor5Value);
    int note5 = map(abs(perc_deviation5), 0,30, 36, 60);

    int n=note5/12;
    n=n*12;
    int r=note5%12;
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
    note5=n+scale[index];

    noteOn(0x94, note5, 0x45); delay(duration);
    noteOn(0x94, note5, 0x00); delay(duration);
  }

  //To calculate the average of the 5 finger-sensors values, it has to be 1*Sensor1+2*Sensor2+3*Sensor3+4*Sensor4+5*Sensor5 divided by
  //15, which is the sum of 1+2+3+4+5.
  averageValue = ((1*sensor1Value)+(2*sensor2Value)+(3*sensor3Value)+(4*sensor4Value)+(5*sensor5Value))/(15);
  
  //Mapping of the sensors values average 
  //The map_avgSensors is the pitch.
  int map_avgSensors = map(abs(averageValue), 500,800, 36, 90);
  noteOn(0x95, map_avgSensors, 0x45); delay(duration);
  noteOn(0x95, map_avgSensors, 0x00); delay(duration);

    
  //Mapping of the sensor values average with the duration
  //The duration is the times between all the notes
  //0 is the min value for example when you crash the car or there is a flatline. 100 is ms)
  int map_avgDuration = map(abs(averageValue), 500,800, 0, 75);
  int duration_time = 75;
  noteOn(0x96, map_avgSensors, 0x45); delay(map_avgDuration);
  noteOn(0x96, map_avgSensors, 0x00); delay(duration_time);

}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

