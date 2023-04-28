/* This code sets up a simple HTTP server using the ESP8266 microcontroller and the ESP8266WebServer library. 
The code creates a WiFi access point with the SSID "ESP-SoftAP" and a password "thereisnospoon". 
When a client connects to the access point and browses to http://192.168.4.1, the handleRoot function sends a 
response with the text "You are connected". The server starts listening on port 80 and waits for incoming 
client connections. The loop function handles incoming client requests and responses. */

// Including the libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/*
The code receives three inputs from the user, namely APSSID, APPSK, and CHANNEL. 
APSSID represents the name of the WiFi network that the NodeMCU Soft Access Point will broadcast. 
APPSK is the password for the network; if it's left empty, devices can connect to the network without a password. 
CHANNEL specifies the WiFi channel that we want to use, with available options ranging from 1 to 13 (1 being the default channel).
*/
#ifndef APSSID
#define APSSID "ESP-SoftAP"
#define APPSK "thereisnospoon"
#define CHANNEL 1
#endif

// Set these to your desired credentials.
const char *ssid = APSSID;
const char *password = APPSK;
const int *channel = CHANNEL;

/*
We are setting up an ESP8266 web server that will allow for data to be delivered to all connected devices.
Webserver port is set to 80
*/
ESP8266WebServer server(80);

/* 
To provide information to devices that connect to NodeMCU's WiFi, a function named handleRoot() is defined. 
This function delivers a message to the devices and can be accessed by entering the IP address 192.168.4.1 in the web browser. 
The message is usually enclosed in HTML tags, such as <h1>You are connected</h1>. 
The message is sent to the devices using the Webserver's send() function.
*/
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /*
  The ESP8266WiFi.h library provides the built-in function WiFi.softAP() which can take up to five parameters. 
  The first parameter is the name of the WiFi, which is the SSID. The second parameter is the pre-shared key (PSK), which is the password of the WiFi. 
  The third parameter is the WiFi channel. The fourth parameter, which is called hidden, is set to true if we want to hide the SSID (name) 
  of the WiFi from other devices. The fifth parameter, max-connections, lets us set the maximum number of devices that can connect to the WiFi. 
  In this code, we have used only the first three parameters. 
  You can find the list of methods in the ESP8266WebServer.h library at these links: 
  https://links2004.github.io/Arduino/d3/d58/class_e_s_p8266_web_server.html and,
  https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer.
  */
  WiFi.softAP(ssid, password, channel);
  // You can remove the password parameter if you want Soft-AP to be open.
  // WiFi.softAP(ssid, NULL, channel);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  /*
  After establishing the WiFi connection, we can use the on() function of the Webserver to send a message to all the connected devices. 
  We can pass the handleRoot() function as a parameter to the on() function for this purpose.
  */
  server.on("/", handleRoot);
  
  /*
  server.begin() Starts the server
  */
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
