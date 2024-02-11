#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <peekpoke.h>
#include <cc65.h>
#include <cbm.h>
#include <6502.h>

unsigned int v = 53248;

unsigned char spriteData[63] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 224, 0, 3, 224, 0, 7, 28, 0, 6, 28, 0, 6, 24, 0, 6, 0, 0, 6, 0, 0, 6, 24, 0, 6, 28, 0, 7, 28, 0, 3, 224, 0, 1, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void rasterWait(unsigned char line);

int main(void) {

    int t;
    int x = 56;
    int sx = 0;
    int counter = 0;

    POKE(v+21,255);

    for (t = 0; t < 63; t++) {
        POKE(12288+t,spriteData[t]);
    }

    for (t = 0; t < 8; t++) {
        POKE(v+39+t,1); POKE(2040+t,192);
    }
    
    for (t = 0; t < 16; t = t + 2) {
        POKE(v+t,x);
        x = x + 25;
    }
    
    while (counter < 500) {

        __asm__("SEI");

        rasterWait(45);
        for (sx = 0; sx < 16; sx+=2) POKE(v+1+sx,50);
        rasterWait(80);
        for (sx = 0; sx < 16; sx+=2) POKE(v+1+sx,145);
        rasterWait(170);
        for (sx = 0; sx < 16; sx+=2) POKE(v+1+sx,230);

        counter += 1;
        rasterWait(235);
    
    }
    
    return EXIT_SUCCESS;
    
}
void rasterWait(unsigned char line) {
    while (VIC.rasterline < line);
}