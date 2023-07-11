/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-http-request
 */

#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Connect your yellow pin to Pin12 on Arduino
#define ONE_WIRE_BUS 8

// replace the MAC address below by the MAC address printed on a sticker on the Arduino Shield 2
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "POST"; 
char   HOST_NAME[] = "url";


String postData;
String postVariable = "tub=";


String postData2;
String postVariable2 = "& ph=";

String postData3;
String postVariable3 = "& temp=";

String review;
int sensorValue2;
int sensorValue;


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
 /// Serial.begin(9600);
 
sensors.begin();
  
}
void loop() {


   sensors.requestTemperatures(); 
  
  
  float deg = sensors.getTempCByIndex(0); 
  

 int sensorValue2 = 1024 - analogRead(A2);
 float tub2 = sensorValue2 * (5.0 / 1024.0);
 float tub3 = sensorValue2 * (100 / 1024.0);
  float tub =tub3-20;
 

 int sensorValue = analogRead(A0);
 float ph2 = sensorValue * (5.0 / 1024.0);
 float ph3 = sensorValue * (14.0 / 1024.0);
 float ph = ph3-3;

 float sensorData1= ph ;
 float sensorData2 = tub;
 float sensorData3 = deg;
  
  postData = postVariable + sensorData2;
  postData2 = postVariable2 + sensorData1;
   postData3 = postVariable3 +sensorData3;

  review = (postVariable+sensorData1 + postVariable2+sensorData2 + postVariable3+sensorData3);

  // initialize the Ethernet shield using DHCP:
  if (Ethernet.begin(mac) == 0) {
    ///Serial.println("Failed to obtaining an IP address using DHCP");
    while(true);
  }

  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    ///Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println("POST /r-rita/sensor.php HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));

    //client.println("Connection: close");
   // client.println(); // end HTTP header


  
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(review.length());
    client.println();
    client.print(review);
    delay (4000);
   
    ///Serial.println("Email Sent");




    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        ///Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
   ///Serial.println();
   /// Serial.println("disconnected");
  } else {// if not connected:
   // Serial.println("connection failed");
  }
}