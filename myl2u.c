#include "ucode.c"
#define BLKSIZE 1024

int main(int argc, char *argv[ ])
{
	char buf[1024];
	int n,i;

	int fd = open(argv[1], O_RDONLY);

	creat(argv[2]);
	int gd = open(argv[2], O_WRONLY);
	while (n = read(fd, buf, BLKSIZE))
	{
		for (i = 0; i < n; i++)
		{

			if (buf[i] >= 'a' && buf[i] <= 'z')
				buf[i] = buf[i]+('A'-'a');
		}

		write(gd, buf, n);
	}
	close(fd);
	close(gd);
}