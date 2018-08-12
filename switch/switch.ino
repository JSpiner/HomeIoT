#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

int RELAY_PIN = D2;

const char* ssid = "HotSpiner2G";
const char* password = "JSpinerJSpiner1";
ESP8266WebServer server(80);
String s = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, user-scalable=no\"></head><body><br><input type=\"button\" name=\"b1\" value=\"ON\" onclick=\"location.href='/on'\" style=\"width:100%;height:70px;font-weight:bold;font-size:1em\"><br/><input type=\"button\" name=\"b1\" value=\"OFF\" onclick=\"location.href='/off'\" style=\"width:100%;height:80px;font-weight:bold;font-size:1em\"></body></html>";

int state = 0;

void handleRoot() {
  server.send(200, "text/plain", "PST-BKZ-FL: ready");
}

void setup() {
  Serial.begin(115200);

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.print("state : " + state);



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
    digitalWrite(BUILTIN_LED, HIGH);
    digitalWrite(RELAY_PIN, HIGH);
    server.send(200, "text/html", s);
  });

  server.on("/off", []() {
    Serial.println("POWER OFF");
    digitalWrite(BUILTIN_LED, LOW);
    digitalWrite(RELAY_PIN, LOW);
    server.send(200, "text/html", s);
  });

  server.begin();
  Serial.print("HTTP Server started");

}

void loop() {
  server.handleClient();
}
