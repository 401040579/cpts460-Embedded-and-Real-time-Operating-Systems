// login.c : Upon entry, argv[0]=login, argv[1]=/dev/ttyX
#include "ucode.c"
int in, out, err;
char username[128], password[128];

#define NULL 0

int strcpy(char *dest, char *src);
char *strcat(char *dest, const char *src);
//cited from website
char *my_strtok(char *s,const char *delim) 
{
    static char *last;
    char *tok;
    char *ucdelim;
    char *spanp;
    int c,sc;

    if (s == NULL && (s = last) == NULL)
        return NULL;
  
    
    int found = 0;
    cont:
    c=*s++;
    for (spanp = (char *)delim;(sc = *spanp++) != 0;)
    {
        if (c == sc)
            goto cont;
    }
    if (c == 0) 
    {
        last = NULL;
        return NULL;
    }

    tok = s-1;
    while (!found && *s != '\0') 
    {
        ucdelim = (char *) delim;
        while (*ucdelim) 
        {
            if (*s == *ucdelim) 
            {
                found = 1;
                *s = '\0';
                last = s + 1;
                break;
            }
            ucdelim++;
        }
        if (!found)
        {
            s++;
            if(*s=='\0')
                last = NULL;
        }
    }

    return tok;
}

int my_atoi(char str[128])
{
	int dec = 0, i, j;
	int len = strlen(str);
	for (i = 0; i < len; i++)
	{
		dec = dec * 10 + (str[i] - '0');
	}
	return dec;
}

void tokPart(char* accounts, char *name, char *password, int *uid, int *gid, char *path)
{
	char *part = my_strtok(accounts, ":");
	char temp[10];

	//printf("%s\n", part);
	strcpy(name, part);

	part = my_strtok(0, ":");

	//printf("%s\n", part);
	strcpy(password, part);

	part = my_strtok(0, ":");

	//printf("%s\n", part);
	strcpy(temp, part);
	*uid = my_atoi(temp);

	part = my_strtok(0, ":");

	//printf("%s\n", part);
	strcpy(temp, part);
	*gid = my_atoi(temp);

	part = my_strtok(0, ":"); part = my_strtok(0, ":");

	//printf("%s\n", part);
	strcpy(path, part);
}

main(int argc, char *argv[])
{
	signal(2, 1);
	char buf[1024], path[128];
	char accounts[4][128];
	char *newLine, name_k[128], password_k[128];
	int uid, gid;
	int n;
	//(1). close file descriptors 0, 1 inherited from INIT.
	//close(0); close(1);

	//(2). open argv[1] 3 times as in(0), out(1), err(2).
	//in = open(argv[1], O_RDONLY);
	//out = open(argv[1], O_WRONLY);
	//err = open(argv[1], O_WRONLY);

	//(3). settty(argv[1]); // set tty name string in PROC.tty
	//settty(argv[1]);
printf("well come to login%s",".");
	//(4). open /etc/passwd file for READ;
	int fd = open("/etc/passwd", O_RDONLY);
	int i = 0;
	while (1) {
		printf("login: %s"," "); gets(username);
		printf("password: %s"," "); gets(password);
		n = read(fd, buf, 1024);
		buf[n] = 0;
		newLine = my_strtok(buf, "\n\r");
		//for each line in /etc/passwd file do {
		//tokenize user account line;
		//(6). if (user has a valid account) {
		//(7). change uid, gid to user's uid, gid; // chuid()
		//change cwd to user's home DIR // chdir()
		//close opened /etc/passwd file // close()
		//(8). exec to program in user account // exec()
		//}
		//}

		while (newLine != 0)
		{
			//printf("%s\n", newLine);
			for (i = 0; i < 4; i++) {
				strcpy(accounts[i], newLine);
				newLine = my_strtok(0, "\n\r");
			}

			for (i = 0; i < 4; i++) {
				tokPart(accounts[i], name_k, password_k, &uid, &gid, path);
				printf("name: %s password: %s uid: %d gid: %d path: %s\n", name_k, password_k, uid, gid, path);
				if (strcmp(name_k, username) == 0 && strcmp(password_k, password) == 0)
				{
					printf("valid account%s\n",".");
					chuid(uid, gid);
					chdir(path);
					close(fd);
					exec("lsh");
				}
			}
		}

		printf("login failed, try again\n");
	}
}
