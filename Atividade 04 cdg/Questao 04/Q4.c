#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void quickSort(int valor[], int esquerda, int direita){
    int i, j, x, y;
    i = esquerda;
    j = direita;
    x = valor[(esquerda + direita) / 2];
    while (i <= j) {
        while (valor[i] < x && i < direita) {
            i++;
        }
        while (valor[j] > x && j > esquerda) {
            j--;
        }
        if (i <= j) {
            y = valor[i];
            valor[i] = valor[j];
            valor[j] = y;
            i++;
            j--;
        }
    }

    if (j > esquerda) {
        quickSort(valor, esquerda, j);
    }

    if (i < direita) {
        quickSort(valor, i, direita);
    }
}

void selectionSort(int num[], int tam){
    int i, j, min, aux;
    for (i = 0; i < (tam - 1); i++){
        min = i;
        for (j = (i + 1); j < tam; j++) {
            if (num[j] < num[min]) {
                min = j;
            }
        }
        if (i != min) {
            aux = num[i];
            num[i] = num[min];
            num[min] = aux;
        }
    }
}

void imprimirVetor(int vet[], int n) {
    printf("[");
    for (int i = 0; i < n - 1; i++) {
        printf("%d ", vet[i]);
    }
    printf("%d]\n", vet[n - 1]);
}

int main(){
    pid_t pid_p = getpid(); //utilizei para poder capturar o valor do PID do pai

    int vetor[10] = {1,10,3,5,2,7,9,6,4,8}; //Criei um vetor com 10 valores de forma desordenada;
    
    clock_t temp_pai_ini, temp_pai_fim, temp_filho_ini, temp_filho_fim; //Variaveis para receber os tempos de inicio e fim de cada processo
    float total_pai, total_filho; //variaveis para receber os valores calculados do tempo de execução dos processos
    pid_t pid = fork(); //Crio o processo filho

    if(pid < 0){//veritica se foi possivel criar os filhos, caso contrário aponta o erro
        printf("erro ao criar filhos.\n");
    }
    else if(pid == 0){//Execução do processo filho
        printf("Sou o filho PID: %d", pid); //Inidica que é o filho e o PID do mesmo
        printf("O filho utiliza quicksort\n");//Indica o algoritmo utilizado pelo filho
        temp_filho_ini = clock();//captura o tempo de inicio do processo
        quickSort(vetor, 0, 9);//executa o algoritmo quicksort pela função implementada
        temp_filho_fim = clock();//captura o valor de termino do processo

        imprimirVetor(vetor, 10);//executa função de imprimir o vetor que agora está ordenado

        total_filho = (temp_filho_fim - temp_filho_ini)*1000 / CLOCKS_PER_SEC; // calcula o tempo para realizar a tarefa

        int matar; //cria uma variável para receber o valor do processo kill()

        sleep(3);//uma pausa no processo 

        matar = kill(pid_p, SIGKILL);//executa a tentativa de eliminar o processo pai

        if(matar == -1){//Indica que houve erro em elimnar o pai 
            printf("Assassinar o pai\n");
            exit(EXIT_FAILURE);
        }
    }
    else{//inica ações do pai
        printf("Eu sou o pai PID: %d", pid_p);// Indica que é o pai e o PID do mesmo
        printf("O pai utilizar selection-sort\n");

        temp_pai_ini = clock();//captura inicio do processo pai
        selectionSort(vetor, 10);//executa o algoritmo
        temp_pai_fim = clock();//captura o fim do processo pai
        imprimirVetor(vetor, 10);//impime o vetor
        
        int wstatus;
        wait(&wstatus); //continua esperando o processo do filho acabar
        
        total_pai = (temp_pai_fim - temp_pai_ini)*1000 / CLOCKS_PER_SEC;
        int matarfilho;

        matarfilho = kill(pid, SIGKILL);//tenta matar o filho
        if(matarfilho > 0){//Manda mensagem ao eliminar o filho
            printf("filho morto\n");
        }
    }
    printf("tempo de execução pai: %f e tempo de execução filho: %f", total_pai, total_filho);//mostra o tempo de execução do pa e do filho
}