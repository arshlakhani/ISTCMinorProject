#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32_Servo.h>

const char *ssid = "ConForNode";
const char *password = "12345678";

const int servoPin = 26;  // GPIO pin where the servo signal wire is connected
Servo myServo;

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

    // Print the extracted values to Serial Monitor
    Serial.print("Id: ");
    Serial.println(idValue);
    Serial.print("value: ");
    Serial.println(valueValue);

    // Respond with the extracted values
    String response = "Id: " + idValue + ", value: " + valueValue;
    request->send(200, "text/plain", response);
}

void setup() {
  Serial.begin(115200);

  myServo.attach(servoPin);

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

