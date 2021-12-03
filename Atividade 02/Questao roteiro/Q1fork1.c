#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    pid_t pid = fork();//cria o filho

    printf(" O PID do filho é %d\n", pid);//PID do filho

    if (pid < 0 ){//erro na criação do processo filho
        fprintf(stderr,"Fork failed!\n");
        return 1;
    } else if (pid == 0){//Caso seja filho
        sleep(10);
        printf("[CHILD]: I'm finished.\n");
        return 42;
    } else {//caso seja pai
        printf("[PARENT]: Waiting on child.\n");
        int wstatus;
        wait(&wstatus);//espera o filho terminar e permite visualizar o status
        if (WIFEXITED(wstatus)) {
            printf("[PARENT]: Child returned with code %d.\n", WEXITSTATUS(wstatus));//finalizado normalmente
        }
        if (WIFSIGNALED(wstatus)) {//verifica se foi emitido o sinal para terminar o processo filho
            printf("[PARENT]: Filho terminou devido a um sinal %d.\n", WTERMSIG(wstatus));//termino devido a sinal
        }
    }
    return 0;
}