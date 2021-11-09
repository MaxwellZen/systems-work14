#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

static void sighandler(int signo) {
	if (signo==SIGINT) {
		int out = open("exitlog", O_CREAT | O_WRONLY | O_APPEND, 0777);
		char *msg = "Program exited due to SIGINT\n";
		write(out, msg, strlen(msg));
		close(out);
		exit(0);
	} else if (signo==SIGUSR1) {
		printf("Parent process pid: %d\n", getppid());
	}
}

int main() {
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	printf("SIGINT: %d    SIGUSR1: %d\n", SIGINT, SIGUSR1);
	while(1) {
		printf("pid: %d\n", getpid());
		sleep(1);
	}
	return 0;
}
