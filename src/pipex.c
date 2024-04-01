/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:20:59 by wlin              #+#    #+#             */
/*   Updated: 2024/04/01 17:23:38 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_and_exit(char *file, int code)
{
	perror(file);
	exit(code);
}

void	fd_dup2(int oldfd, int newfd)
{
	if (oldfd != -1 && dup2(oldfd, newfd) == -1)
	{
		close(oldfd);
		perror_and_exit("dup2", EXIT_FAILURE);
	}
	close(oldfd);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
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

char	*execute_command(char *command_path, char **cmd_args, char **envp)
{
	char	**result_array_concat = NULL;

	execve(command_path, cmd_args, envp);
	free(command_path);
	command_path = NULL;
	if (errno == 8) 
	{
		result_array_concat = array_concat("/bin/sh", cmd_args);
		execve("/bin/sh", result_array_concat, envp);
		free_array(cmd_args);
		cmd_args = NULL;
		free_array(result_array_concat);
		result_array_concat = NULL;
	}
	else if (errno == ENOENT)
		perror(command_path);
	perror(command_path);
	return (0);
}
