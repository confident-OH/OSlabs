#include "sem.h"

int tickit = 10000;
int sem_id;
int sellor1 = 0, sellor2 = 0, sellor3 = 0;

void* thread_sell(void*);

int main(void)
{
    void* status;
    sem_id = create_Sem(0, 1);    //key = 0, size = 1;
    pthread_t pt1, pt2, pt3;
    set_N(sem_id, 0, 1);
    if(pthread_create(&pt1, NULL, thread_sell, &sellor1)!=0){
        printf("线程1创建失败\n");
    }
    if(pthread_create(&pt2, NULL, thread_sell, &sellor2)!=0){
        printf("线程2创建失败\n");
    }
    if(pthread_create(&pt3, NULL, thread_sell, &sellor3)!=0){
        printf("线程3创建失败\n");
    }
    pthread_join(pt3, &status);
    printf("售票处1出售%d张票\n", sellor1);
    printf("售票处2出售%d张票\n", sellor2);
    printf("售票处3出售%d张票\n", sellor3);
    printf("线程执行完毕\n");
    return 0;
}

void* thread_sell(void* arg)
{
    //printf("售票处出售%d张票\n", *((int *)arg));
    while(1){
        P(sem_id, 0);
        if(tickit>0){
            tickit--;
            *((int *)arg) = *((int *)arg) + 1;
        }else{
            V(sem_id, 0);
            break;
        }
        V(sem_id, 0);
    }
    return arg;
}