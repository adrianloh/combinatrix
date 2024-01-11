#include <DS3231M.h> 

const uint32_t SERIAL_SPEED{115200}; 

DS3231M_Class DS3231M;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(SERIAL_SPEED);
    while (!DS3231M.begin()) { // Initialize RTC communications
      Serial.println("Unable to find DS3231M. Checking again in 1 second.");
      delay(1000);
    } // of loop until device is located
    DS3231M.pinSquareWave();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(5, HIGH);
  digitalWrite(11, LOW);
  delay(250);
  digitalWrite(5, LOW);
  digitalWrite(11, HIGH);
  delay(250);
}
