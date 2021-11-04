/* Autor: Ricardo Francisco Luis Martínez 
 * Proyecto: 
 * Descripción: 
 * Licencia: 
 * Nombre del Archivo: 
*/
#include <stdio.h>
#include <stdlib.h>

#define byte_addr(x,y) (((y)/4)*90 + ((y)&3)*0x2000 + ((x)/8))
#define bit_pos(x)     (1 << (7 - ((x)&7)))
#define bit_num(x)     ((x)&7)
#define outp(port,data) _DX=port; _AL=data; asm out DX,AL

/* char far* screen = (char far *)0xb0000000; */
char gr6845[] = {0x38, 0x2d, 0x30, 0x08, 0x5a, 0x00, 0x57, 0x57, 0x02,	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
char te6845[] = {0x61, 0x50, 0x52, 0x0f, 0x19, 0x06, 0x19, 0x19, 0x02,	0x0d, 0x0b, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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

int main(int argc,char **argv){ 
  int x;
  
  Screen(1);  
  /* gcls(0); */
  for (x=0;x<348;x++) Line(0,174,719,x);
  for (x=0;x<348;x++) Line(719,174,0,x);
  Screen(0);
  return 0;
}

