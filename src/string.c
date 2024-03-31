/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:21:17 by wlin              #+#    #+#             */
/*   Updated: 2024/03/31 22:22:17 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strchr(char *str, char ref)
{
	int	i;
	
	i = -1;
	if (!*str || !str)
		return (0);
	while (str[++i])
		if (str[i] == ref)
			return (i);
	return (0);
}

int	string_compare(char *str1, char *str2, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		if (str2[i] != str1[i])
			return (0);
		i++;
	}
	return (1);
}


char	*get_env(char **strs, char *ref)
{
	int		i;
	int		until;
	int		ref_len;
	char	**array;
	
	i = 0;
	ref_len = ft_strlen(ref);
	while (strs[i])
	{
		until = ft_strchr(strs[i], '=');
		if (until == ref_len && string_compare(strs[i], ref, until))
		{
			array = ft_split(strs[i], '=');
			if (!array || !array[1])
				return (NULL);
			return (array[1]);
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return(len);
}

char	*string_concat(char *path, char *cmd)
{
	char 	*result_path;
	size_t	path_len;
	size_t	cmd_len;
	size_t	total_len;
	size_t	i;

	path_len = ft_strlen(path);
	cmd_len = ft_strlen(cmd);
	total_len = path_len + cmd_len;
	result_path = malloc(sizeof(char) * (total_len + 1));
	if (!result_path)
		return (NULL);
	i = 0;
	while (i < path_len)
	{
		result_path[i] = path[i];
		i++;
	}
	cmd_len = 0;
	while (i < total_len)
		result_path[i++] = cmd[cmd_len++];
	result_path[i] = '\0';
	return (result_path);
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
