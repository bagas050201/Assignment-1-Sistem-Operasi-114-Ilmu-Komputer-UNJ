<h1 align="center"> ASSIGNMENT 1 REPORT </h1>
<br>

## Modified Code

notes : 
- point yang dimaksud adalah rujukan pengerjaan pada file assignment1.pdf
- line sebelum, didapat dari file default xv6-pdx.tar
- line sesudah, didapat dari file xv6-pdx github repository

### Xv6 Makefile & Conditional compilation (point 1 dan 2)

#### Makefile

`Sebelum`
- line 3-4
```
CS333_PROJECT ?= 0
PRINT_SYSCALLS ?= 0
```

`Sesudah`
- line 4-5
```
CS333_PROJECT ?= 1
PRINT_SYSCALLS ?= 1
```

###  Implementing a new system call (Point 3)

#### Syscall.c
`Sebelum`
- line 166 - 180

```
void
syscall(void)
{
  int num;
  struct proc *curproc = myproc();

  num = curproc->tf->eax;
  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    curproc->tf->eax = syscalls[num]();
  } else {
    cprintf("%d %s: unknown sys call %d\n",
            curproc->pid, curproc->name, num);
    curproc->tf->eax = -1;
  }
}
```
`Sesudah`
- line 177 - 198

```
void
syscall(void)
{
  int num;
  struct proc *curproc = myproc();

  num = curproc->tf->eax;
  //point 3
  #ifdef CS333_P1
    #ifdef PRINT_SYSCALLS
      cprintf("%s -> %d \n", syscallnames[num], num);
    #endif
  #endif

  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    curproc->tf->eax = syscalls[num]();
  } else {
    cprintf("%d %s: unknown sys call %d\n",
            curproc->pid, curproc->name, num);
    curproc->tf->eax = -1;
  }
}
```

###  Creating a new user command & The xv6 process structure (Point 4 dan 5)

#### Makefile
`Sebelum`
```
CS333_PROJECT ?= 0
PRINT_SYSCALLS ?= 0
CS333_UPROGS += #_date
```

`Sesudah`
```
CS333_PROJECT ?= 1
PRINT_SYSCALLS ?= 1
CS333_UPROGS += _date
```
#### syscall.c
`Sebelum`
- line 85 - 108

```
extern int sys_chdir(void);
extern int sys_close(void);
extern int sys_dup(void);
extern int sys_exec(void);
extern int sys_exit(void);
extern int sys_fork(void);
extern int sys_fstat(void);
extern int sys_getpid(void);
extern int sys_kill(void);
extern int sys_link(void);
extern int sys_mkdir(void);
extern int sys_mknod(void);
extern int sys_open(void);
extern int sys_pipe(void);
extern int sys_read(void);
extern int sys_sbrk(void);
extern int sys_sleep(void);
extern int sys_unlink(void);
extern int sys_wait(void);
extern int sys_write(void);
extern int sys_uptime(void);
#ifdef PDX_XV6
extern int sys_halt(void);
#endif // PDX_XV6
```

`Sesudah`
- line 85 - 114

```
extern int sys_chdir(void);
extern int sys_close(void);
extern int sys_dup(void);
extern int sys_exec(void);
extern int sys_exit(void);
extern int sys_fork(void);
extern int sys_fstat(void);
extern int sys_getpid(void);
extern int sys_kill(void);
extern int sys_link(void);
extern int sys_mkdir(void);
extern int sys_mknod(void);
extern int sys_open(void);
extern int sys_pipe(void);
extern int sys_read(void);
extern int sys_sbrk(void);
extern int sys_sleep(void);
extern int sys_unlink(void);
extern int sys_wait(void);
extern int sys_write(void);
extern int sys_uptime(void);
#ifdef PDX_XV6
extern int sys_halt(void);
#endif // PDX_XV6

//point 4 dan 5
#ifdef CS333_P1
// internally, the function prototype must be ???int??? not ???uint??? for sys_date()
extern int sys_date(void);
#endif // CS333_P1
```

`Sebelum`
- line 110 - 135

```
static int (*syscalls[])(void) = {
[SYS_fork]    sys_fork,
[SYS_exit]    sys_exit,
[SYS_wait]    sys_wait,
[SYS_pipe]    sys_pipe,
[SYS_read]    sys_read,
[SYS_kill]    sys_kill,
[SYS_exec]    sys_exec,
[SYS_fstat]   sys_fstat,
[SYS_chdir]   sys_chdir,
[SYS_dup]     sys_dup,
[SYS_getpid]  sys_getpid,
[SYS_sbrk]    sys_sbrk,
[SYS_sleep]   sys_sleep,
[SYS_uptime]  sys_uptime,
[SYS_open]    sys_open,
[SYS_write]   sys_write,
[SYS_mknod]   sys_mknod,
[SYS_unlink]  sys_unlink,
[SYS_link]    sys_link,
[SYS_mkdir]   sys_mkdir,
[SYS_close]   sys_close,
#ifdef PDX_XV6
[SYS_halt]    sys_halt,
#endif // PDX_XV6
};
```

`Sesudah`
- line 116 - 146

```
static int (*syscalls[])(void) = {
[SYS_fork]    sys_fork,
[SYS_exit]    sys_exit,
[SYS_wait]    sys_wait,
[SYS_pipe]    sys_pipe,
[SYS_read]    sys_read,
[SYS_kill]    sys_kill,
[SYS_exec]    sys_exec,
[SYS_fstat]   sys_fstat,
[SYS_chdir]   sys_chdir,
[SYS_dup]     sys_dup,
[SYS_getpid]  sys_getpid,
[SYS_sbrk]    sys_sbrk,
[SYS_sleep]   sys_sleep,
[SYS_uptime]  sys_uptime,
[SYS_open]    sys_open,
[SYS_write]   sys_write,
[SYS_mknod]   sys_mknod,
[SYS_unlink]  sys_unlink,
[SYS_link]    sys_link,
[SYS_mkdir]   sys_mkdir,
[SYS_close]   sys_close,
#ifdef PDX_XV6
[SYS_halt]    sys_halt,
#endif // PDX_XV6

//point 4 dan 5
#ifdef CS333_P1
[SYS_date]    sys_date,
#endif
};
```
#### syscall.h
`Sebelum`
- line 1 - 24

```
// System call numbers -- Portland State University version
#define SYS_fork    1
#define SYS_exit    SYS_fork+1
#define SYS_wait    SYS_exit+1
#define SYS_pipe    SYS_wait+1
#define SYS_read    SYS_pipe+1
#define SYS_kill    SYS_read+1
#define SYS_exec    SYS_kill+1
#define SYS_fstat   SYS_exec+1
#define SYS_chdir   SYS_fstat+1
#define SYS_dup     SYS_chdir+1
#define SYS_getpid  SYS_dup+1
#define SYS_sbrk    SYS_getpid+1
#define SYS_sleep   SYS_sbrk+1
#define SYS_uptime  SYS_sleep+1
#define SYS_open    SYS_uptime+1
#define SYS_write   SYS_open+1
#define SYS_mknod   SYS_write+1
#define SYS_unlink  SYS_mknod+1
#define SYS_link    SYS_unlink+1
#define SYS_mkdir   SYS_link+1
#define SYS_close   SYS_mkdir+1
#define SYS_halt    SYS_close+1
// student system calls begin here. Follow the existing pattern.
```

`Sesudah`
- line 1 - 26

```
// System call numbers -- Portland State University version
#define SYS_fork    1
#define SYS_exit    SYS_fork+1
#define SYS_wait    SYS_exit+1
#define SYS_pipe    SYS_wait+1
#define SYS_read    SYS_pipe+1
#define SYS_kill    SYS_read+1
#define SYS_exec    SYS_kill+1
#define SYS_fstat   SYS_exec+1
#define SYS_chdir   SYS_fstat+1
#define SYS_dup     SYS_chdir+1
#define SYS_getpid  SYS_dup+1
#define SYS_sbrk    SYS_getpid+1
#define SYS_sleep   SYS_sbrk+1
#define SYS_uptime  SYS_sleep+1
#define SYS_open    SYS_uptime+1
#define SYS_write   SYS_open+1
#define SYS_mknod   SYS_write+1
#define SYS_unlink  SYS_mknod+1
#define SYS_link    SYS_unlink+1
#define SYS_mkdir   SYS_link+1
#define SYS_close   SYS_mkdir+1
#define SYS_halt    SYS_close+1
// student system calls begin here. Follow the existing pattern.
//point 4 dan 5
#define SYS_date    SYS_halt+1
```

#### usys.S
`Sebelum`
- line 1 - 32

```
#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
SYSCALL(halt)
```
`Sesudah`
- line 1 - 33

```
#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
SYSCALL(halt)
SYSCALL(date)
```

#### user.h

`Sebelum`
- line 29 - 45

```
// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
#ifdef PDX_XV6
int atoo(const char*);
int strncmp(const char*, const char*, uint);
#endif // PDX_XV6
```

`Sesudah`
- line 29 - 49
```
// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
#ifdef PDX_XV6
int atoo(const char*);
int strncmp(const char*, const char*, uint);
#endif // PDX_XV6

#ifdef CS333_P1
int date(struct rtcdate*);
#endif // CS333_P1
```

#### sysproc.c

`Sebelum`
- batas paling bawah hanya sampai line 99

```
#endif // PDX_XV6
```

`Sesudah`
- line 101 - 111

```
//point 4 dan 5
#ifdef CS333_P1
int
sys_date(void)
{
  struct rtcdate *d;
  if(argptr(0, (void*)&d, sizeof(d)) < 0) return -1;
  cmostime(d);
  return 0;
}
#endif
```

### The control-p console command (point 6)

#### proc.h

`Sebelum`
- line 37 - 52

```
// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  uint pid;                    // Process ID
  struct proc *parent;         // Parent process. NULL indicates no parent
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)
};
```

`Sesudah`
- line 36 - 56

```
// Per-process state
struct proc {
  uint sz;                     // Size of process memory (bytes)
  pde_t* pgdir;                // Page table
  char *kstack;                // Bottom of kernel stack for this process
  enum procstate state;        // Process state
  uint pid;                    // Process ID
  struct proc *parent;         // Parent process. NULL indicates no parent
  struct trapframe *tf;        // Trap frame for current syscall
  struct context *context;     // swtch() here to run process
  void *chan;                  // If non-zero, sleeping on chan
  int killed;                  // If non-zero, have been killed
  struct file *ofile[NOFILE];  // Open files
  struct inode *cwd;           // Current directory
  char name[16];               // Process name (debugging)
  
  //point 6
  #ifdef CS333_P1
  uint start_ticks;
  #endif
};
```


#### proc.c

`Sebelum`
- line 147 - 153

```
 sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}
```

`Sesudah`
- line 146 - 158

```
sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  //control P point 6
  //ticks maksudnya mikrodetik, jadi ingin tau prosesnya dimulainya dari mikrodetik
  #ifdef CS333_P1 
  p -> start_ticks = ticks;
  #endif

  return p;
}
```

`Sebelum`
- line 562 - 569

```
#elif defined(CS333_P1)
void
procdumpP1(struct proc *p, char *state_string)
{
  cprintf("TODO for Project 1, delete this line and implement procdumpP1() in proc.c to print a row\n");
  return;
}
#endif
```

`Sesudah`
- line 563 - 598

```
#elif defined(CS333_P1)
//point 6
void
procdumpP1(struct proc *p, char *state_string)
{
  int i;
  uint pc[10];
  char *state;
  uint enumState = p -> state;

  if(enumState == 4){state = "Running";}
  else if(enumState == 3){state = "Runnable";}
  else if(enumState == 2){state = "Sleeping";}
  else if(enumState == 1){state = "Embryo";}
  else if(enumState == 0){state = "Unused";}
  else{
    state = "Zombie";
  }

  uint getTicks = ticks-p->start_ticks;
  uint ticksDiv = (getTicks) / 1000;
  uint ticksMod = getTicks % (ticksDiv*1000);

  cprintf("%d", getTicks);

  cprintf("\n%d\t%s\t%d.%d\t%s\t%d\t", p->pid, p->name, ticksDiv, ticksMod, state, p->sz);

  getcallerpcs((uint*)p->context->ebp+2, pc);

  for(i=0; i<10 && pc[i] != 0; i++)
    cprintf(" %p", pc[i]);

  cprintf("\n");
  return;
}
#endif
```
