/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:13:02 by wlin              #+#    #+#             */
/*   Updated: 2023/10/28 19:25:14 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_copy;

	s_copy = (char *)s;
	while (*s_copy != '\0')
	{
		if (*s_copy == c)
			return (s_copy);
		s_copy++;
	}
	if (c == '\0')
		return (s_copy);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *storage, char *buffer)
{
	char	*dup_storage;
	int		i;

	i = -1;
	if (!storage || !buffer)
		return (NULL);
	dup_storage = malloc(ft_strlen(storage) + ft_strlen(buffer) + 1);
	if (!dup_storage)
		return (ft_free_space(&storage));
	while (storage[++i] != '\0')
		dup_storage[i] = storage[i];
	dup_storage[i] = '\0';
	return (dup_storage);
}

char	*ft_strjoin(char *storage, char *buffer)
{
	char	*result;
	int		i;
	int		j;

	if (!storage)
	{
		storage = malloc(sizeof(char));
		if (!storage)
			return (NULL);
		storage[0] = '\0';
	}
	i = ft_strlen(storage);
	result = ft_strdup(storage, buffer);
	if (!result)
		return (NULL);
	j = -1;
	while (buffer[++j] != '\0')
		result[i + j] = buffer[j];
	result[i + j] = '\0';
	free(storage);
	return (result);
}

/*
int	main()
{
	char s[] = "Welcome to 42";
	int	c = 'l';

	printf("%s", ft_strchr(s, c));
	return (0);
}
int	main()
{
	char const s1[] = "Hola";
	char const s2[] = ", quetal?";
	printf("%s", ft_strjoin(s1, s2));
}*/
