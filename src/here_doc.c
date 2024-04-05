#include "pipex.h"

int check_limiter(char *next_line, char *limiter)
{
    int i;

    if ((str_size(next_line) - 1) == str_size(limiter))
    {
        i = -1;
        while (limiter[++i])
            if (next_line[i] != limiter[i])
                return (0);
        return (1);
    }
    return (0);
}

int read_here_doc(char *limiter)
{
    int     pipe_fd[2];
    char    *next_line;

    pipe(pipe_fd);
    next_line = get_next_line(STDIN_FILENO);
    while (check_limiter(next_line, limiter) == 0)
    {
        write(pipe_fd[WR], next_line, str_size(next_line)); 
        free(next_line);
        next_line = get_next_line(STDIN_FILENO);
    }
    close(pipe_fd[WR]);
    free(next_line);
    return (pipe_fd[RD]);
}