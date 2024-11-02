#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char *ssid = "BTS_CIEL";
const char *password = "ERIR1234";
AsyncWebServer server(80);
void setup()
{
Serial.begin(9600);
Serial.println("\n");
pinMode(2, OUTPUT);
pinMode(4, OUTPUT); 
pinMode(5, OUTPUT); 
pinMode(19, OUTPUT); 
digitalWrite(2, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
digitalWrite(19, LOW);
//--------------------------SPIFFS---------------------
if(!SPIFFS.begin()) /* Démarrage du gestionnaire de fichiers SPIFFS */
{
Serial.println("Erreur SPIFFS...");
return;
}

/* Détection des fichiers présents sur l'Esp32 */
File root = SPIFFS.open("/"); /* Ouverture de la racine */
File file = root.openNextFile(); /* Ouverture du 1er fichier */
while(file) /* Boucle de test de présence des fichiers - Si plus de fichiers la boucle s'arrête*/
{
Serial.print("File: ");
Serial.println(file.name());
file.close();
file = root.openNextFile(); /* Lecture du fichier suivant */
}
//--------------------------WIFI------------------------
WiFi.begin(ssid, password); /* Connexion au réseau Wifi */
Serial.print("Tentative de connexion...");
while(WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(100);
}
Serial.println("\n");
Serial.println("Connexion etablie!");
Serial.print("Adresse IP: ");
Serial.println(WiFi.localIP());

//---------------------------------SERVEUR ------------------------------
/* Lorsque le serveur est actif , la page index.html est chargée */
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
{
request->send(SPIFFS, "/index.html", "text/html");
});

/* Lorsque l'on clique sur ON, on allume la led */
server.on("/haut", HTTP_GET, [](AsyncWebServerRequest *request)
{
digitalWrite(2, HIGH);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
digitalWrite(19, LOW);
request->send(SPIFFS, "/index.html", "text/html");
});
/* Lorsque l'on clique sur OFF, on éteint la led */
server.on("/bas", HTTP_GET, [](AsyncWebServerRequest *request)
{
digitalWrite(2, LOW);
digitalWrite(4, LOW);
digitalWrite(5, LOW);
digitalWrite(19, HIGH);
request->send(SPIFFS, "/index.html", "text/html");
});
server.on("/gauche", HTTP_GET, [](AsyncWebServerRequest *request)
{
digitalWrite(2, LOW);
digitalWrite(4, HIGH);
digitalWrite(5, LOW);
digitalWrite(19, LOW);
request->send(SPIFFS, "/index.html", "text/html");
});
server.on("/droit", HTTP_GET, [](AsyncWebServerRequest *request)
{
digitalWrite(2, LOW);
digitalWrite(4, LOW);
digitalWrite(5, HIGH);
digitalWrite(19, LOW);
request->send(SPIFFS, "/index.html", "text/html");
});
/* On affiche que le serveur est actif */
server.begin();
Serial.println("Serveur actif!");
}
void loop() /* La loop est vide */
{

}