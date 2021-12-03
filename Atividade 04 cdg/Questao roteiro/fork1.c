#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if (pid < 0 ){
        fprintf(stderr,"Fork failed!\n");
        return 1;
    } else if (pid == 0){
        printf("[CHILD]: I'm finished.\n");
        return 42;
    } else {
        printf("[PARENT]: Waiting on child.\n");
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            printf("[PARENT]: Child returned with code %d.\n", WEXITSTATUS(wstatus));
        }
    }
    return 0;
}