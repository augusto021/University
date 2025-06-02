# TPC3 - Conversor de Markdown para HTML (Data: 2025-03-11)

## Resumo

**Objetivo:** O objetivo deste trabalho é desenvolver um conversor de Markdown para HTML em Python, capaz de processar elementos básicos da sintaxe Markdown e transformá-los nos correspondentes elementos HTML.

**Explicação das Funcionalidades:**
1. Leitura de um arquivo Markdown (`.md`).
2. Identificação e conversão de elementos Markdown:
   - Cabeçalhos (`#`, `##`, `###` → `<h1>`, `<h2>`, `<h3>`).
   - Texto em negrito (`**texto**` → `<b>texto</b>`).
   - Texto em itálico (`*texto*` → `<i>texto</i>`).
   - Listas numeradas (`1. item` → `<ol><li>item</li></ol>`).
   - Links (`[texto](url)` → `<a href="url">texto</a>`).
   - Imagens (`![alt](url)` → `<img src="url" alt="alt"/>`).
3. Escrita da saída formatada num arquivo HTML.

## Implementação

O programa foi desenvolvido em Python, empregando expressões regulares para identificar e substituir os padrões Markdown pelos equivalentes HTML.

### **Estrutura e Lógica do Código**

1. **Leitura do Arquivo Markdown:**
   - O programa abre e lê todo o conteúdo do arquivo `markdown_file.md`.

2. **Definição de Padrões de Conversão:**
   - Uma lista de tuplos contém os padrões Markdown e seus respectivos formatos HTML.

3. **Aplicação das Substituições:**
   - Utiliza-se `re.sub()` para substituir os padrões encontrados no texto.

4. **Tratamento de Listas Numeradas:**
   - O código adiciona manualmente as tags `<ol>` e `</ol>` ao redor das listas numeradas.

5. **Escrita do Arquivo HTML:**
   - O texto convertido é salvo no arquivo `markdown_to_html.html`.

## Resultados

Após a execução do programa, um arquivo HTML é gerado contendo a conversão completa do Markdown:
1. [MarkDown to HTML](markdown_to_html.html)

## Execução do Programa

Para executar o programa, basta garantir que o arquivo `markdown_file.md` está presente e correr o código. O arquivo HTML resultante será salvo automaticamente.

> python3 main.py

## Autor

João Augusto Macedo Moreira A93326

