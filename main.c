/*
 * Título: Implementação de um shell simplificado 
 * Autor: Antônio Cicero (811455) & Vitor Vechin (RA) 
 * Disciplina: Sistemas Operacionais 
 *
 * Descrição:
 * Este programa é um shell simplificado, que atua como um interpretador de comando.
 * Ele é capaz de criar processos para usuários.
 * O shell aceita comando inseridos pelo usuário no prompt "$" e executa esses
 * comando usando chamadas do sistema fornecidas pela biblioteca padrão do C.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

void shell_loop();
char* inserir_command();
char** split_command(char*);
void exec_command(char**);


int main(void)
{
    shell_loop();
    return (0);
}

void shell_loop()
{
    char* command = NULL;
    char** list_command = NULL; 
    int indice = 0;
    while(1)
    {
        printf("$ ");
        command = inserir_command();
        list_command = split_command(command);
        if(list_command[0][0] != '\n')
        {
            exec_command(list_command);
        }
        free(list_command);
        free(command);
    }
}

char* inserir_command()
{
    char *command= NULL;
    size_t size = 0;
    size_t ok;
    ok = getline(&command, &size, stdin);
    if(ok == -1)
    {
        printf("erro");
        exit(1);
    }
    return command;
}

char** split_command(char *command)
{
    int size = strlen(command);
    char **list_command = (char**)malloc(size * sizeof(char*));
    int indice = 0;
    char *token = strtok(command, " ");
    while(token != NULL)
    {
        list_command[indice] = token;
        indice++;
        token = strtok(NULL, " ");
    }
    list_command[indice] = NULL;
    return list_command;
}

/* ----FORK()----
 * FUNÇÂO:
 * Criar processos a partir de um processo PAI 
 *
 * RETORNO:
 * -1 -> não foi possivel criar o processo filho
 *  0 -> processo seja um filho
 * >0 -> PID do filho criado
 *
 *
 *----EXEC*()----
 * FUNÇÂO:
 * Transforma um processo filho em um novo programa
 * {execl, execle, execlep, execv, execvp}
 * v -> vector
 * l -> list
 * p -> path
 * e -> nao entendi
 *
 * RETORNO:
 * -1 -> não foi possivel executar
 *
 *
 * ----WAITPID(pid_t, int*, int)----
 *FUNÇÂO:
 *Esperar o execução e morte de um processo para so assim continuar
 *
 * RETORNO:
 * 0 -> sucesso
 * 1 -> erro não especificado
 * 2 -> sistema não aprenseta as funcionalidades necessarias
 * 3 -> limite de tempo
 */
void exec_command(char **list_command)
{
    pid_t pid_filho= fork();
    int status;
    if(pid_filho == 0) // Processo filho
    {
        status = execvp(list_command[0], list_command);
        if(status == -1)
        {
            perror("Ocorreu um erro na execução!");
            exit(1);
        }
    }
    else
    {

        if(pid_filho > 0) // Processo pai
        {
            // Esperar o processo filho terminar
            waitpid(pid_filho,&status, )

        }
        else // Erro (pid_filho == -1)
        {
            exit(1);
        }
    }
}
