// Device Details
#define BLYNK_TEMPLATE_ID "TMPLpQvLWDf_"
#define BLYNK_DEVICE_NAME "Design Misting"
#define BLYNK_AUTH_TOKEN "38_nnjkDxoAsPEVSyIkVBa096y_YFu7y"

// Libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "PAMBID_WIFI_2.4GHz";
char pass[] = "PAMBID142528!";

void setup()
{
  // Debug serial monitor
  Serial.begin(9600);

  // Blynk begin
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();

  // Write to V1
  Blynk.virtualWrite(V1, millis() / 1000);
}

// Execute when V0 changes
BLYNK_WRITE(V0)
{
  Serial.println(param.asInt());
}

// Execute once connected to network
BLYNK_CONNECTED()
{
  // Execute all BLYNK_WRITE functions
  // BLYNK_WRITE functions parameters
  // such as V1, V2, ... must Enable "Sync with latest server value every time device connects to the cloud"
  Blynk.syncAll();

  // Execute BLYNK_WRITE(V0)
  Blynk.syncVirtual(V0);
}
