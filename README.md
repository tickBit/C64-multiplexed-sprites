# C64's sprites multiplexed

24-sprites.c draws 24 sprites. Just a little test in C. I was very young back in my C64 days and never even tried to do sprite multiplexing. The program exits after a while after starting it..

24-sprites.c is also a test program to test my JavaScript sprite editor for Commodore 64. Particularly the C source output of the editor.

Steps to compile with CC65:

- cc65 -t c64 24-sprites.c
- ca65 24-sprites.s
- cl65 24-sprites.o -o 24-sprites.prg

Next, just run 24-sprites.prg in your choice of C64 emulator.

![24-sprites](https://github.com/tickBit/C64-multiplexed-sprites/assets/61118857/66a5efcd-6b17-4937-b277-734cd6c906a6)
