#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"
#include "QuickBLE_ble.h"
#include "QuickBLE_device.h"

// define pins (varies per shield/board)
#define BLE_REQ   10
#define BLE_RDY   2
#define BLE_RST   9

// create ble serial instance, see pinouts above
BLESerial BLESerial(BLE_REQ, BLE_RDY, BLE_RST);

extern device_t device;

void QuickBLE_ble_init(void)
{
  BLESerial.setLocalName("QuickBLE_test");
  BLESerial.begin();
}

void QuickBLE_ble_process(void)
{
    BLESerial.poll();  
    if (BLESerial) {
      int x;
      char RX_buffer[50]={0};
      int number=0;
      while ((x = BLESerial.read()) > 0)
      {      
          RX_buffer[number]=x;
          number++;
      }
      if(strcmp(RX_buffer,"buzzerON")==0) device.buzzer=1;
      else if(strcmp(RX_buffer,"buzzerOFF")==0) device.buzzer=0;
      else if(strcmp(RX_buffer,"usb1ON")==0) device.USB1=1;
      else if(strcmp(RX_buffer,"usb1OFF")==0) device.USB1=0;
      else if(strcmp(RX_buffer,"usb2ON")==0) device.USB2=1;
      else if(strcmp(RX_buffer,"usb2OFF")==0) device.USB2=0;
      else if(strcmp(RX_buffer,"relay1ON")==0) device.Relay1=1;
      else if(strcmp(RX_buffer,"relay1OFF")==0) device.Relay1=0;
      else if(strcmp(RX_buffer,"relay2ON")==0) device.Relay2=1;
      else if(strcmp(RX_buffer,"relay2OFF")==0) device.Relay2=0;
      
      if(strcmp(RX_buffer,"DO1HIGH")==0) device.DO1=1;
      else if(strcmp(RX_buffer,"DO1LOW")==0) device.DO1=0;
      else if(strcmp(RX_buffer,"DO2HIGH")==0) device.DO2=1;
      else if(strcmp(RX_buffer,"DO2LOW")==0) device.DO2=0;  

      if(strcmp(RX_buffer,"Pin1State")==0) 
      {
        if(digitalRead(_PIN_1_)==HIGH) BLESerial.write("PIN1 is HIGH");
        if(digitalRead(_PIN_1_)==LOW) BLESerial.write("PIN1 is LOW");
      }
      else if(strcmp(RX_buffer,"Pin2State")==0) 
      {
        if(digitalRead(_PIN_2_)==HIGH) BLESerial.write("PIN2 is HIGH");
        if(digitalRead(_PIN_2_)==LOW) BLESerial.write("PIN2 is LOW");
      }
      else if(strcmp(RX_buffer,"Pin3State")==0) 
      {
        if(digitalRead(_PIN_3_)==HIGH) BLESerial.write("PIN3 is HIGH");
        if(digitalRead(_PIN_3_)==LOW) BLESerial.write("PIN3 is LOW");
      }
  }
}
