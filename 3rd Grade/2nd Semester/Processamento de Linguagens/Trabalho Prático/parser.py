import ply.yacc as yacc
from lexer import tokens
import logging
import os

precedence = (
    ('left', 'OR'),
    ('left', 'AND'),
    ('right', 'NOT'),
    ('nonassoc', 'IFX'),
    ('nonassoc', 'ELSE'),
    )

# ----------------------------------------- Program -----------------------------------------

def p_Program(p):
    '''Program : PROGRAM ID SEMICOLON Function VarsDeclaration CodeBlock DOT'''
    missing_funcs = [func for func in p.parser.called_funcs if func in registered_funcs]
    funcs_code = "\n".join(registered_funcs[func] for func in missing_funcs if func in registered_funcs)
    p[0] = (
        f"{p[5]}"
        f"start\n"
        f"{p[6]}"
        f"stop\n\n"
        f"{funcs_code}\n"
    )


# ----------------------------------------- Function -----------------------------------------

def p_Function_empty(p):
    '''Function : '''
    p[0] = ""


# ----------------------------------- Variable Declaration -----------------------------------

def p_VarsDeclaration(p):
    '''VarsDeclaration : VAR Declarations
                       | '''
    if len(p) == 3:
        p[0] = p[2]
    else:
        p[0] = ""


def p_Declarations(p):
    '''Declarations : Declaration SubDeclarations'''
    p[0] = p[1] + p[2]


def p_SubDeclarations(p):
    '''SubDeclarations : Declaration
                       | '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = ""


def p_Declaration_simple(p):
    '''Declaration : ID COLON Type SEMICOLON'''
    add_var(p[1], 1, p.parser.current_type, p)
    if p.parser.current_type == 0:
        p[0] = f"pushi 0\n"
    else:
        p[0] = f'pushs ""\n'


def p_Declaration(p):
    '''Declaration : VariablesList COLON Type SEMICOLON'''
    code = ""
    for var in p[1]:
        add_var(var, 1, p.parser.current_type, p)
        if p.parser.current_type == 0:
            code += f"pushi 0\n"
        else:
            code += f'pushs ""\n'
    p[0] = code


def p_Declaration_array(p):
    '''Declaration : ID COLON ARRAY LBRACKET NUMBER DOT DOT NUMBER RBRACKET OF INTEGER SEMICOLON'''
    size = int(p[8]) - int(p[5]) + 1
    lower_bound = int(p[5])
    add_var(p[1], size, 0, p, lower_bound)
    p[0] = f"pushn {size}\n"


def p_VariablesList(p):
    '''VariablesList : ID
                     | VariablesList COMMA ID'''
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[0] = p[1] + [p[3]]


def p_Type(p):
    '''Type : INTEGER
            | BOOLEAN
            | STRING'''
    p.parser.current_type = 0 if p[1].lower() in ('integer', 'boolean') else 1


# ---------------------------------------- Code Block ----------------------------------------

def p_CodeBlock(p):
    '''CodeBlock : BEGIN Instructions END'''
    p[0] = p[2]


# --------------------------------------- Instructions ---------------------------------------

def p_Instructions(p):
    '''Instructions : Instructions Instruction SEMICOLON
                    | Instruction SEMICOLON
                    | Instruction'''
    if len(p) == 4:
        p[0] = p[1] + p[2]
    else:
        p[0] = p[1]


def p_Instruction_writeln(p):
    '''Instruction : WRITELN LPAREN Write_Exp STRING_LITERAL Write_Exp RPAREN'''
    p[0] = f'{p[3]}pushs "{p[4]}"\nwrites\n{p[5]}writeln\n'


def p_Instruction_write(p):
    '''Instruction : WRITE LPAREN Write_Exp STRING_LITERAL Write_Exp RPAREN'''
    p[0] = f'{p[3]}pushs "{p[4]}"\nwrites\n{p[5]}'


def p_Write_Exp_empty(p):
    '''Write_Exp : '''
    p[0] = ""


def p_Write_Exp_string(p):
    '''Write_Exp : COMMA String Write_Exp'''
    p[0] = f'pushs "{p[2]}"\nwrites\n{p[3]}'


def p_Write_id(p):
    '''Write_Exp : COMMA ID Write_Exp'''
    v = get_index(p[2], p)
    (_, _, offset, _) = v
    p[0] = f"pushg {offset}\nwritei\n{p[3]}"


def p_Write_var(p):
    '''Write_Exp : ID COMMA'''
    v = get_index(p[1], p)
    (_, _, offset, _) = v
    p[0] = f"pushg {offset}\nwritei\n"


def p_Instruction_readln(p):
    '''Instruction : READLN LPAREN ID RPAREN'''
    v = get_index(p[3], p)
    (_, type, offset, _) = v
    if type == 0:
        p[0] = f"read\natoi\nstoreg {offset}\nwriteln\n"
    else:
        p[0] = f"read\nstoreg {offset}\nwriteln\n"


def p_Instruction_read_array(p):
    '''Instruction : READLN LPAREN ID LBRACKET Exp RBRACKET RPAREN'''
    v = get_index(p[3], p)
    (_, _, offset, lower_bound) = v
    if lower_bound != 0:
        p[0] = f"pushgp\npushi {offset}\npadd\n{p[5]}pushi {lower_bound}\nsub\nread\natoi\nstoren\nwriteln\n"
    else:
        p[0] = f"pushgp\npushi {offset}\npadd\n{p[5]}read\natoi\nstoren\nwriteln\n"



def p_Instruction_assign(p):
    '''Instruction : ID ASSIGN Exp'''
    v = get_index(p[1], p)
    (_, _, offset, _) = v
    p[0] = f"{p[3]}storeg {offset}\n"


def p_Instruction_code_blocl(p):
    '''Instruction : CodeBlock'''
    p[0] = p[1]


# --- Condicionais e Ciclos ---

def p_Condition(p):
    '''Instruction : IF Log THEN Instruction ELSE Instruction'''
    current_if = p.parser.ifs
    p[0] = (f"{p[2]}"
            f"jz else{current_if}\n"
            f"{p[4]}"
            f"jump endif{current_if}\n"
            f"else{current_if}:\n"
            f"{p[6]}\n"
            f"endif{current_if}:\n"
        )
    p.parser.ifs += 1


def p_Condition_simple(p):
    '''Instruction : IF Log THEN Instruction %prec IFX'''
    current_if = p.parser.ifs
    p[0] = (f"{p[2]}"
            f"jz endif{current_if}\n"
            f"{p[4]}"
            f"endif{current_if}:\n"
        )
    p.parser.ifs += 1


def p_Cycle_While(p):
    '''Instruction : WHILE Log DO Instruction'''
    p[0] = (
        f"while{p.parser.cycles}:\n"
        f"{p[2]}"
        f"jz endwhile{p.parser.cycles}\n"
        f"{p[4]}"
        f"jump while{p.parser.cycles}\n"
        f"endwhile{p.parser.cycles}:\n"
    )
    p.parser.cycles += 1


def p_Cycle_For_Do(p):
    '''Instruction : FOR ID ASSIGN Exp TO Exp DO Instruction'''
    v = get_index(p[2], p)
    (_, _, offset, _) = v

    p[0] = (
        f"{p[4]}storeg {offset}\n"
        f"while{p.parser.cycles}:\n"
        f"pushg {offset}\n"
        f"{p[6]}infeq\n"
        f"jz endwhile{p.parser.cycles}\n"
        f"{p[8]}"
        f"pushg {offset}\npushi 1\nadd\nstoreg {offset}\n"
        f"jump while{p.parser.cycles}\n"
        f"endwhile{p.parser.cycles}:\n"
    )
    p.parser.cycles += 1


def p_Cycle_For_Downto(p):
    '''Instruction : FOR ID ASSIGN Exp DOWNTO Exp DO Instruction
                   | FOR ID ASSIGN ID LPAREN ID RPAREN DOWNTO NUMBER DO Instruction'''
    v = get_index(p[2], p)
    (_, _, offset, _) = v

    if len(p) == 10:
        p[0] = (
            f"{p[4]}storeg {offset}\n"
            f"while{p.parser.cycles}:\n"
            f"pushg {offset}\n"
            f"{p[6]}supeq\n"
            f"jz endwhile{p.parser.cycles}\n"
            f"{p[8]}"
            f"pushg {offset}\n"
            f"storeg {offset}\n"
            f"jump while{p.parser.cycles}\n"
            f"endwhile{p.parser.cycles}:\n"
        )
    else:
        p.parser.called_funcs.add(p[4])
        if p[4] in p.parser.funcs:
            res = get_index(p[6], p)
            (_, _, offset1, _) = res
            p[0] = (
                f"pushg {offset1}\n"
                f"pusha {p[4]}\n"
                f"call\n"
                f"pushi 1\n"
                f"sub\n"
                f"storeg {offset}\n"
                f"while{p.parser.cycles}:\n"
                f"pushg {offset}\n"
                f"pushi {p[9]}\n"
                f"pushi 1\n"
                f"sub\n"
                f"supeq\n"
                f"jz endwhile{p.parser.cycles}\n"
                f"{p[11]}"
                f"pushg {offset}\n"
                f"pushi 1\n"
                f"sub\n"
                f"storeg {offset}\n"
                f"jump while{p.parser.cycles}\n"
                f"endwhile{p.parser.cycles}:\n"
            )
    p.parser.cycles += 1


# ---------------------------------------- Expressions ----------------------------------------

def p_Log_and(p):
    '''Log : Log AND Rel'''
    p[0] = f"{p[1]}{p[3]}and\n"


def p_Log_or(p):
    '''Log : Log OR Rel'''
    p[0] = f"{p[1]}{p[3]}or\n"


def p_Log_not(p):
    '''Log : NOT Log'''
    p[0] = f"{p[2]}not\n"


def p_Log_rel(p):
    '''Log : Rel
           | LPAREN Log RPAREN'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = p[2]  


def p_Rel_less(p):
    '''Rel : Rel LESS Exp'''
    p[0] = f"{p[1]}{p[3]}inf\n"


def p_Rel_lessequal(p):
    '''Rel : Rel LESSEQUAL Exp'''
    p[0] = f"{p[1]}{p[3]}infeq\n"


def p_Rel_greater(p):
    '''Rel : Rel GREATER Exp'''
    p[0] = f"{p[1]}{p[3]}sup\n"


def p_Rel_greaterequal(p):
    '''Rel : Rel GREATEREQUAL Exp'''
    p[0] = f"{p[1]}{p[3]}supeq\n"


def p_Rel_equals(p):
    '''Rel : Rel EQUAL Exp'''
    p[0] = f"{p[1]}{p[3]}equal\n"


def p_Rel_exp(p):
    '''Rel : Exp
           | LPAREN Rel RPAREN'''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = p[2]


def p_Exp_add(p):
    '''Exp : Exp PLUS Term'''
    p[0] = f"{p[1]}{p[3]}add\n"


def p_Exp_sub(p):
    '''Exp : Exp MINUS Term'''
    p[0] = f"{p[1]}{p[3]}sub\n"


def p_Exp_term(p):
    '''Exp : Term'''
    p[0] = p[1]


def p_Term_mult(p):
    '''Term : Term TIMES Factor'''
    p[0] = f"{p[1]}{p[3]}mul\n"


def p_Term_div(p):
    '''Term : Term DIVIDE Factor'''
    f"{p[1]}{p[3]}div\n"


def p_Term_mod(p):
    '''Term : Term MOD Factor'''
    p[0] = f"{p[1]}{p[3]}mod\n"


def p_Term_divide(p):
    '''Term : Term DIV Factor''' 
    p[0] = f"{p[1]}{p[3]}div\n"


def p_Term_factor(p):
    '''Term : Factor'''
    p[0] = p[1]


def p_Factor_true(p):
    '''Factor : TRUE'''
    p[0] = "pushi 1\n"


def p_Factor_false(p):
    '''Factor : FALSE'''
    p[0] = "pushi 0\n"


def p_Factor_num(p):
    '''Factor : NUMBER'''
    p[0] = f"pushi {p[1]}\n"


def p_Factor_id(p):
    '''Factor : ID'''
    res = get_index(p[1], p)
    (_, _, offset, _) = res
    p[0] = f"pushg {offset}\n"


def p_Factor_paren(p):
    '''Factor : LPAREN Exp RPAREN'''
    p[0] = p[2]


def p_Factor_func(p):
    '''Factor : ID LPAREN ID RPAREN'''
    p.parser.called_funcs.add(p[1])
    if p[1] in p.parser.funcs:
        res = get_index(p[3], p)
        (_, _, offset, _) = res
        p[0] = f"pushg {offset}\npusha {p[1]}\ncall\n\n"
    else:
        raise Exception(f"Function {p[1]} not declared")


def p_Factor_string(p):
    '''Factor : STRING_LITERAL'''
    p[0] = f'pushs "{p[1]}"\npushi 0\ncharat\n'


def p_Factor_array(p):
    '''Factor : ID LBRACKET Exp RBRACKET'''
    res = get_index(p[1], p)
    (_, type, offset, lower_bound) = res
    if type == 0:
        if lower_bound != 0:
            p[0] = f"pushgp\npushi {offset}\npadd\n{p[3]}pushi {lower_bound}\nsub\nloadn\n"
        else:
            p[0] = f"pushgp\npushi {offset}\npadd\n{p[3]}loadn\n"
    else:
        p[0] = f"pushg {offset}\n{p[3]}charat\n"


# ------------------------------------------ String ------------------------------------------

def p_String(p):
    '''String : STRING_LITERAL'''
    p[0] = p[1]


# ------------------------------------------ Others ------------------------------------------

def p_error(p):
    if p:
        print(f"Erro de sintaxe na linha {p.lineno}, token '{p.value}' (tipo: {p.type})")
        # Mostra os últimos 5 tokens processados
        print("Contexto:", parser.symstack[-5:])
    else:
        print("Erro de sintaxe no final do arquivo")


def add_var(id, size, type, p, lower_bound = 0):
    if id not in p.parser.var.keys():
        p.parser.var[id] = (size, type, p.parser.offset, lower_bound)
        #print(f"Adding variable {id} with size {size} at offset {p.parser.offset}")
        p.parser.offset += size
    else:
        raise Exception
    

def get_index(id, p):
    if id in p.parser.var.keys():
        return p.parser.var[id]


# ------------------------------------------- Run -------------------------------------------

r = 1
while r:
    inFileFolder = "input/"
    inFile = input("Code File >> ")
    inFilePath = os.path.join(inFileFolder, inFile)

    try:
        fileIn = open(inFilePath, "r")
        r = 0
    except (FileNotFoundError, NotADirectoryError):
        print("Inexistent file!\n\nAvailable files:")
        files = os.listdir(inFileFolder)
        files.sort()
        for file in files:
            print(file)


r = 1
while r:
    outFileFolder = "output/"
    outFilePath = os.path.join(outFileFolder, inFile) + ".vm"

    if outFilePath != inFilePath:
        try:
            fileOut = open(outFilePath, "w")
            r = 0
        except (FileNotFoundError, NotADirectoryError):
            print("Wrong File Path\n")
    else:
        print("Wrong File Path\n")

parser = yacc.yacc(debug=True)

parser.var = dict()
parser.funcs = set()
parser.called_funcs = set()
parser.offset = 0
parser.ifs = 0
parser.cycles = 0
parser.current_type = None


parser.funcs.add("length")
registered_funcs = {
    'length': "length:\npushfp\nload -1\nstrlen\nreturn"
}


data = fileIn.read()

try:
    result = parser.parse(data)
    fileOut.write(result)
except (TypeError, Exception):
    print("\nCompilation error, aborting!")
    os.remove(outFilePath)

fileIn.close()
fileOut.close()