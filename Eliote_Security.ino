/***************************************************
     IOT Based HOME AUTOMATION AND SECURITY SYSTEM
                  #TEAM PI BOTS
               FOLLOW AND SUPPORT
                    @pi_bots

         CONTACT FOR TECHNICAL ASSISTANCE
                 Instagram.com
           -------------------------
            >>  @at_mega_328p
            
 ****************************************************/
 
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <DHT.h>
#include <U8g2lib.h>


#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

char auth[] = "r_7Yd9I9HwkdFc-v3ohes5NFJxPZTebG";

WidgetLED warn(V2);
WidgetLED accessgrant(V1);

#define RELAYPIN D5
#define WARNLEDPIN D6

#define celsius_width 64
#define celsius_height 64

   
#define x_width 64
#define x_height 64
static unsigned char x_bits[] PROGMEM = {
   0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe,
   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x87, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x33, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x33, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x33,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x79, 0x0e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xfc, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe,
   0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe, 0x1d, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xfe, 0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfe,
   0x1d, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0x1c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x79, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe7, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0xc3, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x81,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf0, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00,
   0x1e, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x3f, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0x06, 0xc0, 0xfb, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0,
   0xf1, 0xf1, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0e,
   0x0e, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3f, 0x3f, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0xc7, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xc6, 0xf1,
   0xf1, 0xf1, 0x00, 0x00, 0x00, 0x00, 0xce, 0xc0, 0xc0, 0x40, 0x00, 0x00,
   0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x1c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf0, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00 };

   

#define front_width 128
#define front_height 64
static unsigned char front_bits[] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0x3f, 0x80, 0x00, 0xe0, 0x8f, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0xc0, 0x01, 0x80, 0x03, 0x1e,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc0, 0xc1,
   0x01, 0x80, 0x03, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0xc0, 0x83, 0x00, 0x80, 0x03, 0x1c, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc0, 0x03, 0x00, 0x80, 0x03, 0x1c,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xc0, 0x03,
   0x00, 0x80, 0x03, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0xc0, 0xe1, 0x01, 0x80, 0x03, 0x1c, 0x80, 0x03, 0x1e, 0x06,
   0x0e, 0xc0, 0x01, 0x00, 0x00, 0xe0, 0xc0, 0xc1, 0x01, 0x80, 0x03, 0x1c,
   0x60, 0x1c, 0x9c, 0x9f, 0x1f, 0x30, 0x06, 0x00, 0x00, 0xe0, 0xe0, 0x80,
   0x01, 0x80, 0xff, 0x1f, 0x30, 0x38, 0x58, 0x5c, 0x38, 0x18, 0x0c, 0x00,
   0x00, 0xe0, 0x1f, 0x80, 0x01, 0x80, 0x03, 0x1c, 0x38, 0x30, 0x38, 0x38,
   0x38, 0x1c, 0x0c, 0x00, 0x00, 0xe0, 0x00, 0x80, 0x01, 0x80, 0x03, 0x1c,
   0x38, 0x70, 0x38, 0x38, 0x38, 0x1c, 0x1c, 0x00, 0x00, 0xe0, 0x00, 0x80,
   0x01, 0x80, 0x03, 0x1c, 0x3c, 0x70, 0x18, 0x38, 0x38, 0xfc, 0x1f, 0x00,
   0x00, 0xe0, 0x00, 0x80, 0x01, 0x80, 0x03, 0x1c, 0x3c, 0x70, 0x18, 0x38,
   0x38, 0x1c, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x80, 0x01, 0x80, 0x03, 0x1c,
   0x38, 0x70, 0x18, 0x38, 0x38, 0x1c, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x80,
   0x01, 0x80, 0x03, 0x1c, 0x38, 0x30, 0x18, 0x38, 0x38, 0x1c, 0x00, 0x00,
   0x00, 0xe0, 0x00, 0x80, 0x01, 0x80, 0x03, 0x1c, 0x30, 0x38, 0x18, 0x38,
   0x38, 0x38, 0x00, 0x00, 0x00, 0xf0, 0x00, 0xc0, 0x01, 0x80, 0x03, 0x1e,
   0x60, 0x1c, 0x38, 0x38, 0x38, 0x30, 0x08, 0x00, 0x00, 0xfc, 0x07, 0xe0,
   0x07, 0xe0, 0x8f, 0x7f, 0x80, 0x03, 0x7e, 0xfe, 0xfe, 0xc0, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
   0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x1f, 0x00, 0x00, 0xe1, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x0f, 0x00,
   0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x04, 0x00, 0x00, 0x00,
   0x18, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x04, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x81, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00,
   0x00, 0x07, 0x60, 0x80, 0xe3, 0x1c, 0xce, 0x1c, 0x9f, 0xe7, 0xc0, 0x73,
   0x18, 0x00, 0x0d, 0x00, 0x00, 0x3c, 0x18, 0x61, 0xc4, 0x10, 0x8c, 0x18,
   0x06, 0x43, 0x80, 0x21, 0x18, 0x00, 0x30, 0x00, 0x00, 0xf0, 0x0c, 0x31,
   0xc4, 0x10, 0x8c, 0x10, 0x06, 0x03, 0x80, 0x01, 0x18, 0x00, 0x30, 0x00,
   0x00, 0xc0, 0xfc, 0x33, 0xc4, 0x10, 0x0c, 0x10, 0x06, 0x06, 0x00, 0x13,
   0x18, 0x00, 0x30, 0x00, 0x80, 0x80, 0x0c, 0x30, 0xc0, 0x10, 0x0c, 0x10,
   0x06, 0x06, 0x00, 0x03, 0x18, 0x00, 0x31, 0x00, 0x80, 0x80, 0x0c, 0x30,
   0xc0, 0x10, 0x0c, 0x10, 0x06, 0x0c, 0x00, 0x06, 0x18, 0x88, 0x31, 0x00,
   0x80, 0x41, 0x18, 0x60, 0xc0, 0x38, 0x0c, 0x18, 0x06, 0x08, 0x00, 0x04,
   0x18, 0x0c, 0x10, 0x00, 0x00, 0x1c, 0x60, 0xc0, 0x81, 0x73, 0x3e, 0x3c,
   0x0c, 0x08, 0x00, 0x04, 0x7e, 0x08, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00 };

   
#define shield_width 64
#define shield_height 64
static unsigned char shield_bits[] PROGMEM = {
   0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x80, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff,
   0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x7f, 0xff, 0x1f, 0x00, 0x00,
   0x00, 0x00, 0xfe, 0x1f, 0xf8, 0x7f, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x07,
   0xe0, 0xff, 0x03, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x80, 0xff, 0x0f, 0x00,
   0x00, 0xfc, 0x3f, 0x00, 0x00, 0xfc, 0x3f, 0x00, 0x00, 0xff, 0x0f, 0x00,
   0x00, 0xf0, 0xff, 0x00, 0xe0, 0xff, 0x03, 0x00, 0x00, 0xc0, 0xff, 0x07,
   0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0f, 0xf0, 0x1f, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x0f, 0xf0, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x0f,
   0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0xf0, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x80, 0x0f, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f,
   0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0xf0, 0x01, 0x00, 0xe0,
   0x07, 0x00, 0x80, 0x0f, 0xf0, 0x01, 0x00, 0xfc, 0x3f, 0x00, 0x80, 0x0f,
   0xf0, 0x01, 0x00, 0xff, 0xff, 0x00, 0x80, 0x0f, 0xf0, 0x01, 0x80, 0xff,
   0xff, 0x01, 0x80, 0x0f, 0xf0, 0x01, 0xc0, 0xff, 0xff, 0x03, 0x80, 0x0f,
   0xf0, 0x01, 0xe0, 0x3f, 0xfc, 0x07, 0x80, 0x0f, 0xf0, 0x01, 0xf0, 0x07,
   0xf0, 0x0f, 0x80, 0x0f, 0xf0, 0x01, 0xf0, 0x03, 0xf8, 0x0f, 0x80, 0x0f,
   0xf0, 0x01, 0xf8, 0x01, 0xfc, 0x1f, 0x80, 0x0f, 0xf0, 0x01, 0xf8, 0x00,
   0xfe, 0x1f, 0x80, 0x0f, 0xf0, 0x01, 0xf8, 0x00, 0x7f, 0x1f, 0x80, 0x0f,
   0xf0, 0x01, 0xfc, 0x80, 0x3f, 0x3f, 0x80, 0x0f, 0xf0, 0x01, 0x7c, 0xc0,
   0x1f, 0x3e, 0x80, 0x0f, 0xf0, 0x01, 0x7c, 0xe0, 0x0f, 0x3e, 0x80, 0x0f,
   0xf0, 0x01, 0x7c, 0xf0, 0x07, 0x3e, 0x80, 0x0f, 0xf0, 0x01, 0x7c, 0xf8,
   0x03, 0x3e, 0x80, 0x0f, 0xf0, 0x01, 0xf8, 0xfc, 0x01, 0x1f, 0x80, 0x0f,
   0xf0, 0x01, 0xf8, 0xfe, 0x00, 0x1f, 0x80, 0x0f, 0xf0, 0x01, 0xf8, 0x7f,
   0x80, 0x1f, 0x80, 0x0f, 0xf0, 0x03, 0xf8, 0x3f, 0x80, 0x1f, 0xc0, 0x0f,
   0xe0, 0x03, 0xf0, 0x1f, 0xc0, 0x0f, 0xc0, 0x07, 0xe0, 0x03, 0xe0, 0x0f,
   0xf0, 0x07, 0xc0, 0x07, 0xe0, 0x03, 0xe0, 0x7f, 0xfe, 0x07, 0xc0, 0x07,
   0xe0, 0x07, 0xc0, 0xff, 0xff, 0x03, 0xe0, 0x07, 0xc0, 0x07, 0x80, 0xff,
   0xff, 0x01, 0xe0, 0x03, 0xc0, 0x0f, 0x00, 0xfe, 0x7f, 0x00, 0xf0, 0x03,
   0x80, 0x0f, 0x00, 0xf8, 0x1f, 0x00, 0xf0, 0x01, 0x80, 0x1f, 0x00, 0x80,
   0x01, 0x00, 0xf8, 0x01, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01,
   0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x7e, 0x00, 0x00,
   0x00, 0x00, 0x78, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00,
   0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0x00,
   0x00, 0x78, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00, 0xfc, 0x00, 0x00,
   0x00, 0x80, 0xff, 0x01, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0f,
   0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff,
   0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf8, 0x1f, 0x00, 0x00, 0x00 };
#define b_width 64
#define b_height 64
static const unsigned char b_bits[] PROGMEM = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x01, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff,
   0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00,
   0x00, 0x80, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff,
   0x7f, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff,
   0xff, 0x01, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0x03, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00,
   0x00, 0xf8, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0x07, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00,
   0x00, 0xf8, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0x07, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff,
   0xff, 0x03, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0xfc, 0x01, 0x00, 0x00,
   0x00, 0xe0, 0x0f, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0x00,
   0xfe, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0x00, 0xff, 0x00, 0x00, 0x00,
   0x00, 0x80, 0xff, 0xe1, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x1f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xfc, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff,
   0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x7f, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00,
   0x00, 0x01, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0xc0, 0x0f, 0x00, 0x00,
   0x80, 0xff, 0x03, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0xc0, 0xff, 0x0f, 0x00,
   0xfc, 0xff, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xf3, 0xff, 0xff, 0x01, 0x00,
   0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0xf8, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0xfe, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00,
   0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x70,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x78, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xfb, 0x3f, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0x7e,
   0xff, 0xff, 0xff, 0xff, 0x7f, 0xc0, 0x8f, 0x3f, 0xff, 0xff, 0xff, 0xff,
   0x3f, 0x8e, 0xc3, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0xe1, 0x0f,
   0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xf0, 0x07, 0xff, 0xff, 0xff, 0xff,
   0x3f, 0x7e, 0xf8, 0x01, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xfe, 0x00,
   0xf8, 0xff, 0xff, 0xff, 0x7f, 0xf8, 0x7f, 0x00, 0xc0, 0xff, 0xff, 0xff,
   0xff, 0xf0, 0x3f, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xe1, 0x1f, 0x00,
   0x00, 0x00, 0x00, 0x1f, 0x00, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };



char tag[] = "27002199148B";
char tag2[] = "2700219726B7";   // Replace with your own Tag ID
char input[12];                 // A variable to store the Tag ID being presented
int count = 0;                  // A counter variable to navigate through the input[] character array
boolean flag = 0;               // A variable to store the Tag match status

int dd = 0;

int state = 0;
int pir = D8;
int valpir = 0;
int servopin = 0;





/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "Pi Home"
#define WLAN_PASS       "Pihome@7560"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "anoofc"
#define AIO_KEY         "b2a92fdf7dac485c9e4284a7dec03ea6"


/************ Global State (you don't need to change this!) ******************/

BLYNK_WRITE(V20){
  int value = param.asInt();
  if (value==HIGH){
    accessgrant.on();
    state=1;
    }
  else if (value==LOW){
    accessgrant.off();
    state=0;
    }
  }

 


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'sensor' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/motion");

/*************************** Sketch Code ************************************/
void dhtsend()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  u8g2.setCursor(0,49); u8g2.print("Connecting to MQTT");
  u8g2.sendBuffer();
  delay(100);
  

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  u8g2.setCursor(0,61); u8g2.print("MQTT Connected");
  u8g2.sendBuffer();
  delay(1000);
  dd = 1;
}

void MQTT_connect();


void warnc() {
  u8g2.clearBuffer();
  u8g2.drawXBMP(32,0,shield_width,shield_height,shield_bits);
  u8g2.sendBuffer();
  Serial.println("Access Denied"); // Incorrect Tag Message
  Blynk.notify("Wrong Access...!!");

  digitalWrite(WARNLEDPIN, HIGH);
  warn.on();
  delay(100);
  digitalWrite(WARNLEDPIN, LOW);
  warn.off();
  delay(100);
  digitalWrite(WARNLEDPIN, HIGH);
  warn.on();
  delay(100);
  digitalWrite(WARNLEDPIN, LOW);
  warn.off();
  delay(100);
  digitalWrite(WARNLEDPIN, HIGH);
  warn.on();
  delay(100);
  digitalWrite(WARNLEDPIN, LOW);
  warn.off();
  delay(100);
  digitalWrite(WARNLEDPIN, HIGH);
  warn.on();
  delay(100);
  digitalWrite(WARNLEDPIN, LOW);
  warn.off();
}
void notifysms(){
  if (state == 0) {
  valpir = digitalRead(pir);
  if (valpir == HIGH) {
    photocell.publish("1");
    Blynk.notify("Security Breach Reported..!!");
    delay(1000);
  }
  else {
    photocell.publish("0");
    delay(1000);
  }

}

  }
void setup() {
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.drawXBMP(0,0,front_width,front_height,front_bits);
  u8g2.sendBuffer();
  delay(500);
  
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  Blynk.begin(auth, WLAN_SSID, WLAN_PASS);
  dht.begin();
  timer.setInterval(1000L, dhtsend);
  pinMode(servopin,OUTPUT);

  Serial.begin(9600);   // Initialise Serial Communication with the Serial Monitor
  pinMode(RELAYPIN, OUTPUT); // RELAY OUTPUT
  pinMode(WARNLEDPIN, OUTPUT); //WRONG TAG INDICATOR
  pinMode(pir, INPUT);

  Serial.println(F("TESCOMOBIS v.1.5"));
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); 
  u8g2.drawStr(12,10,"TESCOMOBIS" ); 
  
  u8g2.sendBuffer();
  
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  u8g2.setCursor(0,25); u8g2.print("Connecting to wifi");
  u8g2.sendBuffer();
  delay(100);
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  u8g2.setCursor(0,37); u8g2.print("WiFi Connected");
  u8g2.sendBuffer();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  delay(100);

}

uint32_t x = 0;

void accessunlock() {

  digitalWrite(RELAYPIN, HIGH);
  digitalWrite(servopin,HIGH);
  Blynk.notify("Door unlocked");
  delay(5000);
  digitalWrite(servopin,LOW);
  
  
  
}
void displayt(){
  if (dd==1){
  
  float a = dht.readHumidity();
  float b = dht.readTemperature();
  int h,t;
  
  h = (int)(a+0.5);
  t = (int)(b+0.5);
    
    u8g2.clearBuffer();
    u8g2.setFont( u8g2_font_osr21_tr);

    u8g2.drawXBMP(0,0,x_width,x_height,x_bits);
    u8g2.setCursor(58,60); u8g2.print(h); u8g2.setCursor(92,60); u8g2.print("%");
    u8g2.setCursor(58,27); u8g2.print(t); u8g2.setCursor(92,27); u8g2.print("C");
    u8g2.sendBuffer();
    delay(100);
  }
}

void loop() {

  displayt();
  
  Blynk.run();
  notifysms();
  timer.run();
  MQTT_connect();


  if (Serial.available()) // Check if there is incoming data in the RFID Reader Serial Buffer.
  {
    count = 0; // Reset the counter to zero
    /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty
       or till 12 Bytes (the ID size of our Tag) is read */
    while (Serial.available() && count < 12)
    {
      input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
      count++; // increment counter
      delay(5);
    }
    /* When the counter reaches 12 (the size of the ID) we stop and compare each value
        of the input[] to the corresponding stored value */
    if (count == 12) //
    {
      count = 0; // reset counter varibale to 0
      flag = 1;
      /* Iterate through each value and compare till either the 12 values are
         all matching or till the first mistmatch occurs */
      while (count < 12 && flag != 0)
      {
        if (input[count] == tag[count])
          flag = 1; // everytime the values match, we set the flag variable to 1
        else if (input[count] == tag2[count])
          flag = 1;
        else
          flag = 0;
        /* if the ID values don't match, set flag variable to 0 and
           stop comparing by exiting the while loop */
        count++; // increment i
      }
    }
    if (flag == 1) // If flag variable is 1, then it means the tags match
    {
      Serial.println("Access Allowed!");
      u8g2.clearBuffer();
      u8g2.drawXBMP(32,0,b_width,b_height,b_bits);
      u8g2.sendBuffer();
      
      accessunlock();
      
      }
      
    
    else {
      warnc();
      Serial.println("Access Denied");
      
      }
      delay(500);
  }
}
//WidgetLED accessled(V1);
