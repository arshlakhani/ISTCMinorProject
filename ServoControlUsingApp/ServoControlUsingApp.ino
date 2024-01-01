#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32_Servo.h>

const char *ssid = "ConForNode";
const char *password = "12345678";


Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
Servo myServo5;
Servo myServo6;

#define servo1pin 16
#define servo2pin 17
#define servo3pin 18
#define servo4pin 19
#define servo5pin 21
#define servo6pin 22
AsyncWebServer server(80);
void handleRequest(AsyncWebServerRequest *request) {
    // Get the value of the 'Id' parameter from the URL
    String idValue = "N/A";
    if (request->hasParam("Id")) {
        idValue = request->getParam("Id")->value();
    }

    // Get the value of the 'value' parameter from the URL
    String valueValue = "N/A";
    if (request->hasParam("value")) {
        valueValue = request->getParam("value")->value();
    }
-
    // Print the extracted values to Serial Monitor
    Serial.print("Id: ");
    Serial.println(idValue);
    Serial.print("value: ");
    Serial.println(valueValue);
    
    valueValue = round(valueValue.toFloat());
    int id_t = idValue.toInt();
    switch (id_t){
      case 1:
        myServo1.write(valueValue.toInt());
        Serial.println(idValue +"Servo set at " + valueValue);
        break;

      case 2:
        myServo2.write(valueValue.toInt());
        Serial.println(idValue +"Servo set at " + valueValue);
        break;
      case 3:
        myServo3.write(valueValue.toInt());
        Serial.println(idValue +"Servo set at " + valueValue);
        break;
      case 4:
        myServo4.write(valueValue.toInt());
        Serial.println(idValue +"Servo set at " + valueValue);
        break;
      case 5:
        myServo5.write(valueValue.toInt());
        Serial.println(idValue +"Servo set at " + valueValue);
        break;
      case 6:
        myServo6.write(valueValue.toInt());
        Serial.println(idValue +"Servo set at " + valueValue);
        break;
      default:
        break;
    }
    // Respond with the extracted values
    String response = "Id: " + idValue + ", value: " + String(valueValue.toInt());
    request->send(200, "text/plain", response);
}

void setup() {
  Serial.begin(115200);

  myServo1.attach(servo1pin);
  myServo2.attach(servo2pin);
  myServo3.attach(servo3pin);
  myServo4.attach(servo4pin);
  myServo5.attach(servo5pin);
  myServo6.attach(servo6pin);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print(WiFi.localIP());

  // Define and handle web server routes
  server.on("/greet", HTTP_GET, handleRequest);

  

  server.begin();
}

void loop() {
  // Your code here
}

