#define IR_PIN 3
#define LED_PIN 13

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int state = digitalRead(IR_PIN);
  Serial.print("State: ");
  Serial.print(state, DEC);
  Serial.println(".");
  if (state == 1) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(100);
}
