#include <SPI.h>
#include "QuickBLE_device.h"

#define _device_Buzzer_ 10
#define _device_USB1_ 11
#define _device_USB2_ 12
#define _device_Relay1_ 13
#define _device_Relay2_ 14

device_t device;

void QuickBLE_device_init(void)
{
  pinMode(_device_Buzzer_,OUTPUT);
  pinMode(_device_USB1_,OUTPUT);
  pinMode(_device_USB2_,OUTPUT);
  pinMode(_device_Relay1_,OUTPUT);
  pinMode(_device_Relay2_,OUTPUT);

  pinMode(_PIN_1_,INPUT);
  pinMode(_PIN_2_,INPUT);
  pinMode(_PIN_3_,INPUT);
  pinMode(_PIN_6_,OUTPUT);
  pinMode(_PIN_7_,OUTPUT);  
}

void QuickBLE_device_process(void)
{
  if(device.buzzer==1) digitalWrite(_device_Buzzer_,HIGH);
  else if(device.buzzer==0) digitalWrite(_device_Buzzer_,LOW);

  if(device.USB1==1) digitalWrite(_device_USB1_,HIGH);
  else if(device.USB1==0) digitalWrite(_device_USB1_,LOW);

  if(device.USB2==1) digitalWrite(_device_USB2_,HIGH);
  else if(device.buzzer==0) digitalWrite(_device_USB2_,LOW);

  if(device.Relay1==1) digitalWrite(_device_Relay1_,HIGH);
  else if(device.Relay1==0) digitalWrite(_device_Relay1_,LOW);

  if(device.Relay2==1) digitalWrite(_device_Relay2_,HIGH);
  else if(device.Relay2==0) digitalWrite(_device_Relay2_,LOW);

  if(device.DO1==1) digitalWrite(_PIN_6_,HIGH);
  else if(device.DO1==0) digitalWrite(_PIN_6_,LOW);

  if(device.DO2==1) digitalWrite(_PIN_7_,HIGH);
  else if(device.DO2==0) digitalWrite(_PIN_7_,LOW);
}
