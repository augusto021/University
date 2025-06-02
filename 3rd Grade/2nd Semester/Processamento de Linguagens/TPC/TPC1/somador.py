import sys

def somador_on_off(text):
    soma = 0
    ativo = True
    
    palavras = iter(text.split())
    
    for palavra in palavras:
        palavra_lower = palavra.lower()
        
        if palavra_lower == "off":
            ativo = False
        elif palavra_lower == "on":
            ativo = True
        elif palavra == "=":
            print(soma)
        else:
            try:
                num = int("".join(filter(str.isdigit, palavra)))
                if ativo:
                    soma += num
            except ValueError:
                pass

    print(soma)

if __name__ == "__main__":
    texto = sys.stdin.read()
    somador_on_off(texto)