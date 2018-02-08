#include <ESP8266WiFi.h>
#include <Servo.h>

Servo servo;
 
const char* ssid = "TECHNOLOGY";
const char* password = "TechMandu321";
const char* host = "IP OF THE ESP8266"; //it will tell you the IP once it starts up
                                        //just write it here afterwards and upload
static int pos = 0;
IPAddress ip(172, 16, 4, 8); //set static ip
IPAddress gateway(172, 16, 5, 1); //set getteway
IPAddress subnet(255, 255, 254, 0);//set subnet
WiFiServer server(301);//just pick any port number 

void setup() {
  Serial.begin(115200);
  delay(10);

  servo.attach(2); //D4

  servo.write(0);

  delay(2000);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(ip, gateway, subnet);
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

 // Print the MAC address
 Serial.print("MAC address:");
 Serial.println(WiFi.macAddress());
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
 
  char  *value = "LEFT";
  
   if (request.indexOf("/KEY=LEFT") != -1)  { // check if you clicked LEFT
    
    value = "LEFT";

    int i=1;
    while(pos<180 && i <=15)
    {
      
      servo.write(pos);
      i++;
      pos++;
      delay(25);
    }
    Serial.print("The angle position is:");
    Serial.println(pos);
    Serial.print("inside request index:");
    Serial.println(value);
  }
  if (request.indexOf("/KEY=RIGHT") != -1)  { // check if you click RIGHT
    
    value = "RIGHT";
    
     int i =1;
    while(pos>0 && i<=15)
    {
      servo.write(pos);
      i++;
      pos--;
      delay(25);
    }
    Serial.print("The angle position is:");
    Serial.println(pos);
    Serial.print("inside request index:");
    Serial.println(value);
  }
 

 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  
  client.println("<html>");
  client.print("Servo is at : ");
  client.print(pos);
  client.print("  degree and turning ");
 
  if(value == "LEFT") {
    client.print("LEFT");
  } 
  else {
    client.print("RIGHT");
  }
  client.println("<br><br>");
  client.println("<a href=\"/KEY=LEFT\"\"><button>Left </button></a>");
  client.println("<a href=\"/KEY=RIGHT\"\"><button>Right</button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
