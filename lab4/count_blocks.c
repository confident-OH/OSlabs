#include "main.h"

int count_blocks(char *dir_path)
{
    DIR* diradd;
    diradd = opendir(dir_path);
    struct dirent* folders;
    struct stat fileadd;
    unsigned long result = 0;
    if(stat(dir_path, &fileadd)==-1){
        printf("open failed!\n\n");
    }
    //result += fileadd.st_blocks;
    while((folders = readdir(diradd)) != NULL){
        char file_path[256];
        char opmode[11];
        char *opuser;
        char *opgroup;
        long int opsize;
        short opnlinks;
        opmode[10] = '\0';
        if(strcmp(folders->d_name, "..")&&strcmp(folders->d_name, ".")){
            // unsigned long  st_blocks;
            memset(file_path, 0, 256);
            strcpy(file_path, dir_path);
            file_path[strlen(file_path)] = '/';
            file_path[strlen(file_path)] = '\0';
            strcat(file_path, folders->d_name);
            if(stat(file_path, &fileadd)==-1){
                printf("open failed!\n\n");
            }
            if(folders->d_type == 4){
                result+=fileadd.st_blocks;
            }else{
                result+=fileadd.st_blocks;
            }
        }     
    }
    closedir(diradd);
    return result/2;
}
