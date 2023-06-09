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
#include <fcntl.h>
#include <sys/stat.h>

void shell_loop();
char* inserir_command();
char** split_command(char*);
void exec_command(char**);
int background(char**);
int redirection(char **);


int main(void)
{
    shell_loop();
    return 0;
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
        if(list_command[0] != " \n")
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
        printf("");
        exit(1);
    }
    return command;
}

char** split_command(char *command)
{
    int size = strlen(command);
    char **list_command = (char**)malloc(size * sizeof(char*));
    int indice = 0;
    char *token = strtok(command, " \n");
    while(token != NULL)
    {
        list_command[indice] = token;
        indice++;
        token = strtok(NULL, " \n");
    }
    list_command[indice] = NULL;
    return list_command;
}

/* ----FORK()----
 * FUNÇÂO:
 * Criar processos a partir de um processo PAI.
 *
 * RETORNO:
 * -1 -> não foi possivel criar o processo filho
 *  0 -> processo seja um filho
 * >0 -> PID do filho criado
 *
 *
 *----EXEC*()----
 * FUNÇÂO:
 * Transforma um processo filho em um novo programa.
 * {execl, execle, execlep, execv, execvp}
 * v -> vector
 * l -> list
 * p -> path
 *
 * RETORNO:
 * -1 -> não foi possivel executar.
 *
 *
 * ----WAIT()----
 *  FUNÇÂO:
 *  Espera o termino da execução do processo filho.
 *
 *
 *  ----OPEN()----
 *  FUNÇÂO:
 *  Acessar um arquivo.
 *
 *  FLAGS:
 *  O_CREAT -> Se o arquivo nao existir ele cria.
 *  O_TRUNC -> Permite a escrita no arquivo.
 *  O_RDWR -> Solicita a abetura do arquivo leitura/gravação (?)
 *
 *
 *  ----DUP2()----
 *  FUNÇÂO:
 *  Redirencionamento da entrada/saída de um arquivo.
 *
 *
 *  ----CHMOD()----
 *  FUNÇÂO:
 *  Ele concede privilegios a um arquivo.
 *
 *  FLAGS:
 *  S_IRUSR -> Permissão de leitura para o criador
 *  S_IWUSR -> Permissão de escrita para o criador
 * 
 */


void exec_command (char **list_command)
{
    pid_t pid_filho= fork();
    int bg_flag = background(list_command);

    if(pid_filho == 0) // Processo filho
    {
        int redirect_indx = redirection(list_command);

        if (redirect_indx > 0)
        {
            int dup_flag;
            int permit_flag;
            int arquivo = open(list_command[redirect_indx], O_CREAT | O_TRUNC |
                    O_RDWR);

            if(arquivo == -1)
            {
                perror("Error ao abrir o arquivo");
                exit(1);
            }

            dup_flag = dup2(arquivo, STDOUT_FILENO);
            if(dup_flag == -1)
            {
                perror("Error na mudança de output");
                exit(1);
            }

            permit_flag = chmod(list_command[redirect_indx], S_IRUSR | S_IWUSR);
            if(permit_flag == -1)
            {
               perror("Arquivo não recebeu privilegios");
               exit(1);
            }

            close(arquivo);
        }

        int exec_flag = execvp(list_command[0], list_command);
        if(exec_flag == -1)
        {
            perror("Erro na execução");
            exit(1);
        }

    }
    else
    {
        if(pid_filho > 0) // Processo pai
        {
            // Esperar o processo filho terminar
            if(!bg_flag)
            {
                wait(NULL);
            }
        }
        else // Erro (pid_filho == -1)
        {
            perror("Ocorreu um erro na criação do filho");
            exit(1);
        }
    }
}

int background(char **list_command)
{
    int indice = 0;
    while(list_command[indice] != NULL)
    {
        if(strcmp(list_command[indice], "&") == 0)
        {
            list_command[indice] = NULL;
            return 1;
        }
        indice++;
    }
    return 0; // Não existe &
}

int redirection(char **list_command)
{
    int indice = 0;
    while(list_command[indice] != NULL)
    {
        if(strcmp(list_command[indice], ">") == 0)
        {
            list_command[indice] = NULL;

            return indice + 1;
        }
        indice++;
    }
    return 0; // Não existe >
}
