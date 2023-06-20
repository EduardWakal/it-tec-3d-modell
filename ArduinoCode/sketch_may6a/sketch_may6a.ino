#ifndef BOARD_HAS_PSRAM
#error "Bitte aktivieren Sie PSRAM !!!"
#endif

// Einbindung der notwendigen Bibliotheken
#include <Arduino.h>
#include <cstdint>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "epd_driver.h"
#include "esp_adc_cal.h"
#include <FS.h>
#include <SPI.h>
#include <SD.h>
#include "font/firasans.h"
#include "pins.h"
#define NULL 0

#if defined(T5_47_PLUS)
#include "pcf8563.h"
#include <Wire.h>
#endif

// Instanzierung der Real Time Clock (RTC) falls das Display T5_47_PLUS verwendet wird
#if defined(T5_47_PLUS)
PCF8563_Class rtc;
#endif

// Anmeldedaten für das WLAN
const char* ssid = "";
const char* password =  "";

// Daten zur Verbindung mit dem Server
char server[] = "192.168.247.213"; 
String endpoint = "/read-data";
int port = 3000;

// Instanzierung des WiFi- und HttpClient
WiFiClient wifiClient;
HttpClient client = HttpClient(wifiClient, server, port);

// Deklaration von Variablen für Spannungsreferenz, Statuscode, Drucktext, Sitzungs-ID und Koordinaten auf dem Display
int vref = 1100;
int statusCode = 0;
int cursor_x = 200;
int cursor_y = 250;
char* print = "Test result";
const char* sessionId;

// Funktion zum Abrufen des Stundenplans
void getTimetable(){
  // HTTP-GET Anfrage
  client.get("/read-data");
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  // Ausgabe von Statuscode und Antwort
  Serial.print("Statuscode: ");
  Serial.println(statusCode);
  Serial.print("Antwort: ");
  Serial.println(response);

  // Erstellen des JSON-Dokuments
  DynamicJsonDocument doc(ESP.getMaxAllocHeap());

  // Deserialisieren des JSON-Dokuments
  DeserializationError error = deserializeJson(doc, response);

  // Überprüfen, ob das Parsen erfolgreich war
  if (error) {
    Serial.print(F("deserializeJson() fehlgeschlagen: "));
    Serial.println(error.f_str());
    return;
  }

  // Extrahieren der Werte
  const char *kl_name = doc["kl"][0]["name"];
  const char *kl_longname = doc["kl"][0]["longname"];
  const char *date = doc["date"];
  const char *startTime = doc["startTime"];
  const char *endTime = doc["endTime"];

  // Anzeigen der Daten auf dem E-Paper-Display (EPD)
  epd_poweron();
  writeln((GFXfont *)&FiraSans, kl_name, &cursor_x, &cursor_y, NULL);
  delay(500);
  cursor_x = 200;
  cursor_y += 50;
  writeln((GFXfont *)&FiraSans, kl_longname, &cursor_x, &cursor_y, NULL);
  delay(500);
  cursor_x = 200;
  cursor_y += 50;
  writeln((GFXfont *)&FiraSans, date, &cursor_x, &cursor_y, NULL);
  delay(500);
  cursor_x = 200;
  cursor_y += 50;
  writeln((GFXfont *)&FiraSans, startTime, &cursor_x, &cursor_y, NULL);
  delay(500);
  cursor_x = 200;
  cursor_y += 50;
  writeln((GFXfont *)&FiraSans, endTime, &cursor_x, &cursor_y, NULL);
  delay(500);
  epd_poweroff();
} 

// Initialisierungsprozedur
void setup() {
    // Beginn der seriellen Kommunikation
    Serial.begin(115200);
    delay(10);

    // Verbindungsaufbau zum WLAN
    Serial.println();
    Serial.print("Verbindung zu ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Ausgabe, dass die WiFi-Verbindung hergestellt wurde
    Serial.println("");
    Serial.println("WiFi verbunden");
    Serial.println("IP-Adresse: ");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.macAddress());

    // Initialisierung des Displays
    epd_init();
    getTimetable();
}

// Hauptloop, der sich immer wieder wiederholt
void loop() {
  delay(10000);  // Warte 10 Sekunden vor dem nächsten Aktualisieren
  epd_clear(); // Leert das Display
  getTimetable(); // Ruft erneut den Stundenplan ab
  epd_poweroff(); // Schaltet das Display ab
}
