#include "pipex.h"

void	perror_and_exit(char *file, int code)
{
	perror(file);
	exit(code);
}

t_pipe    init_state(int pid_arr_size, int fd_infile, char **envp)
{
    t_pipe  state;

    state.envp = envp;
    state.cmd_idx = -1;
    state.fd_in = fd_infile;
    state.num_cmds = pid_arr_size;
    state.pid_arr = malloc(sizeof(pid_t) * pid_arr_size);
    return (state);
}

void    parse_command(t_pipe *state, char **all_cmds)
{
    char    *all_paths;

    state->cmd_args = ft_split(all_cmds[state->cmd_idx], ' ');
    if (!state->cmd_args)
        exit (EXIT_FAILURE);
    all_paths = get_env(state->envp, "PATH");
    state->cmd_path = find_path(all_paths, state->cmd_args[0]);
    free(all_paths);
}

int    pipe_all(char **all_cmds, t_pipe *state, int fd_out)
{
    int     i;
    int     status;
    int     stat_code;
    
    while (all_cmds[++(state->cmd_idx)])
    {
        parse_command(state, all_cmds);
        if (state->cmd_idx == state->num_cmds - 1)
        {
            create_process(state, fd_out);
            close(state->fd_in);
            close(fd_out);
        }
        else
            create_process(state, NEGATIVE);
        free(state->cmd_path);
        free_array(state->cmd_args);
    }
    i = -1;
    while (++i < state->num_cmds)
    {
        waitpid(state->pid_arr[i], &status, 0);
        stat_code = get_wait_status(status);
    }
    exit (stat_code);
}
