#include "ESP8266WiFi.h";
const char* ssid = "BachichiHome";
const char* password = "mamina1326";
int ledPin = LED_BUILTIN; // GPIO13 
int ledPin1 = 5; // GPIO13 
int ledPin3 = 0; // GPIO13 
int ledPin5 = 14; // GPIO13 
WiFiServer server(80); 
void setup() { 
 Serial.begin(115200); 
 delay(10); 
 pinMode(ledPin, OUTPUT); 
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin3, OUTPUT);
 pinMode(ledPin5, OUTPUT);
 digitalWrite(ledPin, LOW);
 digitalWrite(ledPin1, LOW);
 digitalWrite(ledPin3, LOW);
 digitalWrite(ledPin5, LOW);
 // Connect to WiFi network 
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, password); 
 while (WiFi.status() != WL_CONNECTED) { 
   delay(500); 
   Serial.print("."); 
 } 
 Serial.println(""); 
 Serial.println("WiFi connected"); 
 // Start the server 
 server.begin(); 
 Serial.println("Server started"); 
 // Print the IP address 
 Serial.print("Use this URL to connect: "); 
 Serial.print("http://"); 
 Serial.print(WiFi.localIP()); 
 Serial.println("/"); 
} 
void loop() { 
 // Check if a client has connected 
 WiFiClient client = server.available(); 
 if (!client) { 
   return; 
 } 
 // Wait until the client sends some data 
 Serial.println("new client"); 
 while(!client.available()){ 
   delay(1); 
 } 
 // Read the first line of the request 
 String request = client.readStringUntil('\r'); 
 Serial.println(request); 
 client.flush(); 
 // Match the request 
 int value = HIGH; 
 if (request.indexOf("/LED=ON") != -1)  { 
   digitalWrite(ledPin, LOW);
   digitalWrite(ledPin1, LOW); 
   digitalWrite(ledPin3, LOW); 
   digitalWrite(ledPin5, LOW); 
   value = LOW; 
 } 
 if (request.indexOf("/LED=OFF") != -1)  { 
   digitalWrite(ledPin, HIGH); 
   digitalWrite(ledPin1, HIGH); 
   digitalWrite(ledPin3, HIGH); 
   digitalWrite(ledPin5, HIGH); 
   value = HIGH; 
 } 
// Set ledPin according to the request 
//digitalWrite(ledPin, value); 
 // Return the response 
client.println("<html>");
client.println("<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css' integrity='sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO' crossorigin='anonymous'>");
client.println("<body style='background: #ffffff; width: 90%; margin-left: 5%; text-align: center;'>");
client.println("<h1 style='font-size: 4em; margin-top: 10px;'>Riegomatic 3000</h1><br>");
if(value == LOW) { 
  client.println("<div class='alert alert-success' style='font-size: 3em;' role='alert'>En funcionamiento</div>");
}
else 
{ 
  client.println("<div class='alert alert-warning' style='font-size: 3em;' role='alert'>Apagado</div><br>");
} 
client.println("<a type='button' class='btn btn-primary' style='font-size: 3em;' href=\"/LED=ON\"\">Prender</a>");
client.println("<a type='button' class='btn btn-secondary' style='font-size: 3em;' href=\"/LED=OFF\"\">Apagar</a><br />  ");
client.println("</body></html>");

} 
