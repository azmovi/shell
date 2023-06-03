/*
 * Título: Implementação de um shell simplificado 
 * Autor: Antônio Cicero (811455) & Vitor Vechin (RA) 
 * Disciplina: Sistemas Operacionais 
 *
 * Descrição:
 * Este programa é um shell simplificado, que atua como um interpretador de comandos.
 * Ele é capaz de criar processos para usuários.
 * O shell aceita comandos inseridos pelo usuário no prompt "$" e executa esses
 * comandos usando chamadas do sistema fornecidas pela biblioteca padrão do C.
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void shell_loop();
char* inserir_comando();
char** split_comando();


int main(void)
{
    shell_loop();
    return (0);
}

void shell_loop()
{
    char* comando = NULL;
    while(true)
    {
        printf("$ ");
        comando = inserir_comando();
    }
}

char* inserir_comando()
{
    char *comando= NULL;
    size_t size = 0;
    size_t ok;
    ok = getline(&comando, &size, stdin);
    if(ok == -1)
    {
        printf("erro");
        exit(1);
    }
    return comando;
}
char** split_comando()
{

}
