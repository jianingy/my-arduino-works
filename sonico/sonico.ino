/*
This piece of code is written by
   Jianing Yang <jianingy.yang@gmail.com>
with love and passion!

       H A P P Y    H A C K I N G !
             _____               ______
    ____====  ]OO|_n_n__][.      |    |
   [________]_|__|________)<     |YANG|
    oo    oo  'oo OOOO-| oo\\_   ~o~~o~
+--+--+--+--+--+--+--+--+--+--+--+--+--+
                            19 Mar, 2016
*/

// must skip PIN0 and PIN1 for serial read/write
const int ECHO_PIN = 2;
const int TRIG_PIN = 3;
const int RM_EN_PIN = 10;
const int RM_DI_PIN = 12;
const int LM_EN_PIN = 11;
const int LM_DI_PIN = 13;

int RM_SPEED = 127, LM_SPEED = 127;

void ranger_setup() {
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}

void motor_setup() {
  pinMode(RM_EN_PIN,OUTPUT);
  pinMode(RM_DI_PIN,OUTPUT);
  pinMode(LM_EN_PIN,OUTPUT);
  pinMode(LM_DI_PIN,OUTPUT);

  // initial motor speed set to zero
  analogWrite(RM_EN_PIN, 0);
  analogWrite(LM_EN_PIN, 0);
}

long get_range()
{
  long duration, distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);

  // convert the time into a distance (centimeter)
  distance = duration / 29.1 / 2;

  return distance;
}

void stop(void) {
  analogWrite(RM_EN_PIN, 0);
  analogWrite(LM_EN_PIN, 0);
}

void forward(void) {
  analogWrite(RM_EN_PIN, RM_SPEED);
  analogWrite(LM_EN_PIN, LM_SPEED);

  digitalWrite(RM_DI_PIN, LOW);
  digitalWrite(LM_DI_PIN, LOW);
}

void rotate(void) {
  analogWrite(RM_EN_PIN, RM_SPEED);
  analogWrite(LM_EN_PIN, LM_SPEED);

  digitalWrite(RM_DI_PIN, HIGH);
  digitalWrite(LM_DI_PIN, LOW);
}

void send_system_status() {
  long distance = get_range();
  Serial.println("[#] System Report");
  Serial.println("-----------------");
  Serial.print("[#]");
  Serial.print(" RM_DI = ");
  Serial.print(digitalRead(RM_DI_PIN));
  Serial.print(" LM_DI = ");
  Serial.print(digitalRead(LM_DI_PIN));
  Serial.println();
  Serial.print("[#]");
  Serial.print(" distance = ");
  if (distance <= 0){
    Serial.print("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.print("cm");
  }
  Serial.println();
  Serial.println("-----------------");
  Serial.println();
}

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  motor_setup();
  ranger_setup();
}

void loop() {
  long required_distance = 80;
  long distance = get_range();
  while (distance < required_distance) {
    send_system_status();
    rotate();
    delay(50);
    stop();
    distance = get_range();
    delay(500);
  }
  forward();
  delay(500);
  stop();
  send_system_status();
}