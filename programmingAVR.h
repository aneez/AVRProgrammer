#ifndef AVR_H
#define AVR_H
#define AVR_PROGRAMMING_ENABLE 0xAC530000
#define AVR_READ_SIGNATURE_BITS 0x30000000
#define AVR_READ_FUSE_BITS 0x50000000
#define AVR_READ_LOCK_BITS 0x58000000
#define AVR_READ_LOW_BYTE 0x20400000
#define AVR_READ_HIGH_BYTE 0x28400000
#define AVR_CHIP_ERASE 0xAC800000
#define AVR_LOAD_LOW_BYTE 0x40000000
#define AVR_LOAD_HIGH_BYTE 0x48000000
#define AVR_WRITE_PAGE 0x4C000000
#define PAGESIZE 256

#include "utils.h"
void readSignatureBits();
void readSinglePage();
void enableAVRProgramming();
void eraseAVRFlash();
uint8_t doAVRSPIProtocol(uint32_t, uint8_t);
void writeSinglePage(HEX_LINE* );
void deactivateReset();
#endif
