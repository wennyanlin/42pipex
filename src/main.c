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
    cmds[i - start] = NULL;
    return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
    int     fd_infile;
    int     fd_outfile;
    int     stat_code;
    char    **cmds;

	if (argc != 5)
		return (EXIT_FAILURE);
    fd_infile = create_fd_infile(argv[1]);
    fd_outfile = create_fd_outfile(argv[argc - 1]);
    cmds = extract_cmds(argv, argc, 2);
    stat_code = pipe_all(cmds, fd_infile, fd_outfile, envp);
    return (stat_code);
}