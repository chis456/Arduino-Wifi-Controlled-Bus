#include <ESP8266WiFi.h>
#include <Wire.h>

//pin outs for KeeYees ESP8226 Module
static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;

//internet credentials 
const char* ssid     = "test";
const char* password = "test";

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  //master slave connection with Arduino 
  Wire.begin(D1, D2);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); //Go to this URL in your browser to get the controls page
  server.begin();
}

void loop() {

  WiFiClient client = server.available();
  if(!client)
  {
    return;
  }

  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  Wire.beginTransmission(8);
  
  String request = client.readStringUntil('\r');
  Serial.println("request: " + request);

  //send Arduino a certain letter based on what the user inputs to the webserver
  if (request == "GET /control?command=forward HTTP/1.1") 
  {
    Serial.println("f");
    Wire.write('f');
  } 
  else if (request == "GET /control?command=left HTTP/1.1") 
  {
    Serial.println("l");
    Wire.write('l');
  } 
  else if (request == "GET /control?command=right HTTP/1.1") 
  {
    Serial.println("r");
    Wire.write('r');
  } 
  else if (request == "GET /control?command=backward HTTP/1.1") 
  {
    Serial.println("b");
    Wire.write('b');
  }
  else if (request == "GET /control?command=stop HTTP/1.1") 
  {
    Serial.println("s");
    Wire.write('s');
  }
  
  client.flush();

  //webpage view
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // The connection will be closed after completion of the response
  client.println();
  client.println("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Arduino Car Control</title></head><body>");
  client.println("<h1>Arduino Bus Control Page</h1>");
  client.println("<h1>W - Drive forward</h1>");
  client.println("<h1>A - Turn Left </h1>");
  client.println("<h1>S - Drive backward </h1>");
  client.println("<h1>D - Turn Right </h1>");
  client.println("<h1>X - Brake </h1>");
  client.println("<script>");
  client.println("function sendCommand(command) {");
  client.println("var xhttp = new XMLHttpRequest();");
  client.println("xhttp.open('GET', '/control?command=' + command, true);");
  client.println("xhttp.send();");
  client.println("}");

  //event listener for key presses
  client.println("document.addEventListener('keydown', function(event) {");
  client.println("switch(event.key) {");
  client.println("case 'w':");
  client.println("case 'W':");
  client.println("sendCommand('forward');");
  client.println("break;");
  client.println("case 'a':");
  client.println("case 'A':");
  client.println("sendCommand('left');");
  client.println("break;");
  client.println("case 's':");
  client.println("case 'S':");
  client.println("sendCommand('backward');");
  client.println("break;");
  client.println("case 'd':");
  client.println("case 'D':");
  client.println("sendCommand('right');");
  client.println("break;");
  client.println("case 'x':");
  client.println("case 'X':");
  client.println("sendCommand('stop');");
  client.println("break;");
  client.println("}");
  client.println("});");
  client.println("</script>");
  client.println("</body></html>");

  Serial.println("Client disconnected");
  
  //Serial.println();
  Wire.endTransmission();
  //delay(100);

}
