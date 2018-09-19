#include "HX711.h"

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0

HX711 scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library

void setup() {
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  scale.set_scale(415.f); // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(); // reset the scale to 0

  Serial.print("read: \t\t");
  Serial.println(scale.read()); // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20)); // print the average of 20 readings from the ADC

  Serial.println("Readings:");
}

void loop() {
  Serial.print("\t average(weight):\t");
  Serial.print(scale.get_units(10), 1);
  Serial.println("  gram");
  delay(500);
}
