#include "sem.h"

int item_c = 0;
int sem_1 = 0;


void* cal(void* arg);
void* pri1(void* arg);
void* pri2(void* arg);
int main(void)
{
    void *status;
    sem_1 = create_Sem(0, 3);
    set_N(sem_1, 0, 1);  // cal = 1
    set_N(sem_1, 1, 0);  // pr1 = 0
    set_N(sem_1, 2, 0);  // pr2 = 0
    pthread_t ptcal, ptpr1, ptpr2;
    if(pthread_create(&ptpr1, NULL, pri1, NULL)!=0){
        printf("线程2创建失败\n");
    }
    if(pthread_create(&ptpr2, NULL, pri2, NULL)!=0){
        printf("线程3创建失败\n");
    }
    if(pthread_create(&ptcal, NULL, cal, NULL)!=0){
        printf("线程1创建失败\n");
    }
    pthread_join(ptcal, &status);
    printf("打印结束\n");
    return 0;
}

void* cal(void* arg)
{
    while(1){
        P(sem_1, 0);
        if(item_c<100){
            item_c++;
            if(item_c%2 == 0){
                V(sem_1, 1);
            }
            else{
                V(sem_1, 2);
            }
        }
        else{
            break;
        }
    }
    return arg;
}

void* pri1(void* arg)
{
    while(1){
        P(sem_1, 1);
        printf("打印机1打印信息: %d\n", item_c);
        if(item_c == 100){
            V(sem_1, 0);
            break;
        }
        V(sem_1, 0);
    }
    return arg;
}

void* pri2(void* arg)
{
    while(1){
        P(sem_1, 2);
        printf("打印机2打印信息: %d\n", item_c);
        if(item_c == 99){
            V(sem_1, 0);
            break;
        }
        V(sem_1, 0);
    }
    return arg;
}