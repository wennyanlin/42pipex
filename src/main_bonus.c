#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
    char    **cmds;
    int     fd_infile;
    int     fd_outfile;
    int     pipe_stat_code;
    t_pipe  state;
    
	if (argc < 5)
		return (EXIT_FAILURE);
    if (str_size(argv[1]) == 8 && substr_compare(argv[1], "here_doc", 8))
    {
        fd_infile = read_here_doc(argv[2]);
        fd_outfile = create_fd_outfile(argv[argc - 1], APPEND);
        cmds = extract_cmds(argv, argc, 3);
        state = init_state((argc - 4), fd_infile, envp); //total - oufile - heredoc - limiter - ./pipex_bonus
    }
    else
    {
        fd_infile = create_fd_infile(argv[1]);
        fd_outfile = create_fd_outfile(argv[argc - 1], TRUNC);
        cmds = extract_cmds(argv, argc, 2);
        state = init_state((argc - 3), fd_infile, envp); //total - outfile - infile - ./pipex
    }
    pipe_stat_code = pipe_all(cmds, &state, fd_outfile);
    free_array(cmds);
    return (pipe_stat_code);
}
