#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void    print2(char *str, char *arg)
{
    while (*str)
        write(2, str++, 1);
    if (arg)
        while (*arg)
            write(2, arg++, 1);
    write(2, "\n", 1);
}

void    ft_execute(char **argv, int i, int tmp_fd, char **env)
{
    argv[i] = NULL;
    dup2(tmp_fd, STDIN_FILENO);
    close(tmp_fd);
    execve(argv[0], argv, env);
    print2("error: cannot execute ", argv[0]);
    exit(1);
}


int main(int ac, char **argv, char **env)
{
    int i;
    int fd[2];
    int tmp_fd;
    (void)ac;

    i = 0;
    tmp_fd = dup(STDIN_FILENO);
    while (argv[i] && argv[i + 1])
    {
        argv = &argv[i + 1];
        i = 0;
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (strcmp(argv[0], "cd") == 0)
        {
            if (i != 2)
                print2("error: cd: bad arguments", NULL);
            else if (chdir(argv[1]) != 0)
                print2("error: cd: cannot change directory to ", argv[1]);
        }
        else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
        {
            if (fork() == 0)
                ft_execute(argv, i, tmp_fd, env);
            else
			{
                close(tmp_fd);
                while (waitpid(-1, NULL, WUNTRACED) != -1)
                    ;
                tmp_fd = dup(STDIN_FILENO);
			}
		}
        else if (i != 0 && strcmp(argv[i], "|") == 0)
        {
            pipe(fd);
            if (fork() == 0)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                ft_execute(argv, i, tmp_fd, env);
            }
            else
            {
                close(tmp_fd);
                close(fd[1]);
                tmp_fd = fd[0];
            }
        }
    }
    close (tmp_fd);
    return (0);
}

