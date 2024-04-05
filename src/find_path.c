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
