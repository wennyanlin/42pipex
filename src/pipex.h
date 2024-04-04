/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:21:10 by wlin              #+#    #+#             */
/*   Updated: 2024/04/04 11:19:59 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//LIB
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "gnl/get_next_line.h"

//MACRO
# define INVALID -1
# define NEGATIVE 0
# define CHILD 0
# define WR 1
# define RD 0
# define ENOCMD 2

//STRUCT
typedef struct s_str
{
	char	*value;
	int		continue_from_index;
}			t_str;

typedef struct s_pipe
{
	pid_t	pid;
	int		fd_in;
}			t_pipe;

//PROT
void	execute_command(char *cmd1, char **cmd_args, char **envp);
char	**ft_split(char *string, char separator);
int		count_words(char *string, char separator);
t_str	get_next_word(char *string, char separator, int continue_from);
t_str	parse_string(char *string, char separator, int continue_from);
char	*string_concat(char *path, char *cmd);
size_t  ft_strlen(const char *str);
char	*find_path(char *env, char *cmd);
// int		redirect_stdin(char *infile, char *cmd1, char *cmd2, char *outfile, char **envp);
char	*get_env(char **strs, char *ref);
int		string_compare(char *str1, char *str2, int until);
char	**array_concat(char *shell_path, char **args);
void	perror_and_exit(char *file, int code);
// void	child_process(int pipefd[2], char *cmd1, char **envp);
// void	parent_process(int pipefd[2], int fd2, char *cmd2, char **envp);
void	fd_dup2(int oldfd, int newfd);
t_str	chars_copy(t_str result, char *string, int len, int end);
int		is_empty_command(char *cmd);
void	free_array(char **array);
void	child_process(int pipefd[2], char *cmd1, char **cmd_args, int fd_out_override, char **envp);
int 	*create_fd(char *infile, char *outfile);
int		pipe_all(char **all_cmds, int infile_fd, int fd_out, char **envp);
int		array_size(char **array);
char 	*make_path(char *dir, char *cmd);
int		char_index(char *str, char ref);

#endif

