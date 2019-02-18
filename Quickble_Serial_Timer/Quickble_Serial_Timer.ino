

// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

/*
   Serial Port over BLE
   Create UART service compatible with Nordic's *nRF Toolbox* and Adafruit's *Bluefruit LE* iOS/Android apps.

   BLESerial class implements same protocols as Arduino's built-in Serial class and can be used as it's wireless
   replacement. Data transfers are routed through a BLE service with TX and RX characteristics. To make the
   service discoverable all UUIDs are NUS (Nordic UART Service) compatible.

   Please note that TX and RX characteristics use Notify and WriteWithoutResponse, so there's no guarantee
   that the data will make it to the other end. However, under normal circumstances and reasonable signal
   strengths everything works well.
*/

// Import libraries (BLEPeripheral depends on SPI)
#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"

// define pins (varies per shield/board)
#define BLE_REQ   10
#define BLE_RDY   2
#define BLE_RST   9

// create ble serial instance, see pinouts above
BLESerial BLESerial(BLE_REQ, BLE_RDY, BLE_RST);

#define _device_Buzzer_ 10
#define _device_USB1_ 11
#define _device_USB2_ 12
#define _device_Relay1_ 13
#define _device_Relay2_ 14

#define _PIN_1_ 17
#define _PIN_2_ 18
#define _PIN_3_ 19
#define _PIN_6_ 23
#define _PIN_7_ 24

Timer t;
void doSomething()
{
  Serial.println("One Sec.");
}

void setup() {

  t.every(1000, doSomething);

  Serial.begin(9600);

  Serial.println("Hello QuickBLE EVB");


  BLESerial.setLocalName("Quick_test");
  BLESerial.setDeviceName("Quick_test");
  BLESerial.begin();

  pinMode(_device_Buzzer_, OUTPUT);
  pinMode(_device_USB1_, OUTPUT);
  pinMode(_device_USB2_, OUTPUT);
  pinMode(_device_Relay1_, OUTPUT);
  pinMode(_device_Relay2_, OUTPUT);

  pinMode(_PIN_1_, INPUT);
  pinMode(_PIN_2_, INPUT);
  pinMode(_PIN_3_, INPUT);
  pinMode(_PIN_6_, OUTPUT);
  pinMode(_PIN_7_, OUTPUT);
}

void loop() {
  t.update();

  BLESerial.poll();
  QuickBLE_ble_process();


  //Serial RX Example
  int serial_data;
  char serial_rx_buffer[50] = {0};
  int serial_rx_buffer_number = 0;

  while ((serial_data = Serial.read()) > 0)
  {
    serial_rx_buffer[serial_rx_buffer_number] = serial_data;
    serial_rx_buffer_number++;
  }
  if (strlen(serial_rx_buffer) > 0)
  {
    Serial.print("Serial RX:");
    Serial.println(serial_rx_buffer);
  }

}

void QuickBLE_ble_process(void)
{

  if (BLESerial) {
    int ble_data;
    char rx_buffer[50] = {0};
    int rx_buffer_number = 0;

    while ((ble_data = BLESerial.read()) > 0)
    {
      rx_buffer[rx_buffer_number] = ble_data;
      rx_buffer_number++;
    }
    if (strlen(rx_buffer) > 0)
    {
      Serial.print("BLE RX:");
      Serial.println(rx_buffer);
    }


    if (strcmp(rx_buffer, "buzzerON") == 0) digitalWrite(_device_Buzzer_, HIGH);
    else if (strcmp(rx_buffer, "buzzerOFF") == 0) digitalWrite(_device_Buzzer_, LOW);
    else if (strcmp(rx_buffer, "usb1ON") == 0) digitalWrite(_device_USB1_, HIGH);
    else if (strcmp(rx_buffer, "usb1OFF") == 0) digitalWrite(_device_USB1_, LOW);
    else if (strcmp(rx_buffer, "usb2ON") == 0) digitalWrite(_device_USB2_, HIGH);
    else if (strcmp(rx_buffer, "usb2OFF") == 0) digitalWrite(_device_USB2_, LOW);
    else if (strcmp(rx_buffer, "relay1ON") == 0) digitalWrite(_device_Relay1_, HIGH);
    else if (strcmp(rx_buffer, "relay1OFF") == 0) digitalWrite(_device_Relay1_, LOW);
    else if (strcmp(rx_buffer, "relay2ON") == 0) digitalWrite(_device_Relay2_, HIGH);
    else if (strcmp(rx_buffer, "relay2OFF") == 0) digitalWrite(_device_Relay2_, LOW);

    if (strcmp(rx_buffer, "DO1HIGH") == 0) digitalWrite(_PIN_6_, HIGH);
    else if (strcmp(rx_buffer, "DO1LOW") == 0) digitalWrite(_PIN_6_, LOW);
    else if (strcmp(rx_buffer, "DO2HIGH") == 0) digitalWrite(_PIN_7_, HIGH);
    else if (strcmp(rx_buffer, "DO2LOW") == 0) digitalWrite(_PIN_7_, LOW);

    if (strcmp(rx_buffer, "Pin1State") == 0)
    {
      if (digitalRead(_PIN_1_) == HIGH) BLESerial.write("PIN1 is HIGH");
      if (digitalRead(_PIN_1_) == LOW) BLESerial.write("PIN1 is LOW");
    }
    else if (strcmp(rx_buffer, "Pin2State") == 0)
    {
      if (digitalRead(_PIN_2_) == HIGH) BLESerial.write("PIN2 is HIGH");
      if (digitalRead(_PIN_2_) == LOW) BLESerial.write("PIN2 is LOW");
    }
    else if (strcmp(rx_buffer, "Pin3State") == 0)
    {
      if (digitalRead(_PIN_3_) == HIGH) BLESerial.write("PIN3 is HIGH");
      if (digitalRead(_PIN_3_) == LOW) BLESerial.write("PIN3 is LOW");
    }

    memset(rx_buffer, 0, sizeof(rx_buffer));
    rx_buffer_number = 0;
  }
}


