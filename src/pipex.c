/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:20:59 by wlin              #+#    #+#             */
/*   Updated: 2024/03/29 18:59:22 by wlin             ###   ########.fr       */
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

void	child_process(int pipefd[2], char *cmd1, char **envp)
{
	close(pipefd[0]);//close the read-end
	fd_dup2(pipefd[1], STDOUT_FILENO);
	execute_command(cmd1, envp);
	exit(EXIT_SUCCESS);
}

void	parent_process(int pipefd[2], int fd2, char *cmd2, char **envp)
{
	close(pipefd[1]);
	fd_dup2(fd2, STDOUT_FILENO);
	fd_dup2(pipefd[0], STDIN_FILENO);//make pipefd(0)/read-end as STDIN
	execute_command(cmd2, envp);
}

int	redirect_stdin(char *infile, char *cmd1, char *cmd2, char *outfile, char **envp)
{
	int		fd;
	int		fd2;
	int		pipefd[2];
	int		pid;

	fd = open(infile, O_RDONLY);
	fd2 = open(outfile, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror(infile);
	if (fd2 == -1)
		perror_and_exit(outfile, EXIT_FAILURE);
	fd_dup2(fd, STDIN_FILENO);
	if (pipe(pipefd) == -1)
		perror_and_exit("pipe", EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
		child_process(pipefd, cmd1, envp);
	else
		parent_process(pipefd, fd2, cmd2, envp);
	return (0);
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

char	*find_path(char *env, char *cmd)
{
	char 	**split_env;
	char 	**all_paths;
	char	*path;
	char	*path2;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
	{
		printf("%s\n", cmd);
		return (cmd);
	}
	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
		perror_and_exit(cmd, 126);
	else if (is_empty_command(cmd) == 1)
	{
		write(2, cmd, (ft_strlen(cmd) + 1));
		write(2, ": command not found\n", 20);
		exit(EXIT_FAILURE);
	}
	split_env = split(env, '=');
	all_paths = split(split_env[1], ':');
	free_array(split_env);
	split_env = NULL;
	while (all_paths[i])
	{
		path = string_concat(all_paths[i], "/");
		path2 = string_concat(path, cmd);
		free(path);
		path = NULL;
		if (access(path2, X_OK) == 0)
			return (path2);
		free(path2);
		path2 = NULL;
		i++;
	}
	free_array(all_paths);
	all_paths = NULL;
	write(2, cmd, (ft_strlen(cmd) + 1));
	write(2, ": command not found\n", 20);
	exit(EXIT_FAILURE);
}

char	*execute_command(char *cmd1, char **envp)
{
	char	**args;
	char	*env;
	char	*command_path;
	char	**result_array_concat = NULL;

	env = get_env(envp, "PATH");
	//################################ if env == NULL, check what should happen?
	args = split(cmd1, ' ');//["./script", NULL]
	command_path = find_path(env, args[0]);//"./script"
	printf("after find_path: %s, %s\n", command_path, args[1]);
	execve(command_path, args, 0);
	printf("faild\n");
	free(command_path);
	command_path = NULL;
	if (errno == 8)
	{
		result_array_concat = array_concat("/bin/sh", args);
		execve("/bin/sh", result_array_concat, 0);
		free_array(args);
		args = NULL;
		free_array(result_array_concat);
		result_array_concat = NULL;
	}
	else if (errno == ENOENT)
		perror(cmd1);
	perror(cmd1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;

	if (argc != 5)
		return (0);
	infile = argv[1];
	cmd1 = argv[2];
	cmd2 = argv[3];
	outfile = argv[4];
	redirect_stdin(infile, cmd1, cmd2, outfile, envp);
}
