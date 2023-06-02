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
 *
 * Casos Tratados:
 * $ prog
 * Cria um processo em foreground deste programa.
 *
 * $ prog &
 * Cria um processo em background deste programa.
 *
 * $ prog parâmetros
 * Cria um processo em foreground deste programa com parâmetros especificados.
 *
 * $ prog parâmetros &
 * Cria um processo em background deste programa com parâmetros especificados.
 *
 * $ prog [parâmetros] > arquivo
 * Cria um processo deste programa com parâmetros especificados e redireciona a
 * saída gerada para um arquivo.
 *
 * $ prog1 | prog2
 * Cria um processo do programa 1 que envia a saída gerada para a entrada de um
 * processo criado do programa 2.

 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main(void){
    /*
       */
  return (0);
}


