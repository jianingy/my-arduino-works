#define PIN_OUTPUT 12

void setup(void)
{
  pinMode(PIN_OUTPUT, OUTPUT);
}

void loop(void)
{
  digitalWrite(PIN_OUTPUT, HIGH);
  delay(1000);
  digitalWrite(PIN_OUTPUT, LOW);
  delay(1000);
}

/* vim: set sw=2 et: */
