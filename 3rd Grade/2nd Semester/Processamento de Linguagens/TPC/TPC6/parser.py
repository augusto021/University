import ply.yacc as yacc
from lexer import tokens, lexer
import sys

# Precedência dos operadores
precedence = (
    ('left', 'PLUS', 'MINUS'),
    ('left', 'TIMES', 'DIVIDE'),
)

def p_program(p):
    """program : exp"""
    p[0] = p[1]

def p_exp_number(p):
    """exp : NUMBER"""
    p[0] = p[1]

def p_exp_binop(p):
    """exp : exp PLUS exp
           | exp MINUS exp
           | exp TIMES exp
           | exp DIVIDE exp"""
    if p[2] == '+':
        p[0] = p[1] + p[3]
    elif p[2] == '-':
        p[0] = p[1] - p[3]
    elif p[2] == '*':
        p[0] = p[1] * p[3]
    elif p[2] == '/':
        if p[3] == 0:
            raise ValueError("Divisão por zero")
        p[0] = p[1] / p[3]

def p_exp_paren(p):
    """exp : LPAREN exp RPAREN"""
    p[0] = p[2]

def p_error(p):
    if p:
        print(f"Erro de sintaxe em '{p.value}'")
    else:
        print("Erro de sintaxe no final da entrada")

parser = yacc.yacc()

def calcular_expressao(expr):
    try:
        return parser.parse(expr)
    except ValueError as e:
        return str(e)
    except Exception as e:
        return f"Erro: {str(e)}"

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python parser.py arquivo_entrada.txt")
        sys.exit(1)
    
    arquivo_entrada = sys.argv[1]
    
    try:
        with open(arquivo_entrada, 'r') as f:
            for linha in f:
                linha = linha.strip()
                if linha:  # Ignora linhas vazias
                    resultado = calcular_expressao(linha)
                    print(f"{linha} = {resultado}")
    except FileNotFoundError:
        print(f"Arquivo não encontrado: {arquivo_entrada}")
    except Exception as e:
        print(f"Erro ao processar arquivo: {str(e)}")