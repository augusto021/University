# TPC5 - Simulação de uma Máquina de Vending (Data: 2025-03-13)

## Resumo

**Objetivo:**
O objetivo deste trabalho é construir um programa em Python que simule o funcionamento de uma máquina de vending, permitindo interações com o utilizador para listar produtos, inserir moedas, selecionar produtos e receber troco.

**Explicação das Funcionalidades:**
1. **Carregamento e persistência do stock:**
   - O stock de produtos é armazenado num ficheiro JSON (`stock.json`).
   - O programa carrega o stock ao iniciar e salva as alterações ao encerrar.
2. **Interação com o utilizador:**
   - O utilizador pode listar produtos, inserir dinheiro, selecionar um produto e sair da máquina.
3. **Gestão de moedas e saldo:**
   - O saldo é atualizado à medida que o usuário insere moedas.
   - Se o saldo for suficiente, o produto é dispensado e o saldo atualizado.
   - Se o saldo for insuficiente, o programa informa o utilizador.
   - Ao sair, o troco é calculado e devolvido.
4. **Validação de entradas:**
   - Caso o código do produto não exista ou o stock esteja esgotado, o programa avisa o utilizador.
   - O saldo é convertido corretamente para euros e cêntimos.

## Implementação

O programa foi desenvolvido em Python e utiliza a biblioteca `PLY` para análise lexical e `JSON` para manipulação do stock.

### **Estrutura e Lógica do Código**

1. **Definição de Tokens para Reconhecimento de Entradas:**
   - Utiliza-se `PLY` para definir tokens que reconhecem comandos, códigos de produtos, quantidades, preços e moedas.
2. **Gestão do Stock:**
   - Funções para carregar e salvar o stock no ficheiro `stock.json`.
   - Função para adicionar produtos ao stock, permitindo atualização de quantidade e inclusão de novos produtos.
3. **Comandos da Máquina:**
   - `LISTAR`: Exibe os produtos disponíveis com código, nome, quantidade e preço.
   - `MOEDA X`: Processa as moedas inseridas e atualiza o saldo.
   - `SELECIONAR <código>`: Verifica disponibilidade do produto e saldo suficiente antes de realizar a compra.
   - `SAIR`: Calcula e devolve o troco, encerrando a interação.
4. **Cálculo de Troco:**
   - O troco é devolvido com as moedas de maior valor primeiro (1e, 50c, 20c, 10c, etc.).

## Resultados

Após a execução do programa, a máquina de vending simula corretamente um ambiente de compra:
1. **Carrega o stock inicial do ficheiro JSON.**
2. **Aceita moedas e atualiza o saldo do utilizador.**
3. **Dispensa produtos disponíveis quando o saldo é suficiente.**
4. **Informa o usuário sobre saldo insuficiente ou produto inexistente.**
5. **Devolve corretamente o troco ao encerrar a sessão.**


## Execução do Programa

Para executar o programa:
1. A existência de um ficheiro `stock.json` para carregar o estado do stock.
2. Executar o código Python e interagir com a máquina inserindo comandos no terminal.

> python3 main.py

**Comandos da máquina**
> LISTAR

> MOEDAS <valor>

> SELECIONAR <codigo>

> SAIR 

## Autor

João Augusto Macedo Moreira A93326

