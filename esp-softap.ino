/* This code sets up a simple HTTP server using the ESP8266 microcontroller and the ESP8266WebServer library. 
The code creates a WiFi access point with the SSID "ESP-SoftAP" and a password "thereisnospoon". 
When a client connects to the access point and browses to http://192.168.4.1, the handleRoot function sends a 
response with the text "You are connected". The server starts listening on port 80 and waits for incoming 
client connections. The loop function handles incoming client requests and responses. */

/* Including the libraries */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "ESP-SoftAP"
#define APPSK "thereisnospoon"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  //WiFi.softAP(ssid, NULL, 1);
  WiFi.softAP(ssid, password, 1);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
