#include "hexaWiFi.h"

ESP8266WebServer server(80);

void initWiFi()
{
  WiFi.softAP( _SSID_, _PASSWORD_ );
  server.on( "/", handleRoot );
  server.on( "/up", handleForward );
  server.on( "/down", handleBackward );
  server.on( "/left", handleLeft );
  server.on( "/right", handleRight );
  server.begin();
}

void waitInstr()
{
  server.handleClient();
}

void handleRoot() 
{
  server.send(200, "text/html", "<h1>&emsp;&emsp;&emsp;&emsp;<a href=\"/up\">up</a><br/><a href=\"/left\">left</a>&emsp;<a href=\"/\">home</a>&emsp;<a href=\"/right\">right</a><br/>&emsp;&emsp;&emsp;<a href=\"/down\">down</a><br/></h1>");
}

void handleForward()
{
  hexaToward( 1, 1, 0 );
  server.send(200, "text/html", "<h1>&emsp;&emsp;&emsp;&emsp;<a href=\"/up\">up</a><br/><a href=\"/left\">left</a>&emsp;<a href=\"/\">home</a>&emsp;<a href=\"/right\">right</a><br/>&emsp;&emsp;&emsp;<a href=\"/down\">down</a><br/></h1>");
}

void handleBackward()
{
  hexaToward( -1, 1, 0 );
  server.send(200, "text/html", "<h1>&emsp;&emsp;&emsp;&emsp;<a href=\"/up\">up</a><br/><a href=\"/left\">left</a>&emsp;<a href=\"/\">home</a>&emsp;<a href=\"/right\">right</a><br/>&emsp;&emsp;&emsp;<a href=\"/down\">down</a><br/></h1>");
}

void handleLeft()
{
  hexaRotate( 1, 1, 0 );
  server.send(200, "text/html", "<h1>&emsp;&emsp;&emsp;&emsp;<a href=\"/up\">up</a><br/><a href=\"/left\">left</a>&emsp;<a href=\"/\">home</a>&emsp;<a href=\"/right\">right</a><br/>&emsp;&emsp;&emsp;<a href=\"/down\">down</a><br/></h1>");
}

void handleRight()
{
  hexaRotate( -1, 1, 0 );
  server.send(200, "text/html", "<h1>&emsp;&emsp;&emsp;&emsp;<a href=\"/up\">up</a><br/><a href=\"/left\">left</a>&emsp;<a href=\"/\">home</a>&emsp;<a href=\"/right\">right</a><br/>&emsp;&emsp;&emsp;<a href=\"/down\">down</a><br/></h1>");
}

