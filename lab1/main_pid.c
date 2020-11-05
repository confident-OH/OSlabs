#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>


void child1();
void child2();
void close1(int sig);
void close2(int sig);
void father_close(int sig);

pid_t p1, p2;
int p1num = 0;
int p2num = 0;
int pipefd[2];   //pipefd[0]:读信息, pipefd[1]: 写信息

int main(void)
{
    pipe(pipefd);
    p1 = fork();
    if(p1 == 0){
        //子进程1运行
        child1();
    }else{
        p2 = fork();
        if(p2 == 0){
            //子进程2运行
            child2();
        }
        else{
            //父进程运行
            signal(SIGINT, father_close);
            int send_n = 20;
            int i;
            char buffer[30] = "I send you xx times.\n";
            for(i = 0; i<send_n; i++){
                buffer[11] = i/10+'0';
                buffer[12] = i%10+'0';
                //发送
                write(pipefd[1], buffer, 30);
                sleep(1);
            }
            kill(p1, SIGUSR1);
            wait(&p1);
            kill(p2, SIGUSR2);
            wait(&p2);
            printf("Parent Process is Killed!\n");
        }
    }
    return 0;
}

void father_close(int sig)
{
    if(sig == SIGINT){
        kill(p1, SIGUSR1);
        wait(&p1);
        kill(p2, SIGUSR2);
        wait(&p2);
        printf("Parent Process is Killed!\n");
        exit(1);
    }
}

void p1_recv(int sig)
{
    if(sig == SIGUSR1){
        printf("子进程1接受到父进程信息\n");
    }
        
    if(sig == SIGUSR2){
        printf("子进程2接受到父进程信息\n");
    }
}

void child1()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR1, close1);
    char a[30];
    while(1){
        read(pipefd[0], a, 30);
        printf("子进程1接受：%s", a);
        p1num++;
    }
}

void child2()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGUSR2, close2);
    char a[30];
    while(1){
        read(pipefd[0], a, 30);
        printf("子进程2接受：%s", a);
        p2num++;
    }
}

void close1(int sig)
{
    printf("Child1 has recieved %d information.\n", p1num);
    printf("Child Process l is Killed by Parent!\n");
    exit(1);
}

void close2(int sig)
{
    printf("Child2 has recieved %d information.\n", p2num);
    printf("Child Process 2 is Killed by Parent!\n");
    exit(1);
}