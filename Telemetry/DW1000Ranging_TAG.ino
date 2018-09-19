/

#include <SPI.h>
#include "DW1000Ranging.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

double updates = 0;
double distanceSum = 0;
double changeSum = 0;
double oldDistance = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin

  //Starts up the new device.
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);

  //Starts the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
  delay(1000);
}

void loop() {
  DW1000Ranging.loop();
}

void newRange() {

  double change = 0;
  double distance = DW1000Ranging.getDistantDevice()->getRange();
  changeSum = changeSum + change;
  //refreshes the sum and number of updates every 10 values.
  //This is to reduce the chance that the average is off.
  if (updates == 20) {
    changeSum = 0;
    distanceSum = 0;
    updates = 0;
  }
  updates++;


  //Converts from m to cm
  distance = distance * 100;

  //Prints the Device Address
  Serial.print("from: ");
  Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);

  //Prints the distance from the the second device
  Serial.print("\t Range: ");
  Serial.print(distance);

  if ( distance >= 350 && distance <= 650) {
    distance = distance - 80;
  }

  if (distance >= 655) {
    distance = distance - 100;
  }
  Serial.print(" cm");

  //Calculates and prints average using the refreshed sum and update counter.
  distanceSum = distanceSum + distance;
  Serial.print("\t Average: ");
  Serial.print(distanceSum / updates - 50);

  //Calculates and prints the change from the previous value
  change = distance - oldDistance;
  Serial.print("\t Change: ");
  Serial.print(change);

  //Calculates and prints average change using the refreshed sum and update counter.
  Serial.print("\t Average Change: ");
  //Serial.print(changeSum/updates);
  Serial.print("\n");

  //Sets previous value to the current to use for the next cycle.
  oldDistance = distance;
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}

