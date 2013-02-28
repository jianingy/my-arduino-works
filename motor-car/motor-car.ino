#include <string.h>

/* must skip PIN0 and PIN1 for serial read/write */
#define PIN_LA 8
#define PIN_LB 9
#define PIN_LE 10
#define PIN_LL 11

#define PIN_RA 4
#define PIN_RB 5
#define PIN_RE 6
#define PIN_RL 7

int speed = 5, l_speed, r_speed;
int led = 0, jiffies = 0;
float ratio = 0.1;
char last_state;

void setup(void)
{
  jiffies = millis();

  Serial.begin(115200);

  pinMode(PIN_LA, OUTPUT);
  pinMode(PIN_LB, OUTPUT);
  pinMode(PIN_LE, OUTPUT);
  pinMode(PIN_LL, OUTPUT);

  pinMode(PIN_RA, OUTPUT);
  pinMode(PIN_RB, OUTPUT);
  pinMode(PIN_RE, OUTPUT);
  pinMode(PIN_RL, OUTPUT);

  analogWrite(PIN_LE, 0);
  analogWrite(PIN_RE, 0);
}

void stop(void)
{
  digitalWrite(PIN_LA, LOW);
  digitalWrite(PIN_LB, LOW);

  digitalWrite(PIN_RA, LOW);
  digitalWrite(PIN_RB, LOW);

  l_speed = r_speed = 0;
}

void forward(void)
{
  digitalWrite(PIN_LA, HIGH);
  digitalWrite(PIN_LB, LOW);

  digitalWrite(PIN_RA, HIGH);
  digitalWrite(PIN_RB, LOW);

  l_speed = r_speed = speed;
}

void backward(void)
{
  digitalWrite(PIN_LA, LOW);
  digitalWrite(PIN_LB, HIGH);

  digitalWrite(PIN_RA, LOW);
  digitalWrite(PIN_RB, HIGH);

  l_speed = r_speed = speed;
}

void forward_left(void)
{
  forward();
  r_speed = speed;
  l_speed = r_speed * ratio;
}

void forward_right(void)
{
  forward();
  l_speed = speed;
  r_speed = l_speed * ratio;
}

void show(void)
{
  Serial.print("LA = ");
  Serial.print(digitalRead(PIN_LA));
  Serial.print(", LB = ");
  Serial.print(digitalRead(PIN_LB));
  Serial.print(", LE = ");
  Serial.print(l_speed);

  Serial.print(" <--==--> RA = ");
  Serial.print(digitalRead(PIN_RA));
  Serial.print(", RB = ");
  Serial.print(digitalRead(PIN_RB));
  Serial.print(", RE = ");
  Serial.print(r_speed);

  Serial.print(" ---> speed = ");
  Serial.print(speed);

  Serial.print(", ratio = ");
  Serial.print(ratio);

  Serial.println(".");

}

void tempt()
{
    // light some fancy leds
  if (millis() - jiffies > 1000)  {

    jiffies = millis();

    led = led + 1;
    led = led & 3;

    if (led & 1)
      digitalWrite(PIN_LL, HIGH);
    else
      digitalWrite(PIN_LL, LOW);

    if (led & 2)
      digitalWrite(PIN_RL, HIGH);
    else
      digitalWrite(PIN_RL, LOW);


  }

}

void loop(void)
{

  if (Serial.available() > 0) {
    byte ch = Serial.read();

    if (ch >= '0' && ch <= '9') {
      speed = ch - '0' ;
      speed = constrain(speed, 0, 9);
      ch = last_state;
    }

    if (ch == '+' || ch == '-') {
      if (ch == '+')
        ratio += 0.1;
      if (ch == '-')
        ratio -= 0.1;
      ratio = constrain(ratio, 0, 1);
      ch = last_state;
    }

    switch (ch) {
      case 'w': forward(); break;
      case 's': backward(); break;
      case 'a': forward_left(); break;
      case 'd': forward_right(); break;
      case ' ': stop(); break;
    }


    l_speed = map(l_speed, 0, 9, 0, 255);
    r_speed = map(r_speed, 0, 9, 0, 255);

    analogWrite(PIN_LE, l_speed);
    analogWrite(PIN_RE, r_speed);

    show();

    last_state = ch;
  }

  //tempt();

}
