#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();//cria o processo filho

    printf(" O PID do filho é %d\n", pid);//PID do filho

    if (pid < 0 ){
        fprintf(stderr,"Fork failed!\n");//falha a cirar os processos filho
        return 1;
    } else if (pid == 0){//Caso seja filho
        sleep(8);
        printf("[CHILD]: I'm finished.\n");//mensagem para caso o filho encerre normalmente
        return 42;
    } else {//Caso seja pai
        printf("[PARENT]: Waiting on child.\n");
        int wstatus;//variável para o status do processo
        waitpid(pid, &wstatus, WUNTRACED);//waitpid com opção que permite verificar o estado do processo caso tenha sido suspenso
        //wait(&wstatus);
        if (WIFEXITED(wstatus)) {//Caso tenha finalizado normalmente
            printf("[PARENT]: Child returned with code %d.\n", WEXITSTATUS(wstatus));
        }
        if (WIFSIGNALED(wstatus)) {//Caso tenha sido emitido um sinal Kill -SIGKILL
            printf("[PARENT]: Filho terminou devido a um sinal %d.\n", WTERMSIG(wstatus));//emite o número do sinal de kill
        }
        else if (WIFSTOPPED(wstatus)) {//Caso tenha sido emitido um sinal para suspender o processo filho
            printf("[PARENT]: Filho foi suspenso devido ao sinal %d.\n", WSTOPSIG(wstatus));//emite o número do sinal
        }
    }
    return 0;
}