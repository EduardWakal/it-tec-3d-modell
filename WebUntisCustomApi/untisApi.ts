// Importieren von benötigten Modulen
const express = require('express');
const {MongoClient, ServerApiVersion} = require('mongodb');
const {WebUntis} = require('webuntis');
const dotenv = require('dotenv');

// Laden der Umgebungsvariablen aus .env Datei
dotenv.config();

// Initialisierung der WebUntis Instanz mit den Daten aus der .env Datei
const untis = new WebUntis(
    'oppenheimer-schule',
    process.env.USERNAME,
    process.env.PASSWORD,
    'borys.webuntis.com'
);

// Initialisierung der MongoClient Instanz für den Zugriff auf MongoDB mit SSL-Zertifikat
const credentials = 'cert.pem'
const client = new MongoClient('mongodb+srv://cluster0.k33rfzw.mongodb.net/?authSource=%24external&authMechanism=MONGODB-X509&retryWrites=true&w=majority', {
    sslKey: credentials,
    sslCert: credentials,
    serverApi: ServerApiVersion.v1
});

// Erzeugen einer neuen Express-Anwendung
const app = express();

// Erster Endpunkt, /write-data. Dieser Endpunkt speichert den eigenen Stundenplan in MongoDB
app.get('/write-data', async (req, res) => {
    try {
        // Einloggen in WebUntis und Abrufen des eigenen Stundenplans
        await untis.login();
        const timetable = await untis.getOwnTimetableForToday()
        console.log(timetable);

        // Konvertierung des Stundenplans in ein einfaches Objekt, falls dies noch nicht geschehen ist
        let timetableData = JSON.parse(JSON.stringify(timetable));

        // Verbindung zu MongoDB herstellen
        await client.connect();
        console.log('Connected to MongoDB');

        // Speichern der Daten in MongoDB
        const db = client.db(process.env.MONGO_DB_NAME);
        const collection = db.collection('untis');
        await collection.insertOne({timetableData});
        console.log('Data written to MongoDB');

        // Schließen der Verbindung zu MongoDB
        await client.close();
        console.log('Disconnected from MongoDB');

        // Senden einer Erfolgsmeldung an den Client
        res.send('Data written to MongoDB');

    } catch (error) {
        // Bei einem Fehler wird die Fehlermeldung in der Konsole angezeigt und eine Fehlermeldung an den Client gesendet
        console.error('Error:', error);
        res.status(500).send('Error occurred');
    }
});

// Zweiter Endpunkt, /read-data. Dieser Endpunkt liest die Daten aus MongoDB und sendet sie an den Client
app.get('/read-data', async (req, res) => {
    try {
        // Verbindung zu MongoDB herstellen
        await client.connect();
        console.log('Connected to MongoDB');

        // Lesen der Daten aus MongoDB
        const db = client.db(process.env.MONGO_DB_NAME);
        const collection = db.collection('untis');
        const doc = await collection.findOne();

        // Überprüfen, ob ein Dokument gefunden wurde und ggf. eine Meldung ausgeben
        if (!doc) {
            console.log('No such document!');
            res.send('No such document!');
        } else {
            console.log('Document data:', doc);
            res.json(doc);
        }

        // Schließen der Verbindung zu MongoDB
        await client.close();
        console.log('Disconnected from MongoDB');
    } catch (error) {
        // Bei einem Fehler wird die Fehlermeldung in der Konsole angezeigt und eine Fehlermeldung an den Client gesendet
        console.error('Error:', error);
        res.status(500).send('Error occurred');
    }
});

// Starten der Express-Anwendung auf Port 3000
app.listen(3000, () => console.log('Server is listening on port 3000'));
