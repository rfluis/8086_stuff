#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int main(int argc,char **argv){ 
  char far * ptr;
  unsigned int chunk;
  unsigned int idx;
  FILE * out;
  char buf[32768];
  ptr=0;
  
  out = fopen("mem","w+");
  for (chunk=0;chunk<32;chunk++){
    printf("Reading ... %2d",chunk);
    for (idx=0;idx<32768;idx++) buf[idx]=ptr[idx];
    printf(" Writing ... %2d \n ",chunk);
    fwrite(buf,4096,8,out);
    ptr+=32768;
    }
  fclose(out);
  return 0;
}

