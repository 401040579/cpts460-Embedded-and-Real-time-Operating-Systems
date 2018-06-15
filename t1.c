/********** test.c file *************/
#include "ucode.c"

int main(int argc, char *argv[ ])
{
  int i;

  int pid = getpid();
  printf("t1.c proc %d running test program\n", pid);

  printf("t1.c argc = %d\n", argc);
  for (i=0; i<argc; i++)
    printf("t1.c argv[%d] = %s\n", i, argv[i]);
  printf(" t1.c exit\n");
}
