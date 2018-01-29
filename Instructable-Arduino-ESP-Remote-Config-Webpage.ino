#include <WiFi.h>

const char* ssid     = "yourssid";
const char* password = "yourpasswd";

WiFiServer server(80);

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while(!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop()
{
  // listen for incoming clients
  WiFiClient client = server.available();   // listen for incoming clients
  bool sendResponse = false;                // set to true if we want to send a response
  String urlLine = "";                      // make a String to hold the requested URL

  if(client)                                // if you get a client,
  {
    Serial.println("New Client.");          // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while(client.connected())               // loop while the client's connected
    {
      if(client.available())                // if there's bytes to read from the client,
      {
        char c = client.read();             // read a byte, then
        
        if(c == '\n')                       // if the byte is a newline character
        {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if(currentLine.length() == 0)
          {
            sendResponse = true;             // everything's fine!
            break;                           // break out of the while loop
          }
          else                               // if you got a newline, then clear currentLine:
          {
            if(currentLine.indexOf("GET /") >= 0) // this should be the URL line
            {
              urlLine = currentLine;         // save it for later use
            }
            currentLine = "";                // reset the currentLine String
          }
        }
        else if(c != '\r')                   // if you got anything else but a carriage return character,
        {
          currentLine += c;                  // add it to the end of the currentLine
        }
      }
    }
    
    if(sendResponse)
    {
      Serial.print("Client requested ");
      Serial.println(urlLine);
      
      // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
      // and a content-type so the client knows what's coming, then a blank line:
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println();
      
      if(urlLine.indexOf("GET / ") >= 0) // if the URL is only a "/"
      {
        // the content of the HTTP response follows the header:
        client.println("<!doctype html><html><head><script src=\"https://billynate.github.io/Instructable-Arduino-ESP-Remote-Config-Webpage/remote-conf.js\"></script></head><body></body></html>");
      }
      
      // The HTTP response ends with another blank line:
      client.println();
    }
    
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

