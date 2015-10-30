#include <Dns.h>
#include <Dhcp.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <util.h>
#include <SPI.h>
#include <stdio.h>

// Pump and light modes
typedef enum {LIGHT_ON, LIGHT_OFF, LIGHT_AUTO, PUMP_ON, PUMP_OFF, PUMP_AUTO} MODES;

// Defines
#define HTTP_OFFSET 5
#define PUMP_PIN PD5
#define TRIAC_TRIG PD6
#define HUMIDITY_SEN_PIN A0
#define LIGHT_SEN_PIN A1
#define TRIAC_ZEROCROSS_INT 1
#define T_HALF_PERIOD (1.0/50/2 * pow(10, 6))
#define TRIAC_TRIGER_DELAY 5
#define PUMP_HUMIDITY_THRESHOLD 100
#define HUMIDITY_AN_DIV 4
#define LIGHT_INTNS_AN_DIV 4
#define LIGHT_AN_MAX_VAL 255
#define LIGHT_AN_MIN_VAL 1
#define NUM_LIGHT_INT_SAMPLES 200

// Modes are set to off at the beginning, meaning that pump and light are off
MODES l_mode = LIGHT_OFF;
MODES p_mode = PUMP_OFF;

const char htmlHeader[] PROGMEM = {"HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\n\n"
                              "<!DOCTYPE HTML>\n<html>\n<head>\n<style type=\"text/css\">\n.boxer{display:table;margin-left:auto;margin-right:auto;width:50%;}.box-row{display: table-row;}\n"
                              "\n.box{display:table-cell;padding:0.5em;text-align:center;}\n.box-spanned{display:table-caption;padding:0.5em;text-align:center;}\n"
                              "</style>\n</head>\n"};
                              
                              
const char htmlLight[] PROGMEM = {"<body>\n<div class=\"boxer\">\n<div class=\"box-spanned\">LIGHT CONTROL</div><div class=\"box-row\"><div class=\"box\">ON</div><div class=\"box\">OFF</div><div class=\"box\">AUTO</div>\n"
                                 "</div><div class=\"box-row\">"};
                                 
const char htmlPump[] PROGMEM = {"</div>\n</div>\n<div class=\"boxer\">\n<div class=\"box-spanned\">PUMP CONTROL</div><div class=\"box-row\">\n<div class=\"box\">ON</div>\n<div class=\"box\">OFF</div>\n<div class=\"box\">AUTO</div>\n</div>"
                                 "<div class=\"box-row\">"};
                                 
const char htmlFoot[] PROGMEM = {"</a></div>\n</div>\n</div>\n</body>\n</html>"};

// Time vars
unsigned long triacZeroCrossTime, triacTriggerTime;

// Mac
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Ip
IPAddress ip;
char str_ip[24];

// Light intensity
uint16_t lightIntensity = 255;

// Server
EthernetServer server(80);


void setup(){

  // Set pin modes and interrupt
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(TRIAC_TRIG, OUTPUT);
  // Set interrupt
  attachInterrupt(TRIAC_ZEROCROSS_INT, isr, RISING);
  // Init serial
  Serial.begin(9600);
  // Init server
  Ethernet.begin(mac); // Dhcp request
  server.begin();
  // Save ip
  ip = Ethernet.localIP();
  // Convert ip to char array
  sprintf(str_ip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
  // Print IP
  Serial.print("My ip: ");
  Serial.println(ip);
  
}

void loop(){
  
  // listen for incoming clients
  EthernetClient client = server.available();

  if(client){
    
    // Temp buffer
    String buffer = "";
    // Request number
    short requestNumber;
    // Temp for char
    char chr;
    
    while(client.available() && buffer.length() < 100){
    
      if((chr = client.read()) == '\0')
        break;
      buffer +=chr;
    }
    
    // Parse message
    requestNumber = parseHttp(buffer);

    // Set modes
    if(requestNumber >= LIGHT_ON && requestNumber <= LIGHT_AUTO)
      l_mode = (MODES)requestNumber;
    else if(requestNumber >= PUMP_ON && requestNumber <= PUMP_AUTO)
      p_mode = (MODES)requestNumber;
      
    // Turn on/off light/pump
    if(requestNumber == LIGHT_ON)
      lightIntensity = LIGHT_AN_MIN_VAL;
    else if(requestNumber == LIGHT_OFF)
      lightIntensity = LIGHT_AN_MAX_VAL;
    else if(requestNumber == PUMP_ON)
      digitalWrite(PUMP_PIN, HIGH);
    else if(requestNumber == PUMP_OFF)
      digitalWrite(PUMP_PIN, LOW);
      
    // Send response
    sendHttpResponse(client);
    
    // Close connection
    client.stop();
   
  }
  
  // Check time and trigger triac
  if(micros() - triacZeroCrossTime >= ((double)lightIntensity / LIGHT_AN_MAX_VAL) * T_HALF_PERIOD - TRIAC_TRIGER_DELAY){
    PORTD |= _BV(TRIAC_TRIG);
    triacZeroCrossTime = triacZeroCrossTime + 1000000;
    if(l_mode == LIGHT_AUTO)
      lightIntensity = getLightIntensity() / LIGHT_INTNS_AN_DIV;
  }
  
  // Check time and turn off base on triac
  if(micros() - triacTriggerTime >= TRIAC_TRIGER_DELAY){
    digitalWrite(TRIAC_TRIG, LOW);
    PORTD &= ~_BV(TRIAC_TRIG);
    triacTriggerTime = triacTriggerTime + 1000000;
  }

  // Pump modes
  if(p_mode == PUMP_AUTO){
    if(getSoilHumidity() / HUMIDITY_AN_DIV > PUMP_HUMIDITY_THRESHOLD)
      PORTD &= ~_BV(PUMP_PIN);
    else
      PORTD |= _BV(PUMP_PIN);
  }
  
}

short parseHttp(String msg){
  
  short index_q = msg.indexOf("?");
  short index_eq = msg.indexOf("=");
  short requestNumber = -1;
  
  if(index_q < index_eq && msg.substring(index_q + 1, index_eq).equals("mode")){
    short msg_i = index_eq + 1;

    while(msg_i < msg.length()){
      char chr = msg.charAt(msg_i);
      
      // Check if a char is a digit
      if(chr >= 48 && chr <= 57){
        if(requestNumber < 0)
          requestNumber = 0;
        // Convert char digit to number. Then sum it with requestnumber var
        requestNumber = requestNumber * 10 + chr - '0';
      }
      else
        break; // End of a number sequence
     
      msg_i++;
      
    }
    
  }
  
  return requestNumber;
  
}

inline short getLightIntensity(){
  
  static short lightIntensities[NUM_LIGHT_INT_SAMPLES];
  static long sum = 0;
  static uint8_t firstElement;
  short currentIntensity;
  
  // Get current light intensity as an analog value
  currentIntensity = analogRead(LIGHT_SEN_PIN);
  // Add it to the sum of previous elements. At the same time, we should remove element, which has a position current position - NUM_LIGHT_INT_SAMPLES on an infinity length track
  sum = sum - lightIntensities[firstElement] + currentIntensity;
  // Save current element in the table
  lightIntensities[firstElement] = currentIntensity;
  // Set table index to zero if at the end of the table
  firstElement = (firstElement + 1) % (NUM_LIGHT_INT_SAMPLES - 1);
  // Return average
  return sum / NUM_LIGHT_INT_SAMPLES;
  
}

unsigned short getSoilHumidity(){
  return analogRead(HUMIDITY_SEN_PIN);
  
}

void sendHttpResponse(EthernetClient client){
    unsigned short i;
    
    // Css and head
    for(i = 0; i < strlen_P(htmlHeader); i++)
      client.print((char)pgm_read_byte_near(htmlHeader + i));
    // part of the light html
    for(i = 0; i < strlen_P(htmlLight); i++)
      client.print((char)pgm_read_byte_near(htmlLight + i));
    // Light on
    client.println("<div class=\"box\">");
    client.print("<a href = \"http://");client.print(ip);client.print("/control?mode=0");
    client.print("\"><img src = \"https://cdn0.iconfinder.com/data/icons/super-mono-reflection/");client.print(l_mode == LIGHT_ON ? "green/button-power_green.png\" />" : "red/button-power_red.png\" />");
    client.println("</a></div>");
    // Light off
    client.println("<div class=\"box\">");
    client.print("<a href = \"http://");client.print(ip);client.print("/control?mode=1");
    client.print("\"><img src = \"https://cdn0.iconfinder.com/data/icons/super-mono-reflection/");client.print(l_mode == LIGHT_OFF ? "green/button-power_green.png\" />" : "red/button-power_red.png\" />");
    client.println("</a></div>");
    // Light auto
    client.println("<div class=\"box\">");
    client.print("<a href = \"http://");client.print(ip);client.print("/control?mode=2");
    client.print("\"><img src = \"https://cdn0.iconfinder.com/data/icons/super-mono-reflection/");client.print(l_mode == LIGHT_AUTO ? "green/button-power_green.png\" />" : "red/button-power_red.png\" />");
    client.println("</a></div>");
    
    // Part of the pump html
    for(i = 0; i < strlen_P(htmlPump); i++)
      client.print((char)pgm_read_byte_near(htmlPump + i));
    // Pump on
    client.println("<div class=\"box\">");
    client.print("<a href = \"http://");client.print(ip);client.print("/control?mode=3");
    client.print("\"><img src = \"https://cdn0.iconfinder.com/data/icons/super-mono-reflection/");client.print(p_mode == PUMP_ON ? "green/button-power_green.png\" />" : "red/button-power_red.png\" />");
    client.println("</a></div>");
    // Pump off
    client.println("<div class=\"box\">");
    client.print("<a href = \"http://");client.print(ip);client.print("/control?mode=4");
    client.print("\"><img src = \"https://cdn0.iconfinder.com/data/icons/super-mono-reflection/");client.print(p_mode == PUMP_OFF ? "green/button-power_green.png\" />" : "red/button-power_red.png\" />");
    client.println("</a></div>");
    // Pump auto
    client.println("<div class=\"box\">");
    client.print("<a href = \"http://");client.print(ip);client.print("/control?mode=5");
    client.print("\"><img src = \"https://cdn0.iconfinder.com/data/icons/super-mono-reflection/");client.print(p_mode == PUMP_AUTO ? "green/button-power_green.png\" />" : "red/button-power_red.png\" />");
    // Sensors
    
    // Html footer
    for(i = 0; i < strlen_P(htmlFoot); i++)
      client.print((char)pgm_read_byte_near(htmlFoot + i));
}

void isr(){
  
  // Capture current time
  triacZeroCrossTime = triacTriggerTime = micros();

}
