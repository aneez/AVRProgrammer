#include <stdio.h>
#include <unistd.h>
#include <ftdi.h>
#include <stdint.h>

struct ftdi_context ftdic;

int OutputByte(uint8_t output_b)
{
    int result=0; // returned error code
    ftdi_write_data(&ftdic, &output_b, 1);
    return result;
}

uint8_t InputByte()
{
    uint8_t buf;
    ftdi_read_pins(&ftdic,&buf);
    //printf("%2x\t",buf);
    return buf;
}

int initializeHardware()
{
    int f;

    if (ftdi_init(&ftdic) < 0)
    {
        fprintf(stderr, "ftdi_init failed\n");
        return EXIT_FAILURE;
    }

    f = ftdi_usb_open(&ftdic, 0x0403, 0x6014);
    if (f < 0 && f != -5)
    {
        fprintf(stderr, "unable to open ftdi device: %d (%s)\n", f, ftdi_get_error_string(&ftdic));
        exit(-1);
    }

    ftdi_set_interface(&ftdic,INTERFACE_A);
    ftdi_set_bitmode(&ftdic, 0xfb, BITMODE_BITBANG);
    //OutputByte(0x01);
    return 0;
}

int freeHardwareResources()
{
    ftdi_disable_bitbang(&ftdic);
    ftdi_usb_close(&ftdic);
    ftdi_deinit(&ftdic);
    return 0;
}


