#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

int RELAY_PIN = D2;

const char* ssid = "HotSpiner2G";
const char* password = "JSpinerJSpiner1";
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "PST-BKZ-FL: ready");
}

void setupPin() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void setup() {
  setupPin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.on("/on", []() {
    Serial.println("POWER ON");
    digitalWrite(RELAY_PIN, HIGH);
    server.send(200, "text/html", "ok");
  });

  server.on("/off", []() {
    Serial.println("POWER OFF");
    digitalWrite(RELAY_PIN, LOW);
    server.send(200, "text/html", "ok");
  });

  server.begin();
  Serial.print("HTTP Server started");

}

void loop() {
  server.handleClient();
}
