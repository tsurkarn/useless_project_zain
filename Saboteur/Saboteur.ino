/*Saboteur: Wake up or lose your job
By: Zain Jisa Chemmanoor
*/

#include <WiFi.h> //WiFi Library
#include <WiFiClientSecure.h> //SSL Library

#define ENABLE_SMTP
#define ENABLE_DEBUG

#include <ReadyMail.h>  //SMTP Server Library

WiFiClientSecure ssl_client;
SMTPClient smtp(ssl_client);

void setup() {  //Code is written in the setup part because it only needs to be run once to do the damage

  Serial.begin(115200);
  WiFi.begin("SSID", "PASSWORD"); //Put in your SSID and PASSWORD
  WiFi.setTxPower(WIFI_POWER_8_5dBm); //Low power to prevent sudden connection drops

  while (WiFi.status() != WL_CONNECTED)
  delay(500);

  ssl_client.setInsecure();

  auto statusCallback = [](SMTPStatus status) {
    Serial.println(status.text);
    };

  smtp.connect("smtp.gmail.com", 465, statusCallback);

  if (smtp.isConnected()) {
    smtp.authenticate("SENDER_MAIL_ADDRESS", "APP_PASSWORD", readymail_auth_password); //Put in your own sender mail address and app password

    while(analogRead(3)<1000) { //Sets the sensor threshold
      delay(100);
      analogRead(3);
    }


    SMTPMessage msg;  //Setting up the mail message
    msg.headers.add(rfc822_from, "Sender <sender@mail.com>");
    msg.headers.add(rfc822_to, "Reciever <reciever@mail.com>");
    msg.headers.add(rfc822_subject, "Respected Sir");
    msg.text.body("You're a piece of crap. Get recked."); //Send the doomed message (at your own risk)

    configTime(0, 0, "pool.ntp.org");
    while (time(nullptr) < 100000) delay(100);
    msg.timestamp = time(nullptr);

    smtp.send(msg); //Sending the mail
  }
}

void loop() {} //Keep this blank. One damage is enough
