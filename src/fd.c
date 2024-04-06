#include "pipex.h"

int create_fd_infile(char *infile)
{
    int fd_infile;

    fd_infile = open(infile, O_RDONLY);
    if (fd_infile == INVALID)
		perror(infile);
    return (fd_infile);
}

int create_fd_outfile(char *outfile, int mode)
{
    int fd_outfile;
    if (mode == TRUNC)
        fd_outfile = open(outfile, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR
                    | S_IRGRP | S_IROTH);
    else
        fd_outfile = open(outfile, O_CREAT | O_APPEND | O_RDWR, S_IRUSR | S_IWUSR
                    | S_IRGRP | S_IROTH);
	if (fd_outfile == INVALID)
		perror_and_exit(outfile, EXIT_FAILURE);
    return (fd_outfile);
}

void	fd_dup2(int oldfd, int newfd)
{
	if (oldfd != -1 && dup2(oldfd, newfd) == -1)
	{
		close(oldfd);
		perror_and_exit("dup2", EXIT_FAILURE);
	}
	close(oldfd);
}