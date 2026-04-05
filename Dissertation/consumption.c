#include <Wire.h>             // Include Wire library for I2C communication
#include "thingProperties.h"  // Include thingProperties.h header file
#include <Adafruit_LIS3DH.h>  // Include Adafruit LIS3DH library
#include <Adafruit_Sensor.h>   // Include Adafruit Sensor library
#include <LM35.h>             // Include LM35 library
#include <WiFi.h>             // Include WiFi library for connection
#include <Callmebot_ESP32.h>  // Include CallMeBot library for the WhatsApp

#define NUM_READINGS 10    // Define constant for number of readings

Adafruit_LIS3DH lis = Adafruit_LIS3DH();  // Create an instance of the LIS3DH library

int trigPin = 11;    // Trigger pin for ultrasonic sensor
int echoPin = 12;    // Echo pin for ultrasonic sensor
float duration;      // Duration of the pulse received from ultrasonic sensor
float distance;      // Distance measured by ultrasonic sensor
float distanceReadings[NUM_READINGS];  // Array to store distance readings
int readingIndex = 0;  // Index for distance readings array
float totallength = 11.55;  // Total length of container
float bottleradius = 5;     // Radius of container
float watervolume;          // Calculated water volume
float currentDistance;      // Current distance measured by sensor
float previousDistance; // Previous distance measured by sensor
int currentVolume;           // Current volume of water
float previousVolume = 0;    // Previous volume of water
int volumeDifference;        // Volume Difference used for logic
int consumptiongoal = 3000;  // Consumption goal can be set to any value according to users needs
float gravitydifference;     // The difference between flat surface 
int counter = 0;

const char* ssid = //enter here the ssid of the network you wish the connect to;
const char* password = //enter here the password of the network you wish the connect to;
String phoneNumber = //enter your phone number here to allow messages from callmebot;
String apiKey = //enter the value of the API key that will be provided to you once you set up callmebot api;
String fillupMessage = "Bottle is being filled up...";
String consumptionMessage = "Water is being consumed...";
String goalreachedMessage = "Congratulations your water consumption goal has been reached today, well done!";

void setup() {
  initProperties();                      // Initialize properties
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);  // Begin Arduino Cloud connection
  setDebugMessageLevel(2);               // Set debug message level
  ArduinoCloud.printDebugInfo();         // Print debug info to serial monitor
  pinMode(trigPin, OUTPUT);              // Set trigPin as output
  pinMode(echoPin, INPUT);               // Set echoPin as input
  waterconsumed = 0;                     // Initialises the water consumed value to zero
  for (int i = 0; i < NUM_READINGS; i++) { // A for loop that initialises the integer i to zero and will continue while i is less than the number of readings, this will be used for the distance       readings to make an average across a set value of NUM_READINGS
    distanceReadings[i] = 0;  // Initialize all elements of distanceReadings to 0
  }
  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   // The I2C address used on the Nano ESP32 in order for connection to accelerometer to start
    Serial.println("Couldnt start");  // Error message to display if connection to the LIS3DH accelerometer is unsucessful
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
  	WiFi.begin(ssid, password);
	Serial.println("Connecting");
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoCloud.update();  // Update Arduino Cloud
  readAccelerometer();  // Function to read accelerometer data
  readTemperature();    // Function to read temperature
  measureDistance();    // Function to measure distance using ultrasonic sensor
  calculateVolume();    // Function to calculate water volume
  outputSerial();       // Function to print data to serial monitor
  delay(2000);      // Delay for 2 seconds
}

// Function to read accelerometer data
void readAccelerometer() {
  lis.read();  // Read data from LIS3DH accelerometer
  sensors_event_t event;
  lis.getEvent(&event);

  Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2 ");

  gravitydifference = fabs(event.acceleration.z - 9.8);
}

// Function to read temperature
void readTemperature() {
  float rawtemp;
  float temp;
  rawtemp = analogRead(A0);//Connect LM35 on Analog 0
  temp =(322.34 * rawtemp) / 4096;  // Convert analog reading to temperature in Celsius
}

// Function to measure distance using ultrasonic sensor
void measureDistance() {
  digitalWrite(trigPin, LOW);  // Send LOW signal to trigPin
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); // Send HIGH signal to trigPin
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  // Send LOW signal to trigPin

  duration = pulseIn(echoPin, HIGH, 20000); // Measure duration of pulse from echoPin

  distance = duration / 58;     // Convert duration to distance (cm)

// Store the distance reading in the array
  distanceReadings[readingIndex] = distance;
  readingIndex = (readingIndex + 1) % NUM_READINGS;

  // Calculate the average of the last 5 readings
  float sum = 0;
  int numValidReadings = 0; // Count of valid readings
  for (int i = 0; i < NUM_READINGS; i++) {
    if (distanceReadings[i] != 0) {
      sum += distanceReadings[i];
      numValidReadings++;
    }
  }
  currentDistance = sum / numValidReadings;  // Calculate average distance
}

// Function to calculate water volume
void calculateVolume() {
     watervolume = PI * pow(bottleradius, 2) * (totallength - currentDistance); // Calculate water volume based on distance
  // Round the volume to the nearest 10ml
  currentVolume = round(watervolume / 10) * 10;
  if (previousVolume== 0){
    previousVolume = currentVolume;
  }
  int volDifference = previousVolume - currentVolume;
  if (gravitydifference < 1 && previousVolume > currentVolume && volDifference > 40){
  int consumption = previousVolume - currentVolume;  // Calculate water consumption
  waterconsumed += consumption;  // Update total water consumed
  }
  if (gravitydifference < 1){
    previousVolume = currentVolume;
  }
  if (waterconsumed >=consumptiongoal){
  Callmebot.whatsappMessage(phoneNumber, apiKey, goalreachedMessage);
  Serial.println(Callmebot.debug());
  }
}

// Function to print data to serial monitor
void outputSerial() {
  Serial.print("Current distance: ");
  Serial.print(currentDistance);  // Print current distance
  Serial.print(" cm, Current volume: ");
  Serial.print(currentVolume);     // Print current water volume
  Serial.print(" Previous Valid Volume: ");
  Serial.print(previousVolume);     // Print previous water volume
  Serial.print(" ml, Total water consumption:");
  Serial.print(waterconsumed);     // Print total water consumed
  Serial.print(" ml");
  Serial.println("");
 
}


/*
  Since Waterconsumed is READ_WRITE variable, onWaterconsumedChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onWaterconsumedChange()  {
  // Add your code here to act upon Waterconsumed change
}

