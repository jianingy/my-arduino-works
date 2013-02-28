#define PIN_OUTPUT 13

void setup(void)
{
  pinMode(PIN_OUTPUT, OUTPUT);
}

void loop(void)
{
  digitalWrite(PIN_OUTPUT, HIGH);
  delay(1);
  digitalWrite(PIN_OUTPUT, LOW);
  delay(1);
}

/* vim: set sw=2 et: */
