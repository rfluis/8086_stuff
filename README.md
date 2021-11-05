# 8086_stuff
Code created for 8086/8088 + 8087

C for 8086 has some quirks:
* int defaults to short int (16 bytes)
* 32-bit integers are declared with long int
* 64-bit integers with long long int
* CPU has native support for 16-bit arithmetics, but 32-bit (and wider) is done by software or by an specific hardware (8087)
* Pointers are near by default (within a 64 kB segment). Random-access pointers are far pointers.
* No protected mode. Any program can access any hardware or any memory region, just setting up a far pointer.

All code must be compiled with Borland Turbo C and may not be portable
