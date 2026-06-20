import math
import matplotlib.pyplot as plt


def entrada_dados():
    nome_x = input("Digite a letra maiúscula para a variável INDEPENDENTE (ex: X): ").strip().upper()
    nome_y = input("Digite a letra maiúscula para a variável DEPENDENTE (ex: Y): ").strip().upper()

    print(f"\nDigite os pares ({nome_x}, {nome_y}), um por linha.")
    print("Formato: valor_x valor_y  (separados por espaço)")
    print("Digite 'fim' para encerrar a entrada.\n")

    x_vals = []
    y_vals = []
    i = 1
    while True:
        entrada = input(f"  Par {i}: ").strip()
        if entrada.lower() == "fim":
            if len(x_vals) < 2:
                print("  É necessário pelo menos 2 pares de dados. Continue digitando.")
                continue
            break
        try:
            partes = entrada.replace(",", " ").split()
            xi = float(partes[0])
            yi = float(partes[1])
            x_vals.append(xi)
            y_vals.append(yi)
            i += 1
        except (ValueError, IndexError):
            print("  Entrada inválida. Use o formato: valor_x valor_y")

    return nome_x, nome_y, x_vals, y_vals


def calcular_regressao(nome_x, nome_y, x_vals, y_vals):
    N = len(x_vals)

    # --- Somas básicas ---
    soma_x = sum(x_vals)
    soma_y = sum(y_vals)
    soma_xy = sum(x_vals[i] * y_vals[i] for i in range(N))
    soma_x2 = sum(xi ** 2 for xi in x_vals)
    soma_y2 = sum(yi ** 2 for yi in y_vals)

    # --- Médias: μ_X = Σx_i / N  e  μ_Y = Σy_i / N ---
    media_x = soma_x / N
    media_y = soma_y / N

    # --- Média do produto: μ_XY = Σ(x_i * y_i) / N ---
    media_xy = soma_xy / N

    # --- Desvios padrão: σ_X = √(Σx_i² / N − μ_X²) ---
    sigma_x = math.sqrt(soma_x2 / N - media_x ** 2)
    sigma_y = math.sqrt(soma_y2 / N - media_y ** 2)

    # --- Covariância: Cov(X,Y) = μ_XY − μ_X * μ_Y ---
    cov_xy = media_xy - media_x * media_y

    # --- Coeficiente de Pearson: r = Cov(X,Y) / (σ_X * σ_Y) ---
    if sigma_x == 0 or sigma_y == 0:
        r = 0.0
    else:
        r = cov_xy / (sigma_x * sigma_y)

    # --- Coeficiente de determinação: r² ---
    r2 = r ** 2

    # --- Coeficientes a e b pelo MMQ ---

    denominador = N * soma_x2 - soma_x ** 2
    if denominador == 0:
        print("\nErro: não é possível calcular a regressão (denominador zero).")
        return None

    b = (N * soma_xy - soma_x * soma_y) / denominador
    a = (soma_y - soma_x * b) / N

    return {
        "N": N,
        "nome_x": nome_x,
        "nome_y": nome_y,
        "x_vals": x_vals,
        "y_vals": y_vals,
        "soma_x": soma_x,
        "soma_y": soma_y,
        "soma_xy": soma_xy,
        "soma_x2": soma_x2,
        "soma_y2": soma_y2,
        "media_x": media_x,
        "media_y": media_y,
        "media_xy": media_xy,
        "sigma_x": sigma_x,
        "sigma_y": sigma_y,
        "cov_xy": cov_xy,
        "r": r,
        "r2": r2,
        "a": a,
        "b": b,
    }


def exibir_resultados(res):
    #Exibe todos os resultados formatados.
    nx, ny = res["nome_x"], res["nome_y"]

    print("\n" + "=" * 60)
    print("        RESULTADOS DA REGRESSÃO LINEAR (MMQ)")
    print("=" * 60)

    print(f"\n  n (número de pares)              = {res['N']}")
    print(f"  Σ{nx}  (soma de {nx})               = {res['soma_x']}")
    print(f"  Σ{ny}  (soma de {ny})               = {res['soma_y']}")
    print(f"  Σ({nx}·{ny}) (soma dos produtos)    = {res['soma_xy']}")
    print(f"  Σ{nx}² (soma dos quadrados de {nx})  = {res['soma_x2']}")
    print(f"  Σ{ny}² (soma dos quadrados de {ny})  = {res['soma_y2']}")

    print(f"\n  μ_{nx} (média de {nx})              = {res['media_x']}")
    print(f"  μ_{ny} (média de {ny})              = {res['media_y']}")
    print(f"  μ_{nx}{ny} (média do produto)        = {res['media_xy']}")

    print(f"\n  σ_{nx} (desvio padrão de {nx})      = {res['sigma_x']}")
    print(f"  σ_{ny} (desvio padrão de {ny})      = {res['sigma_y']}")

    print(f"\n  Cov({nx},{ny})                      = {res['cov_xy']}")

    print(f"\n  Coef. de Pearson (r)             = {res['r']:.8f}")
    print(f"  Coef. de determinação (r²)       = {res['r2'] * 100:.2f}%")

    print(f"\n  Coeficientes da reta (f(x) = a + b·x):")
    print(f"    a = {res['a']}")
    print(f"    b = {res['b']}")

    # Formatar a equação
    sinal_b = "+" if res["b"] >= 0 else "-"
    print(f"\n  Reta de regressão de {ny} para {nx}:")
    print(f"    {ny} = {res['a']:.6f} {sinal_b} {abs(res['b']):.6f}·{nx}")

    print("=" * 60)


def plotar_grafico(res):
    #Plota o diagrama de dispersão com a reta de regressão.o
    nx, ny = res["nome_x"], res["nome_y"]
    x_vals, y_vals = res["x_vals"], res["y_vals"]
    a, b = res["a"], res["b"]

    # Pontos da reta
    x_min = min(x_vals) - 1
    x_max = max(x_vals) + 1
    x_reta = [x_min, x_max]
    y_reta = [a + b * xi for xi in x_reta]

    plt.figure(figsize=(8, 5))
    plt.scatter(x_vals, y_vals, color="blue", zorder=5, label="Dados observados")
    plt.plot(x_reta, y_reta, color="red", linewidth=1.5, label=f"{ny} = {a:.4f} + {b:.4f}·{nx}")

    sinal_b = "+" if b >= 0 else "-"
    plt.title(f"Regressão Linear de {ny} para {nx}\n"
              f"{ny} = {a:.4f} {sinal_b} {abs(b):.4f}·{nx}   |   r = {res['r']:.4f}   |   R² = {res['r2'] * 100:.2f}%")
    plt.xlabel(nx)
    plt.ylabel(ny)
    plt.legend()
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig("regressao_linear.png", dpi=150)
    print("\n  Gráfico salvo em: regressao_linear.png")
    plt.show()


def main():
    print("=" * 60)
    print("  REGRESSÃO LINEAR — Método dos Mínimos Quadrados (MMQ)")
    print("=" * 60)

    nome_x, nome_y, x_vals, y_vals = entrada_dados()
    resultado = calcular_regressao(nome_x, nome_y, x_vals, y_vals)

    if resultado is None:
        return

    exibir_resultados(resultado)
    plotar_grafico(resultado)


if __name__ == "__main__":
    main()
