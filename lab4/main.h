#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h> 
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

typedef struct pdir
{
    char dirname[256];
    struct pdir *next;
}pdir;

int count_blocks(char *dir_path);
void turnst_mode(char *mode, long int stmode);
void print_dir(char *dir_path);