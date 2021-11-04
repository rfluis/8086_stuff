/* Autor: Ricardo Francisco Luis Martínez 
 * Proyecto: 
 * Descripción: 
 * Licencia: 
 * Nombre del Archivo: 
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv){ 
  FILE *file;
  char *mem;
  size_t size;
  int i;
  file = fopen(argv[1],"rb");
  fseek(file,0,SEEK_END);
  size = ftell(file);
  rewind(file);
  mem = (char*) malloc(size);
  fread(mem,size,1,file);
  fclose(file);
  printf("char %s[%d]={\n",argv[2],size);
  for (i=0;i<size;i++) {
    printf("0x%02X",((int)mem[i])&0xff);
    if (i!=size-1) {
      printf(",");
      if ((i+1)%8==0) printf("\n");
      }
    else printf("};\n");
    }
  return 0;}

