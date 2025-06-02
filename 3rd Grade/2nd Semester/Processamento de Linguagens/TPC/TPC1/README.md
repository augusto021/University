# TPC1 - Somador ON/Off (Data: 2025-02-10)

## Resumo

**Objetivo:** Criar um programa 'somador' que deve somar todos os números que estejam presentes no texto recebido por input.

**Explicação das Funcionalidades:**

1. Quando encontra a palavra **'Off'** (case-insensitive), a função de somar é desligada / posta em pausa.
2. Quando encontra a palavra **'On'** (case-insensitive), a função de somar é ligada / retomada.
3. Sempre que encontrar o sinal **'='** deve ser efetuado um print do total atual da soma para o stdout. A nenhum ponto do programa deve-se dar reset ao total da soma. Após o print o somador continua a somar como se nada tivesse acontecido.


## Implementação

A implementação foi desenvolvida em **Python**, utilizando a biblioteca `sys` para ler o texto de entrada. O código segue uma abordagem sequencial baseada em manipulação de strings.

### **Estrutura e Lógica do Código**  

O programa começa por ler um texto de entrada a partir do `stdin` utilizando `sys.stdin.read()`, dividindo-o em palavras com `.split()`, separando os elementos por espaços. Em seguida, define duas variáveis principais: `soma = 0`, que armazena a soma dos números extraídos, e `ativo = True`, que controla se os números devem ser somados ou ignorados. Durante o processamento do texto, percorre cada palavra e verifica diferentes condições: se a palavra for `"On"` (independentemente da capitalização), ativa a soma (`ativo = True`); se for `"Off"`, desativa a soma (`ativo = False`); se a palavra contiver `"="`, imprime a soma atual. Caso contrário, tenta extrair apenas os dígitos numéricos da palavra para evitar erros com palavras que misturam letras e números. No final do processamento, exibe o valor total da soma.


## Resultados

1. [Somador (Python)](somador.py)
2. [Ficheiro de Teste](input.txt)

## Execução do Programa

O programa lê da entrada (sys.stdin) um input para testar o programa. Depois de escrever, pressionar Ctrl+D para finalizar a entrada.

> python3 somador.py


## Autor

João Augusto Macedo Moreira A93326

