#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266httpUpdate.h>
#include <Streaming.h>
#include "secrets.h"

const char* url = "https://raw.githubusercontent.com/SembeiNorimaki/esp8266_test/master/Blink.bin";
const char* host = "raw.githubusercontent.com";
const int httpsPort = 443;

const char* ssid = STASSID;     // from secrets.h
const char* password = STAPSK;  // from secrets.h

void connect_wifi() {
    Serial << "\nConnecting to " << ssid;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial << ".";
    }
    Serial << "\nConnected. IP address: " << WiFi.localIP() << "\n";
}

WiFiClientSecure connect_to_host() {
    WiFiClientSecure client;
    Serial << "Connecting to " << host << "\n";
    Serial << "Using fingerprint " << fingerprint << "\n";
    client.setFingerprint(fingerprint);

    if (!client.connect(host, httpsPort)) {
        Serial << "Connection failed" << "\n";
    }
    return client;
}

void setup() {
    Serial.begin(115200);    
    connect_wifi();
    WiFiClientSecure client = connect_to_host();   // connect to github client    
    t_httpUpdate_return ret = ESPhttpUpdate.update(client, url);  // flash esp8266 using the bin file in the url
}

void loop() {
}
