#ifdef CS333_P2
#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
  if(argc == 1) {
    printf(1, "(null) ran in 0.00\n");
  } 
  else {
    int start = uptime();
    int pid = fork();

    if (pid > 0) {
      pid = wait();
    } 
    else if (pid == 0) {
      exec(argv[1], argv+1);
      printf(1, "ERROR: Unknown Command\n");
      kill(getppid());
      exit();
    } 
    else {
      printf(1, "ERROR: Fork error return -1\n");
    }

    int end = uptime();
    int interval = end - start;
    int seconds = interval/1000;
    int milSec = interval % 1000;
    char *milSecZero = "";

    if (milSec < 10) {
      milSecZero = "00";
    } 
    else if (milSec < 100) {
      milSecZero = "0";
    }

    printf(
      1,"%s ran in %d.%s%d\n",argv[1],seconds,milSecZero,milSec
    );
  }

  exit();
}
#endif
