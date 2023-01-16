#define BLYNK_TEMPLATE_ID "TMPLU29yebA2"
#define BLYNK_DEVICE_NAME "IOT Gas Detector"
#define BLYNK_AUTH_TOKEN "NQq05iSbDnyQFdrw3Rii7wFAS1Xb66pD"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>

char auth[] = "NQq05iSbDnyQFdrw3Rii7wFAS1Xb66pD";
char ssid[] = "#############"; //Wifi Name
char pass[] = "#############"; //Wifi Password

Servo servo;
BlynkTimer timer;

#define MQ2 34
#define buzzer 27
int MQ2_Val = 0;


void setup() //Setup function
{
  Serial.begin(9600); //Start the serial output at 9600 baud
  
  Blynk.begin(auth, ssid, pass);//Splash screen delay
  delay(2000);
  timer.setInterval(1000L, mySensor);
  servo.attach(13);
}

BLYNK_WRITE(V1)
{
   servo.write(param.asInt());
}

void loop() //Loop function
{
  Blynk.run();
  timer.run();
}

void mySensor()
{
  for(int x = 0 ; x < 100 ; x++)
    {
        MQ2_Val = MQ2_Val + analogRead(MQ2);
    }
    MQ2_Val = MQ2_Val/100.0;
  
  Blynk.virtualWrite(V0, MQ2_Val);
    
  if (MQ2_Val > 600)
  {
    //Blynk.notify("Gas Detected!");
    Blynk.logEvent("gas", "Gas Detected!");
    digitalWrite(buzzer, HIGH);
    //led.on();
  }

  else
  {
    digitalWrite(buzzer, LOW);
    //led.off();
  }  
  Serial.print("MQ2 Level: ");
  Serial.println(MQ2_Val);
  
}
