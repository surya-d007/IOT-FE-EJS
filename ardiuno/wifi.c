#include <ESP8266WiFi.h>

const char* ssid = "Xiaomi 11i"; // Replace with your WiFi SSID
const char* password = "123456789012"; // Replace with your WiFi password
const char* serverAddress = "192.168.91.172"; // Replace with your computer's IP address
const int serverPort = 5000; // Port where your Flask server is running

void setup() {
  Serial.begin(9600); // Initialize serial communication
  delay(1000); // Wait for serial monitor to open
  WiFi.begin(ssid, password); // Connect to Wi-Fi network
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
}

String accumulatedData = ""; // Global variable to accumulate data

void sendDataToServer(String data) {
  WiFiClient client;
  
  if (client.connect(serverAddress, serverPort)) {
    client.print("POST /receiveData HTTP/1.1\r\n");
    client.print("Host: ");
    client.print(serverAddress);
    client.print("\r\n");
    client.print("Content-Type: text/plain\r\n");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\r\n\r\n");
    client.print(data);
    client.stop();
    Serial.println("Data sent to server");
  } else {
    Serial.println("Connection to server failed");
  }
}

void loop() {
  if (Serial.available()) { // If there is data available from Arduino Uno
    String dataReceived = Serial.readStringUntil('\n'); // Read the data
    accumulatedData += dataReceived + "\n"; // Accumulate the data
  }
  
  // Check if accumulated data is complete (e.g., received the complete line)
  if (accumulatedData.endsWith("\n")) {
    // Send the accumulated data to the server
    sendDataToServer(accumulatedData);
    // Clear accumulated data for the next iteration
    accumulatedData = "";
  }

  delay(100);
}