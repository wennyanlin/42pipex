#include "pipex.h"

void	child_process(int pipefd[2], char *cmd1, char **cmd_args, int fd_out_override, char **envp)
{
	close(pipefd[RD]);
    if (fd_out_override != NEGATIVE)
        fd_dup2(fd_out_override, STDOUT_FILENO);
    else
	    fd_dup2(pipefd[WR], STDOUT_FILENO);
	execute_command(cmd1, cmd_args, envp);
	exit(127);
}

int create_fd_infile(char *infile)
{
    int fd_infile;

    fd_infile = open(infile, O_RDONLY);
    if (fd_infile == INVALID)
		perror(infile);
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

// t_pipe  update_pid(t_pipe state, pid_t pid)
// {
//     state.pid_arr[state.cmd_idx++] = pid;
// }


void create_process(t_pipe *state, char *cmd_path, char **cmd_args, int fd_out_override, char **envp)
{
    int     pipe_fd[2];
    pid_t   pid;

    if (pipe(pipe_fd) == INVALID)
        perror_and_exit("pipe", EXIT_FAILURE);
    pid = fork();
    if (pid == INVALID)
        perror_and_exit("fork", EXIT_FAILURE);
    else if (pid == CHILD)
    {
        if (access(cmd_path, X_OK) == -1 && access(cmd_path, F_OK) == 0)
        {
            write(STDERR_FILENO, cmd_args[0], str_size(cmd_args[0]));
            write(STDERR_FILENO, ": permission denied\n", 20);
            exit (126);
        }
        if (state->fd_in == -1)
        {
            state->fd_in = -1;
            close(pipe_fd[WR]);
            close(pipe_fd[RD]);
            exit (127);
        }
        fd_dup2(state->fd_in, STDIN_FILENO);
        child_process(pipe_fd, cmd_path, cmd_args, fd_out_override, envp);
    }
    state->pid_arr[++(state->cmd_idx)] = pid;
    close(state->fd_in);
    state->fd_in = pipe_fd[RD];
    close(pipe_fd[WR]);
}

t_pipe    init_state(int pid_arr_size, int fd_infile)
{
    t_pipe  state;

    state.cmd_idx = -1;
    state.fd_in = fd_infile;
    state.num_cmds = pid_arr_size;
    state.pid_arr = malloc(sizeof(pid_t) * pid_arr_size);
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

int    pipe_all(char **all_cmds, t_pipe *state, int fd_out, char **envp)
{
    int     i;
    int     status;
    int     stat_code;
    char    *cmd_path;
    char    **cmd_args;
    char    *all_paths;

    i = -1;
    while (all_cmds[++i])
    {
        cmd_args = ft_split(all_cmds[i], ' ');
        if (!cmd_args)
            return (EXIT_FAILURE);
        all_paths = get_env(envp, "PATH");
        cmd_path = find_path(all_paths, cmd_args[0]);
        free(all_paths);
        if (i == state->num_cmds - 1)
        {
            create_process(state, cmd_path, cmd_args, fd_out, envp);
            close(state->fd_in);
            close(fd_out);
        }
        else
            create_process(state, cmd_path, cmd_args, NEGATIVE, envp);
        free(cmd_path);
        free_array(cmd_args);
    }
    i = -1;
    while (++i < state->num_cmds)
    {
        waitpid(state->pid_arr[i], &status, 0);
        stat_code = get_wait_status(status);
    }
    exit (stat_code);
}
