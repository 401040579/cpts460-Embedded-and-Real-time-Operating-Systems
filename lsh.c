#include "ucode.c"

int strcpy(char *dest, char *src);
char *strcat(char *dest, const char *src);

int main()
{
	int pid, status;
	signal(2, 1);
	while (1)
	{
		char line[128];
		printf("mysh %d # :", getpid());
		gets(line);
		if (line == 0) return;
		token(line);

		if (argc == 0)
		{
			printf("argc=%d\n", argc);
		}
		else if (argc == 1)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);

			char cmd[128];
			strcpy(cmd, argv[0]);

			printf("cmd=%s\n", cmd);

			if (strcmp("logout", cmd) == 0)
			{
				exit(0);
			}
			//fork() create a process and return pid=0 for child
			//child's pid to the parent
			pid = fork();
			if (pid == 0)
				exec(cmd); // child doing something
			else
				pid = wait(&status);//parent doing something
		}
		else if (argc == 2)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);
			printf("argv[1]=%s\n", argv[1]);

			char src[128], dest[128];
			strcpy(src, argv[0]);
			strcpy(dest, argv[1]);
			strcat(src, " ");
			strcat(src, dest);

			pid = fork();
			if (pid == 0)
				exec(src);
			else
				pid = wait(&status);
		}
		else if (argc == 3)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);
			printf("argv[1]=%s\n", argv[1]);
			printf("argv[2]=%s\n", argv[2]);

			if (strcmp(argv[1], "<") == 0)
			{
				close(0);
				open(argv[2], O_RDONLY);
				exec(argv[0]);
			}
		}
		else if (argc == 4)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);
			printf("argv[1]=%s\n", argv[1]);
			printf("argv[2]=%s\n", argv[2]);
			printf("argv[3]=%s\n", argv[3]);

			if (strcmp(argv[2], ">") == 0)
			{
				close(1);
				open(argv[3], O_WRONLY | O_CREAT);

				char src[128], dest[128];
				strcpy(src, argv[0]);
				strcpy(dest, argv[1]);
				strcat(src, " ");
				strcat(src, dest);

				exec(src);
			}
			else if (strcmp(argv[2], ">>") == 0)
			{
				close(1);
				open(argv[3], O_WRONLY | O_APPEND | O_CREAT);

				char src[128], dest[128];
				strcpy(src, argv[0]);
				strcpy(dest, argv[1]);
				strcat(src, " ");
				strcat(src, dest);

				exec(src);
			}
			else
			{
				char src[128], dest[128];
				strcpy(src, argv[0]);
				strcpy(dest, argv[1]);
				strcat(src, " ");
				strcat(src, dest);

				int pid, pd[2];

				pipe(pd); // create a pipe: pd[0]=READ, pd[1]=WRITE

				pid = fork(); // fork a child to share the pipe

				if (pid) { // parent: as pipe READER
					close(pd[1]); // close pipe WRITE end
					dup2(pd[0], 0); // redirect stdin to pipe READ end
					exec(argv[3]);
				}
				else { // child : as pipe WRITER
					close(pd[0]); // close pipe READ end
					dup2(pd[1], 1); // redirect stdout to pipe WRITE end
					exec(src);
				}
			}

		}
		else if (argc == 5)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);
			printf("argv[1]=%s\n", argv[1]);
			printf("argv[2]=%s\n", argv[2]);
			printf("argv[3]=%s\n", argv[3]);
			printf("argv[4]=%s\n", argv[4]);

			//argv[0]+argv[1]
			char src[128], dest[128];
			strcpy(src, argv[0]);
			strcpy(dest, argv[1]);
			strcat(src, " ");
			strcat(src, dest);

			//argv[3]+argv[4]
			char src2[128], dest2[128];
			strcpy(src2, argv[3]);
			strcpy(dest2, argv[4]);
			strcat(src2, " ");
			strcat(src2, dest2);

			int pid, pd[2];

			pipe(pd); // create a pipe: pd[0]=READ, pd[1]=WRITE

			pid = fork(); // fork a child to share the pipe

			if (pid) { // parent: as pipe READER
				close(pd[1]); // close pipe WRITE end
				dup2(pd[0], 0); // redirect stdin to pipe READ end
				exec(src2);
			}
			else { // child : as pipe WRITER
				close(pd[0]); // close pipe READ end
				dup2(pd[1], 1); // redirect stdout to pipe WRITE end
				exec(src);
			}
		}
	}
}