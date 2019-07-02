#include <math.h>
#include <IRremote.h>

IRsend irsend;
double maxTemp = 24.0;
double minTemp = 18.0;
bool heaterOn = false;
int thermoPin = 0;

double temperature() {
  double Temp;
  int RawADC = analogRead(thermoPin);
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15; // Convert Kelvin to Celcius
  return Temp;
}

void turnOn() {
   irsend.sendNEC(0x00ff807f, 32);
   delay(2000);
   irsend.sendNEC(0x00ff906f, 32);
}

void turnOff() {
   irsend.sendNEC(0x00ff807f, 32);
}

void setup() {
   Serial.begin(9600);
}
void loop()
{ 
  double temp = temperature();
  if ( temp > minTemp && temp < maxTemp) {
    Serial.println("Current Temp " );
    Serial.println(temp);
    Serial.println("Doing Nothing");
  } else if ( ( temp  < minTemp ) && !heaterOn){
    Serial.println("Current Temp ");
    Serial.println(temp);
    Serial.println("Turning on the heater");
    heaterOn = true;
    turnOn();
  } else if ( ( temp > maxTemp ) && heaterOn) {
    Serial.println("Current Temp ");
    Serial.println(temp);
    Serial.println("Turning off the heater");
    heaterOn = false;
    turnOff();
  }
  delay(60000);
}
