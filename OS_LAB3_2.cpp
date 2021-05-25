#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;


bool flag = true;
int fd[2];


void* task1(void* args)
{
    char buf = '1';
    while (flag)
    {
        write(fd[1], &buf, 1);
        buf++;
        sleep(1);
    }
    close(fd[1]);
    return NULL;
}


void* task2(void* args)
{
    char buf = '0';
    while (flag)
    {
        read(fd[0], &buf, 1);
        if (buf != '0'){
            cout << buf << " ";
            cout.flush();
        }
    }
    close(fd[0]);
    return NULL;
}




int main()
{
    pthread_t th1, th2;
    pipe(fd);

    pthread_create(&th1, NULL, task1, NULL);
    pthread_create(&th2, NULL, task2, NULL);

    getchar();
    flag = false;

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
