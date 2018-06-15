/********** mygrep.c file *************/
#include "ucode.c"
#define BLKSIZE 1024

char *mystrstr(char*s1, char*s2)
{
	if (*s1 == 0)
	{
		if (*s2)
			return (char*)0;
		return (char*)s1;
	}
	while (*s1)
	{
		int i = 0;
		while (1)
		{
			if (s2[i] == 0)
				return s1;
			if (s2[i] != s1[i])
				break;
			i++;
		}
		s1++;
	}
	return (char*)0;
}
void mymemset(void *b, int c, int len)
{
	char *s = b;

	while (len--)
		*s++ = c;
}
int main(int argc, char *argv[ ])
{
	char mybuf;  // a null char at end of mybuf[ ]
	char line[128];
	int n;
	int i = 0;
	char hit[128];
	int count = 0;
	int fd = open(argv[2], O_RDONLY);
	//printf("argv[1]=%s", argv[1]);
	//printf("strlen(argv[1])=%d", strlen(argv[1]));
	//char mybuf2[strlen(argv[1])];
	//strcpy(mybuf2, argv[1]);
	//printf("mybuf2 = %s", mybuf2);

	if (fd < 0) return -1;
	printf("%s----------------------------------\n", "-");
	while ( n = read(fd, &mybuf, 1)) {
		//mybuf[n] = 0;
		//gets(hit); printf("n=%d\n", n);


		if (mybuf != '\n')
		{
			line[i] = mybuf;
			i++;
		}
		else
		{
			//printf("mybuf=%s\n", ".");
			//mputc(mybuf);
			if (strstr(line, argv[1]) != 0)
				printf("here: %s\n", line);
			memset(line, 0, sizeof(line));
			i = 0;
		}
		/*

		for (i = 0; i < n; i++)
		{
			if (mybuf[i] == '\n')
			{
				if (strstr(line, argv[1]) != 0)
				{
					printf("%s\n", line);
				}
				memset(line, 0, sizeof(line));

			}

			mputc(mybuf[i]);
		}
		*/
	}
	printf("%s----------------------------------\n", "\n");

	close(fd);
}