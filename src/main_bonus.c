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
    cmds[i - start] = NULL;
    return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
    char    **cmds;
    int     fd_infile;
    int     fd_outfile;
    
	if (argc < 5)
		return (EXIT_FAILURE);
    if (str_size(argv[1]) == 8 && substr_compare(argv[1], "here_doc", 8))
    {
        fd_infile = read_here_doc(argv[2]);
        fd_outfile = create_fd_outfile(argv[argc - 1], APPEND);
        cmds = extract_cmds(argv, argc, 3);
    }
    else
    {
        fd_infile = create_fd_infile(argv[1]);
        fd_outfile = create_fd_outfile(argv[argc - 1], TRUNC);
        cmds = extract_cmds(argv, argc, 2);
    }
    return (pipe_all(cmds, fd_infile, fd_outfile, envp));
}