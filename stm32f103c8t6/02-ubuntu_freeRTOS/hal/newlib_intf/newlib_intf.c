#include <stdio.h>
#include "usart.h"

#pragma import(__use_no_semihosting)                           
struct __FILE  { 
	int handle; 
};
struct stat {
	off_t st_size;
};
typedef char *caddr_t;
typedef long int off_t;
typedef int pid_t;

FILE __stdout;

int fputc(int ch, FILE *f)
{
	while((USART1->SR & 0X40) == 0);
    USART1->DR = (u8) ch;

	return ch;
}

void _sys_exit(int x) { x = x; }
int _write_r (struct _reent *ptr, int fd, const char *buf, size_t nbyte) { ; }
caddr_t _sbrk_r (struct _reent *ptr, ptrdiff_t incr) { ; }
int _close_r (struct _reent *ptr, int fd) { ; }
void abort (void) { while(1); }
int _read_r (struct _reent *ptr, int fd, char *buf, size_t nbyte) { ; }
off_t _lseek_r (struct _reent *ptr, int fd, off_t pos, int whence) { ; }
int _fstat_r (struct _reent *ptr, int fd, struct stat *buf) { ; }
int _isatty_r (struct _reent *ptr, int fd) { ; }
int _kill_r (struct _reent *ptr, pid_t pid, int sig) { ; }
pid_t _getpid_r (struct _reent *ptr, pid_t *pid) { ; }