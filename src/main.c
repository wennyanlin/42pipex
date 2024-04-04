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
    {
        cmds[i - start] = argv[i];
    }
    cmds[i] = NULL;
    return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
    int     *fd_array;
    int     stat_code;
    char    **cmds;

	if (argc != 5)
		return (EXIT_FAILURE);
    fd_array = create_fd(argv[1], argv[argc - 1]);
    //a function to pass in only commands
    cmds = extract_cmds(argv, argc, 2);
    stat_code = pipe_all(cmds, fd_array[0], fd_array[1], envp);
    return (stat_code);
}