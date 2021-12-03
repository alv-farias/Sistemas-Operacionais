#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

extern int errno;

int main() {
    
    printf("Eu sou o pai, meu PID é %d.\n", getpid());//captura o PID do pai

    pid_t pid = fork();//cira o processo filho

    printf(" O PID do filho é %d\n", pid);//mostra o PID do processo filho

    if (pid < 0){//verifica se aconteceu um erro em criar os prcesso filho
        fprintf(stderr,"Fork failed!\n");
        return 1;
    }
    else if (pid == 0){//Indica que é as ações do processo filho
        printf("[CHILD]: Sou o filho PID: %d.\n", getpid());//mosta o PID do filho
        sleep(1000);//Uma pausa que permite executar alguns comandos no terminal para modificar o estado do processo
    }
    else{//Indica que é o processo pai que executa essas ações
        int teste;//Variável teste para realizar os testes em relação aos erros que podem ocorrer
        do{
            int wstatus;//variável status
            teste = waitpid(pid, &wstatus, WUNTRACED);//varipavel teste recebe a chamada waitpid permitindo verificar mudanças de status dos
                                                      //processos sendo suspenso ou eliminado
            if (teste == -1){//Caso da obtenção de algum erro
                if(errno == ECHILD){//Comparação com a constante de erro aprensentada na mensagem
                    fprintf(stderr,"Erro devido a não existencia de filhos para terminar: %d\n",errno);
                }
                else if(errno == EINTR || WIFSTOPPED(wstatus)){//Comparação com a constate de erro apresentada na mensagem e o caso de ter sido interrompida
                    fprintf(stderr,"Erro devido interupção da função: %d\n",errno);
                }
            }
        }while(teste != -1);
    }
}