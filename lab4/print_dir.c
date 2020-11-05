#include "main.h"

void print_dir(char *dir_path)
{
    pdir *dirhead = NULL, *dircurrent = NULL;
    DIR* diradd;
    diradd = opendir(dir_path);
    struct dirent* folders;
    struct tm* beijing;
    struct stat fileadd;
    unsigned long total = count_blocks(dir_path);
    printf("%s:\n", dir_path);
    printf("total %ld\n", total);
    while((folders = readdir(diradd)) != NULL){
        char file_path[256];
        char opmode[11];
        char *opuser;
        char *opgroup;
        long int opsize;
        short opnlinks;
        opmode[10] = '\0';
        if(strcmp(folders->d_name, "..")&&strcmp(folders->d_name, ".")){
            /*
            * st_mode: 文件类型和读取权限
            * st_nlink: 文件的硬连接数
            * st_uid: 用户ID
            * st_gid: 组ID
            * st_size: 文件字节数
            * st_mtime: 最后一次访问时间
            * 文件名
            */
            memset(file_path, 0, 256);
            strcpy(file_path, dir_path);
            file_path[strlen(file_path)] = '/';
            file_path[strlen(file_path)] = '\0';
            strcat(file_path, folders->d_name);
            if(stat(file_path, &fileadd)==-1){
                printf("open failed!\n\n");
            }
            beijing = localtime(&(fileadd.st_mtime));
            turnst_mode(opmode, fileadd.st_mode);
            opnlinks = fileadd.st_nlink;
            opuser = getpwuid(fileadd.st_uid)->pw_name;
            opgroup = getgrgid(fileadd.st_gid)->gr_name;
            opsize = fileadd.st_size;
            printf("%s ", opmode);
            printf("%hd ", opnlinks);
            printf("%s %s ", opuser, opgroup);
            printf("%6ld ", opsize);
            printf("%2d月 %2d %02d:%02d ", beijing->tm_mon+1,beijing->tm_mday,
						beijing->tm_hour,beijing->tm_min);
            printf("%s\n", folders->d_name);
            if(folders->d_type == 4){
                if(dirhead == NULL){
                    dirhead = (pdir*)malloc(sizeof(pdir));
                    strcpy(dirhead->dirname, file_path);
                    dirhead->next = NULL;
                    dircurrent = dirhead;
                }else{
                    dircurrent->next = (pdir*)malloc(sizeof(pdir));
                    dircurrent = dircurrent->next;
                    strcpy(dircurrent->dirname, file_path);
                    dircurrent->next = NULL;
                }
            }
        }     
    }
    printf("\n");
    while(dirhead!=NULL){
        print_dir(dirhead->dirname);
        dircurrent = dirhead;
        dirhead = dirhead->next;
        free(dircurrent);
    }
    closedir(diradd);
}
