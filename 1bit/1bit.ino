#define PIN_INPUT 2
#define PIN_OUTPUT 13

void setup(void)
{
  Serial.begin(9600);
  pinMode(PIN_INPUT, INPUT);
}

void loop(void)
{
  int buttonState = digitalRead(PIN_INPUT);
  Serial.println(buttonState);
  delay(1);
}

/* vim: set sw=2 et: */
