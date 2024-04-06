/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:21:17 by wlin              #+#    #+#             */
/*   Updated: 2024/04/06 16:03:58 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	char_index(char *str, char ref)
{
	int	i;

	i = -1;
	if (!*str || !str)
		return (-1);
	while (str[++i])
		if (str[i] == ref)
			return (i);
	return (-1);
}

int	substr_compare(char *str1, char *str2, int until)
{
	int	i;

	i = -1;
	while (++i < until)
		if (str2[i] != str1[i])
			return (0);
	return (1);
}

char	*str_cpy(char *src)
{
	int	i;
	int	src_len;
	char *copy;

	i = -1;
	src_len = str_size(src);
	copy = malloc(sizeof(char) * (src_len + 1));
	if (!copy)
		return (NULL);
	while (src[++i])
		copy[i] = src[i];
	copy[i] = '\0';
	return (copy);
}

int	str_size(const char *str)
{
	int	len;

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

	path_len = str_size(path);
	cmd_len = str_size(cmd);
	total_len = path_len + cmd_len;
	result_path = malloc(sizeof(char) * (total_len + 1));
	if (!result_path)
		return (NULL);
	i = -1;
	while (++i < path_len)
		result_path[i] = path[i];
	cmd_len = 0;
	while (i < total_len)
		result_path[i++] = cmd[cmd_len++];
	result_path[i] = '\0';
	return (result_path);
}
