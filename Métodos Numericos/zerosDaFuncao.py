import math
import matplotlib.pyplot as plt


def format_num(value):
    if isinstance(value, float):
        text = f"{value:.10f}".rstrip("0").rstrip(".")
        return text if text != "" else "0"
    return str(value)


def parse_function(expression: str):
    """Retorna uma função f(x) a partir de uma expressão em texto."""
    allowed_names = {name: getattr(math, name) for name in dir(math) if not name.startswith("__")}
    allowed_names.update({"abs": abs, "pow": pow})

    def f(x):
        try:
            return eval(expression, {"__builtins__": None}, {**allowed_names, "x": x})
        except Exception as error:
            raise ValueError(f"Erro ao avaliar a função: {error}") from error

    return f


def bisseccao(f, inicial: float, final: float, e: float, max_iter: int = 1000):
    if max_iter <= 0:
        raise RuntimeError("Número máximo de iterações atingido antes de atingir a precisão desejada.")
    f1 = f(inicial)
    f2 = f(final)

    if f1 == 0:
        return inicial, 0.0
    if f2 == 0:
        return final, 0.0

    if f1 * f2 > 0:
        raise ValueError("O intervalo informado não contém mudança de sinal. Tente outro intervalo.")

    x0 = (inicial + final) / 2.0
    fx0 = f(x0)
    erroAtual = abs(final - inicial) / 2.0

    print(f"\n--- Iteração {1000 - max_iter} ---")
    print(f"Intervalo atual: [{format_num(inicial)}, {format_num(final)}]")
    print(f"x0 (ponto médio) = {format_num(x0)}")
    print(f"f({format_num(inicial)}): {format_num(f1)}")
    print(f"f(x0): {format_num(fx0)}")
    print(f"f({format_num(final)}): {format_num(f2)}")
    print(f"Erro atual: {format_num(erroAtual)}")
    print(20 * "-")

    if fx0 == 0 or erroAtual <= e:
        return x0, erroAtual

    if f1 * fx0 < 0:
        final = x0
        f2 = fx0
    else:
        inicial = x0
        f1 = fx0
    return bisseccao(f, inicial, final, e, max_iter - 1)


def plotar_grafico(f, expressao, a, b, x0):
    """Plota a função no intervalo [a, b] e marca o zero encontrado."""
    # Gera 200 pontos entre a e b
    n = 200
    xs = [a + (b - a) * i / (n - 1) for i in range(n)]
    ys = [f(x) for x in xs]

    plt.plot(xs, ys, label=f"f(x) = {expressao}")
    plt.axhline(0, color="black", linewidth=0.8)  # eixo x
    plt.scatter([x0], [0], color="red", zorder=5, label=f"x0 ≈ {format_num(x0)}")
    plt.title("Método da Bisseção")
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.grid(True)
    plt.legend()
    plt.show()


def entrada_de_dados():
    print("Método da bisseção para encontrar zeros de uma função")
    print("Use x como variável. Exemplo: x**3 - 4*x - 9")

    expression = input("Digite a função em x: ").strip()
    a = float(input("Digite o ponto inicial do intervalo: "))
    b = float(input("Digite o ponto final do intervalo: "))
    e = float(input("Digite o erro estimado mínimo: "))

    f = parse_function(expression)
    return f, a, b, e, expression


def main():
    try:
        f, a, b, e, expression = entrada_de_dados()
        x0, erro = bisseccao(f, a, b, e)
        print(f"\nPonto zero aproximado: {format_num(x0)}")
        print(f"Erro estimado: {format_num(erro)}")
        print(f"f(x0) = {format_num(f(x0))}")
        plotar_grafico(f, expression, a, b, x0)
    except Exception as error:
        print(f"Erro: {error}")


if __name__ == "__main__":
    main()
