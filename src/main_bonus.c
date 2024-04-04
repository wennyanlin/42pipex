#include "pipex.h"

char    **extract_cmds(char **argv, int argc, int start)
{
    char    **cmds;
    int     i;

    cmds = malloc(sizeof(char *) * (argc - start));
    if (!cmds)
        return (NULL);
    i = start - 1;
    while (++i < (argc - 1))
        cmds[i - start] = argv[i];
    cmds[i] = NULL;
    return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
    char    *next_line;
    int     pipe_fd[2];
    int     *fd_array = NULL;
    char    **cmds;
    
	if (argc < 5)
		return (EXIT_FAILURE);
    if (str_size(argv[1]) == 8 && string_compare(argv[1], "here_doc", 8))
    {
        next_line = get_next_line(STDIN_FILENO);
        pipe(pipe_fd);
        write(pipe_fd[WR], next_line, str_size(next_line));
        cmds = extract_cmds(argv, argc, 3);
        // need to open outfile
    }
    else
    {
        fd_array = create_fd(argv[1], argv[argc - 1]);
        cmds = extract_cmds(argv, argc, 2);
    }
    //a function to pass in only commands
    pipe_all(cmds, fd_array[0], fd_array[1], envp);
}