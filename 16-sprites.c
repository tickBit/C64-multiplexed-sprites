#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <peekpoke.h>
#include <cc65.h>
#include <cbm.h>
#include <6502.h>

unsigned int v = 53248l;

unsigned char spriteData[63] ={0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 224, 0, 3, 224, 0, 7, 28, 0, 6, 28, 0, 6, 24, 0, 6, 0, 0, 6, 0, 0, 6, 24, 0, 6, 28, 0, 7, 28, 0, 3, 224, 0, 1, 224, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

unsigned char pow2(unsigned char exponent);
void rasterWait(unsigned char line);

int main(void) {

    unsigned char t;
    unsigned int x[8] = {60, 80, 100, 120, 140, 160, 180, 200};
    unsigned char area2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char sx = 0;
    unsigned int counter = 0;

    POKE(v+21,255);

    for (t = 0; t < 63; t++) {
        POKE(12288+t,spriteData[t]);
    }

    for (t = 0; t < 8; t++) {
        POKE(v+39+t,1); POKE(2040+t,192);
    }
    
    while (counter < 2500) {

        __asm__("SEI");

        for (sx = 0; sx < 16; sx+=2) {
            if (x[sx/2] == 256 && area2[sx/2] == 0) {
                POKE(v+16,(PEEK(v+16) | pow2(sx/2)));
                x[sx/2] = 0;
                area2[sx/2] = 1;

            } else {
                if (x[sx/2] == 64 + 25 && area2[sx/2] == 1) {
                    POKE(v+16,(PEEK(v+16) & (255 - pow2(sx/2))));
                    x[sx/2] = x[sx/2] / 88;
                    area2[sx/2] = 0;
                }
            }
            POKE(v+sx,x[sx/2]);
            x[sx/2] += 1;
        }
        rasterWait(90);
        for (sx = 0; sx < 16; sx+=2) POKE(v+1+sx,172);

        rasterWait(178);
        for (sx = 0; sx < 16; sx+=2) POKE(v+1+sx,235);

        counter += 1;

        /* rasterWait(235); */
    
    }
    
    return EXIT_SUCCESS;
    
}
void rasterWait(unsigned char line) {
    while (VIC.rasterline < line);
}

unsigned char pow2(unsigned char exponent) {
    unsigned char i;
    unsigned char power = 1;

    if (exponent == 0) return 1;

    for (i = 0; i < exponent; i++) {
        power = power + power;
    }

    return power;
}