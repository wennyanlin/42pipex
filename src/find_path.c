#include "pipex.h"

char *make_path(char *dir, char *cmd)
{
	char *full_dir;
	char *full_path;

	full_dir = string_concat(dir, "/");
	full_path = string_concat(full_dir, cmd);
	free(full_dir);
	return (full_path);
}

char	*get_env(char **strs, char *ref)
{
	int		i;
	int		until;
	int		ref_len;
	char	**array;
	char	*env_value;
	
	i = 0;
	ref_len = str_size(ref);
	while (strs[i])
	{
		until = char_index(strs[i], '=');
		if (until == ref_len && substr_compare(strs[i], ref, until))
		{
			array = ft_split(strs[i], '=');
			if (!array || !array[1])
				return (NULL);
			env_value = str_cpy(array[1]);
			free_array(array);
			return (env_value);
		}
		i++;
	}
	return (NULL);
}

//recieve the variable PATH, trying to find the correct path which contains the command
char	*find_path(char *env, char *cmd)
{
	int		i;
	char 	*full_path;
	char 	**path_dirs;

	if (!env)
		return (str_cpy(cmd));	
	if (char_index(cmd, '/') != INVALID)
		return (str_cpy(cmd));
	path_dirs = ft_split(env, ':');
	i = -1;
	while (path_dirs[++i])
	{
		full_path = make_path(path_dirs[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path_dirs);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
	}
	free_array(path_dirs);
	path_dirs = NULL;
	return (str_cpy(cmd));
}
