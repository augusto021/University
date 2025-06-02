# TPC4 - Analisador Léxico(Data: 2025-03-18)

## Resumo

**Objetivo:**
O objetivo deste trabalho é construir um analisador léxico para uma linguagem de query similar a SPARQL, permitindo a identificação de diferentes tokens utilizados em consultas a bases de dados semânticas.

**Explicação das Funcionalidades:**
1. **Reconhecimento de Tokens:**
   - O analisador identifica elementos como `SELECT`, `WHERE`, `LIMIT`, variáveis (`?var`), prefixos e tipos.
   - Suporta identificação de literais (`"texto"`), comentários (`#`), e identificadores de linguagem (`@en`).
2. **Uso de Expressões Regulares:**
   - Cada tipo de token é identificado por uma expressão regular específica.
3. **Processamento de Arquivo:**
   - O analisador lê um arquivo de entrada (`input.txt`), tokeniza cada linha e imprime os tokens reconhecidos.
4. **Gestão de Erros:**
   - Caracteres inválidos são ignorados e uma mensagem de erro é exibida.

## Implementação

O analisador léxico foi implementado em Python utilizando a biblioteca `PLY` para definir tokens e regras de reconhecimento.

### **Estrutura e Lógica do Código**

1. **Definição de Tokens:**
   - Os tokens suportados incluem:
     - `SELECT`, `WHERE`, `LIMIT`
     - `VAR` (variáveis: `?nome`)
     - `PREFIX`, `PREFIX_A`, `PREFIX_TYPE`
     - `LITERAL` (valores entre aspas)
     - `LANGUAGE` (identificador de linguagem: `@en`)
     - `NUM` (números inteiros)
     - `COMMENT` (comentários iniciados por `#`)
     - `LBRACES`, `RBRACES` (chaves `{}`)
     - `DOT` (ponto `.`)
2. **Funções de Processamento:**
   - `t_<TOKEN>`: Cada função identifica um token específico através de expressões regulares.
   - `t_newline`: Contabiliza novas linhas para rastreamento correto de posições.
   - `t_error`: Exibe mensagens de erro para caracteres inválidos.
3. **Leitura de Arquivo:**
   - O analisador lê um arquivo de entrada e processa linha por linha.

## Resultados

Após a execução do analisador léxico, o programa imprime os tokens reconhecidos no terminal.

**Entrada:**
```
# DBPedia: obras de Chuck Berry
select ?nome ?desc where {
    ?s a dbo:MusicalArtist.
    ?s foaf:name "Chuck Berry"@en.
    ?w dbo:artist ?s.
    ?w foaf:name ?nome.
    ?w dbo:abstract ?desc
} LIMIT 1000
```

**Saída:**
```
LexToken(COMMENT,'# DBPedia: obras de Chuck Berry',1,0)
LexToken(SELECT,'select',2,0)
LexToken(VAR,'nome',2,7)
LexToken(VAR,'desc',2,13)
LexToken(WHERE,'where',2,19)
LexToken(LBRACES,'{',2,25)
LexToken(VAR,'s',3,4)
LexToken(PREFIX_A,'a',3,7)
LexToken(PREFIX,'dbo',3,9)
LexToken(PREFIX_TYPE,'MusicalArtist',3,13)
LexToken(DOT,'.',3,26)
LexToken(VAR,'s',4,4)
LexToken(PREFIX,'foaf',4,7)
LexToken(PREFIX_TYPE,'name',4,12)
LexToken(LITERAL,'"Chuck Berry"',4,17)
LexToken(LANGUAGE,'en',4,30)
...
LexToken(PREFIX_TYPE,'abstract',7,11)
LexToken(VAR,'desc',7,20)
LexToken(RBRACES,'}',8,0)
LexToken(LIMIT,'LIMIT',8,2)
LexToken(NUM,'1000',8,8)
```

## Execução do Programa

Para executar o programa é necessário a existência de um ficheiro `input.txt` que irá ser analisado. O resultado será exposto no terminal.

> python3 main.py

## Autor

João Augusto Macedo Moreira A93326


