#include <ESP8266WiFi.h>
#include <stdio.h>
#include <string.h>

const char* ssid = "NETGEAR";
const char* password = "";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(50007);

// SETUP PROCEDURE
void setup() {
  Serial.begin(9600);
  delay(10);
  
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started, IP address:");

  // Print the IP address
  Serial.println(WiFi.localIP());
} // END PROCEDURE

// LOOP PROCEDURE
void loop() {
  String data = "";
  char seps[] = ";";
  char *token1, *token2, *token3, *token4;
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("NEW CLIENT");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);    // M=Motion, L=Loudness, T=Temperature, H=Humidity
  client.flush();
  
  // Send the response to the client
  // prepare for sending UART data    
  if (Serial.available() > 0){
    data = Serial.readString();    
    token1 = strtok(const_cast<char*>(data.c_str()), seps); 
    int i=1;

    while( i<5 ){      
        /* Get next token: */
        if (i==2) token2 = token1;
        if (i==3) token3 = token1;
        if (i==4) token4 = token1;   
        token1 = strtok( NULL, seps );      
        i++;
    }
  }

  if (req == "M"){
    client.print(token1);
  }
  else if (req == "L"){
    client.print(token2);
  }
  else if (req == "T"){
    client.print(token3);
  }
  else if (req == "H"){
    client.print(token4);
  }
  delay(1);
  Serial.println("Client disonnected");
  delay(1000);
  // The client will actually be disconnected 
  // when the function returns and 'client' object is destroyed
} // END PROCEDURE

