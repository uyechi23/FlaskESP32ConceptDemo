// include libraries - WiFi.h
#include <WiFi.h>

// define the pin that the potentiometer is attached to
#define POT_PIN 33

// SSID - the Wi-Fi network's name
// Password - the Wi-Fi network's password
const char* ssid     = "UPIoT";
const char* password = "";

// host - the main URL of the webpage you want to connect to; you can use the IP address of a Flask app
const char host[] = "http://10.13.135.141:5000";
const byte flaskappip[4] = {10, 13, 135, 141};

// port - the port of the flask app
const int port = 5000;

// url - the route of your app to connect to
const String url = "/potentiometer/esp32/";
    
// WiFiClient - a struct that contains relevant Wi-Fi data
WiFiClient client;

void setup() {
  // initialize Serial communication
  Serial.begin(115200);

  // potentiometer setup
  pinMode(POT_PIN, INPUT);

  // Wi-Fi setup

  // begin the Wi-Fi connection
  WiFi.begin(ssid, password);

  // pending Wi-Fi connection...
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // notify the Serial monitor when the Wi-Fi connection is a success
  // display the device's IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    // read potentiometer value and convert it to a percentage
    int pot_value = analogRead(POT_PIN);
    double pot_percentage = (double(pot_value))/(double(4095.0))*100;
    
    // connect to the client using the IP address and Port of the Flask App
    // set these values above - they can be found when running the Flask application
    if(client.connect(flaskappip, port)){    
      // send an HTTPS GET request
      client.print(String("GET ") + url + String(pot_percentage) + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "Connection: close\r\n\r\n");
    }else{
      // failure message
      Serial.println("Failed to connect...");
    }
    
    // timeout loop
    unsigned long timeout = millis();
      while (client.available() == 0) {
        // if 5 seconds pass, stop the client due to timeout issue
        if (millis() - timeout > 5000) {
          Serial.println(">>> Client Timeout !");
          client.stop();
          return;
        }
    }
    
    // while the client is available, print out the returned data
    // after the while loop, line will contain just the last line of data
    // from Flask, this last line is what's put in the return statement
    String line = "";
    while (client.available()) {
      // read the client's response line-by-line
      line = client.readStringUntil('\r');
    }

    // print out the data
    Serial.print("The average value is: ");
    Serial.print(line);
    Serial.println("%");
    
    // delay 5 seconds; sensors can be implemented on a "polling" basis
    // so the Flask app continuously gets real-time data
    delay(5000);
}
