#include "pipex.h"

void	child_process(int pipefd[2], char *cmd1, char **cmd_args, int fd_out_override, char **envp)
{
	close(pipefd[RD]);
    if (fd_out_override != NEGATIVE)
        fd_dup2(fd_out_override, STDOUT_FILENO);
    else
	    fd_dup2(pipefd[WR], STDOUT_FILENO);
	execute_command(cmd1, cmd_args, envp);
	exit(127); //modificado
}

int *create_fd(char *infile, char *outfile)
{
    int *fd_array;

    fd_array = malloc(sizeof(int) * 2);
    if (!fd_array)
        return (NULL);
    fd_array[0] = open(infile, O_RDONLY);
    fd_array[1] = open(outfile, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR
                    | S_IRGRP | S_IROTH);
    if (fd_array[0] == INVALID)
    {
        //noot handling return ???
		perror(infile);
    }
	if (fd_array[1] == INVALID)
		perror_and_exit(outfile, EXIT_FAILURE);
    return (fd_array);
}

int create_process(int fd_in, char *cmd_path, char **cmd_args, int fd_out_override, char **envp)
{
    int pipe_fd[2];
    int process_id;
    int fd_out;

    if (pipe(pipe_fd) == INVALID)
        perror_and_exit("pipe", EXIT_FAILURE);
    process_id = fork();
    printf("%d\n", process_id);
    if (process_id == INVALID)
        perror_and_exit("fork", EXIT_FAILURE);
    else if (process_id == CHILD)
    {
        int i = 1;
        while (i)
            ;
        fd_dup2(fd_in, STDIN_FILENO);
        child_process(pipe_fd, cmd_path, cmd_args, fd_out_override, envp);
    }
    fd_out = pipe_fd[RD];
    close(fd_in);
    close(pipe_fd[WR]);
    return (fd_out);
}

int get_wait_status(pid_t status)
{
    int stat_code;

    stat_code = 0;
    if (WIFEXITED(status))
        stat_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        stat_code = WTERMSIG(status);
    else if (WIFSTOPPED(status))
        stat_code = WSTOPSIG(status);
    return (stat_code);
}

int    pipe_all(char **all_cmds, int infile_fd, int fd_out, char **envp, int argc)
{   //handle command starts at [2] end at [end - 1]
    int     i;
    int     j;
    pid_t   status;
    int     stat_code;
    int     fd_in;
    char    *cmd_path;
    char    **cmd_args;

    i = 1;
    fd_in = infile_fd;
    while (all_cmds[++i] && i < (argc - 1))
    {   //execve() requires the command full path
        cmd_args = ft_split(all_cmds[i], ' ');
        cmd_path = find_path(get_env(envp, "PATH"), cmd_args[0]);
        if (i == argc - 2)
        {
            fd_in = create_process(fd_in, cmd_path, cmd_args, fd_out, envp);
            close(fd_in);
            close(fd_out);
        }
        else
            fd_in = create_process(fd_in, cmd_path, cmd_args, NEGATIVE, envp);
    }
    j = 1;
    status = 0;
    while (++j < (argc - 1))
    {
        wait(NULL);
        if (j == argc - 2)
        {
        wait(&status);
    stat_code = get_wait_status(status);
        }
    }
    return (stat_code);
}
