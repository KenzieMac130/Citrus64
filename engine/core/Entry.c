#include <stdio.h>

#include <libdragon.h>

int main(void)
{
    console_init();

    debug_init_usblog();
    debug_init_isviewer();
    console_set_debug(true);
    while(1){
        printf("Hello world!!!!!\n");
        debugf("Error message");
        wait_ms(10000);
        float icecream = 32.0f;
        icecream += 4.0f;
        assert(0);
    }

    while(1) {}
}