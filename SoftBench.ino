#include "hexaWiFi.h"
#include "hexaServo.h"

void setup() 
{
  delay(1000);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 

  Serial.begin(115200);
  Serial.println();
  Serial.println( "Serial connexion established" );

  initWiFi();
  Serial.println();
  Serial.println( "WiFi access point established" );
  
  hexaServoInit();
  hexaHoming();
  delay(1000);
  
  Serial.println();
  Serial.println( "Home position set" );

  hexaToward( 5, 1, 0 );
}

void loop() 
{
  //hexaHoming();
  waitInstr();
}
