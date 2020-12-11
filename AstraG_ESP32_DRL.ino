#include <FastLED.h>
#define NUM_LEDS 8
CRGBArray<NUM_LEDS> ledsL;
CRGBArray<NUM_LEDS> ledsR;

#include <WiFi.h>

const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

const int pin1 = 33;
const int pin2 = 25;

WiFiServer server(80);

String header;  

void setup() {
 xTaskCreatePinnedToCore(
      taskLED, 
      "taskLED",
      10000,
      NULL,
      0,
      NULL,
      1);

  xTaskCreatePinnedToCore(
      taskWifi,
      "taskWifi",
      10000,
      NULL,
      0,
      NULL,
      0);
            
  FastLED.addLeds<NEOPIXEL,13>(ledsL, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.addLeds<NEOPIXEL,14>(ledsR, NUM_LEDS).setCorrection(TypicalSMD5050);
  
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
    FastLED.show();
    FastLED.delay(40);
  }
  fill_solid(&(ledsL[0]), 8, CRGB::Black);  
  FastLED.show();
  
  for (int i = 0; i <= NUM_LEDS; i++){
    ledsR[i].setRGB(255, 0, 0);
    if(i > 0){
      ledsR[i-1].setRGB(100, 0, 0);
      if(i > 1){
        ledsR[i-2].setRGB(0, 0, 0);
      }
    }    
    FastLED.show();
    FastLED.delay(40);

    if (i == NUM_LEDS){
      end = true;
      fill_solid(&(ledsL[0]), 8, CRGB::Black);
      FastLED.show();
      }
    } 
  } else if (end == true){
    for (int i = NUM_LEDS; i >= 0; i--){
    ledsR[i].setRGB(255, 0, 0);

    if (i < 8){
      ledsR[i+1].setRGB(100, 0, 0);
      if (i < 7){
        ledsR[i+2].setRGB(0, 0, 0);
        }
      }
    
    FastLED.show();
    FastLED.delay(40);
  }
  fill_solid(&(ledsR[0]), 8, CRGB::Black);
  FastLED.show();

  for (int i = NUM_LEDS; i >= 0; i--){
    ledsL[i].setRGB(255, 0, 0);
    if(i < 8){
      ledsL[i+1].setRGB(100, 0, 0);
      if(i < 7){
        ledsL[i+2].setRGB(0, 0, 0);
        }
      }    
    FastLED.show();
    FastLED.delay(40);

    if (i == 0){
      end = false;
      fill_solid(&(ledsL[0]), 8, CRGB::Black);
      FastLED.show();
      }
    }
  }
}

int rainbowHue = 0;

void rainbow(){    
    fill_rainbow(&(ledsL[0]), 8 , rainbowHue, 10);
    fill_rainbow(&(ledsR[0]), 8 , rainbowHue+100, 10);
    FastLED.show();
    if (rainbowHue >= 255){
      rainbowHue = 0;
      } else{
      rainbowHue = rainbowHue + 20;
      }
    delay(30);
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

void redBlueFlash(){
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
  FastLED.show();
  FastLED.delay(50);
  fill_solid(&(ledsR[0]), 8, CRGB::Black);  
  FastLED.show();
  FastLED.delay(50);
  } 
}
/*****************************************************************************************************************/
void signal(){
  int val1 = digitalRead(pin1);
  int val2 = digitalRead(pin2);

if(val1 == HIGH && val2 == HIGH){ // having problems here
  for(int i = 8, j = 0; i >= 0 && j <= 8; i--, j++){
    ledsR[j] = CRGB:: OrangeRed;
    ledsL[i] = CRGB:: OrangeRed;    
    FastLED.show();    
    FastLED.delay(75);    
  }
  fill_solid(&(ledsR[0]), 8, CRGB(0, 0, 0));
  fill_solid(&(ledsL[0]), 8, CRGB(0, 0, 0));
  FastLED.show(); 
      
} else if (val2 == HIGH){
    for (int i = 0; i < 8; i++){
      ledsR[i].setRGB(255, 50, 0);      
      FastLED.show();
      FastLED.delay(75);
      }
    fill_solid(&(ledsR[0]), 8, CRGB(0, 0, 0));
  FastLED.show();
   
  } else if(val1 == HIGH){
  for (int i = 8; i >= 0; i--)  {
    ledsL[i].setRGB(255, 50, 0);
    FastLED.show();
    FastLED.delay(75);
  }
  fill_solid(&(ledsL[0]), 8, CRGB(0, 0, 0));
  FastLED.show();

  } else if (val1 == LOW && val2 == LOW){
    fill_solid(&(ledsL[0]), 8, CRGB(25, 25, 25));
    fill_solid(&(ledsR[0]), 8, CRGB(25, 25, 25));
    FastLED.show();
  }
}

int modeRGB = 0;

void taskLED(void * parameter){
  while (1){
    switch(modeRGB){
      case 0:
      signal();  
      break;
      case 1:
      white();
      break;
      case 2:
      knightRider();
      break;
      case 3:
      ambient();
      break;
      case 4:
      redBlueFlash();
      break;
      case 5:
      rainbow();
      break;
    }
  }
  vTaskDelete( NULL );
}

void loop(){
   while(1){
     delay(1000);
   }
}
void taskWifi(void * TaskParameters_t){
  while(1){
  WiFiClient client = server.available();

  if (client) {                             
    String currentLine = "";                
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
      //  Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
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
            } else if (header.indexOf("GET /5/") >=0) {
              modeRGB = 5;
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>ESP32 Web Server</h1>");            
                      
            client.println("<p><a href=\"/0/\"><button class=\"button\">OFF</button></a></p>");
            client.println("<p><a href=\"/1/\"><button class=\"button\">White Only</button></a></p>");
            client.println("<p><a href=\"/2/\"><button class=\"button\">Knight Rider</button></a></p>");
            client.println("<p><a href=\"/3/\"><button class=\"button\">Ambient</button></a></p>");
            client.println("<p><a href=\"/4/\"><button class=\"button\">158</button></a></p>");
            client.println("<p><a href=\"/5/\"><button class=\"button\">Rainbow</button></a></p>");
            
            client.println("</body></html>");
            client.println();            
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";    
    client.stop();    
  }
}
}