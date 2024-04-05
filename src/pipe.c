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

int create_fd_infile(char *infile)
{
    int fd_infile;

    fd_infile = open(infile, O_RDONLY);
    if (fd_infile == INVALID)
    {
        //noot handling return ???
		perror(infile);
    }
    return (fd_infile);
}

int create_fd_outfile(char *outfile, int mode)
{
    int fd_outfile;
    if (mode == TRUNC)
        fd_outfile = open(outfile, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR
                    | S_IRGRP | S_IROTH);
    else
        fd_outfile = open(outfile, O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR
                    | S_IRGRP | S_IROTH);
	if (fd_outfile == INVALID)
		perror_and_exit(outfile, EXIT_FAILURE);
    return (fd_outfile);
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
        if (access(cmd_path, X_OK) == -1 && access(cmd_path, F_OK) == 0)
        {
            write(STDERR_FILENO, cmd_args[0], str_size(cmd_args[0]));
            write(STDERR_FILENO, ": permission denied\n", 20);
            exit (126);
        }
        if (fd_in == -1)
        {
            state.fd_in = -1;
            close(pipe_fd[WR]);
            close(pipe_fd[RD]);
            exit (127);
        }
        fd_dup2(fd_in, STDIN_FILENO);
        child_process(pipe_fd, cmd_path, cmd_args, fd_out_override, envp);
    }
    state.fd_in = pipe_fd[RD];
    close(fd_in);
    close(pipe_fd[WR]);
    return (state);
}

int get_wait_status(int status)
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

int    pipe_all(char **all_cmds, int infile_fd, int fd_out, char **envp)
{
    int     i;
    int     j;
    int     status;
    int     stat_code;
    pid_t   pid;
    char    *cmd_path;
    char    **cmd_args;
    char    *all_paths;
    t_pipe  state;
    int     all_cmds_len;

    i = -1;
    all_cmds_len = array_size(all_cmds);
    state.fd_in = infile_fd;
    while (all_cmds[++i])
    {
        cmd_args = ft_split(all_cmds[i], ' ');
        all_paths = get_env(envp, "PATH");
        cmd_path = find_path(all_paths, cmd_args[0]);
        if (i == all_cmds_len - 1)
        {
            state = create_process(state.fd_in, cmd_path, cmd_args, fd_out, envp);
            // printf("started last command '%s', pid: %d\n", cmd_args[0], state.pid);
            close(state.fd_in);
            close(fd_out);
        }
        else
        {
            state = create_process(state.fd_in, cmd_path, cmd_args, NEGATIVE, envp);
            // printf("started command '%s', pid: %d\n", cmd_args[0], state.pid);
        }
    }
    j = -1;

    while (++j < all_cmds_len)
    {
        // printf("waiting\n");
        pid = wait(&status);
        // printf("finished: %d\n", pid);
        if (pid == state.pid)
        {
            stat_code = get_wait_status(status);
            // printf("last finished: %d, status: %d\n", pid, stat_code);
        }
        else
        {
            get_wait_status(status);
        }
    }
    exit (stat_code);
}
