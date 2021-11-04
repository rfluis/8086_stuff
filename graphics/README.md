# Graphics in Borland Turbo C using assembler
These two small demos show how to make graphics in C for 8086
* gdemo.c does calling int 0x10 for VGA/EGA
* hgdemo.c has a small routine to Setup Graphics mode in Hercules card
Both files implement Bresenham algorithm to draw lines

I left some mouse routines (calls to int 0x33), 
just to check if current loaded mouse driver supports Hercules

To compile these two files Borland Turbo C Compiler (TCC.EXE) and Borland Turbo Assembler (TASM.EXE) are needed.
I didn't try with other compilers.

* I got Hercules Driver from an internet FTP I don't remember
* Mouse Routines and Int 0x10 codes from BASM (Basic to Assembler translator by Kevin Diggins)
* Bresenham algorithm from Wikipedia (https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
