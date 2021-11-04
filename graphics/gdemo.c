typedef struct { int x,y;} pair;

void Screen(int mode){
  if (mode==0){
    _AX=0x3;
    asm int 10h;
    }
  if (mode==12){
    _AX=0x12;
    asm int 10h;
    }
  return;
  }

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

void Pset(int x,int y,int c){
  _CX = x;
  _DX = y;
  _BH = 0;
  _AX = c;
  _AH = 0x0c;
  asm int 10h;  
  }
  
void Line(int x0,int y0,int x1,int y1,int c){
  int dx,sx,dy,sy,err,e2;
    dx = abs(x1-x0);
    sx = x0<x1 ? 1 : -1;
    dy = -abs(y1-y0);
    sy = y0<y1 ? 1 : -1;
    err = dx+dy; 
    for(;;){
        {  
        _CX = x0;
        _DX = y0;
        _BH = 0;
        _AX = c;
        _AH = 0x0c;
        asm int 10h; 
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = 2*err;
        if (e2 >= dy){err += dy; x0 += sx;}
        if (e2 <= dx){err += dx; y0 += sy;}
        }
    return;
  }

int main(int argc,char **argv){ 
  int x;
  
  Screen(12);
  
  for (x=0;x<480;x++) Line(0,240,639,x,7);
  for (x=0;x<480;x++) Line(639,240,0,x,9);
  
  Screen(0);
  return 0;
}

