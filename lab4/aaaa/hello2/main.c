#include "sem.h"

typedef struct data{
    char mem[512];
}data;

int main(int args, char** argv)
{
    if(args<3){
        printf("Commend Error!\n");
        exit(-1);
    }
    int shm_id, sem_id;
    int shm_lable;
    pid_t pid1, pid2;
    shm_id = shmget(100,  8*sizeof(data), IPC_CREAT|0666);
    shm_lable = shmget(101, 8*sizeof(unsigned int), IPC_CREAT|0666);
    if(shm_id == -1||shm_lable == -1){
        printf("Failed to build the shared memory\n");
        exit(-2);
    }
    sem_id = create_Sem(201814778, 2);
    set_N(sem_id, 0, 6);   //将文件写入共享内存
    set_N(sem_id, 1, 0);      //将共享内存中的数据输出文件
    pid1 = fork();
    if(pid1 == 0){
        //子进程1：将文件写入共享内存
        int p_id = 0;
        data* rw_data;
        unsigned int* rw_lable;
        unsigned int rw_size;
        rw_data = (data*)shmat(shm_id, NULL, SHM_W);
        rw_lable = (unsigned int*)shmat(shm_lable, NULL, SHM_W);
        FILE *fp = NULL;
        if((fp = fopen(argv[1], "r")) == NULL){
            printf("Failed to open the file(%s)!\n", argv[1]);
            *rw_lable = 0;
            V(sem_id, 1);
            return 0;
        }
        fseek(fp, 0, SEEK_END);
        long int value = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        int circle_n = value/512;
        int circle_end = value%512;
        while(1){
            P(sem_id, 0);
            if(circle_n>0){
                fread((rw_data+p_id)->mem, sizeof(char), 512, fp);
                *(rw_lable+p_id) = 512;
                p_id++;
                circle_n--;
                if(p_id == 8){
                    p_id = 0;
                }
                V(sem_id, 1);
            }else{
                fread((rw_data+p_id)->mem, sizeof(char), circle_end, fp);
                *(rw_lable+p_id) = circle_end;
                p_id++;
                circle_n--;
                if(p_id == 8){
                    p_id = 0;
                }
                V(sem_id, 1);
                *(rw_lable+p_id) = 0;   //告诉写进程文件已传输完毕
                V(sem_id, 1);
                break;
            }
        }
        fclose(fp);
        return 0;
    }else{
        pid2 = fork();
        if(pid2 == 0){
            //子进程2：将共享内存中的数据输出文件
            int p_id = 0;
            data* rw_data;
            unsigned int* rw_lable;
            unsigned int rw_size;
            rw_data = (data*)shmat(shm_id, NULL, SHM_R);
            rw_lable = (unsigned int*)shmat(shm_lable, NULL, SHM_R);
            FILE *fp = NULL;
            fp = fopen(argv[2], "w");
            while(1){
                P(sem_id, 1);
                rw_size = *(rw_lable+p_id);
                if(rw_size>0){
                    fwrite((rw_data+p_id)->mem, sizeof(char), rw_size, fp);
                    p_id++;
                    if(p_id == 8){
                        p_id = 0;
                    }
                    V(sem_id, 0);
                }else{
                    break;
                }
            }
            fclose(fp);
            return 0;
        }else{
            //父进程
            wait(&pid1);
            wait(&pid2);
            printf("Finished the processes\n");
        }
    }
    return 0;
}
