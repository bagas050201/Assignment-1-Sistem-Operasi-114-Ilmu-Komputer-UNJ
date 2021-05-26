#ifdef CS333_P2
#include "types.h"
#include "user.h"
#include "uproc.h"

#define MAX 16

int
main(void)
{
  struct uproc *proc = malloc(sizeof(struct uproc)*MAX);
  int MaxNumber = getprocs(MAX, proc);
  printf(1,"PID\tName\t\tUID\tGID\tPPID\tElapsed\tCPU\tState\tSize\n");

  int i;
  for(i = 0; i < MaxNumber; i++){
    struct uproc currentProc = proc[i];
    uint getElapsedTicks = currentProc.elapsed_ticks;
    uint Second = getElapsedTicks/1000;
    uint milSecond = getElapsedTicks%1000;
    char* zero = "";
    uint getCpuTotalTicks = currentProc.CPU_total_ticks;
    uint cpuTotalSecond = getCpuTotalTicks/1000;
    uint cpuTotalMilSecond = getCpuTotalTicks % 1000;
    char* cpuZero = "";

    if (milSecond < 10) {
      zero = "00";
    } 
    else if (milSecond < 100) {
      zero = "0";
    }

    if(cpuTotalMilSecond < 10){
      cpuZero = "00";
    } 
    else if (cpuTotalMilSecond < 100) {
      cpuZero = "0";
    }

    printf(
      1,
      "%d\t%s\t\t%d\t%d\t%d\t%d.%s%d\t%d.%s%d\t%s\t%d\n",
      currentProc.pid,currentProc.name,currentProc.uid,currentProc.gid,currentProc.ppid,
      Second,zero,milSecond,cpuTotalSecond,cpuZero,cpuTotalMilSecond,
      currentProc.state,currentProc.size
    );
  }

  free(proc);
  exit();
}
#endif
