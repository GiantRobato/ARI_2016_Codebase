//reciever.c
//by geozak @ GitHub
#include "golay.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 0x5
//length 0x1 - 0xF
#define START 0xB3800000
//start 0x[0-F][0-F][0or8]00000

char *buffer;
size_t bufsize = 32;

unsigned int recieve () {
  static int initialized=0;

  if (!initialized) {
    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
      perror("Unable to allocate buffer");
      exit(1);
    }
  }
  
  do {
    printf("Enter packet: ");
    getline(&buffer,&bufsize,stdin);
  } while (strlen(buffer) == 0);
  unsigned int value = strtol(buffer, NULL, 16);
  if (value & START){
  }
  else {
    printf("Potential Error.\n");
  }
  return value & 0x7FFFFF;
  //return strtol(buffer, NULL, 16) & 0x7FFFFF;
}

void prettyprintset(unsigned int set[LENGTH]) {
  printf("[ '1' => 0x%X (%d)", set[1], set[1]);
  int i;
  for(i=1; i<LENGTH; i++) {
    printf(", '%d' => 0x%X (%d)", i, set[i], set[i]);
  }
  printf(" ]\n");
}

void main () {
  unsigned int set[LENGTH];
  int i;
  for (i=0; i<LENGTH; i++) {set[i] = 0;}

  while (1) {
    unsigned int data = recieve();
    data = decode_golay(data);
    printf("Decoded: 0x%X\n", data);
    i = (data & 0xF00) >> 8;
    if (i < LENGTH) {
      set[i] = data & 0xff;
      printf("0x%X -> [0x%X] = 0x%X (%d)\n", data, i, set[i], set[i]);
      //setmotor(i, set[i]);
    }
    else {
      printf("Index out of bounds. 0x%X -> [0x%X] = 0x%X (%d)\n", data, i, data & 0xff, data & 0xff);
    }
    prettyprintset(set);
  }
}