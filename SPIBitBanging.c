#include <stdint.h>
#include "SPIBitBanging.h"
#include "setupHardware.h"
#include "utils.h"

uint8_t SPIProtocol(uint8_t DataOut,uint8_t clockPhase)
{
    uint8_t ChipSelect = 0x00;
    uint8_t Clock = 0x00;
    uint8_t DataIn = 0x00;
    uint8_t count = 0;
    
    do{ 
        //falling edge
        OutputByte((Clock&CLKMASK)|(DataOut&DOMASK)|(ChipSelect&CSMASK));
        Usleep(HALFCLOCK);
        (clockPhase && count) ? (DataOut=DataOut<<1):(DataOut=DataOut);
        //rising edge
        OutputByte((~Clock&CLKMASK)|(DataOut&DOMASK)|(ChipSelect&CSMASK));
        Usleep(HALFCLOCK);
        DataIn = (DataIn<<1)|((InputByte()&DIMASK)>>2);
        (!clockPhase) ? (DataOut = DataOut<<1):(DataOut=DataOut);
    }while ( ++count<8 );
    OutputByte(0x00);
    return DataIn;
}

