// This is just a mockup sketch for test scons works

#define PIN_LED_START 11
#define PIN_LED_END   13
#define DELAY 200

void setup(void)
{
  int i = 0;
  for (i = PIN_LED_START; i <= PIN_LED_END; i++)
    pinMode(i, OUTPUT);
}

void loop(void)
{
  int i = 0;
  for (i = PIN_LED_START; i <= PIN_LED_END; i++) {
    digitalWrite(i, HIGH);
    delay(DELAY);
    digitalWrite(i, LOW);
    delay(DELAY);
  }
}

/* vim: set sw=2 et: */
