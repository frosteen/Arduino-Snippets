#include <ESP8266WiFi.h>

String api_key = "JVOJ47D2HFZOHYKJ";
const char *ssid = "PLDTMyDSL";
const char *password = "pldtwifiB4489";
const char *server = "api.thingspeak.com";

WiFiClient client;

void setup()
{
  Serial.begin(9600);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.disconnect();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.println("Connecting...");
  }

  Serial.println("WiFi connected");
}

void loop()
{
  if (client.connect(server, 80))
  {
    String post_string = api_key;
    post_string += "&field1=";
    post_string += String(11);
    post_string += "&status=";
    post_string += "LOW";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(post_string.length());
    client.print("\n\n");
    client.print(post_string);
  }

  client.stop();

  Serial.println("Waiting…");

  delay(15000);
}
