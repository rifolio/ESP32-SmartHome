#include <WiFi.h>
#include <WebSocketsServer.h>
#include <SPIFFS.h>

// Replace with your network credentials
const char* ssid = "rifolio";
const char* password = "qwerty12345";

// Web server on port 80
WiFiServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// Sensor pins (example GPIOs, adjust as necessary)
const int lightPin = 34;    // Light sensor pin
// const int tempPin = 35;     // Temperature sensor pin (analog)
// const int humidityPin = 36; // Humidity sensor pin (analog)

// Variables to store sensor readings
int lightValue = 0;
int tempValue = 0;
int humidityValue = 0;

// Timing for broadcasting sensor values
unsigned long timer = 0;

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
        webSocket.sendTXT(num, "Connected");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  Serial.println("SPIFFS mounted successfully");

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the HTTP server
  server.begin();

  // Start the WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  // Handle WebSocket events
  webSocket.loop();

  // Handle HTTP client
  WiFiClient client = server.available();   
  if (client) {
    String header = "";
    String currentLine = "";
    String filePath = "/index.html"; // Default file
    bool isGetRequest = false;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Determine the requested file from the GET request
            if (isGetRequest) {
              if (filePath.endsWith("/")) {
                filePath += "index.html"; // Serve index.html for directory request
              }

              // Open the file requested by the client
              File file = SPIFFS.open(filePath, "r");
              if (file) {
                // Send HTTP headers
                client.println("HTTP/1.1 200 OK");
                if (filePath.endsWith(".html")) client.println("Content-type:text/html");
                else if (filePath.endsWith(".css")) client.println("Content-type:text/css");
                else if (filePath.endsWith(".js")) client.println("Content-type:application/javascript");
                client.println("Connection: close");
                client.println();

                // Send the file content to the client
                while (file.available()) {
                  client.write(file.read());
                }
                file.close();
              } else {
                // If the file was not found, send 404
                client.println("HTTP/1.1 404 Not Found");
                client.println("Content-type:text/html");
                client.println("Connection: close");
                client.println();
                client.println("<html><body><h1>404 Not Found</h1></body></html>");
              }
            }
            break;
          } else { // New line detected, check for GET request
            if (currentLine.startsWith("GET ")) {
              isGetRequest = true;
              filePath = currentLine.substring(4, currentLine.indexOf(' ', 4)); // Extract path
              Serial.println("Requested file: " + filePath);
            }
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

  // Read sensor values (simulate with analogRead, replace with actual sensor code)
  lightValue = analogRead(lightPin);

  // Simulated conversion (replace with actual sensor calibration)
  lightValue = map(lightValue, 0, 4095, 0, 1000); // e.g., 0-1000 lux

  // Send sensor data via WebSocket every second
  if (millis() - timer > 1000) {
    String json = "{\"temperature\":" + String(tempValue) +
                  ",\"humidity\":" + String(humidityValue) +
                  ",\"light\":" + String(lightValue) + "}";
    webSocket.broadcastTXT(json);
    // String json = "{\"light\":" + String(lightValue) +"}";
    webSocket.broadcastTXT(json);
    timer = millis();
  }
}