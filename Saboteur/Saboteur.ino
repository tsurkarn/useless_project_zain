#include <WiFi.h>
#include <WiFiClientSecure.h>

#define ENABLE_SMTP
#define ENABLE_DEBUG

#include <ReadyMail.h>

WiFiClientSecure ssl_client;
SMTPClient smtp(ssl_client);

void setup() {

  Serial.begin(115200);
  WiFi.begin("Room 17", "pachavellam");
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  while (WiFi.status() != WL_CONNECTED)
  delay(500);

  ssl_client.setInsecure();

  auto statusCallback = [](SMTPStatus status) {
    Serial.println(status.text);
    };

  smtp.connect("smtp.gmail.com", 465, statusCallback);

  if (smtp.isConnected()) {
    smtp.authenticate("tsurkarn08@gmail.com", "tdxk diyu jxtv kupz", readymail_auth_password);

    while(analogRead(3)<1000) {
      delay(100);
      analogRead(3);
    }


    SMTPMessage msg;
    msg.headers.add(rfc822_from, "Zain <tsurkarn08@gmail.com>");
    msg.headers.add(rfc822_to, "Zain <zayikrishna@gmail.com>");
    msg.headers.add(rfc822_subject, "Respected Sir");
    msg.text.body("You're a piece of crap. Get recked.");

    configTime(0, 0, "pool.ntp.org");
    while (time(nullptr) < 100000) delay(100);
    msg.timestamp = time(nullptr);

    smtp.send(msg);
  }
}

void loop() {}