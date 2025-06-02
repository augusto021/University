import ply.lex as lex
import re

tokens = (
    'SELECT',
    'WHERE',
    'COMMENT',
    'VAR',
    'LANGUAGE',
    'LBRACES',
    'RBRACES',
    'LIMIT',
    'NUM',
    'PREFIX',
    'PREFIX_A',
    'PREFIX_TYPE',
    'DOT',
    'LITERAL'
)

def t_SELECT(t):
    r'^select\b'
    return t

def t_WHERE(t):
    r'\bwhere\b'
    return t

def t_COMMENT(t):
    r'^\#.*$'
    return t

def t_VAR(t):
    r'\?\w+'
    var = re.match(r'\?(\w+)', t.value)
    t.value = var.group(1)
    return t

def t_PREFIX(t):
    r'[a-zA-Z]+(?=:)'
    return t

def t_PREFIX_A(t):
    r'\ba\b'
    return t

def t_PREFIX_TYPE(t):
    r'(?<=:)([a-zA-Z]+)'
    return t

def t_DOT(t):
    r'\.'
    return t

def t_LITERAL(t):
    r'".+"'
    return t


def t_LANGUAGE(t): 
    r'@.+\b'
    var = re.match(r'@(.+)\b', t.value)
    t.value = var.group(1)        
    return t

def t_LBRACES(t):
    r'\{'
    return t

def t_RBRACES(t):
    r'\}'
    return t

def t_LIMIT(t):
    r'\bLIMIT\b'
    return t

def t_NUM(t):
    r'\d+'
    return t


def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)


def t_error(t):
        print(f'Illegal character: {t.value[0]}')
        t.lexer.skip(1)

t_ignore = ' \t:'

lexer = lex.lex()

with open("input.txt",'r') as file:    
    for line in file:
        lexer.input(line)
        for tok in lexer:
            print(tok)