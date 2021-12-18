#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>

#define MSGSIZE 100

int compare(char a[], char b[])
{
    int flag = 1, i = 0;  
    while (a[i] != '\0' && b[i] != '\0')  
    {
        if (a[i] != b[i])
        {
            flag = 0;
            break;
        }
        i++;
    }
    return flag;
}

main()
{
    char inbuf[MSGSIZE];
    int number_of_children = 2;
    int j;
    int pipes[number_of_children][2];
    pid_t children[1000]; 
    pid_t father;
    int new_children = 0;
    int actual_number = 2;


    for (int i = 0; i < number_of_children; i++)
    {
        children[i] = fork();
        char *msg = "Hello\n";
        write(pipes[i][1], msg, MSGSIZE);
    }
    
    father = getppid();

    while (1)
    {
        srand(time(0));
        for (int i = number_of_children; i < number_of_children + new_children; i++)
        {
            children[i] = fork();
        }   
        number_of_children += new_children;
        new_children = 0;

        if (!actual_number)
        {
            break;
        }

        for (int i = 0; i < number_of_children; i++)
        {
            if (children[i] == -1)
            {
            }
            else
            {
                read(pipes[i][0], inbuf, MSGSIZE); 
                if (compare(inbuf, "Die\n"))
                {
                    kill(children[i], SIGSTOP); 
                    close(pipes[i]);
                    actual_number--;
                }
                else
                {
                    int number = (rand() % (1 - 0 + 1)) + 0;
                    char *msg;  
                    if (number)
                    {
                        msg = "Hello\n";
                    }
                    else
                    {
                        msg = "More\n";
                    }
                    write(pipes[i][1], msg, MSGSIZE);
                }
            }
        }

        for (int i = 0; i < number_of_children; i++)
        {
            read(pipes[i][0], inbuf, MSGSIZE);
            if (compare(inbuf, "More\n")) 
            {
                actual_number++;
                new_children++;
                char *msg = "Hello\n";
                write(pipes[i][1], msg, MSGSIZE);
            }
            if (compare(inbuf, "Hello\n"))
            {
                char *msg = "Die\n";
                write(pipes[i][1], msg, MSGSIZE);
            }
        }
    }
}
