#include <stdio.h>
#include <stdint.h>
#include "setupHardware.h"
#include "utils.h"
#include "programmingAVR.h"

int main(int argc, char *argv[])
{
    HEX_LINE  *hexFile;
    initializeHardware();
    deactivateReset();
    enableAVRProgramming();
    hexFile = parseHexFile(argv[1]);
    printHexfile(hexFile);
    eraseAVRFlash();
    writeSinglePage(hexFile);
    readSinglePage();
    deactivateReset();
    deleteHexfile(hexFile);
    freeHardwareResources();
    return 0;
} // end main()






