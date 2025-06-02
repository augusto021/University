# TPC6 - Parser LL(1) para Expressões Aritméticas (Data: 2025-04-16)

## Resumo

**Objetivo:**
Desenvolver um parser LL(1) recursivo descendente em Python capaz de analisar e calcular expressões aritméticas com operadores básicos, parênteses e precedência correta de operações.

**Explicação das Funcionalidades:**
1. Análise léxica: Identificação de números, operadores e parênteses;
2. Análise sintática: Verificação da estrutura gramatical das expressões;
3. Cálculo matemático: Avaliação do valor das expressões válidas.


## Implementação 

O programa foi desenvolvido em Python utilizando a biblioteca PLY (Python Lex-Yacc) para implementar:

* Um analisador léxico (lexer)
* Um analisador sintático (parser) LL(1) recursivo descendente


### **Estrutura e Lógica do Código**

1. Definição de Tokens:

```python
tokens = ('NUMBER', 'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'LPAREN', 'RPAREN')
```
Reconhecimento de números inteiros e operadores básicos

2. Gramática Implementada:

```python
program  → empty | program exp
empty    → ε
exp      → exp PLUS exp
         | exp MINUS exp
         | exp TIMES exp
         | exp DIVIDE exp
         | LPAREN exp RPAREN
         | NUMBER
```

3. Precedência de Operadores:

```python
precedence = (
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'DIVIDE'),
)
```

4. Funções Principais:

* p_exp_binop: Processa operações binárias
* p_exp_number: Processa números
* p_exp_paren: Processa expressões entre parênteses
* p_error: Tratamento de erros sintáticos



## Resultados

O parser é capaz de:

* Analisar corretamente expressões aritméticas complexas
* Respeitar a precedência de operadores (multiplicação/divisão antes de adição/subtração)
* Processar expressões com múltiplos níveis de parênteses
* Detetar e reportar erros como:
   * Parênteses desbalanceados
   * Operadores mal posicionados
   * Caracteres inválidos
   * Divisões por zero

**Entrada:**

```
2+3
67-(2+3*4)
(9-2)*(13-4)
```

**Saída:**

```
2+3 = 5
67-(2+3*4) = 53
(9-2)*(13-4) = 63
```

## Execução do Programa

Para executar o programa:
1. A existência de um ficheiro `arquivo_entrada.txt` com as operações a testar.
2. Executar o código Python e obter a resolucação dos problemas matemáticos.

> python3 parser.py arquivo_entrada.txt


## Autor

João Augusto Macedo Moreira A93326

