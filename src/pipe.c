#include "pipex.h"

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
