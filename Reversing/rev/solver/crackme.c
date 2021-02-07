#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/sendfile.h>
#include <fcntl.h>

void __attribute__((constructor)) setup()
{
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  alarm(0x30);
}


int check(char* buffer, size_t len)
{
  // make sure the key is in ascii range
  for(int i=0; i<len; i++) {
    if(buffer[i] < '0' || buffer[i] > 'z') {
      return 0;
    }
  }

  if((buffer[0] + buffer[3]) != 100) {
    return 0;
  }

  if((buffer[1] + buffer[18]) != 214) {
    return 0;
  }

  if((buffer[2] + buffer[4]) != 178) {
    return 0;
  }

  if((buffer[5] ^ buffer[6]) != 76) {
    return 0;
  }

  if((buffer[8] - buffer[7]) != 17) {
    return 0;
  }

  if((buffer[10] - buffer[9]) != 59) {
    return 0;
  }

  if((buffer[11] + buffer[12] - buffer[13]) != 69) {
    return 0;
  }

  if((buffer[14] + buffer[15] - buffer[16]) != 31) {
    return 0;
  }

  if((buffer[17] + buffer[16] - buffer[18]) != 88) {
    return 0;
  }

  if((buffer[19] ^ buffer[20] ^ buffer[21]) != 69) {
    return 0;
  }

  return 1;
}

int main()
{
  char buffer[256];
  printf("Enter key: ");
  size_t bytes_read = read(0, buffer, 255);
  buffer[bytes_read-1] = 0;
  if(check(buffer, bytes_read-1))
  {
    printf("Congrats here is your flag: ");
    sendfile(1, open("/flag", 0), 0, 0x100);
  }
  else
  {
    puts("Invalid key");
  }
  return 0;
}
