import ply.lex as lex
import re
import json

tokens = (
    'CODIGO',
    'NOME',
    'QUANTIDADE',
    'PRECO',
    'MOEDA',
)

t_CODIGO = r'[A-Z][0-9]+'
t_NOME = r'[a-zA-Z0-9]+'
t_QUANTIDADE = r'[0-9]+'
t_PRECO = r'[0-9]+\.[0-9]+'
t_MOEDA = r'[0-9]+[ec]'

t_ignore = ' \t'

def t_error(t):
    print(f"Caracter inválido: '{t.value[0]}'")
    t.lexer.skip(1)


lexer = lex.lex()

def carregar_stock():
    try:
        with open('stock.json', 'r') as file:
            return json.load(file)
    except FileNotFoundError:
        print("Arquivo de stock não encontrado.\nA criar novo arquivo de stock.")
        open('stock.json', "x")
        return


def salvar_stock(stock):
    with open('stock.json', 'w') as file:
        json.dump(stock, file, indent=2)


def adicionar_produto(codigo, nome, quantidade, preco, stock):
    if codigo in stock:
        stock[codigo]['quantidade'] += int(quantidade)
    else:
        stock[codigo] = {'nome': nome, 'quantidade': int(quantidade), 'preco': float(preco)}
    salvar_stock(stock)
    print(f"Produto '{nome}' adicionado ao stock.")


def listar_produtos(stock):
    print("Lista de produtos disponíveis:")
    print("cod | nome | quantidade | preço")
    print("---------------------------------")
    for codigo, produto in stock.items():
        print(f"{codigo} {produto['nome']} {produto['quantidade']} {produto['preco']}")
    print()

def selecionar_produto(codigo, saldo_atual, stock):
    if codigo in stock:
        produto = stock[codigo]
        if produto['quantidade'] > 0 and produto['preco'] <= saldo_atual:
            print(f"Pode retirar o produto: \"{produto['nome']}\"")
            produto['quantidade'] -= 1
            saldo_atual -= produto['preco']
            salvar_stock(stock)
            return saldo_atual
        elif produto['quantidade'] <= 0:
            print("Produto esgotado.")
        else:
            print("Saldo insuficiente para este produto.")
    else:
        print("Produto não encontrado.")
    return saldo_atual

def processar_moeda(moedas):
    total = 0
    for moeda in moedas:
        if moeda.endswith('e'):
            total += int(moeda[:-1]) * 100
        elif moeda.endswith('c'):
            total += int(moeda[:-1])
    return total / 100 


def converter_saldo(saldo):
    euros = int(saldo)
    centimos = round((saldo - euros) * 100) 
    return euros, centimos

def main():
    stock = carregar_stock()
    saldo_atual = 0
    
    print("2024-03-08, Stock carregado, Estado atualizado.")
    print("Bom dia. Estou disponível para atender o seu pedido.")

    while True:
        comando = input(">> ").split()
        if not comando:
            continue
        if comando[0] == "LISTAR":
            listar_produtos(stock)
        elif comando[0] == "MOEDA":
            saldo_atual += processar_moeda(comando[1:])
            euros, centimos = converter_saldo(saldo_atual)
            print(f"Saldo = {euros}e{centimos:02}c")
        elif comando[0] == "SELECIONAR":
            if len(comando) != 2:
                print("Comando inválido. Uso: SELECIONAR <código>")
                continue
            saldo_atual = selecionar_produto(comando[1], saldo_atual, stock)
            euros, centimos = converter_saldo(saldo_atual)
            print(f"Saldo = {euros}e{centimos:02}c")
        elif comando[0] == "SAIR":
            troco = saldo_atual
            saldo_atual = 0
            if troco > 0:
                print("Pode retirar o troco:", end=" ")
                troco_moedas = []
                while troco >= 100:
                    troco_moedas.append("1x 1e")
                    troco -= 100
                while troco >= 50:
                    troco_moedas.append("1x 50c")
                    troco -= 50
                while troco >= 20:
                    troco_moedas.append("1x 20c")
                    troco -= 20
                while troco >= 10:
                    troco_moedas.append("1x 10c")
                    troco -= 10
                while troco >= 5:
                    troco_moedas.append("1x 5c")
                    troco -= 5
                while troco >= 2:
                    troco_moedas.append("1x 2c")
                    troco -= 2
                while troco >= 1:
                    troco_moedas.append("1x 1c")
                    troco -= 1
                print(", ".join(troco_moedas))
            else:
                print("Não há troco a ser devolvido.")
            print("Até à próxima!")
            break
        else:
            print("Comando inválido.")

if __name__ == "__main__":
    main()


