#include <FastLED.h>
#define NUM_LEDS 8
CRGBArray<NUM_LEDS> ledsL;
CRGBArray<NUM_LEDS> ledsR;
// Load Wi-Fi library
#include <WiFi.h>
// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

const int pin1 = 33;
const int pin2 = 25;



// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state

  

//core1
void setup() {
 xTaskCreatePinnedToCore(
      taskLED, /* Function to implement the task */
      "taskLED", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      2,  /* Priority of the task */
      NULL,
      1);  /* Task handle. */

  xTaskCreatePinnedToCore(
      taskWifi, /* Function to implement the task */
      "taskWifi", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      NULL,
      0);  /* Task handle. */
      
      
  FastLED.addLeds<NEOPIXEL,13>(ledsL, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL,14>(ledsR, NUM_LEDS);
  
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);

  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  
 server.begin();
}
bool end = false;
void knightRider(){  
  if(end == false){
  for (int i = 0; i <= NUM_LEDS; i++){
    ledsL[i].setRGB(255, 0, 0);
    if (i > 0){
      ledsL[i-1].setRGB(100, 0, 0);
      if (i > 1){
        ledsL[i-2].setRGB(0, 0, 0);
      }      
    }
    FastLED.delay(1);
    FastLED.show();
    FastLED.delay(40);    
    
    
  }
  fill_solid(&(ledsL[0]), 8, CRGB::Black);
  FastLED.delay(1);
  FastLED.show();
  //FastLED.showColor(CRGB::Black, 100);
  for (int i = 0; i <= NUM_LEDS; i++){
    ledsR[i].setRGB(255, 0, 0);
    if(i > 0){
      ledsR[i-1].setRGB(100, 0, 0);
      if(i > 1){
        ledsR[i-2].setRGB(0, 0, 0);
      }
    }
    FastLED.delay(1);
    FastLED.show();
    FastLED.delay(40);
    if (i == NUM_LEDS){
      end = true;
      fill_solid(&(ledsL[0]), 8, CRGB::Black);
      FastLED.delay(1);
      FastLED.show();
    }
  }
  

  } else if (end == true)
  {
    for (int i = NUM_LEDS; i >= 0; i--){
    ledsR[i].setRGB(255, 0, 0);
    if (i < 8)
    {
      ledsR[i+1].setRGB(100, 0, 0);
      if (i < 7)
      {
        ledsR[i+2].setRGB(0, 0, 0);
      }
      
    }
    FastLED.delay(1);
    FastLED.show();
    FastLED.delay(40);
    
  }
  fill_solid(&(ledsR[0]), 8, CRGB::Black);
  FastLED.delay(1);
  FastLED.show();
  for (int i = NUM_LEDS; i >= 0; i--){
    ledsL[i].setRGB(255, 0, 0);
    if(i < 8){
      ledsL[i+1].setRGB(100, 0, 0);
      if(i < 7){
        ledsL[i+2].setRGB(0, 0, 0);
      }
    }
    FastLED.delay(1);
    FastLED.show();
    FastLED.delay(40);
    if (i == 0){
      end = false;
      fill_solid(&(ledsL[0]), 8, CRGB::Black);
      FastLED.delay(1);
      FastLED.show();
    }
  }

  }
}

void white(){
  fill_solid(&(ledsL[0]), 8, CRGB(25, 25, 25));
  fill_solid(&(ledsR[0]), 8, CRGB(25, 25, 25));
  FastLED.show();
}
void off(){
  fill_solid(&(ledsL[0]), 8, CRGB(0, 0, 0));
  fill_solid(&(ledsR[0]), 8, CRGB(0, 0, 0));
  FastLED.show();
}

void ambient(){
  fill_solid(&(ledsL[0]), 8, CRGB(50, 15, 0));
  fill_solid(&(ledsR[0]), 8, CRGB(50, 15, 0));
  FastLED.show();
}

void illegal(){
  for (int i = 0; i <= 2; i++){
  fill_solid(&(ledsL[0]), 8, CRGB::Blue);

  FastLED.show();
  FastLED.delay(50);
  fill_solid(&(ledsL[0]), 8, CRGB::Black);
  FastLED.show();
  FastLED.delay(50);
  }
  delay(10);
  for (int i = 0; i <= 2; i++){
  fill_solid(&(ledsR[0]), 8, CRGB::Red);
  FastLED.delay(1);
  FastLED.show();
  FastLED.delay(50);
  fill_solid(&(ledsR[0]), 8, CRGB::Black);
  FastLED.delay(1);
  FastLED.show();
  FastLED.delay(50);
  } 
}
int temp1 = 8;
int temp2 = 0;
void signal(){
  int val1 = digitalRead(pin1);
  int val2 = digitalRead(pin2);
if(val1 == HIGH & val2 == HIGH){
      ledsL[temp1].setRGB(255, 50, 0);
      ledsR[temp2].setRGB(255, 50, 0);
      temp1 = temp1 - 1;
      temp2 = temp2 + 1;
      FastLED.delay(1);
      FastLED.show();
      FastLED.delay(50);
      if (temp1 == 0)
      {
        temp1 = 8;
        temp2 = 0;
      }

}
  else if (val2 == HIGH){
    for (int i = 0; i < 8; i++)
    {
      ledsR[i].setRGB(255, 50, 0);
      FastLED.delay(1);
    FastLED.show();
    FastLED.delay(75);
    }
    fill_solid(&(ledsR[0]), 8, CRGB(0, 0, 0));
    FastLED.delay(1);
  FastLED.show();
   
  } else if(val1 == HIGH){
  for (int i = 8; i >= 0; i--)
  {
    ledsL[i].setRGB(255, 50, 0);
    FastLED.delay(1);
    FastLED.show();
    FastLED.delay(75);
  }
  fill_solid(&(ledsL[0]), 8, CRGB(0, 0, 0));
  FastLED.delay(1);
  FastLED.show();
  } else if (val1 == LOW && val2 == LOW){
    fill_solid(&(ledsL[0]), 8, CRGB(25, 25, 25));
    fill_solid(&(ledsR[0]), 8, CRGB(25, 25, 25));
    FastLED.delay(1);
    FastLED.show();
  }
}

int modeRGB = 0;
bool lightsOff = true;
void taskLED(void * parameter){
  while (1)
  {
    if(lightsOff == true){
      signal();
    }
    switch(modeRGB){
      case 0:
      off();
      lightsOff = true;
      break;
      case 1:
      white();
      lightsOff = false;
      break;
      case 2:
      knightRider();
      lightsOff = false;
      break;
      case 3:
      ambient();
      lightsOff = false;
      break;
      case 4:
      illegal();
      lightsOff = false;
      break;
    }
  }
  vTaskDelete( NULL );
}


//core1
void loop(){
   while(1){
     delay(1000);
   }
}
void taskWifi(void * TaskParameters_t){
  while(1){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
      //  Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /0/") >= 0) {
              modeRGB = 0;
            } else if (header.indexOf("GET /1/") >= 0) {
             modeRGB = 1;
            } else if (header.indexOf("GET /2/") >=0) {
              modeRGB = 2;              
            } else if (header.indexOf("GET /3/") >=0) {
              modeRGB = 3;
            } else if (header.indexOf("GET /4/") >=0) {
              modeRGB = 4;
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");            
                      
            client.println("<p><a href=\"/0/\"><button class=\"button\">OFF</button></a></p>");
            client.println("<p><a href=\"/1/\"><button class=\"button\">White Only</button></a></p>");
            client.println("<p><a href=\"/2/\"><button class=\"button\">Knight Rider</button></a></p>");
            client.println("<p><a href=\"/3/\"><button class=\"button\">Ambient</button></a></p>");
            client.println("<p><a href=\"/4/\"><button class=\"button\">158</button></a></p>");
            
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    
    client.stop();
    
  }
}
}