#include "hexaWiFi.h"
#include "hexaServo.h"

int g_hexaAngle;
int g_hexaSpeed;

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

  g_hexaAngle = 0;
  g_hexaSpeed = 0;
  hexaServoInit();
  hexaHoming();
  delay(1000);
  
  Serial.println();
  Serial.println( "Home position set" );

  //hexaMove( 5, 0, 1, 0 );
}

void loop() 
{
  waitInstr();
}
