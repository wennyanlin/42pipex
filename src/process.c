#include "pipex.h"

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

void	child_process(int pipe_fd[2], t_pipe *state, int fd_out_override)
{
    if (access(state->cmd_path, X_OK) == -1
        && access(state->cmd_path, F_OK) == 0)
    {
        write(STDERR_FILENO, state->cmd_args[0], str_size(state->cmd_args[0]));
        write(STDERR_FILENO, ": permission denied\n", 20);
        exit (126);
    }
    if (state->fd_in == -1)
    { 
        close(pipe_fd[WR]);
        close(pipe_fd[RD]);
        exit (127);
    }
    fd_dup2(state->fd_in, STDIN_FILENO);
	close(pipe_fd[RD]);
    if (fd_out_override != NEGATIVE)
        fd_dup2(fd_out_override, STDOUT_FILENO);
    else
	    fd_dup2(pipe_fd[WR], STDOUT_FILENO);
	execute_command(state->cmd_path, state->cmd_args, state->envp);
	exit(127);
}

void create_process(t_pipe *state, int fd_out_override)
{
    int     pipe_fd[2];
    pid_t   pid;

    if (pipe(pipe_fd) == INVALID)
        perror_and_exit("pipe", EXIT_FAILURE);
    pid = fork();
    if (pid == INVALID)
        perror_and_exit("fork", EXIT_FAILURE);
    else if (pid == CHILD)
        child_process(pipe_fd, state, fd_out_override);
    state->pid_arr[state->cmd_idx] = pid;
    close(state->fd_in);
    state->fd_in = pipe_fd[RD];
    close(pipe_fd[WR]);
}