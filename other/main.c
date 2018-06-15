#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DICT_LEN 256
int strlen(char *s)
{
  int i = 0;
  while(*s){
    i++; s++;
  }
  return i;
}

int strcmp(char *s1, char *s2)
{
  while((*s1 && *s2) && (*s1==*s2)){
      s1++; s2++;
  }
  if ((*s1==0) && (*s2==0))
    return 0;
  return(*s1 - *s2);

}

int strcpy(char *dest, char *src)
{
  while(*src){
    *dest++ = *src++;
  }
  *dest = 0;
}

void* memcpy(void *dest, void *src, int n)
{
  char *s = (char *)src;
  char *d = (char *)dest;

  int i;
  for(i=0; i<n; i++)
     d[i] = s[i];

  return dest;
}

int *create_delim_dict(char *delim)
{
	int *d = (int*)malloc(sizeof(int)*DICT_LEN);
	memset((void*)d, 0, sizeof(int)*DICT_LEN);

	int i;
	for (i = 0; i< strlen(delim); i++) {
		d[delim[i]] = 1;
	}
	return d;
}

char *my_strtok(char *str, char *delim)
{

	static char *last, *to_free;
	int *deli_dict = create_delim_dict(delim);

	if (!deli_dict) {
		return NULL;
	}

	if (str) {
		last = (char*)malloc(strlen(str) + 1);
		if (!last) {
			free(deli_dict);
		}
		to_free = last;
		strcpy(last, str);
	}

	while (deli_dict[*last] && *last != '\0') {
		last++;
	}
	str = last;
	if (*last == '\0') {
		free(deli_dict);
		free(to_free);
		return NULL;
	}
	while (*last != '\0' && !deli_dict[*last]) {
		last++;
	}

	*last = '\0';
	last++;

	free(deli_dict);
	return str;
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
	
	part = my_strtok(NULL, ":");

	//printf("%s\n", part);
	strcpy(password, part);
	
	part = my_strtok(NULL, ":");

	//printf("%s\n", part);
	strcpy(temp, part);
	*uid = my_atoi(temp);

	part = my_strtok(NULL, ":");
	
	//printf("%s\n", part);
	strcpy(temp, part);
	*gid = my_atoi(temp);

	part = my_strtok(NULL, ":"); part = my_strtok(NULL, ":");

	//printf("%s\n", part);
	strcpy(path, part);
}

main()
{
	char name[128], password[128], buf[1024], path[128];
	char accounts[4][128];
	char *newLine, name_k[128], password_k[128];
	int uid, gid;
	int n;
	int fd = open("passwd", O_RDONLY);
	printf("login:"); gets(name);
	printf("password:"); gets(password);
	n = read(fd, buf, 1024);
	buf[n] = 0;
	newLine = my_strtok(buf, "\n\r");
	while (newLine != NULL)
	{
		//printf("%s\n", newLine);
		for (int i = 0; i < 4; i++) {
			strcpy(accounts[i], newLine);
			newLine = my_strtok(NULL, "\n\r");
		}

		for (int i = 0; i < 4; i++) {
			tokPart(accounts[i], name_k, password_k, &uid, &gid, path);
			printf("name: %s password: %s uid: %d gid: %d path: %s\n", name_k, password_k, uid, gid, path);
			if (strcmp(name_k, name) == 0 && strcmp(password_k, password) == 0)
			{
				printf("valid account\n");
			}
		}
	}
}