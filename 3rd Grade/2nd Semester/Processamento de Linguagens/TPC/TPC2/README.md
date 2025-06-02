# TPC2 - Análise de um dataset de obras musicais (Data: 2025-03-11)

## Resumo

**Objetivo:** O objetivo deste trabalho é analisar um dataset de obras musicais, extraindo e apresentando informações relevantes, tais como a lista de compositores, a distribuição das obras por período e a associação de obras a seus respectivos períodos.

**Explicação das Funcionalidades:**

1. Leitura e processamento do dataset obras.csv.
2. Extração dos dados relevantes usando expressões regulares.
3. Geração de uma lista ordenada alfabeticamente dos compositores.
4. Cálculo da distribuição das obras por período.
5. Criação de um dicionário associando cada período a uma lista alfabética das obras correspondentes.


## Implementação

O programa foi desenvolvido em Python e utiliza expressões regulares para extrair informações estruturadas do dataset.

### **Estrutura e Lógica do Código**  

1. Leitura do Arquivo: O dataset obras.csv é lido linha por linha.

2. Processamento das Linhas: Caso uma linha não corresponda ao padrão esperado, ela é concatenada com a próxima linha até que se torne válida.

3. Extração dos Dados: Utiliza-se uma expressão regular para capturar os seguintes campos:
* Título da obra
* Período musical
* Compositor

4. Ordenação e Contagem:
* A lista de compositores é extraída, removendo duplicados e ordenando alfabeticamente.
* Um dicionário contabiliza quantas obras existem por período.
* Outro dicionário associa cada período a uma lista ordenada de títulos de obras.

5. Impressão dos Resultados: Os resultados são exibidos no terminal de forma estruturada.


## Resultados

1. Lista de Compositores Ordenada
2. Distribuição das Obras por Período
3. Dicionário de Obras por Período


## Execução do Programa

Para executar o programa, basta garantir que o arquivo obras.csv está na diretoria e correr o código. O programa irá processar os dados e exibir os resultados no terminal.

> python3 main.py


## Autor

João Augusto Macedo Moreira A93326

