#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
    int     *fd_array;
    int     stat_code;

	if (argc != 5)
		return (EXIT_FAILURE);
    fd_array = create_fd(argv[1], argv[argc - 1]);
    //a function to pass in only commands
    stat_code = pipe_all(argv, fd_array[0], fd_array[1], envp);
    return (stat_code);
}