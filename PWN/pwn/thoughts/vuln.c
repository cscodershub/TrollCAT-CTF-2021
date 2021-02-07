#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void __attribute__((constructor)) setup()
{
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  alarm(30);
}

char bad_thought[0x20];
char good_thought[0x200];

void good()
{
  read(0, good_thought, 0x1ff);
  puts("You are a nice hacker");
}

void bad()
{
  char bad_hacker_words[0x20];
  read(0, bad_thought, 0x20);
  strcpy(bad_hacker_words, bad_thought);
  printf("you are a bad hacker, you said: %s\n", bad_hacker_words);
}

int main()
{
  int i = 0;
  while(i<2) 
  {
    puts("1) send good thought\n2) send bad thoughts\n");
    int choice;
    printf("> ");
    scanf("%d", &choice);
    switch(choice)
    {
      case 1:
        good();
        break;
      case 2:
        bad();
        break;
      default:
        puts("Error: Invalid choice\nTry again...");
    }
    i++;
  }
}
