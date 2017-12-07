#include <at89c51ed2.h>
#include <mcs51reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "wdt.h"

void wtd_init()
{
    WDTPRG|=0x07;
    WDTRST=0x1E;
    WDTRST=0xE1;
}
void wtd_reset()
{
    WDTRST=0x1E;
    WDTRST=0xE1;
}
