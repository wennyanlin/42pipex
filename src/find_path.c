#include "pipex.h"

char *make_path(char *dir, char *cmd)
{
	char *full_path;

	full_path = string_concat(dir, "/");
	full_path = string_concat(full_path, cmd);
	return (full_path);
}

//recieve the variable PATH, trying to find the correct path which contains the command
char	*find_path(char *env, char *cmd)
{
	int		i;
	char 	*full_path;
	char 	**path_dirs;

	if (!env)
		return (cmd);	
	if (char_index(cmd, '/') != INVALID)
		return (cmd);
	path_dirs = ft_split(env, ':');
	free(env);
	i = 0;
	while (path_dirs[i])
	{
		full_path = make_path(path_dirs[i], cmd);
		free(path_dirs[i]);
		path_dirs[i] = NULL;
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	free_array(path_dirs);
	path_dirs = NULL;
	return (cmd);
}

// char	*find_path(char *env, char *cmd)
// {
// 	char 	**split_env;
// 	char 	**path_dirs;
// 	char	*path;
// 	char	*path2;
// 	int		i;

// 	i = 0;
// 	if (access(cmd, X_OK) == 0)
// 	{
// 		return (cmd);
// 	}
// 	else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) != 0)
// 		perror_and_exit(cmd, 126);
// 	else if (is_empty_command(cmd) == 1)
// 	{
// 		write(2, cmd, (ft_strlen(cmd) + 1));
// 		write(2, ": command not found\n", 20);
// 		exit(EXIT_FAILURE);
// 	}
// 	split_env = ft_split(env, '=');
// 	path_dirs = ft_split(split_env[1], ':');
// 	while (path_dirs[i])
// 	{
// 		path = string_concat(path_dirs[i], "/");
// 		path2 = string_concat(path, cmd);
// 		free(path);
// 		path = NULL;
// 		if (access(path2, X_OK) == 0)
// 			return (path2);
// 		free(path2);
// 		path2 = NULL;
// 		i++;
// 	}
// 	free_array(path_dirs);
// 	path_dirs = NULL;
// 	write(2, cmd, (ft_strlen(cmd) + 1));
// 	write(2, ": command not found\n", 20);
// 	exit(EXIT_FAILURE);
// }