import sympy as sp
import numpy as np

def integracao_trapezios():
    #ENTRADA DE DADOS
    #Partimos de um problema real para a construcao de um modelo matematico
    print("\n=== INTEGRAÇÃO NUMÉRICA: REGRA DOS TRAPÉZIOS ===")
    print("\nExemplos de entradas:\n - Potência: x**2 (para x²)\n - Raiz Quadrada: sqrt(x)\n - Exponencial: exp(x)\n - Logaritmo: log(x, base)\n - Seno/Cosseno: sin(x), cos(x)\n - Pi: pi")

    expr_str = input("\nDigite a função f(x) (ex: x**2, sin(x), exp(x)): ")
    a = float(input("Início do intervalo [a]: "))
    b = float(input("Fim do intervalo [b]: "))
    n = int(input("Nº de trapézios (n): "))
    casas = int(input("Nº de casas decimais: "))
    
    #Usando a biblioteca sympy, vamos transformar o que foi digitado (string) em um objeto matematico simbolico 
    x_sym = sp.Symbol('x')
    f = sp.sympify(expr_str)

    #Convertemos a expressao simbolica em uma funcao numerica que o Python entende
    f_num = sp.lambdify(x_sym, f, modules=['numpy'])
    
    h = (b - a) / n         #Calculo da amplitude (h)
    X = np.linspace(a, b, n + 1)     #Geramos os pontos x no eixo horizontal, de 'a' ate 'b', divididos em 'n' partes.
    Y = [float(f_num(val)) for val in X]    # Y com precisão total


    #TABELA DE VALORES
    print("\n\n--- TABELA DE VALORES ---")
    print(f"{'x':<15} | {'f(x)':<15}")
    print("-" * 33)
    for i in range(n + 1):
        # Arredondamento apenas na exibicao
        print(f"{X[i]:<15.{casas}f} | {Y[i]:<15.{casas}f}")
    input("\n[Pausa] Pressione ENTER para calcular as ÁREAS...")


    #CALCULO DA SOMA E PARCELAS
    #a primeira e a ultima imagem sao divididas por 2
    p_primeira = Y[0] / 2
    p_ultima = Y[-1] / 2
    p_meio = Y[1:-1]
    
    soma_meio = sum(p_meio)
    soma_colchete = p_primeira + soma_meio + p_ultima   #Somamos todas as parcelas dentro dos colchetes da formula de Newton
    integral_aprox = h * soma_colchete  #e o produto da soma das alturas pela largura h

    print("\n\n--- CÁLCULO DAS ÁREAS ---\n")
    print("Fórmula utilizada: h * [f(x0)/2 + f(x1) + ... + f(xn-1) + f(xn)/2]")
    print(f"Parcela inicial (f(a)/2) = {p_primeira:.{casas}f}")
    if n > 1:
        print(f"Soma das parcelas intermediárias = {soma_meio:.{casas}f}")
    print(f"Parcela final (f(b)/2) = {p_ultima:.{casas}f}")
    print(f"Soma do colchete = {soma_colchete:.{casas}f}")
    print(f"Soma Final (Integral aproximada) = {integral_aprox:.{casas}f}")
    input("\n[Pausa] Pressione ENTER para avaliar o ERRO DE ARREDONDAMENTO...")


    #ERRO DE ARREDONDAMENTO (Ea)
    #e o erro acumulado pelas operacoes com casas decimais limitadas
    #definido como metade da ultima casa decimal vezes a amplitude
    erro_max_casa = 0.5 * (10 ** -casas)
    Ea = n * erro_max_casa * h

    print("\n\n--- ERRO DE ARREDONDAMENTO (Ea) ---\n")
    print(f"Produto: (nº trapézios) * (erro das casas) * (passo h)")
    print(f"Produto: {n} * {erro_max_casa} * {h:.{casas}f}")
    print(f"Módulo do Ea menor ou igual a: {Ea:.{casas+2}f}")
    input("\n[Pausa] Pressione ENTER para avaliar o ERRO DE TRUNCAMENTO...")


    #ERRO DE TRUNCAMENTO (Et)
    #utiliza a segunda derivada (f'') para medir a curvatura da funcao
    f_sec = sp.diff(f, x_sym, 2)
    print("\n\n--- ERRO DE TRUNCAMENTO (Et) ---\n")
    print(f"Derivada segunda f''(x) = {f_sec}")
    
    f_sec_lamb = sp.lambdify(x_sym, f_sec, modules=['numpy'])
    try:
        ##buscamos o valor maximo da segunda derivada no intervalo para ter um limite superior do erro
        x_dense = np.linspace(a, b, 1000)
        y_sec_vals = np.abs(f_sec_lamb(x_dense))
        max_f_sec = np.max(y_sec_vals) if not np.isscalar(y_sec_vals) else y_sec_vals

        Et = ((b - a)**3 / (12 * n**2)) * max_f_sec
        print(f"Máximo de |f''(x)| no intervalo = {max_f_sec:.{casas}f}")
        print(f"Módulo do Et menor ou igual a: {Et:.{casas+5}f}")
    except:
        Et = 0.0
    input("\n[Pausa] Pressione ENTER para ver o RESUMO FINAL...")


    #RESPOSTA FINAL
    Erro_Total = Ea + Et    #e a soma dos erros de arredondamento e truncamento
    limite_inf = integral_aprox - Erro_Total
    limite_sup = integral_aprox + Erro_Total

    print("\n\n--- RESUMO DOS ERROS ---\n")
    print(f"Erro Total (Ea + Et) = {Erro_Total:.{casas+2}f}")

    print("\n\n=== RESPOSTA FINAL ===\n")
    print(f"Valor aproximado da Integral: {integral_aprox:.{casas}f}")

    #Representacao por parenteses (valor +/- erro) ou colchetes (intervalo)
    print(f"Intervalo da resposta (Parêntesis): ( {integral_aprox:.{casas}f} +/- {Erro_Total:.{casas+2}f} )")
    print(f"Intervalo da resposta (Colchetes) : [ {limite_inf:.{casas}f} , {limite_sup:.{casas}f} ]")

if __name__ == "__main__":
    integracao_trapezios()