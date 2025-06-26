#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "NOMBRE_DE_TU_WIFI";
const char* password = "CONTRASEÑA_DE_TU_WIFI";
// Este código es un ejemplo de un servidor web simple en ESP32 que controla un LED integrado. 
WebServer server(80);


const int ledPin = 3; // Pin del LED integrado
int contadorVisitas = 0; // Variable para contar visitas

void handleRoot() {
  contadorVisitas++;
  String html = "<h1>¡Hola desde ESP32!</h1>";
  html += "<p>Visitas a esta página: " + String(contadorVisitas) + "</p>";
  html += "<p><a href='/on'><button>Encender LED</button></a></p>";
  html += "<p><a href='/off'><button>Apagar LED</button></a></p>";
  // ...agrega aquí los botones de otros LEDs si tienes...
  server.send(200, "text/html", html);
}
void handleLedOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", "<h1>LED ENCENDIDO</h1><a href='/'>Volver</a>");
}

void handleLedOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", "<h1>LED APAGADO</h1><a href='/'>Volver</a>");
}
//estoy ensayando  otro ensayo 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado, IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);
  server.begin();
}

void loop() {
  server.handleClient();
}