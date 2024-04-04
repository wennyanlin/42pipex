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

t_pipe create_process(int fd_in, char *cmd_path, char **cmd_args, int fd_out_override, char **envp)
{
    int pipe_fd[2];
    t_pipe  state;

    if (pipe(pipe_fd) == INVALID)
        perror_and_exit("pipe", EXIT_FAILURE);
    state.pid = fork();
    if (state.pid == INVALID)
        perror_and_exit("fork", EXIT_FAILURE);
    else if (state.pid == CHILD)
    {
        if (fd_in == -1)
        {
            state.fd_in = -1;
            close(pipe_fd[WR]);
            close(pipe_fd[RD]);
            exit(127);
        }
        fd_dup2(fd_in, STDIN_FILENO);
        child_process(pipe_fd, cmd_path, cmd_args, fd_out_override, envp);
    }
    state.fd_in = pipe_fd[RD];
    close(fd_in);
    close(pipe_fd[WR]);
    return (state);
}

int get_wait_status(int *status)
{
    int stat_code;

    stat_code = 0;
    if (WIFEXITED(status))
        stat_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        stat_code = WTERMSIG(status);
    else if (WIFSTOPPED(status))
        stat_code = WSTOPSIG(status);
    // printf("stat_code: '%d'\n", stat_code);
    return (stat_code);
}

int    pipe_all(char **all_cmds, int infile_fd, int fd_out, char **envp)
{   //handle command starts at [2] end at [end - 1]
    int     i;
    int     j;
    int     *status;
    int     stat_code;
    pid_t   pid;
    char    *cmd_path;
    char    **cmd_args;
    char    *all_paths;
    t_pipe  state;
    int     all_cmds_len;

    i = -1;
    all_cmds_len = array_size(all_cmds);
    state.fd_in = infile_fd; //here may need to handle if infile is invalid;
    while (all_cmds[++i])
    {
        cmd_args = ft_split(all_cmds[i], ' ');
        all_paths = get_env(envp, "PATH");
        cmd_path = find_path(all_paths, cmd_args[0]);
        if (i == all_cmds_len - 1)
        {
            state = create_process(state.fd_in, cmd_path, cmd_args, fd_out, envp);
            close(state.fd_in);
            close(fd_out);// close outfile
        }
        else
            state = create_process(state.fd_in, cmd_path, cmd_args, NEGATIVE, envp);
        //here shouldn't we close fds when t
    }
    j = 1;
    status = NULL;
    while (++j < all_cmds_len)
    {
        pid = wait(NULL);
        if (pid == state.pid)
            stat_code = get_wait_status(status);
        else
            get_wait_status(status);    
    }
    return (stat_code);
}
