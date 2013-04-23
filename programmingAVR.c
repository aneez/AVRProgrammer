#include<stdio.h>
#include <stdint.h>

#include "programmingAVR.h"
#include "SPIBitBanging.h"
#include "setupHardware.h"
#include "utils.h"

uint8_t doAVRSPIProtocol(uint32_t masterOutput, uint8_t DataIndex)
{
    int8_t i=3;
    uint8_t SlaveOut[4];
    
    for(;i>=0;i--)
    {
        SlaveOut[3-i] = SPIProtocol((masterOutput>>(i*8)&0xff),0);
        Usleep(SHORTSLEEP);
    }
    Usleep(LONGSLEEP);
    return SlaveOut[DataIndex];    
}

void readSignatureBits()
{
    uint8_t i = 0;
    printf("Signature Bits:");
    for(;i<2;i++)
        printf("%02x",doAVRSPIProtocol(AVR_READ_SIGNATURE_BITS+(0x100 * i),3)); //read 3 signature bits
}

void readSinglePage()
{
    uint32_t iAdd = 0;

    for(;iAdd<PAGESIZE;iAdd++)
    {
        printf("\nAddress:%d\t",iAdd);
        printf("%02x",doAVRSPIProtocol(AVR_READ_HIGH_BYTE+(0x100 * iAdd),3)); //read data at address iAdd(H)
        printf("%02x",doAVRSPIProtocol(AVR_READ_LOW_BYTE+(0x100 * iAdd),3));  //read data at address iAdd(L)
    }
}

void eraseAVRFlash()
{
    doAVRSPIProtocol(AVR_CHIP_ERASE,3);
    Usleep(LONGSLEEP);
}

void writeSinglePage(HEX_LINE* hLine)
{
    uint32_t iSize=0;
    Usleep(LONGSLEEP);
    while(hLine)
    {
       uint32_t currentPage = hLine->page;
       while(hLine && ((hLine->page) == currentPage))
       {
          for(iSize=0;iSize<hLine->size;iSize++)
          {
             //printf("%08x\t",AVR_LOAD_LOW_BYTE+(0x100*(hLine->address+iSize))+(hLine->dataArray)[2*iSize]);
             //printf("%08x\n",AVR_LOAD_HIGH_BYTE+(0x100*(hLine->address+iSize))+(hLine->dataArray)[2*iSize+1]);
             doAVRSPIProtocol(AVR_LOAD_LOW_BYTE+(0x100*(hLine->address+iSize))+(hLine->dataArray)[2*iSize],3);
             doAVRSPIProtocol(AVR_LOAD_HIGH_BYTE+(0x100*(hLine->address+iSize))+(hLine->dataArray)[2*iSize+1],3);
          }
          hLine=hLine->pNextLine;
          Usleep(SHORTSLEEP);
       }   
       //printf("Writing Page %d:",currentPage);
       //printf("%08x\n",AVR_WRITE_PAGE | (0x4000 * currentPage));
       doAVRSPIProtocol(AVR_WRITE_PAGE | (0x4000 * currentPage),3);
       Usleep(2*LONGSLEEP);
    }      
}

void deactivateReset()
{
    OutputByte(0x01);
    Usleep(LONGSLEEP);
}

void enableAVRProgramming()
{
    OutputByte(0x00);
    Usleep(LONGSLEEP);
    printf("%x\n",doAVRSPIProtocol(AVR_PROGRAMMING_ENABLE,2));
    readSignatureBits();
    printf("\n");
    OutputByte(0x00);
}
