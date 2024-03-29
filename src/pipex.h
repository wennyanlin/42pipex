/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:21:10 by wlin              #+#    #+#             */
/*   Updated: 2024/03/29 18:26:28 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

typedef struct s_str
{
	char	*value;
	int		continue_from_index;
}	t_str;

char	*execute_command(char *cmd1, char **envp);
char	**split(char *string, char separator);
int		count_words(char *string, char separator);
t_str	get_next_word(char *string, char separator, int continue_from);
t_str	parse_string(char *string, char separator, int continue_from);
char	*string_concat(char *path, char *cmd);
size_t  ft_strlen(char *str);
char	*find_path(char *env, char *cmd);
int		redirect_stdin(char *infile, char *cmd1, char *cmd2, char *outfile, char **envp);
char	*get_env(char **strs, char *ref);
int		string_compare(char *str1, char *str2, int until);
char	**array_concat(char *shell_path, char **args);
void	perror_and_exit(char *file, int code);
void	child_process(int pipefd[2], char *cmd1, char **envp);
void	parent_process(int pipefd[2], int fd2, char *cmd2, char **envp);
void	fd_dup2(int oldfd, int newfd);
t_str	chars_copy(t_str result, char *string, int len, int end);
int		is_empty_command(char *cmd);

#endif

