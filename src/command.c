/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:20:59 by wlin              #+#    #+#             */
/*   Updated: 2024/04/06 14:31:55 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_and_exit(char *file, int code)
{
	perror(file);
	exit(code);
}

int	is_empty_command(char *cmd)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (!cmd)
	{
		flag = 1;
		return (flag);
	}
	while (cmd[i])
	{
		if (cmd[i] != ' ')
			return (flag);
		flag = 1;
		i++;
	}
	return (flag);
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

char    **extract_cmds(char **argv, int argc, int start)
{
    char    **cmds;
    int     i;

    cmds = malloc(sizeof(char *) * (argc - start));
    if (!cmds)
        return (NULL);
    i = start - 1;
    while (++i < (argc - 1))
        cmds[i - start] = argv[i];
    cmds[i - start] = NULL;
    return (cmds);
}

void	execute_command(char *command_path, char **cmd_args, char **envp)
{
	char	**result_array_concat = NULL;

	execve(command_path, cmd_args, envp);
	if (errno == ENOEXEC)
	{
		result_array_concat = array_concat("/bin/sh", cmd_args);
		execve("/bin/sh", result_array_concat, envp);
		free_array(result_array_concat);
		result_array_concat = NULL;
	}
	else if (errno == ENOENT)
	{
		if (char_index(cmd_args[0], '/') != INVALID)
			perror(cmd_args[0]);
		else
		{
			write(STDERR_FILENO, cmd_args[0], str_size(cmd_args[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
			exit(127);
		}
	}
	else
		perror_and_exit(cmd_args[0], EXIT_FAILURE);
}
