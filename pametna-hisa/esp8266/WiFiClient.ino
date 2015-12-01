#include <ESP8266WiFi.h>

const char* ssid      = "NETGEAR";
const char* password  = "";
const char* host      = "192.168.1.5";

// SETUP PROCEDURE
void setup() {

  Serial.begin(9600);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
} // END PROCEDURE

// LOOP PROCEDURE
void loop() {

  // prepare for sending UART data
  String data = "";

  if (Serial.available() > 0){
    data = Serial.readString();
  }

  if ( data != "") {
    Serial.print("connecting to ");
    Serial.println(host);
          
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 50007;
    
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
          
    Serial.print("Sending data: ");
    //data = "Senzor 1: 109309;Senzor 2: 33;url = Senzor 3: 9000;";
    Serial.print(data);
          
    // This will send the request to the server
    client.print(data);
              
    delay(10);
            
    Serial.println();
    Serial.println("closing connection");    

    delay(1000);
  }

} // END PROCEDURE


