#include <xc.h>
#include "config.h"

void initEXTINT(void)
{
    TRISBbits.TRISB0 = 1;

    INTEDG = 0;

    INTF = 0;

    INTE = 1;

    GIE = 1;
}
