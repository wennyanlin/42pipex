#include "pipex.h"

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