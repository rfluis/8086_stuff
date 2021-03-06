/* Autor: Ricardo Francisco Luis Martínez 
 * Proyecto: 
 * Descripción: 
 * Licencia: 
 * Nombre del Archivo: 
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*

#define byte_addr(x,y)  (((y)/4)*90 + ((y)&3)*0x2000 + ((x)/8))
*/
#define byte_addr(x,y)  ( (((y>>2)*90) + ((y&3)<<13)) + (x>>3) )
#define bit_pos(x)     (128 >>(x&7))
#define bit_num(x)     (x&7)
#define outp(port,data) _DX=port; _AL=data; asm out DX,AL

/* char far* screen = (char far *)0xb0000000; */
char gr6845[] = {0x38, 0x2d, 0x30, 0x08, 0x5a, 0x00, 0x57, 0x57, 0x02,	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
char te6845[] = {0x61, 0x50, 0x52, 0x0f, 0x19, 0x06, 0x19, 0x19, 0x02,	0x0d, 0x0b, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

char fnt8[2048]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x81,0xA5,0x81,0xBD,0x99,0x81,0x7E,0x7E,0xFF,0xDB,0xFF,0xC3,0xE7,0xFF,0x7E,0x6C,0xFE,0xFE,0xFE,0x7C,0x38,0x10,0x00,0x10,0x38,0x7C,0xFE,0x7C,0x38,0x10,0x00,0x38,0x7C,0x38,0xFE,0xFE,0xD6,0x10,0x38,0x10,0x10,0x38,0x7C,0xFE,0x7C,0x10,0x38,0x00,0x00,0x18,0x3C,0x3C,0x18,0x00,0x00,
0xFF,0xFF,0xE7,0xC3,0xC3,0xE7,0xFF,0xFF,0x00,0x3C,0x66,0x42,0x42,0x66,0x3C,0x00,0xFF,0xC3,0x99,0xBD,0xBD,0x99,0xC3,0xFF,0x0F,0x07,0x0F,0x7D,0xCC,0xCC,0xCC,0x78,0x3C,0x66,0x66,0x66,0x3C,0x18,0x7E,0x18,0x3F,0x33,0x3F,0x30,0x30,0x70,0xF0,0xE0,0x7F,0x63,0x7F,0x63,0x63,0x67,0xE6,0xC0,0x99,0x5A,0x3C,0xE7,0xE7,0x3C,0x5A,0x99,
0x80,0xE0,0xF8,0xFE,0xF8,0xE0,0x80,0x00,0x02,0x0E,0x3E,0xFE,0x3E,0x0E,0x02,0x00,0x18,0x3C,0x7E,0x18,0x18,0x7E,0x3C,0x18,0x66,0x66,0x66,0x66,0x66,0x00,0x66,0x00,0x7F,0xDB,0xDB,0x7B,0x1B,0x1B,0x1B,0x00,0x7E,0xC3,0x78,0xCC,0xCC,0x78,0x8C,0xF8,0x00,0x00,0x00,0x00,0x7E,0x7E,0x7E,0x00,0x18,0x3C,0x7E,0x18,0x7E,0x3C,0x18,0xFF,
0x18,0x3C,0x7E,0x18,0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x18,0x7E,0x3C,0x18,0x00,0x00,0x18,0x0C,0xFE,0x0C,0x18,0x00,0x00,0x00,0x30,0x60,0xFE,0x60,0x30,0x00,0x00,0x00,0x00,0xC0,0xC0,0xC0,0xFE,0x00,0x00,0x00,0x24,0x66,0xFF,0x66,0x24,0x00,0x00,0x00,0x18,0x3C,0x7E,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0x7E,0x3C,0x18,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x78,0x78,0x30,0x30,0x00,0x30,0x00,0x6C,0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00,0x30,0x7C,0xC0,0x78,0x0C,0xF8,0x30,0x00,0x00,0xC6,0xCC,0x18,0x30,0x66,0xC6,0x00,0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00,0x60,0x60,0xC0,0x00,0x00,0x00,0x00,0x00,
0x18,0x30,0x60,0x60,0x60,0x30,0x18,0x00,0x60,0x30,0x18,0x18,0x18,0x30,0x60,0x00,0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00,0x00,0x30,0x30,0xFC,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x30,0x60,0x00,0x00,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x06,0x0C,0x18,0x30,0x60,0xC0,0x80,0x00,
0x78,0xCC,0xDC,0xFC,0xEC,0xCC,0x78,0x00,0x30,0xF0,0x30,0x30,0x30,0x30,0xFC,0x00,0x78,0xCC,0x0C,0x38,0x60,0xCC,0xFC,0x00,0x78,0xCC,0x0C,0x38,0x0C,0xCC,0x78,0x00,0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x0C,0x00,0xFC,0xC0,0xF8,0x0C,0x0C,0xCC,0x78,0x00,0x38,0x60,0xC0,0xF8,0xCC,0xCC,0x78,0x00,0xFC,0xCC,0x0C,0x18,0x30,0x60,0x60,0x00,
0x78,0xCC,0xCC,0x78,0xCC,0xCC,0x78,0x00,0x78,0xCC,0xCC,0x7C,0x0C,0x18,0x70,0x00,0x00,0x00,0x30,0x30,0x00,0x30,0x30,0x00,0x00,0x00,0x30,0x30,0x00,0x70,0x30,0x60,0x18,0x30,0x60,0xC0,0x60,0x30,0x18,0x00,0x00,0x00,0xFC,0x00,0xFC,0x00,0x00,0x00,0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00,0x78,0xCC,0x0C,0x18,0x30,0x00,0x30,0x00,
0x7C,0xC6,0xDE,0xDE,0xDE,0xC0,0x78,0x00,0x30,0x78,0xCC,0xCC,0xFC,0xCC,0xCC,0x00,0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00,0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00,0xFC,0x6C,0x66,0x66,0x66,0x6C,0xFC,0x00,0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00,0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00,0x3C,0x66,0xC0,0xC0,0xCE,0x66,0x3E,0x00,
0xCC,0xCC,0xCC,0xFC,0xCC,0xCC,0xCC,0x00,0x78,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00,0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00,0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00,0xC6,0xEE,0xFE,0xD6,0xC6,0xC6,0xC6,0x00,0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00,0x38,0x6C,0xC6,0xC6,0xC6,0x6C,0x38,0x00,
0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00,0x78,0xCC,0xCC,0xCC,0xDC,0x78,0x1C,0x00,0xFC,0x66,0x66,0x7C,0x78,0x6C,0xE6,0x00,0x78,0xCC,0xE0,0x38,0x1C,0xCC,0x78,0x00,0xFC,0xB4,0x30,0x30,0x30,0x30,0x78,0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xFC,0x00,0xCC,0xCC,0xCC,0xCC,0xCC,0x78,0x30,0x00,0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00,
0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x30,0x78,0x00,0xFE,0xCC,0x98,0x30,0x62,0xC6,0xFE,0x00,0x78,0x60,0x60,0x60,0x60,0x60,0x78,0x00,0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x78,0x00,0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0x30,0x30,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00,0xE0,0x60,0x7C,0x66,0x66,0x66,0xBC,0x00,0x00,0x00,0x78,0xCC,0xC0,0xCC,0x78,0x00,0x1C,0x0C,0x0C,0x7C,0xCC,0xCC,0x76,0x00,0x00,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00,0x38,0x6C,0x60,0xF0,0x60,0x60,0xF0,0x00,0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0xF8,
0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00,0x30,0x00,0x70,0x30,0x30,0x30,0x78,0x00,0x18,0x00,0x78,0x18,0x18,0x18,0xD8,0x70,0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00,0x70,0x30,0x30,0x30,0x30,0x30,0x78,0x00,0x00,0x00,0xEC,0xFE,0xD6,0xC6,0xC6,0x00,0x00,0x00,0xF8,0xCC,0xCC,0xCC,0xCC,0x00,0x00,0x00,0x78,0xCC,0xCC,0xCC,0x78,0x00,
0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0,0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E,0x00,0x00,0xD8,0x6C,0x6C,0x60,0xF0,0x00,0x00,0x00,0x7C,0xC0,0x78,0x0C,0xF8,0x00,0x10,0x30,0x7C,0x30,0x30,0x34,0x18,0x00,0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00,0x00,0x00,0xCC,0xCC,0xCC,0x78,0x30,0x00,0x00,0x00,0xC6,0xC6,0xD6,0xFE,0x6C,0x00,
0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00,0x00,0x00,0xCC,0xCC,0xCC,0x7C,0x0C,0xF8,0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00,0x1C,0x30,0x30,0xE0,0x30,0x30,0x1C,0x00,0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00,0xE0,0x30,0x30,0x1C,0x30,0x30,0xE0,0x00,0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x38,0x6C,0xC6,0xC6,0xC6,0xFE,0x00,
0x78,0xCC,0xC0,0xCC,0x78,0x18,0x0C,0x78,0x00,0xCC,0x00,0xCC,0xCC,0xCC,0x7E,0x00,0x1C,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00,0x7E,0xC3,0x3C,0x06,0x3E,0x66,0x3F,0x00,0xCC,0x00,0x78,0x0C,0x7C,0xCC,0x7E,0x00,0xE0,0x00,0x78,0x0C,0x7C,0xCC,0x7E,0x00,0x30,0x30,0x78,0x0C,0x7C,0xCC,0x7E,0x00,0x00,0x00,0x7C,0xC0,0xC0,0x7C,0x06,0x3C,
0x7E,0xC3,0x3C,0x66,0x7E,0x60,0x3C,0x00,0xCC,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00,0xE0,0x00,0x78,0xCC,0xFC,0xC0,0x78,0x00,0xCC,0x00,0x70,0x30,0x30,0x30,0x78,0x00,0x7C,0xC6,0x38,0x18,0x18,0x18,0x3C,0x00,0xE0,0x00,0x70,0x30,0x30,0x30,0x78,0x00,0xCC,0x30,0x78,0xCC,0xCC,0xFC,0xCC,0x00,0x30,0x30,0x00,0x78,0xCC,0xFC,0xCC,0x00,
0x1C,0x00,0xFC,0x60,0x78,0x60,0xFC,0x00,0x00,0x00,0x7F,0x0C,0x7F,0xCC,0x7F,0x00,0x3E,0x6C,0xCC,0xFE,0xCC,0xCC,0xCE,0x00,0x78,0xCC,0x00,0x78,0xCC,0xCC,0x78,0x00,0x00,0xCC,0x00,0x78,0xCC,0xCC,0x78,0x00,0x00,0xE0,0x00,0x78,0xCC,0xCC,0x78,0x00,0x78,0xCC,0x00,0xCC,0xCC,0xCC,0x7E,0x00,0x00,0xE0,0x00,0xCC,0xCC,0xCC,0x7E,0x00,
0x00,0xCC,0x00,0xCC,0xCC,0xFC,0x0C,0xF8,0xC6,0x38,0x7C,0xC6,0xC6,0x7C,0x38,0x00,0xCC,0x00,0xCC,0xCC,0xCC,0xCC,0x78,0x00,0x18,0x18,0x7E,0xC0,0xC0,0x7E,0x18,0x18,0x38,0x6C,0x64,0xF0,0x60,0xE6,0xFC,0x00,0xCC,0xCC,0x78,0xFC,0x30,0xFC,0x30,0x00,0xF0,0xD8,0xD8,0xF4,0xCC,0xDE,0xCC,0x0E,0x0E,0x1B,0x18,0x7E,0x18,0x18,0xD8,0x70,
0x1C,0x00,0x78,0x0C,0x7C,0xCC,0x7E,0x00,0x38,0x00,0x70,0x30,0x30,0x30,0x78,0x00,0x00,0x1C,0x00,0x78,0xCC,0xCC,0x78,0x00,0x00,0x1C,0x00,0xCC,0xCC,0xCC,0x7E,0x00,0x00,0xF8,0x00,0xF8,0xCC,0xCC,0xCC,0x00,0xFC,0x00,0xCC,0xEC,0xFC,0xDC,0xCC,0x00,0x3C,0x6C,0x6C,0x3E,0x00,0x7E,0x00,0x00,0x3C,0x66,0x66,0x3C,0x00,0x7E,0x00,0x00,
0x30,0x00,0x30,0x60,0xC0,0xCC,0x78,0x00,0x00,0x00,0x00,0xFC,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0xFC,0x0C,0x0C,0x00,0x00,0xC6,0xCC,0xD8,0x3E,0x63,0xCE,0x98,0x1F,0xC6,0xCC,0xD8,0xF3,0x67,0xCF,0x9F,0x03,0x00,0x18,0x00,0x18,0x18,0x3C,0x3C,0x18,0x00,0x33,0x66,0xCC,0x66,0x33,0x00,0x00,0x00,0xCC,0x66,0x33,0x66,0xCC,0x00,0x00,
0x22,0x88,0x22,0x88,0x22,0x88,0x22,0x88,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0xDD,0x77,0xDD,0x77,0xDD,0x77,0xDD,0x77,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0x18,0x18,0x18,0x18,0x18,0xF8,0x18,0xF8,0x18,0x18,0x18,0x36,0x36,0x36,0x36,0xF6,0x36,0x36,0x36,0x00,0x00,0x00,0x00,0xFE,0x36,0x36,0x36,
0x00,0x00,0xF8,0x18,0xF8,0x18,0x18,0x18,0x36,0x36,0xF6,0x06,0xF6,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x00,0x00,0xFE,0x06,0xF6,0x36,0x36,0x36,0x36,0x36,0xF6,0x06,0xFE,0x00,0x00,0x00,0x36,0x36,0x36,0x36,0xFE,0x00,0x00,0x00,0x18,0x18,0xF8,0x18,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x18,0x18,0x18,
0x18,0x18,0x18,0x18,0x1F,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x18,0x18,0x18,0x18,0xFF,0x18,0x18,0x18,0x18,0x18,0x1F,0x18,0x1F,0x18,0x18,0x18,0x36,0x36,0x36,0x36,0x37,0x36,0x36,0x36,
0x36,0x36,0x37,0x30,0x3F,0x00,0x00,0x00,0x00,0x00,0x3F,0x30,0x37,0x36,0x36,0x36,0x36,0x36,0xF7,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xF7,0x36,0x36,0x36,0x36,0x36,0x37,0x30,0x37,0x36,0x36,0x36,0x00,0x00,0xFF,0x00,0xFF,0x00,0x00,0x00,0x36,0x36,0xF7,0x00,0xF7,0x36,0x36,0x36,0x18,0x18,0xFF,0x00,0xFF,0x00,0x00,0x00,
0x36,0x36,0x36,0x36,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0xFF,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0xFF,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0x3F,0x00,0x00,0x00,0x18,0x18,0x1F,0x18,0x1F,0x00,0x00,0x00,0x00,0x00,0x1F,0x18,0x1F,0x18,0x18,0x18,0x00,0x00,0x00,0x00,0x3F,0x36,0x36,0x36,0x36,0x36,0x36,0x36,0xF7,0x36,0x36,0x36,
0x18,0x18,0xFF,0x00,0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x18,0x18,0x18,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,
0x00,0x00,0x76,0xDC,0xC8,0xDC,0x76,0x00,0x00,0x78,0xCC,0xF8,0xCC,0xF8,0xC0,0xC0,0x00,0xFE,0xC6,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0xFE,0x6C,0x6C,0x6C,0x6C,0x6C,0x00,0xFE,0x66,0x30,0x18,0x30,0x66,0xFE,0x00,0x00,0x00,0x7E,0xCC,0xCC,0xCC,0x78,0x00,0x00,0x66,0x66,0x66,0x66,0x7C,0x60,0xC0,0x00,0x76,0xDC,0x18,0x18,0x18,0x18,0x00,
0xFC,0x30,0x78,0xCC,0xCC,0x78,0x30,0xFC,0x38,0x6C,0xC6,0xFE,0xC6,0x6C,0x38,0x00,0x38,0x6C,0xC6,0xC6,0x6C,0x6C,0xEE,0x00,0x1C,0x30,0x18,0x7C,0xCC,0xCC,0x78,0x00,0x00,0x00,0x7E,0xDB,0xDB,0x7E,0x00,0x00,0x06,0x0C,0x7E,0xDB,0xDB,0x7E,0x60,0xC0,0x3C,0x60,0xC0,0xFC,0xC0,0x60,0x3C,0x00,0x78,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0x00,
0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0x00,0x30,0x30,0xFC,0x30,0x30,0x00,0xFC,0x00,0x60,0x30,0x18,0x30,0x60,0x00,0xFC,0x00,0x18,0x30,0x60,0x30,0x18,0x00,0xFC,0x00,0x0E,0x1B,0x1B,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xD8,0xD8,0x70,0x30,0x30,0x00,0xFC,0x00,0x30,0x30,0x00,0x00,0x72,0x9C,0x00,0x72,0x9C,0x00,0x00,
0x38,0x6C,0x6C,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x00,0x0F,0x0C,0x0C,0x0C,0xEC,0x6C,0x3C,0x1C,0x78,0x6C,0x6C,0x6C,0x6C,0x00,0x00,0x00,0x78,0x0C,0x38,0x60,0x7C,0x00,0x00,0x00,0x00,0x00,0x3C,0x3C,0x3C,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

char icns[768]={
0x7F,0xFF,0xFF,0xF8,0xFC,0x00,0x00,0x3C,0xFC,0x00,0x1F,0x3E,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,
0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF1,0xFF,0xFF,0x8F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF1,0xFF,0xFF,0x8F,
0xF0,0x00,0x00,0x0F,0xB0,0x00,0x00,0x0F,0x90,0x00,0x00,0x0F,0xB1,0xFF,0xFF,0x8F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xFE,
0x7F,0xFF,0xFF,0xF8,0xFC,0x00,0x00,0x3C,0xFC,0x00,0x1F,0x3E,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x1F,0x3F,
0xFC,0x00,0x1F,0x3F,0xFC,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,
0xF0,0x00,0x00,0x0F,0xB0,0x00,0x00,0x0F,0x90,0x00,0x00,0x0F,0xB0,0x00,0x00,0x0F,0xF1,0xFF,0xFF,0x8F,0xF0,0x00,0x00,0x0F,0xF0,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xFE,
0x00,0x00,0x00,0x00,0x00,0x78,0x1E,0x00,0x00,0xFC,0x3F,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x01,0xFF,0xFF,0x80,0x03,0xFF,0xFF,0xC0,
0x3F,0xFE,0x3F,0xFC,0x7F,0xF0,0x0F,0xFE,0x7F,0xE0,0x07,0xFE,0x7F,0xC0,0x03,0xFE,0x7F,0x80,0x01,0xFE,0x3F,0x80,0x01,0xFC,0x1F,0x00,0x01,0xF8,0x1F,0x00,0x00,0xF8,
0x1F,0x00,0x00,0xF8,0x1F,0x80,0x00,0xF8,0x3F,0x80,0x01,0xFC,0x7F,0x80,0x01,0xFE,0x7F,0xC0,0x03,0xFE,0x7F,0xE0,0x07,0xFE,0x7F,0xF0,0x0F,0xFE,0x3F,0xFC,0x7F,0xFC,
0x03,0xFF,0xFF,0xC0,0x01,0xFF,0xFF,0x80,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x00,0xFC,0x3F,0x00,0x00,0x78,0x1E,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xC0,0x00,0x00,0xC0,0x60,0x00,0x00,0x80,0x30,0x00,0x00,0x80,0x1F,0xFF,0xFF,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,
0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,
0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0xC0,0x00,0x00,0x03,0x7F,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x07,0xFF,0xFF,0xE0,0x0E,0xFF,0xFF,0x70,0x0C,0x7F,0xFE,0x30,0x0E,0xFF,0xFF,0x70,0x0F,0xFF,0xFF,0xF0,0x0F,0xFF,0xFF,0xF0,0x0F,0xFC,0x3F,0xF0,0x0F,0xE0,0x07,0xF0,
0x0F,0xC0,0x03,0xF0,0x0F,0x80,0x01,0xF0,0x0F,0x00,0x00,0xF0,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0E,0x00,0x00,0x70,0x0C,0x01,0x80,0x30,0x0C,0x02,0x40,0x30,
0x0C,0x02,0x40,0x30,0x0C,0x01,0x80,0x30,0x0E,0x00,0x00,0x70,0x0E,0x00,0x70,0x70,0x0E,0x00,0x38,0x70,0x0F,0x00,0x38,0xF0,0x0F,0x80,0x1D,0xF0,0x0F,0xC0,0x1F,0xF0,
0x0F,0xE0,0x0F,0xF0,0x0F,0xFC,0x3F,0xF0,0x0F,0xFF,0xFF,0xF0,0x0F,0xFF,0xFF,0xF0,0x0E,0xFF,0xFF,0x70,0x0C,0x7F,0xFE,0x30,0x0E,0xFF,0xFF,0x70,0x07,0xFF,0xFF,0xE0,
0x00,0x00,0x00,0x00,0x00,0x66,0x66,0x00,0x00,0x66,0x66,0x00,0x00,0x66,0x66,0x00,0x1F,0xFF,0xFF,0xF0,0x18,0x66,0x66,0x30,0x18,0x66,0x66,0x30,0x18,0x00,0x00,0x30,
0x18,0x00,0x00,0x30,0xFE,0x00,0x00,0xFE,0xFE,0x00,0x00,0xFE,0x18,0x1F,0xF0,0x30,0x18,0x10,0x30,0x30,0xFE,0x10,0x30,0xFE,0xFE,0x10,0x30,0xFE,0x18,0x10,0x30,0x30,
0x18,0x10,0x30,0x30,0xFE,0x10,0x30,0xFE,0xFE,0x10,0x30,0xFE,0x18,0x1F,0xF0,0x30,0x18,0x1F,0xF0,0x30,0xFE,0x00,0x00,0xFE,0xFE,0x00,0x00,0xFE,0x18,0x00,0x00,0x30,
0x18,0x00,0x00,0x30,0x18,0x66,0x66,0x30,0x18,0x66,0x66,0x30,0x1F,0xFF,0xFF,0xF0,0x00,0x66,0x66,0x00,0x00,0x66,0x66,0x00,0x00,0x66,0x66,0x00,0x00,0x00,0x00,0x00};

void gcls(char v){
  int i,j;
  char far* ptr = (char far *)0xb0000000;
  for (j=0;j<4;j++){
    for (i=0;i<0x1eef;i++) ptr[i]=v;
    ptr +=  0x2000;
  }
  return;
}

void cls(){  
  int x;
  char far* ptr = (char far *)0xb0000000;
  for (x=0;x<4000;x++) ptr[x]=0x20;
  return;
  }

void Screen(int mode){
  int i;
  if (mode==0){
    _AX=0x02;
    asm int 10h;
    outp(0x3bf,0x00);outp(0x3b8,0x28);
    for (i=0; i<18; i++) {outp(0x3b4,i);outp(0x3b5,te6845[i]);}
    cls();
  }
  else{
    outp(0x3b8,0x00);outp(0x3bf,0x03);
    for (i=0; i<18; i++) {outp(0x3b4,i);outp(0x3b5,gr6845[i]);}
    outp(0x3b8,0x06);gcls(0x00);outp(0x3b8,0x0e);
    gcls(0x00);
  }
  return;
}

typedef struct { int x,y;} pair;

int Mouse(){
  _AX=0;
  asm int 33h;
  return _AX;
  }

int MouseOn(){
  _AX=1;
  asm int 33h;
  return _AX;
  }
  
int MouseOff(){
  _AX=2;
  asm int 33h;
  return _AX;
  }
  
int MousePress(){
  _AX=5;
  _BX=0;
  asm int 33h;
  return _AX;
}

pair MouseGet(){
  pair answer;
  _AX=3;
  asm int 33h;
  answer.x = _CX;
  answer.y = _DX;
  return answer;
  }
  
void MouseSet(pair p){
  _CX=p.x;
  _DX=p.y;
  _AX=4;
  asm int 33h;
  return;
  }
  
int MouseAt(int x1,int y1,int x2,int y2){
  pair p;
  p = MouseGet();
  if (p.x<x1) return 0;
  if (p.x>x2) return 0;
  if (p.y<y1) return 0;
  if (p.y>y2) return 0;
  return 1;
  }

  
void dot0(int x,int y){
  ((char far *)0xb0000000)[byte_addr(x,y)] &= ~bit_pos(x);
  return;
}

void dot1(int x,int y){
   ((char far *)0xb0000000)[byte_addr(x,y)] |= bit_pos(x);
  return;
}  

void Line0(int x0,int y0,int x1,int y1){
  int dx,sx,dy,sy,err,e2;
    dx = abs(x1-x0);
    dy = -abs(y1-y0);
    err = dx+dy; 
    for(;;){
        dot1(x0,y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2*err;
        if (e2 >= dy){err += dy; x0++;}
        if (e2 <= dx){err += dx; y0++;}
        }
    return;
  }
  
void Line1(int x0,int y0,int x1,int y1){
  int dx,dy,err,e2;
    dx = abs(x1-x0);
    dy = -abs(y1-y0);
    err = dx+dy; 
    for(;;){
        dot1(x0,y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2*err;
        if (e2 >= dy){err += dy; x0++;}
        if (e2 <= dx){err += dx; y0--;}
        }
    return;
  }

void Line(int x0,int y0,int x1,int y1){
  if (x0>x1){
    if (y1<y0) Line0(x1,y1,x0,y0);
    else       Line1(x1,y1,x0,y0);
    }
  else{
    if (y0<y1) Line0(x0,y0,x1,y1);
    else       Line1(x0,y0,x1,y1);
    
    }
    return;
}

void DrawChar(int x,int y,char c){
  int px,py,cc;
  cc = c; /* each char is 8 bytes long */
  cc = cc*8;
  for (py=0;py<8;py++)  for (px=0;px<8;px++) {
    if (fnt8[cc+py]&(128>>px)) 
      dot1(x+px,y+py);
    else
      dot0(x+px,y+py);
    }
  }

void DrawChar1(int x,int y,char c){
  int px,py,cc;
  cc = c; /* each char is 8 bytes long */
  cc = cc*8;
  for (py=0;py<8;py++)  for (px=0;px<8;px++) {
    if (fnt8[cc+py]&(128>>px)) 
      dot0(x+px,y+py);
    else
      dot1(x+px,y+py);
    }
  }

void DrawIcon32(int x,int y,char c){
  int px,py,cc,xl,xh;
  cc = c; /* each icon is 128 bytes long */
  cc = cc*128; 
  for (py=0;py<32;py++)  for (px=0;px<32;px++) {
    if (icns[cc+py*4+px/8]&(128>>(px&7))) 
      dot1(x+px,y+py);
    else
      dot0(x+px,y+py);
    }
  }
  
void GPrint(int x,int y,char* ptr){
  while(*ptr){
    DrawChar(x,y,*ptr);
    x=x+8;
    ptr++;
    }
  return;
}

void GPrint1(int x,int y,char* ptr){
  while(*ptr){
    DrawChar1(x,y,*ptr);
    x=x+8;
    ptr++;
    }
  return;
}

/*
void Line(int x0,int y0,int x1,int y1){
  int dx,sx,dy,sy,err,e2;
    dx = abs(x1-x0);
    sx = x0<x1 ? 1 : -1;
    dy = -abs(y1-y0);
    sy = y0<y1 ? 1 : -1;
    err = dx+dy; 
    for(;;){
        dot1(x0,y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2*err;
        if (e2 >= dy){err += dy; x0 += sx;}
        if (e2 <= dx){err += dx; y0 += sy;}
        }
    return;
  }
*/

int main(int argc,char **argv){ 
  int x;
  
  Screen(1);  
  gcls(0);
  getch();
  gcls(0xff);
  getch();
  for (x=0;x<43;x++) {gcls(0xaa);  gcls(0x55);}
  getch();
  gcls(0);
  getch();
  for (x=0;x<43;x++)  {
    GPrint (120+x*8,x*8,"Hello World!!!");
    GPrint1 (8+x*8,x*8,"Hello World!!!");
  }
  getch();
  DrawIcon32(280,16,3);
  DrawIcon32(320,16,2);
  DrawIcon32(360,16,4);
  DrawIcon32(400,16,5);
  DrawIcon32(440,16,1);
  getch();
  for (x=0;x<348;x+=3) Line(0,174,719,x);
  for (x=0;x<348;x+=3) Line(719,174,0,x);
  getch();
  for (x=0;x<43;x++)  {
    GPrint (120+x*8,x*8,"Hello World!!!");
    GPrint1 (8+x*8,x*8,"Hello World!!!");
  }
  getch();
  DrawIcon32(280,16,3);
  DrawIcon32(320,16,2);
  DrawIcon32(360,16,4);
  DrawIcon32(400,16,5);
  DrawIcon32(440,16,1);
  getch();
  
  Screen(0);
  return 0;
}

