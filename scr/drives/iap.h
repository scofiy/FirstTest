#ifndef __IAP_H__
#define __IAP_H__

char iap_read(int addr);
void iap_program(int addr, char dat);
void iap_erase(int addr);

#endif
