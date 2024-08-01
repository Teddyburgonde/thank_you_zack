#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


// Version de Zack

int    ft_putstr_fd2(char *str, char *arg)
{
    while (*str)
        write(2, str++, 1);
    if (arg)
        while(*arg)
            write(2, arg++, 1);
    write(2, "\n", 1);
    return (1);
}

int ft_execute(char *argv[], int i, int tmp_fd, char *env[], int fd[2])
{
    if(argv[i] && !strcmp(argv[i], "|"))
    {
            pipe(fd);
    }
    if (fork() == 0)
    {
            if(argv[i] && !strcmp(argv[i], "|"))
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
        argv[i] = NULL;
        dup2(tmp_fd, STDIN_FILENO);
        close(tmp_fd);
        execve(argv[0], argv, env);
        return (ft_putstr_fd2("error: cannot execute ", argv[0]));
    }
    waitpid(-1, NULL, 0);
    return (0);
}

int    main(int argc, char *argv[], char *env[])
{
    int    i;
    int fd[2];
    int tmp_fd = dup(0);
    (void)argc;

    while (argv[0] && argv[1])
    {
        argv++;
        i = 0;
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (!strcmp(argv[0], "cd")) //cd
        {
            if (i != 2)
                ft_putstr_fd2("error: cd: bad arguments", NULL);
            else if (chdir(argv[1]))
                ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
        }
        else if (i)
            ft_execute(argv, i, tmp_fd, env, fd);
        if(argv[i] && !strcmp(argv[i], "|"))
        {
            close(fd[1]);
            close(tmp_fd);
            tmp_fd = fd[0];
        }
        argv = argv + i;
    }
    close(tmp_fd);
    return (0);
}

//--------------------------------------------------------------------------------------



// Ma version 
// int ft_putstr_fd2(char *str, char *arg)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     while (str[i])
//     {
//         write (2, &str[i], 1);
//         i++;
//     }
//     if (arg)
//     {
//         while (arg[j])
//         {
//             write (2, &arg[j], 1);
//             j++;
//         }
//     }
//     write (2, "\n", 1);
//     return (0);
// }

// int   ft_execute(char **argv, int i, int fd[2], int tmp_fd, char **env)
// {
//     if (argv[i] && strcmp(argv[i], '|'))
//         pipe(fd);
//     if (fork == 0)
//     {
//         if (argv[i] && strcmp(argv[i], '|'))
//         {
//             dup2(fd[1], STDOUT_FILENO);
//             close(fd[0]);
//             close(fd[1]);
//         }
//         argv[i] = NULL;
//         dup2(tmp_fd, STDIN_FILENO);
//         close(tmp_fd);
//         execve(argv[0], argv, env);
//         ft_pustr_fd2("error: cannot execute", argv[0]);
//         return (1);
//     }
//     waitpid(-1, NULL, 0);
//     return (0);
// }

// -------------------------------------------------------------------------------------------

//int    main(int argc, char *argv[], char *env[])
//{
    //int    i;
    //int fd[2];
    //int tmp_fd = dup(0);
    //(void)argc;

    //while (argv[0] && argv[1])
    //{
       // argv++;
       // i = 0;
        //while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
          //  i++;
        //if (!strcmp(argv[0], "cd")) //cd
        //{
            //if (i != 2)
             //   ft_putstr_fd2("error: cd: bad arguments", NULL);
           // else if (chdir(argv[1]))
          //      ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
        //}
       // else if (i)
         //   ft_execute(argv, i, tmp_fd, env, fd);
       // if(argv[i] && !strcmp(argv[i], "|"))
       // {
            //close(fd[1]);
            //close(tmp_fd);
          //  tmp_fd = fd[0];
        //}
      //  argv = argv + i;
    //}
    //close(tmp_fd);
  //  return (0);
//}
