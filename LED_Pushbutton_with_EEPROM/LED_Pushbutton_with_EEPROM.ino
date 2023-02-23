#include <EEPROM.h>

const int BUTTON1 = 2;
const int BUTTON2 = 4;
const int LED = 8;

int ledState = LOW; // the current state of the output pin
int buttonState; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin

int ledState2 = LOW; // the current state of the output pin
int buttonState2; // the current reading from the input pin
int lastButtonState2 = LOW; // the previous reading from the input pin

long lastDebounceTime = 0; // the last time the output pin was toggled
long debounceDelay = 50; // the debounce time; increase if the output flickers
long lastDebounceTime2 = 0; // the last time the output pin was toggled
long debounceDelay2 = 50; // the debounce time; increase if the output flickers

void setup()
{
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);

  EEPROM.write(2, 100);
}

void loop()
{
  int reading = digitalRead(BUTTON1);
  int reading2 = digitalRead(BUTTON2);

  int value = EEPROM.read(2);
  Serial.println(value);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (reading2 != lastButtonState2) {
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if ((millis() - lastDebounceTime2) > debounceDelay2) {

      // if the button state has changed:
      if (reading != buttonState) {
        buttonState = reading;

        // only toggle the LED if the new button state is HIGH
        if (buttonState == HIGH) {
          value++;
          EEPROM.write(2,value);
        }
      }
    }
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

      // only toggle the LED if the new button state is HIGH
      if (buttonState2 == HIGH) {
        value--;
        EEPROM.write(2,value);
      }
    }
  }

  // set the LED:
  if (value % 2 == 0) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  // save the reading. Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading;
  lastButtonState2 = reading2;
}
