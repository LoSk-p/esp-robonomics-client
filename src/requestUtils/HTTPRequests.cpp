#include "config.h"
#include "../Utils.h"

#ifdef ROBONOMICS_USE_HTTP

#include <Arduino.h>
#include "HTTPRequests.h"
#ifdef ESP32
#include <HTTPClient.h>
#endif
#ifdef ESP8266
#include <ESP8266HTTPClient.h>
#endif


void HTTPRequests::setup(String host) {
    node_url = "http://" + host + "/rpc/";
}

void HTTPRequests::disconnect() {}

JSONVar HTTPRequests::sendRequest(String message) {
    logMessage("[HTTP]+POST:\n"); 
    JSONVar response;
    HTTPClient http;
    http.begin(wifi_client, node_url.c_str());
    http.addHeader("Content-Type", "application/json");
    uint32_t httpCode = (uint32_t)http.POST(message);
    logMessage("sent: %s", message.c_str());
    if (httpCode > 0) {
        logMessage("[HTTP]+POST code: %ld\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
            const String& payload = http.getString();
            logMessage("received:");
            logMessage(payload.c_str());
            response = JSON.parse(payload);
        } else {
            logMessage("HTTP response is not 200");
        }
    } else {
        logMessage("HTTP response is 0");
    }
    return response;
}

#endif