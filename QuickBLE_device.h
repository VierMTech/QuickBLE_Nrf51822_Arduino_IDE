#ifndef _QuickBLE_device_H_
#define _QuickBLE_device_H_

#define _PIN_1_ 17
#define _PIN_2_ 18
#define _PIN_3_ 19
#define _PIN_6_ 23
#define _PIN_7_ 24

typedef struct{
  int buzzer,USB1,USB2,Relay1,Relay2,DO1,DO2;
}device_t;

void QuickBLE_device_init(void);
void QuickBLE_device_process(void);

#endif
