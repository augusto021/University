import ply.lex as lex


tokens = [
    # Palavras-chave
    'PROGRAM', 'FUNCTION', 'VAR','BEGIN', 'END', 'WRITELN', 'WRITE','READLN', 'INTEGER', 'STRING','BOOLEAN', 'ARRAY', 'OF',
    'IF', 'THEN', 'ELSE', 'FOR', 'TO', 'DOWNTO', 'DO', 'WHILE', 'TRUE', 'FALSE',

    # Operadores e símbolos
    'PLUS', 'MINUS', 'TIMES', 'DIVIDE', 'ASSIGN', 'EQUAL', 'LESS', 'LESSEQUAL', 'GREATER', 'GREATEREQUAL', 
    'LPAREN', 'RPAREN', 'LBRACKET', 'RBRACKET', 'SEMICOLON', 'COLON','COMMA', 'DOT', 'MOD', 'DIV', 'AND', 'OR', 'NOT',

    # Identificadores e literais
    'ID', 'NUMBER', 'STRING_LITERAL'
]

t_LESSEQUAL     = r'<='
t_GREATEREQUAL  = r'>='
t_LESS          = r'<'
t_GREATER       = r'>'
t_PLUS          = r'\+'
t_MINUS         = r'-'
t_TIMES         = r'\*'
t_DIVIDE        = r'/'
t_ASSIGN        = r':='
t_EQUAL         = r'='
t_LPAREN        = r'\('
t_RPAREN        = r'\)'
t_LBRACKET      = r'\['
t_RBRACKET      = r'\]'
t_COMMA         = r','
t_COLON         = r':'
t_SEMICOLON     = r';'
t_DOT           = r'\.'


def t_PROGRAM(t):
    r'\bprogram\b'
    return t

def t_FUNCTION(t):
    r'\bfunction\b'
    return t

def t_VAR(t):
    r'\bvar\b'
    return t

def t_BEGIN(t):
    r'\bbegin\b'
    return t

def t_END(t):
    r'\bend\b'
    return t

def t_WRITELN(t):
    r'\bwriteln\b|\bWriteLn\b'
    return t

def t_WRITE(t):
    r'\b[wW]rite\b'
    return t

def t_READLN(t):
    r'\breadln\b|\bReadLn\b'
    return t

def t_INTEGER(t):
    r'\b[iI]nteger\b|\bINTERGER\b'
    return t

def t_STRING(t):
    r'\b[sS]tring\b|\bSTRING\b'
    return t

def t_BOOLEAN(t):
    r'\b[bB]oolean\b|\bBOOLEAN\b'
    return t

def t_ARRAY(t):
    r'\barray\b'
    return t

def t_OF(t):
    r'\bof\b'
    return t

def t_IF(t):
    r'\bif\b'
    return t

def t_THEN(t):
    r'\bthen\b'
    return t

def t_ELSE(t):
    r'\belse\b'
    return t

def t_FOR(t):
    r'\bfor\b'
    return t

def t_TO(t):
    r'\bto\b'
    return t

def t_DOWNTO(t):
    r'\bdownto\b'
    return t

def t_DO(t):
    r'\bdo\b'
    return t

def t_WHILE(t):
    r'\bwhile\b'
    return t

def t_TRUE(t):
    r'\btrue\b'
    return t

def t_FALSE(t):
    r'\bfalse\b'
    return t

def t_MOD(t):
    r'\bmod\b'
    return t

def t_DIV(t):
    r'\bdiv\b'
    return t

def t_AND(t):
    r'\band\b'
    return t

def t_OR(t):
    r'\bor\b'
    return t

def t_NOT(t):
    r'\bnot\b'
    return t


def t_ID(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    return t

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_STRING_LITERAL(t):
    r"'(.*?)'"
    t.value = t.value[1:-1]
    return t

def t_COMMENT(t):
    r'\{.*?\}'
    pass

t_ignore = ' \t'

def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)


def t_error(t):
    print(f"Illegal character '{t.value[0]}' at line {t.lineno}, column {t.lexpos}")
    t.lexer.skip(1)

# ---------------- Lexer ----------------
lexer = lex.lex()