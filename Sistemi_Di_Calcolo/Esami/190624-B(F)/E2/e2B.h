#ifndef __E2__
#define __E2__
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <fcntl.h>
void make_files(int n, void (*f)(int i, char name[64], char buf[256]));

#endif
