//sender.c
////by geozak @ GitHub
#include "golay.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 0x5
//length 0x1 - 0x10
#define START 0xB3800000
//start 0x[0-F][0-F][0or8]00000

void transmitInt (unsigned int data) {
  printf("Transmit: 0x%X\n", data);
}

void sendPositions(int size, unsigned char values[]) {
  for (int i=0; i<size; i++) {
    unsigned int grouped = (i << 8) | (values[i] & 0xFF);
    unsigned int encoded = encode_golay( grouped );
    transmitInt(0xB3800000 |  encoded);
  }
}

#if(1)
void send (unsigned int data) {
  printf("Encoded: 0x%X\n", data);
  //startbit 101100111 + data
  transmitInt(data | 0xB3800000);
}

void main () {
  unsigned char set[LENGTH];
  int i;

  unsigned int data;

  //printf("Setting test values.\n");
  srand(time(NULL));
  for (i=0; i<LENGTH; i++) {
    set[i] = rand() & 0xFF;
  }

  //printf("Encrypting test values.\n");
  for (i=0; i<LENGTH; i++) {
    data = (i << 8) | (set[i] & 0xFF);
    printf("[%d]=0x%X (%d)->0x%X\n", i, set[i], set[i], data);
    send(encode_golay(data));
  }

  char ex = getchar();
  while (ex != 'q') {
    //printf("--------------------------------\n");
    for (i=0; i<LENGTH; i++) {
      set[i] = rand() & 0xFF;
      data = (i << 8) | (set[i] & 0xFF);
      printf("[%d]=0x%X (%d)->0x%X\n", i, set[i], set[i], data);
      send(encode_golay(data));
    }
    ex = getchar();
  };
}
#endif