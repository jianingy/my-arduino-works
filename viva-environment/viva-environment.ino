#include <SoftwareSerial.h>
#include "DHT22.h"

SoftwareSerial GP2Serial(10, 11); // RX, TX
DHT22 myDHT22(7);

void setup() {
  // setup serial port baudrate
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // Greetings!
  Serial.println("Hello!");

  // setup GP2 software serial port baudrate
  GP2Serial.begin(2400);

}

/* Copied from nethoncho's examples from http://github.com/nethoncho/Arduino-DHT22 */
void DHT22Report(void)
{
  DHT22_ERROR_t errorCode;

  // The DHT22 sensor can only be read from every 1-2s, and requires a minimum
  // 2s warm-up after power-on.
  delay(2000);

  Serial.print("DHT22: Requesting data...");
  errorCode = myDHT22.readData();
  switch(errorCode)
    {
    case DHT_ERROR_NONE:
      Serial.print("DHT22: Got Data ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      // Alternately, with integer formatting which is clumsier but more compact to store and
      // can be compared reliably for equality:
      //
      char buf[128];
      sprintf(buf, "DHT22: T=%hi.%01hi, H=%i.%01i",
              myDHT22.getTemperatureCInt()/10, abs(myDHT22.getTemperatureCInt()%10),
              myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);
      Serial.println(buf);
      break;
    case DHT_ERROR_CHECKSUM:
      Serial.print("DHT22: check sum error ");
      Serial.print(myDHT22.getTemperatureC());
      Serial.print("C ");
      Serial.print(myDHT22.getHumidity());
      Serial.println("%");
      break;
    case DHT_BUS_HUNG:
      Serial.println("DHT22: BUS Hung ");
      break;
    case DHT_ERROR_NOT_PRESENT:
      Serial.println("DHT22: Not Present ");
      break;
    case DHT_ERROR_ACK_TOO_LONG:
      Serial.println("DHT22: ACK time out ");
      break;
    case DHT_ERROR_SYNC_TIMEOUT:
      Serial.println("DHT22: Sync Timeout ");
      break;
    case DHT_ERROR_DATA_TIMEOUT:
      Serial.println("DHT22: Data Timeout ");
      break;
    case DHT_ERROR_TOOQUICK:
      Serial.println("DHT22: Polled too quick ");
      break;
    }
}

#define GP2_DATA_BIT_COUNT 7
#define GP2_START_SIGN 0xaa
#define GP2_END_SIGN 0xff
#define GP2_K 0.35
void GP2Report() {
  char bytes[GP2_DATA_BIT_COUNT];
  double value;
  int i;

  delay(1000);
  // find start byte with timeout
  for (i = 0; i < GP2_DATA_BIT_COUNT * 2 && bytes[0] != GP2_START_SIGN; i++) {
    bytes[0] = GP2Serial.read();
  }

  // return and give cpu to other sensors
  if (bytes[0] != GP2_START_SIGN)
    return;

  // read GP2 data
  for (i = 1; i < GP2_DATA_BIT_COUNT; i++) {
    bytes[i] = GP2Serial.read();
  }
  Serial.print("GP2: Data:");
  for (i = 0; i < GP2_DATA_BIT_COUNT; i++) {
    Serial.print(bytes[i], HEX);
    Serial.print(" ");
  }
  Serial.println(".");

  // verify checksum
  if (bytes[5] != bytes[1] + bytes[2] + bytes[3] + bytes[4]) {
    Serial.println("GP2: checksum error");
    return;
  }

  // unit: ug/m^3
  value = GP2_K * 5.0 * ((bytes[1] * 256 + bytes[2]) * 1000.0 / 1024.0);

  Serial.print("GP2: PM2_5=");
  Serial.println(value, 8);
}

void loop() {
  GP2Report();
  DHT22Report();
}
