#include "ucode.c"
void mutilpip(char* line)
{
	if (!line || (line[0] == 0) || (strcmp(line, "") == 0))
		exit(0);

	int pd[2];
	int pid, status;
	int length = strlen(line);
	char* head = strtok(line, "|");
	char* tail = NULL;

	if (strlen(head) < length)
		tail = line + strlen(head) + 1;
	else
		tail = line + length;


	if (!tail || (strcmp(tail, "") == 0))
		execute_command(head);




	if (pipe(pd) != 0) 
		if ((pid = fork()) < 0)
		
			if (!pid) {
				close(pd[0]);
				close(1);
				dup(pd[1]);
				execute_command(head);
			}
			else {
				pid = wait(&status);
				close(pd[1]);
				close(0);
				dup(pd[0]);

				mutilpip(tail);
			}
}

int main()
{
	while (1)
	{
		int pid, status;

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

			if (strcmp("logout", argv[0]))
			{
				exit(0);
			}


			if ((pid = fork()) < 0)
				printf("forking child process%s", ".");

			if (pid)
			{
				printf("%d waiting...\n", pid);
				pid = wait(&status);
				printf("%d died of %04x\n", pid, status);
			}
			else
			{
				mutilpip(line);
			}
		}
	}
	return 0;
}













int strcpy(char *dest, char *src);
char *strcat(char *dest, const char *src);
int main1()
{
	int pid, status;
	/*
	int pid, pd[2];
	pipe(pd); // create a pipe: pd[0]=READ, pd[1]=WRITE
	pid = fork(); // fork a child to share the pipe
	if (pid) { // parent: as pipe READER
		close(pd[1]); // close pipe WRITE end
		dup2(pd[0], 0); // redirect stdin to pipe READ end
		exec(cmd2);
	}
	else { // child : as pipe WRITER
		close(pd[0]); // close pipe READ end
		dup2(pd[1], 1); // redirect stdout to pipe WRITE end
		exec(cmd1);
	}
	*/
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

			if (strcmp("logout", argv[0]))
			{
				exit(0);
			}

			pid = fork();
			printf("pid=%d", pid);
			if (pid == 0)
				exec(argv[0]);
			else
				pid = wait(&status);
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
			printf("src=%s\n", src);
			exec(src);
		}
		else if (argc == 3)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);
			printf("argv[1]=%s\n", argv[1]);
			printf("argv[2]=%s\n", argv[2]);
		}
		else if (argc == 4)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);
			printf("argv[1]=%s\n", argv[1]);
			printf("argv[2]=%s\n", argv[2]);
			printf("argv[3]=%s\n", argv[3]);
		}
	}
}