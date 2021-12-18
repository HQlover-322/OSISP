#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int which_one = 0; 
int N = 0; 
pid_t parent, child1, child2;

int main()
{
    void p_action(int), c1_action(int), c2_action(int), g_exit(int), ignore(int);
    static struct sigaction pact, cact1, cact2;
    pact.sa_handler = p_action;
    sigaction(SIGUSR2, &pact, NULL);
    child1 = fork();
    if (child1 == 0)
    {
        cact1.sa_handler = c1_action;
        sigaction(SIGUSR1, &cact1, NULL);
        cact1.sa_handler = ignore;
        sigaction(SIGINT, &cact1, NULL);

        parent = getppid();
        for (;;)
        {
            sleep(1);
            printf("%d %d son 1 put SIGUSR2\n", ++N, getpid());
            kill(parent, SIGUSR2);
            pause();
        }
    }
    else
    {
        child2 = fork();
        if (child2 == 0)
        {
            cact2.sa_handler = c2_action;
            sigaction(SIGUSR1, &cact2, NULL);
            cact2.sa_handler = ignore;
            sigaction(SIGINT, &cact2, NULL);    
            parent = getppid();
            for (;;)
            {
                sleep(1);
                printf("%d %d son 2 put SIGUSR2\n", ++N, getpid());
                kill(parent, SIGUSR2);
                pause();
            }
        }
        else
        {
            pact.sa_handler = g_exit;
            sigaction(SIGINT, &pact, NULL);

            for (;;)
            {
                pause();
                sleep(1);
                printf("%d %d parentput SIGUSR1 for son 1\n", ++N, getpid());
                kill(child1, SIGUSR1);
                printf("%d %d parentput SIGUSR1 for son 2\n", ++N, getpid());
                kill(child2, SIGUSR1);
            }
        }
    }
}
void p_action(int sig)
{
    if (which_one == 0)
    {
        printf("%d %d parentget SIGUSR2 from son 1\n", ++N, getpid());
        which_one = 1;
    }
    else
    {
        printf("%d %d parentget SIGUSR2 from son 2\n", ++N, getpid());
        which_one = 0;
    }
}
void c1_action(int sig)
{
    printf("%d %d son 1 get SIGUSR1\n", ++N, getpid());
}
void c2_action(int sig)
{
    printf("%d %d son 2 get SIGUSR1\n", ++N, getpid());
}
void g_exit(int sig)
{
    kill(child1, SIGSTOP);
    kill(child2, SIGSTOP);
    char c;
    printf("\nAre you sure? Enter 1 to yes, anything else - to no. ");
    scanf("%c", &c);
    if (c == '1')
    {
        printf("\nStopping\n");
        exit(0);
    }
    else
    {
        printf("\nContinuing\n");
        kill(child1, SIGCONT);
        kill(child2, SIGCONT);
    }
}

void ignore(int sig) 
{

}
