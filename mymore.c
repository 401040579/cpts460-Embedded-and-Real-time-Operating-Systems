/********** mymore.c file *************/
#include "ucode.c"
#define BLKSIZE 1024

int main(int argc, char *argv[ ])
{
	char mybuf[BLKSIZE];  // a null char at end of mybuf[ ]
	int n;
	int i;
	char hit[128];
	int count = 0;
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) return -1;
	printf("%s----------------------------------\n", "-");
	while ( n = read(fd, mybuf, BLKSIZE)) {
		mybuf[n] = 0;
		gets(hit); printf("n=%d\n", n);

		for (i = 0; i < n; i++)
		{

			mputc(mybuf[i]);

			if (mybuf[i] == '\n' || mybuf[i] == '\r')
			{
				count++;
			}

			if (count == 20)
			{

				gets(hit);

				if (strcmp(hit, " ") == 0)
				{
					count = 0;
				}
				else
				{
					count = 19;
				}
			}

		}
		//spit out chars from mybuf[ ] but handle \n properly;
	}
	printf("%s----------------------------------\n", "\n");

	close(fd);
}