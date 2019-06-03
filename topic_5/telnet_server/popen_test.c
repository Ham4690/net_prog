#include <stdio.h>
#include <stdlib.h>
#define BUF 256

int
main (int argc, char *argv[])
{
	FILE	*fp;
	char	*cmdline = "cal";
	if ( (fp=popen(cmdline,"r")) ==NULL) {
		perror ("can not exec commad");
		exit(EXIT_FAILURE);
	}
	char buf[BUF];
  //fputs(buf,fp);

	while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		printf("=> %s", buf);
	}

	(void) pclose(fp);

	exit (EXIT_SUCCESS);
}
