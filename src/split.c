/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:21:15 by wlin              #+#    #+#             */
/*   Updated: 2024/03/31 22:10:56 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_words(char *string, char separator)
{
	int	count_word;
	int	i;

	i = 0;
	count_word = 0;
	while (string[i])
	{
		while (string[i] && string[i] == separator)
			i++;
		if (string[i] && string[i] != separator)
			count_word++;
		while (string[i] && string[i] != separator)
			i++;
	}
	return (count_word);
}

t_str	parse_string(char *string, char separator, int	continue_from)
{
	int		i;
	int		len;
	int		end;
	t_str	next_word;

	i = continue_from;
	len = 0;
	next_word.value = NULL;
	while (string[i])
	{
		if (string[i] && string[i] == separator)
			i++;
		while (string[i + len] && string[i + len] != separator)
			len++;
		end = i + len;
		next_word.value = malloc(sizeof(char) * (len + 1));
		if (!next_word.value)
			return (next_word);
		next_word = chars_copy(next_word, string, i, end);
		return (next_word);
	}
	return (next_word);
}

t_str	chars_copy(t_str result, char *string, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
		result.value[i++] = string[start++];
	result.value[i] = '\0';
	result.continue_from_index = start + 1;
	return (result);
}

t_str	get_next_word(char *string, char separator, int	continue_from)
{
	int		i;
	t_str	next_word;

	i = continue_from;
	next_word.value = NULL;
	while (string[i])
	{
		while (string[i] && string[i] == separator)
			i++;
		if (string[i] && string[i] == '"')
		{
			return (parse_string(string, '"', i));
		}
		else
			return (parse_string(string, separator, i));
	}
	return (next_word);
}

char	**ft_split(char *string, char separator)
{
	char	**result_array;
	int		num_words;
	int		i;
	t_str	word;
	char	**empty;

	i = 0;
	word.continue_from_index = 0;
	if (!*string)
	{
		empty = malloc(sizeof(char*) * 2);
		empty[0] = "";
		empty[1] = NULL;
		return (empty);
	}
	num_words = count_words(string, separator);
	result_array = malloc(sizeof(char*) * (num_words + 1));
	if (!result_array)
		return (NULL);
	while (i < num_words)
	{
		word = get_next_word(string, separator, word.continue_from_index);
		result_array[i++] = word.value;
	}
	result_array[i] = NULL;
	return (result_array);
}

