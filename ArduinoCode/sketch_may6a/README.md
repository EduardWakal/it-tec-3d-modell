Arduino Code Dokumentation

Dieses Dokument dient dazu, den im Arduino Code verwendeten Funktionen und Variablen zu erklären.
Eingesetzte Bibliotheken

Der Code verwendet verschiedene Bibliotheken, um die Funktionen des Programms zu implementieren:

    Arduino.h: Stellt die Basisfunktionen der Arduino-Umgebung bereit.
    cstdint: Definiert Typen von festgelegten Breiten sowie deren maximalen und minimalen Grenzwerte.
    WiFi.h & WiFiClient.h: Ermöglichen die Kommunikation mit dem WiFi-Netzwerk.
    ArduinoHttpClient.h: Ermöglicht das Senden von HTTP-Anfragen an einen Server.
    ArduinoJson.h: Erlaubt das Arbeiten mit JSON-Strukturen und hilft beim Parsen von JSON-Antworten.
    epd_driver.h: Stellt Funktionen zum Steuern des E-Paper-Displays bereit.
    esp_adc_cal.h: Wird zur Kalibrierung des Analog-Digital-Wandlers (ADC) verwendet.
    FS.h, SPI.h & SD.h: Ermöglichen die Arbeit mit dem Dateisystem und der SD-Karte.
    firasans.h: Definiert die Font, die auf dem E-Paper-Display verwendet wird.
    pins.h: Definiert die spezifischen Pins für das Display.
    pcf8563.h: Ermöglicht die Arbeit mit der Echtzeituhr (RTC) des Displays.
    Wire.h: Erlaubt die Kommunikation über den I²C-Bus.

Code Erklärung

Der Code ermöglicht es, eine Verbindung zu einem WiFi-Netzwerk und einem Server herzustellen, Daten von der
WebUntis-Plattform abzurufen und diese Daten auf einem E-Paper-Display anzuzeigen.

Nach dem erfolgreichen Herstellen einer WLAN-Verbindung wird der Stundenplan über die Funktion getTimetable() abgerufen
und angezeigt.

In der getTimetable() Funktion werden die Daten nicht nur auf dem Display ausgegeben, sondern zwischen den Ausgaben auch
kurzzeitig verzögert. Dadurch kann der Nutzer die Anzeige besser verfolgen. Zudem wird das Display vor dem Anzeigen der
Daten eingeschaltet und nach dem Anzeigen wieder ausgeschaltet, um Energie zu sparen.

Die loop() Funktion ist so programmiert, dass sie alle 10 Sekunden den Stundenplan aktualisiert.
Schlüsselfunktionen

Die Funktion getTimetable() wurde erweitert:

    getTimetable(): Diese Funktion sendet eine Anfrage an den WebUntis-Server, um den Stundenplan abzurufen. Jede Zeile des abgerufenen Stundenplans wird nacheinander auf dem Display angezeigt. Dabei wird zwischen den Ausgaben kurz pausiert und nach der Anzeige aller Daten das Display ausgeschaltet.

Umgebungsvariablen

Die Anwendung verwendet folgende Umgebungsvariablen:

    ssid und password: Nutzernamen und Passwort für die Verbindung mit dem WiFi-Netzwerk.
    server: Die IP-Adresse des Servers.
    endpoint: Der Endpunkt auf dem Server, an den die Anfrage gesendet wird.
    port: Der Port, der für die Kommunikation mit dem Server verwendet wird.

Sicherheitshinweise

Da die WLAN-Zugangsdaten und der Server-IP im Code hart codiert sind, sollte dieser Code nicht öffentlich geteilt
werden, um die Datensicherheit zu gewährleisten. Es wird empfohlen, diese Werte durch Umgebungsvariablen zu ersetzen und
sicher zu speichern, z.B. in einer separaten Konfigurationsdatei, die nicht geteilt wird.