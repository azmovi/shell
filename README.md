# Implementação de um shell simplificado
## Casos a serem tratados
> o simbolo $ representa o prompt do shell 
- ``` $ prog ``` 
    - Criação de um processo desse programa em foreground
- ```$ prog &``` 
    - Criação de um processo desse programa em background
- ```$ prog parâmetros```
    - Criação de um processo desse programa em foreground a partir de 
    especificações
- ```$ prog parâmetros &```
    - Criação de um processo desse programa em background a partir de
    especificações
- ```$ prog [parâmetros] > arquivo```
    - Criação de um processo desse programa a partir de especificações e envia
    o output gerado para arquivo
- ```$ prog1 | prog2 ```
    - Criação de um processo do programa 1 que envia o output gerado para o
    input de um processo criado do programa 2

