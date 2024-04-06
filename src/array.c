#include "pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	array_size(char **array)
{
	int	i;
	
	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**array_concat(char *shell_path, char **args)
{
	char 	**result_args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (args[len])
		len++;
	result_args = malloc(sizeof(char*) * (len + 2));
	if (!result_args)
		return (NULL);
	result_args[i] = shell_path;
	i++;
	while (i < len + 1)
	{
		result_args[i] = args[i - 1];
		i++;
	}
	result_args[i] = NULL;
	return (result_args);
}