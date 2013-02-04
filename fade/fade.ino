#define LED_PIN 9

int g_fadestep = 5;
int g_brightness = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  analogWrite(LED_PIN, g_brightness);

  g_brightness = g_brightness + g_fadestep ;

  if (g_brightness > 254 || g_brightness < 1)
    g_fadestep = -g_fadestep;

  delay(10);
}
