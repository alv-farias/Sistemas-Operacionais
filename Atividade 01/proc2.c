#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    
    pid_t pidinic = getpid();//Como o processo inicial é o próprio main, ao utilizarmos a função getpid() a mesma retorna o PID do processo atual, sendo esse o main.
    printf("Eu sou o main meu PID é: %d\n", pidinic);//Apresenta o valor retornado pela função getpid();
    
    pid_t PID = fork(); //Aqui eu estou executando a função fork() que pode retornar -1, 0 ou 1 e cada valor representa uma situação diferente
    
    if(PID == -1){//Nesse caso, temos que se o fork() retorna -1 significa que houve um erro ao realizar processos
        printf("Erro ao criar processos!\n");    
    }
    
    if(PID == 0){//filho por fork() retorna 0 significando que estou no processo filho. Com isso executo o processo ls partindo da função execl
        execl("/bin/ls","ls",NULL,NULL);//execl("caminho do comando", "comando", "argumento", "argumento");  como só quero executar o comando ls, passo os argumentos 
                                        //como NULL, visto que para essa função é necessário ter quatro componentes que a mesma recebe
    }

    else {//Nessa condição utilizamos o else pois a única condição para o valor de PID que sobra é referente a 1 sendo esse o indicativo de ser o Pai
          //Como o fork() gera um filho partindo do processo atual, temos que o PID do pai será igual ao PID do main, pois foi a partir do mesmo que o processo filho
          //foi criado, por isso o mesmo valor da variável que representa o PID do processo main (Pré fork()) é o valor apresentado no getpid() no estado de pai
          //Para poder apresentar o valor do filho, utilizei o valor do fork(), sendo a variável "PID", pois se estou sendo o pai, o valor que o PID apresenta é o do 
          //filho gerado.
        printf("Aqui é o pai (PID: %d), processo filho PID=%d criado\n",getpid(), PID);
    }

    
return 0;
}
