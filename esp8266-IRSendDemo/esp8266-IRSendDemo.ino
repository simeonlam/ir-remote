/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
//uint16_t rawData[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
//                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
//                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
//                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
//                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
//                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
//                        650, 1650, 650, 1650, 650, 1650, 600};

uint16_t rawData[439] = {3474, 1754,  388, 490,  388, 1374,  390, 488,  390, 490,  388, 488,  388, 488,  390, 488,  388, 482,  388, 488,  414, 464,  414, 464,  388, 490,  388, 490,  388, 1376,  414, 464,  388, 482,  390, 488,  414, 464,  414, 464,  388, 488,  388, 490,  412, 1350,  414, 1350,  414, 1352,  388, 490,  414, 464,  390, 1374,  412, 466,  388, 490,  388, 490,  412, 466,  412, 458,  386, 490,  388, 490,  386, 490,  388, 490,  388, 490,  388, 490,  388, 490,  388, 482,  388, 490,  388, 490,  388, 490,  388, 490,  388, 490,  388, 490,  388, 488,  388, 482,  388, 488,  388, 490,  388, 490,  388, 490,  388, 490,  388, 490,  388, 490,  388, 482,  386, 490,  388, 1376,  388, 1376,  388, 490,  388, 490,  388, 490,  388, 488,  388, 478,  386, 9762,  3514, 1756,  388, 490,  388, 1376,  412, 464,  388, 490,  412, 464,  388, 488,  388, 490,  388, 482,  412, 464,  388, 488,  388, 490,  388, 488,  390, 490,  388, 1376,  388, 490,  412, 458,  412, 464,  388, 490,  388, 490,  412, 464,  408, 470,  414, 1350,  414, 1350,  414, 1352,  390, 488,  414, 464,  414, 1348,  416, 462,  414, 464,  414, 462,  416, 462,  414, 456,  414, 436,  440, 464,  414, 462,  416, 462,  416, 462,  414, 436,  442, 464,  414, 430,  440, 1322,  442, 436,  440, 464,  414, 436,  442, 1350,  414, 1348,  416, 464,  414, 456,  414, 434,  446, 1346,  414, 436,  442, 462,  414, 1348,  416, 1322,  442, 436,  442, 428,  442, 436,  442, 436,  440, 436,  442, 436,  440, 436,  440, 436,  440, 436,  442, 1354,  414, 1320,  442, 1320,  442, 1322,  442, 1350,  414, 434,  444, 1322,  442, 434,  442, 1352,  414, 1320,  442, 436,  440, 1350,  416, 1320,  442, 434,  442, 436,  442, 434,  442, 428,  442, 436,  442, 434,  442, 434,  444, 436,  442, 434,  442, 434,  444, 434,  442, 456,  414, 436,  442, 1320,  444, 1322,  442, 1322,  442, 436,  442, 436,  442, 434,  444, 428,  442, 434,  442, 434,  442, 464,  414, 434,  444, 436,  442, 1320,  442, 1322,  442, 1324,  442, 436,  442, 434,  442, 434,  442, 436,  444, 434,  444, 434,  442, 434,  444, 426,  442, 464,  414, 434,  442, 434,  442, 434,  444, 434,  442, 436,  442, 434,  444, 426,  442, 1322,  442, 434,  444, 434,  442, 434,  442, 464,  414, 434,  442, 434,  444, 428,  442, 434,  444, 434,  442, 434,  444, 434,  442, 434,  444, 436,  442, 434,  442, 428,  442, 434,  442, 1320,  442, 1322,  442, 436,  444, 434,  442, 434,  442, 436,  442, 428,  444, 434,  442, 1322,  442, 436,  442, 1320,  444, 1322,  442, 434,  444, 434,  442, 1318,  444}; 

// Example Samsung A/C state captured from IRrecvDumpV2.ino
uint8_t samsungState[kSamsungAcStateLength] = {
    0x02, 0x92, 0x0F, 0x00, 0x00, 0x00, 0xF0,
    0x01, 0xE2, 0xFE, 0x71, 0x40, 0x11, 0xF0};

uint8_t panasonicState[kPanasonicAcStateLength] = {
    0x02, 0x20, 0xE0, 0x04, 0x00, 0x00, 0x00, 0x06, 0x02, 
    0x20, 0xE0, 0x04, 0x00, 0x31, 0x32, 0x80, 0xAF, 0x0D, 
    0x00, 0x0E, 0xE0, 0x00, 0x00, 0x01, 0x00, 0x06, 0x9A};

void setup() {
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
}

void loop() {
//  Serial.println("NEC");
//  irsend.sendNEC(0x00FFE01FUL);
  Serial.println("wait 2s");
  delay(2000);
//  Serial.println("Sony");
//  irsend.sendSony(0xa90, 12, 2);  // 12 bits & 2 repeats
  Serial.println("wait 2s");
  delay(2000);
  Serial.println("a rawData capture from IRrecvDumpV2");
  irsend.sendRaw(rawData, 439, 38);  // Send a raw data capture at 38kHz.
  Serial.println("wait 2s");
  delay(2000);
//  Serial.println("a Samsung A/C state from IRrecvDumpV2");
//  irsend.sendSamsungAC(samsungState);
  Serial.println("wait 2s");
  delay(2000);
  Serial.println("a Panasonic A/C state on from IRrecvDumpV2");
  irsend.sendSamsungAC(panasonicState);
  Serial.println("wait 2s");
  delay(2000);
}
