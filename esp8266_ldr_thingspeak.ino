/*  ESP8266 LDR ArduinoIDE Thingspeak IoT Example code
 *
 *  This sketch sends data via HTTP GET requests to api.thingspeak.com of the value on
 *  LDR sensor on ESP8266 development board - Wittyboard. You need an api_key from Thingspeak.
 * 
 *  Based on: https://vaasa.hacklab.fi/2016/02/06/esp8266-on-nodemcu-board-ds18b20-arduinoide-thingspeak/
 *  ESP8266 Witty: http://www.schatenseite.de/en/2016/04/22/esp8266-witty-cloud-module/
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "VaasaHacklab";
const char* pass = "wifikey";

// RGB or button pins are not used in LDR example
#define RED_PIN      7   // RGB Light pin at Arduino pin 3
#define GREEN_PIN    8   // RGB Light pin at Arduino pin 5
#define BLUE_PIN     9   // RGB Light pin at Arduino pin 6
#define BUTTON_PIN   4   // Alert When HIGH button
#define LDR_PIN      A0

char host[] = "api.thingspeak.com";
String ApiKey = "THINGSPEAK_API_KEY";
String path = "/update?key=" + ApiKey + "&field1=";

int ldr_value = 0;

void setup() {

  Serial.begin(115200);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(LDR_PIN, INPUT);

}

void loop() {
  ldr_value = analogRead(LDR_PIN); // read input value and store it
  Serial.println(ldr_value);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  client.print(String("GET ") + path + ldr_value + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n\r\n");
  delay(60000);
}
