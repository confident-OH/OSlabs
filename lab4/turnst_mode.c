#include "main.h"

void turnst_mode(char *mode, long int stmode)
{
    //st_mode转换为字符串
    switch(stmode & S_IFMT){
        case S_IFLNK:{
            mode[0] = 'l';
            break;
        }
        case S_IFDIR: {
            mode[0] = 'd';
            break;
        }
        case S_IFREG: {
            mode[0] = '-';
            break;
        }
        case S_IFBLK: {
            mode[0] = 'b';
            break;
        }
        case S_IFCHR:{
            mode[0] = 'c';
            break;
        }
        case S_IFSOCK: {
            mode[0] = 's';
            break;
        }
        case S_IFIFO: {
            mode[0] = 'P';
            break;
        }
        default:{
            mode[0] = '?';
        }
    }
    //文件所有者权限
    mode[1] = (stmode & S_IRUSR) ? 'r':'-';
    mode[2] = (stmode & S_IWUSR) ? 'w':'-';
    mode[3] = (stmode & S_IXUSR) ? 'x':'-';
    //文件所属组权限
    mode[4] = (stmode & S_IRGRP) ? 'r':'-';
    mode[5] = (stmode & S_IWGRP) ? 'w':'-';
    mode[6] = (stmode & S_IXGRP) ? 'x':'-';
    //其他人权限
    mode[7] = (stmode & S_IROTH) ? 'r':'-';
    mode[8] = (stmode & S_IWOTH) ? 'w':'-';
    mode[9] = (stmode & S_IXOTH) ? 'x':'-';
}

