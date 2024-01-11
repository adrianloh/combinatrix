#include <Arduino.h>

const int encoderPinA = 0; // PB0
const int encoderPinB = 1; // PB1
const int outputPinCW = 2; // PB2
const int outputPinCCW = 3; // PB3

volatile int16_t encoderTicks = 0;
int8_t lastEncoded = 0;

const int16_t thresholdTicks = 4; // Update this value based on your encoder's detents

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(outputPinCW, OUTPUT);
  pinMode(outputPinCCW, OUTPUT);

  GIMSK |= (1 << PCIE); // Enable Pin Change Interrupts
  PCMSK |= (1 << PCINT0) | (1 << PCINT1); // Trigger Pin Change Interrupt on A and B pins

  sei(); // Enable interrupts
}

void loop() {
  if (encoderTicks >= thresholdTicks) {
    digitalWrite(outputPinCW, HIGH);
    delay(1); // You can adjust the pulse duration as needed
    digitalWrite(outputPinCW, LOW);
    encoderTicks -= thresholdTicks;
  } else if (encoderTicks <= -thresholdTicks) {
    digitalWrite(outputPinCCW, HIGH);
    delay(1); // You can adjust the pulse duration as needed
    digitalWrite(outputPinCCW, LOW);
    encoderTicks += thresholdTicks;
  }
}

ISR(PCINT0_vect) {
  int8_t encoded = (digitalRead(encoderPinA) << 1) | digitalRead(encoderPinB);
  int8_t sum = (lastEncoded << 2) | encoded;

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) {
    encoderTicks++;
  }
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
    encoderTicks--;
  }

  lastEncoded = encoded;
}
