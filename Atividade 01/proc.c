#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	pid_t childpid = -1;
	int i, n;
	
	if(argc != 2) {
		fprintf(stderr, "Uso %s n_processos\n", argv[0]);
		return 1;
	}
	
	n = atoi(argv[1]);
	
	for (i=1; i<n; i++)
		if(childpid = fork())
			break;
		
		fprintf(stderr, "%d - Meu PID é %ld, o PID do meu pai é %ld e criei um filho com PID igual a %ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);
		return 0;
}
