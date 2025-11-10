#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;
	(void)argc;
//int i = 5;	
	fd = open(argv[1], O_RDONLY);
	line = "";	
	while (line != NULL)
	//while (i-- > 0)
	{
		line = get_next_line(fd);
		if (line == 0)
			return (0);
		printf("%s\n", line);
		free(line);
		printf("------\n");
	}
	close(fd);
	return (0);
}
