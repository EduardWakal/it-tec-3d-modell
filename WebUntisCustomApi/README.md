Projektbeschreibung

Diese Anwendung, entwickelt in TypeScript und Node.js, stellt eine Verbindung zur Untis-API her und ruft den
persönlichen Stundenplan des Benutzers ab. Die abgerufenen Daten werden dann in einer MongoDB-Datenbank gespeichert. Die
Anwendung bietet auch eine Funktion, die die gespeicherten Daten abruft und einen Express.js-Endpunkt bereitstellt.
Verwendete Bibliotheken

    Express.js: Ein minimales und flexibles Node.js-Webanwendungs-Framework, das eine robuste Reihe von Funktionen für Web- und mobile Anwendungen bietet.
    MongoDB: Eine source-to-source Datenbank, die Entwicklern hilft, Daten für ihre Anwendungen zu verwalten.
    WebUntis API Client: Ein Modul, das eine vereinfachte Verbindung zur WebUntis-API bietet.
    dotenv: Ein Zero-Dependency-Modul, das .env-Dateien lädt und die darin enthaltenen Variablen in process.env lädt.

Code-Struktur

    Der Code beginnt mit dem Importieren aller erforderlichen Module und der Initialisierung von WebUntis und MongoClient.
    Danach wird die Express-Anwendung initialisiert.
    Es gibt zwei Routen: /write-data und /read-data. Bei einer GET-Anfrage an /write-data loggt sich die Anwendung bei Untis ein, ruft den persönlichen Stundenplan für den Tag ab und speichert die Daten in MongoDB. Bei einer GET-Anfrage an /read-data liest die Anwendung die Daten aus MongoDB und sendet sie an den Client.
    Die Express-Anwendung wird auf Port 3000 gestartet.

Umgebungsvariablen

Die Anwendung verwendet folgende Umgebungsvariablen:

    USERNAME und PASSWORD: Anmeldedaten für WebUntis.
    MONGO_DB_NAME: Name der MongoDB-Datenbank, in die die Daten geschrieben werden.

SSL-Zertifikat

Die Anwendung verwendet ein SSL-Zertifikat (cert.pem), um eine sichere Verbindung zur MongoDB-Datenbank herzustellen.

Arduino Dokumentation
Verwendete Bibliotheken

Dieser Code verwendet mehrere Bibliotheken:

    Arduino.h: Standardbibliothek für Arduino.
    WiFi.h: Ermöglicht die Kommunikation mit WiFi-Netzwerken.
    WiFiClientSecure.h: Ermöglicht sichere Kommunikation über SSL/TLS mit einem Remote-Server.
    ArduinoHttpClient.h: Ermöglicht das Senden von HTTP-Anfragen an einen Server.
    ArduinoJson.h: Eine Bibliothek, die es ermöglicht, mit JSON zu arbeiten.
    epd_driver.h: Ermöglicht die Ansteuerung eines E-Paper-Displays.
    esp_adc_cal.h: Enthält Funktionen zur Kalibrierung des ADC (Analog-Digital-Umsetzer).
    FS.h: Erlaubt den Zugriff auf das Dateisystem.
    SPI.h: Erlaubt die Kommunikation über die SPI-Schnittstelle.
    SD.h: Ermöglicht die Interaktion mit SD-Karten.
    firasans.h: Die Fira Sans Schriftart.

Code Erklärung

Der Code konfiguriert eine Verbindung zu einem WiFi-Netzwerk und einem Server, um Daten von der WebUntis-Plattform
abzurufen. Anschließend stellt er eine Verbindung zum Netzwerk her und startet eine Session mit WebUntis.

    Verbindung mit dem WiFi-Netzwerk: In der setup() Funktion wird eine Verbindung zum WiFi-Netzwerk hergestellt. Die SSID und das Passwort sind als Konstanten am Anfang des Codes definiert.

    Start einer Session mit WebUntis: Nachdem eine WiFi-Verbindung hergestellt wurde, wird die Funktion authenticate() aufgerufen, um eine Session mit der WebUntis-Plattform zu starten. Diese Funktion sendet eine HTTP-POST-Anfrage an den WebUntis-Server, um sich zu authentifizieren und eine Session zu starten.

    Abrufen des Stundenplans: Nach erfolgreicher Authentifizierung wird die Funktion getTimetable() aufgerufen. Diese Funktion sendet eine weitere HTTP-POST-Anfrage an den WebUntis-Server, um den Stundenplan abzurufen.

Wichtige Funktionen

    authenticate(): Diese Funktion erstellt ein JSON-Dokument und sendet es an den WebUntis-Server, um sich zu authentifizieren und eine Sitzung zu starten. Nachdem die Anfrage gesendet wurde, liest die Funktion die Antwort, extrahiert die Sitzungs-ID und speichert sie.

    getTimetable(): Diese Funktion erstellt ein weiteres JSON-Dokument und sendet es an den WebUntis-Server, um den Stundenplan abzurufen. Es verwendet die in der authenticate() Funktion erhaltene Sitzungs-ID als Teil des Cookie-Headers.

Umgebungsvariablen

Die Anwendung verwendet folgende Umgebungsvariablen:

    ssid und password: Die Anmeldedaten für Ihr WLAN.
    server, endpoint und port: Die Anmeldedaten für den WebUntis-Server.

Bitte stellen Sie sicher, dass Sie alle sensiblen Informationen wie Passwörter und Schlüssel sicher aufbewahren und
nicht in Ihrem Code hart codieren. Es ist empfehlenswert, diese in einer separaten Konfigurationsdatei oder als
Umgebungsvariablen zu speichern, um die Sicherheit zu erhöhen.
User
