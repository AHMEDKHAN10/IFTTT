/* ***************************************************************************************************
// Example sketch from John's DIY Playground
// to demonstrate the Particle Photon wifi IoT device.
// Visit http://www.particle.io/ to purchase a Photon of your own
//
// This sketch will demonstrate a basic Internet of Things function of the Photon.
//   It will report sensor light levels from a photoresistor on pin A5 to the Particle cloud server
//
// Demonstration of this code can be found on my YouTube channel, called John's DIY Playground
// The channel's URL is http://www.youtube.com/c/johnsdiyplayground
// Software code examples can be found on my GitHub page at
// https://github.com/johnsdiyplayground
// 
// Hardware Required:
// 1. Particle Photon
// 2. Photoresistor
// 3. 1K ohm resistor between pins A5 and ground
// 4. USB to micro USB cable for powering the Photon
******************************************************************************************************
*/

// Define our pins
int photoResistor = A5;
int photoResistorPower = A0;

// The next variable defines how often to check the photoresistor's light level
int photoResistorCheckTime = 10000;  // 10000 milliseconds is 10 seconds
// and we also record the time we report the photoresistor status with this
int lastPhotoResistorReport;
char lightValue[4];   // this is a string where we will actual light value read from the photoresistor

void setup() {
  // Tell Photon if our pins are inputs or outputs
  pinMode(photoResistor, INPUT);
  pinMode(photoResistorPower, OUTPUT);

  // Turn on power to the photoresistor
  digitalWrite(photoResistorPower, HIGH);
  
  // Initialize our timer for the photoresistor using millis which is the Photon's internal clock
  lastPhotoResistorReport = millis();
}

void loop() {
  // check if it is time to report the photoresistor's value to the Particle web site
  if ((millis() - lastPhotoResistorReport) >= photoResistorCheckTime) {
      lastPhotoResistorReport = millis();   // update current time for the next time through the loop
      int lightLevel = analogRead(photoResistor);  // we read in the photoResistor level here (value can be 0 to 4095)
      
      // now let's classify the light level into one of three categories
      if (lightLevel < 500) Particle.publish("lightLevel", "dark", PRIVATE);
      if (lightLevel >= 500 && lightLevel < 900) Particle.publish("lightLevel", "medium", PRIVATE);
      if (lightLevel >= 900) Particle.publish("lightLevel", "bright", PRIVATE);
      
      // publish the actual value of the light level
      sprintf(lightValue,"%d", lightLevel);   // this converts the value from an integer to a string for publishing
      Particle.publish("sensorValue", lightValue, PRIVATE);
  }
}  // this is the end of the loop