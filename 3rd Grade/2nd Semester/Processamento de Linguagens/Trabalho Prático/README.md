# Construção de um Compilador para Pascal Standard
Projeto de Processamento de Linguagens 2025

## Autores:
    
* António Fonseca a93167
* Beatriz Almeida a93210
* João Moreira a93326


## Objetivo
O objetivo deste projeto é que os alunos desenvolvam um compilador para a linguagem Pascal standard.
O compilador deverá ser capaz de analisar, interpretar e traduzir código Pascal para um formato intermediário e deste para código máquina ou diretamente para código máquina, neste caso da [VM disponibilizada aos alunos](https://ewvm.epl.di.uminho.pt).

## Etapas do Projeto

### Análise Léxica

* Implementar um analisador léxico (lexer) para converter código Pascal numa lista de tokens;
* Usar a ferramenta ply.lex, na implementação do analisador léxico;
* Identificar palavras-chave, identificadores, números, operadores e símbolos especiais.

### Análise Sintática

* Construir um analisador sintático (parser) para validar a estrutura gramatical do código;
* Usar a ferramenta ply.yacc, na implementação do analisador sintático.

### Análise Semântica

* Verificar tipos de dados, declaração de variáveis e coerência do código.

### Geração de Código

Pode optar por uma das seguintes alternativas:

* Converter o código Pascal em código da [máquina virtual](https://ewvm.epl.di.uminho.pt), tradução dirigida pela sintaxe;
* Ou, gerar uma representação intermédia do programa reconhecido para depois gerar o código da VM
numa travessia sobre esta representação.

### Testes

* Criar uma série de testes para verificar a correção do compilador;
* Testar programas Pascal de exemplo e validar a saída.
