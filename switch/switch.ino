#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>

const int RELAY_PIN = D2;

const char* SSID = "HotSpiner2G";
const char* PASSWORD = "JSpinerJSpiner1";
ESP8266WebServer server(80);

void setupPin() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void setupServer() {
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(WiFi.status());
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  requestInit(WiFi.localIP().toString());

  routeGetOn();
  routeGetOff();

  server.begin();
  Serial.print("HTTP Server started");
}

void requestInit(String ipAddress) {
  HTTPClient http;
  http.begin("http://jsonplaceholder.typicode.com/users/1");
  int httpCode = http.GET();
  String result = http.getString();
  Serial.print("status code : " );
  Serial.println(httpCode);
  Serial.print("result : " );
  Serial.println(result);
  Serial.println("end");
  http.end();
}

void routeGetHealth() {
  server.on("/health", []() {
    Serial.println("health check");
    server.send(200, "text/html", "ok");
  });
}

void routeGetOn() {
  server.on("/on", []() {
    Serial.println("POWER ON");
    digitalWrite(RELAY_PIN, HIGH);
    server.send(200, "text/html", "ok");
  });
}

void routeGetOff() {
  server.on("/off", []() {
    Serial.println("POWER OFF");
    digitalWrite(RELAY_PIN, LOW);
    server.send(200, "text/html", "ok");
  });
}

void setup() {
  setupPin();
  setupServer();
}

void loop() {
  server.handleClient();
}
