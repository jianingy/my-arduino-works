#include <string.h>

/* must skip PIN0 and PIN1 for serial read/write */
#define PIN_LED_START 2
#define PIN_LED_END   9

#define PIN_LIGHT_START 10
#define PIN_LIGHT_END   13

#define DELAY 200

/*
  N   X   G F E D C B A
  0   3f    1 1 1 1 1 1
  1   06          1 1 0
  2   5b  1 0 1 1 0 1 1
  3   4f  1 0 0 1 1 1 1
  4   66  1 1 0 0 1 1 0
  5   6d  1 1 0 1 1 0 1
  6   7d  1 1 1 1 1 0 1
  7   07  0 0 0 0 1 1 1
  8   7f  1 1 1 1 1 1 1
  9   6f  1 1 0 1 1 1 1
 */

int led[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

void setup(void)
{
  int i = 0;

  Serial.begin(9600);

  for (i = PIN_LED_START; i <= PIN_LED_END; i++)
    pinMode(i, OUTPUT);

  for (i = PIN_LIGHT_START; i <= PIN_LIGHT_END; i++)
    pinMode(i, OUTPUT);

  output_digit(0);
}

void output_digit(int digit)
{
  for (int n = 0; n < 8; n++) {
    if (led[digit] & (1 << n))
      digitalWrite(n + PIN_LED_START, HIGH);
    else
      digitalWrite(n + PIN_LED_START, LOW);
  }
}

void output_light(int digit)
{
  for (int n = 0; n < 4; n++) {
    if (digit & (1 << n))
      digitalWrite(n + PIN_LIGHT_START, HIGH);
    else
      digitalWrite(n + PIN_LIGHT_START, LOW);
  }
}

void loop(void)
{
  if (Serial.available() > 0) {
    Serial.print("IN: ");
    int ch = Serial.read();
    Serial.print((char)ch);
    if (ch >= '0' && ch <= '9') {
      output_digit(ch - '0');
      output_light(ch - '0');
      Serial.print(" and displayed!");
    }
    Serial.println(".");
  }
  delay(100);
}

/* vim: set sw=2 et: */
