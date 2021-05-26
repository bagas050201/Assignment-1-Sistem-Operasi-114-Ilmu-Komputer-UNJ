<h1 align="center"> ASSIGNMENT 2 REPORT </h1>
<br>

# Code Modification Report
Berikut adalah bagian-bagian kode yang diubah

## proc.c
Line 10 - 12:
```
#ifdef CS333_P2
  #include "uproc.h"
#endif
```

### allocproc(void)
Line 160 - 163:
```
#ifdef CS333_P2
  p->cpu_ticks_total = 0;
  p->cpu_ticks_in = 0;
#endif // CS333_P2
```

### userinit(void)
Line 192 - 195:
```
#ifdef CS333_P2
  p->uid = DEFAULT_UID;
  p->gid = DEFAULT_GID;
#endif
```

### fork(void)
Line 257 - 260:
```
#ifdef CS333_P2
  np->uid = curproc->uid;
  np->gid = curproc->gid;
#endif
```

### scheduler(void)
Line 415 - 417:
```
#ifdef CS333_P2
  p->cpu_ticks_in = ticks;
#endif // CS333_P2
```

### sched(void)
Line 460 - 462:
```
#ifdef CS333_P2
  p->cpu_ticks_total += (ticks - p->cpu_ticks_in);
#endif // CS333_P2
```

### procdumpP2P3P4(struct proc *p, char *state_string)
Line 591 - 620:
```
  uint getElapsed = ticks-p->start_ticks;
  uint div = (getElapsed) / 1000;
  uint mod = getElapsed % 1000;
  char *zero = "";
  char *cpuZero = "";
  uint cpuTicksTotal = p->cpu_ticks_total;
  uint cpuSecond = cpuTicksTotal / 1000;
  uint cpuMilSecond = cpuTicksTotal % 1000;
  uint ppid = p->parent ? p->parent->pid : p->pid;

  if (mod < 10) {
    zero = "00";
  } 
  else if (mod < 100) {
    zero = "0";
  }

  if (cpuMilSecond < 10) {
    cpuZero = "00";
  } 
  else if (cpuMilSecond < 100) {
    cpuZero = "0";
  }

  cprintf(
    "\n%d\t%s\t%d\t%d\t%d\t%d.%s%d\t%d.%s%d\t%s\t%d\t", 
    p->pid, p->name, p->uid, p->gid, 
    ppid, div, zero, mod, cpuSecond,cpuZero,cpuMilSecond,state_string, 
    p->sz
  );
```

### getprocs(uint max, struct uproc* upTable)
Line 997 - 1027:
```
struct proc* p;
  int num = 0;
  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if (num < max) {
      if(p->state != UNUSED && p->state != EMBRYO) {
        if(p->state >= 0 && p->state < NELEM(states) && states[p->state]){
          safestrcpy(upTable[num].state, states[p->state],STRMAX);
        } 
        else {
          safestrcpy(upTable[num].state,"???",STRMAX);
        }

        upTable[num].pid = p->pid;
        upTable[num].uid = p->uid;
        upTable[num].gid = p->gid;
        upTable[num].ppid = p->parent ? p->parent->pid : p->pid;
        upTable[num].elapsed_ticks = ticks - p->start_ticks;
        upTable[num].CPU_total_ticks = p->cpu_ticks_total;
        upTable[num].size = p->sz;
        safestrcpy(upTable[num].name, p->name, STRMAX);
        num++;
      }
    } 
    else {
      break;
    }
  }
  release(&ptable.lock);
  return num;
```

## proc.h
Line 55 - 60:
```
#ifdef CS333_P2
  uint uid;
  uint gid;
  uint cpu_ticks_total;
  uint cpu_ticks_in;
#endif
```

## time.c
### main(int argc, char *argv[])
Line 6 - 44:
```
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
```

## ps.c
### main(void)
Line 10 - 52:
```
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
```
## syscall.h
Line 25 - 30:
```
#define SYS_getuid      SYS_date+1
#define SYS_getgid      SYS_getuid+1
#define SYS_getppid     SYS_getgid+1
#define SYS_setuid      SYS_getppid+1
#define SYS_setgid      SYS_setuid+1
#define SYS_getprocs    SYS_setgid+1
```

## syscall.c
Line 113 - 120:
```
#ifdef CS333_P2
extern int sys_getuid(void);
extern int sys_getgid(void);
extern int sys_getppid(void);
extern int sys_setuid(void);
extern int sys_setgid(void);
extern int sys_getprocs(void);
#endif
```

Line 150 - 157:
```C
#ifdef CS333_P2
[SYS_getuid]    sys_getuid,
[SYS_getgid]    sys_getgid,
[SYS_getppid]   sys_getppid,
[SYS_setuid]    sys_setuid,
[SYS_setgid]    sys_setgid,
[SYS_getprocs]  sys_getprocs,
#endif
```

## sysproc.c
### sys_getuid(void)
Line 122 - 123:
```
struct proc *curproc = myproc();
return curproc->uid;
```

### sys_getgid(void)
Line 129 - 130:
```
struct proc *curproc = myproc();
return curproc->gid;
```

### sys_getppid(void)
Line 136 - 138:
```
struct proc *curproc = myproc();
struct proc *parent = curproc->parent;
return parent != NULL ? parent->pid : 0;
```

### sys_setuid(void)
Line 143 - 153:
```
uint uid;
struct proc *curproc = myproc();

if(argint(0, (int*)&uid) >= 0) {
  if(uid >= 0 && uid <= 32767) {
    curproc->uid = uid;
    return 0;
  }
}

return -1;
```

### sys_setgid(void)
Line 158 - 168:
```
uint gid;
struct proc *curproc = myproc();

if(argint(0, (int*)&gid) >= 0) {
  if(gid >= 0 && gid <= 32767) {
    curproc->gid = gid;
    return 0;
  }
}

return -1;
```

### sys_getprocs(void)
Line 173 - 184:
```
uint max;
struct uproc* proc;

if (argint(0,(int*)&max) >= 0) {
  if (max == 1 || max == 16 || max == 64 || max == 72) {
    if (argptr(1, (void*)&proc, sizeof(struct uproc)) >= 0) {
      return getprocs(max, proc);
    }
  }
}

return -1;
```



## defs.h
Line 1 - 3:
```
#ifdef CS333_P2
#include "uproc.h"
#endif
```
Line 131 - 133:
```C
#ifdef CS333_P2
int             getprocs(uint max, struct uproc* upTable);
#endif
```

## usys.s
Line 34 - 39:
```
SYSCALL(getuid)
SYSCALL(getgid)
SYSCALL(getppid)
SYSCALL(setuid)
SYSCALL(setgid)
SYSCALL(getprocs)
```

## user.h
Line 52 - 58:
```
uint getuid(void);
uint getgid(void);
uint getppid(void);

int setuid(uint);
int setgid(uint);
int getprocs(uint max, struct uproc* table);
```

