import java.lang.Math;

/** Atividade1: calculadora modo texto (console)/ modo grafico (janela)
    Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.
    
    Classe responsavel realizar operacoes matematicas basicas, 
    incluindo soma, subtracao, multiplicacao, divisao, fatorial, seno e raiz quadrada.
*/

public class CalcBasica {
    /**
     * Método calcular - executa a operação desejada entre operandos.
     * @param operando1 String representando o primeiro operando.
     * @param operador String representando o operador matemático.
     * @param operando2 String representando o segundo operando (ou "0" para operações unárias).
     * @return String com o resultado formatado ou mensagem de erro.
     */
    public String calcular(String operando1, String operador, String operando2) { 
        // Para armazenar resultado
        double result = 0;
        
        // Para armazenar uma mensagem
        String msg = "";

        // Verifica se ambos os operandos são numéricos
        if (isNumeric(operando1) && isNumeric(operando2)) {
            // Realiza a operação matemática correspondente
            switch (operador) {
                case "-":
                    result = Double.parseDouble(operando1) - Double.parseDouble(operando2);
                    msg = String.format("Resultado = %.2f", result);
                    break;
                case "+":
                    result = Double.parseDouble(operando1) + Double.parseDouble(operando2);
                    msg = String.format("Resultado = %.2f", result);
                    break;
                case "*":
                    result = Double.parseDouble(operando1) * Double.parseDouble(operando2);
                    msg = String.format("Resultado = %.2f", result);
                    break;
                case "/":
                    if (Double.parseDouble(operando2) == 0) {
                        msg = "Erro: Divisão por zero!";
                    } else {
                        result = Double.parseDouble(operando1) / Double.parseDouble(operando2);
                        msg = String.format("Resultado = %.2f", result);
                    }
                    break;
                case "sen":
                    result = seno(Double.parseDouble(operando1));
                    msg = String.format("Resultado = %.2f", result);
                    break;
                case "!":
                    int num = Integer.parseInt(operando1);
                    result = (num == 0) ? 1 : fatorial(num);
                    msg = String.format("Resultado = %.2f", result);
                    break;
                case "sqrt":
                    result = Math.sqrt(Double.parseDouble(operando1));
                    msg = String.format("Resultado = %.2f", result);
                    break;
                default:
                    msg = "Operador inválido!";
            }    
        } else {
            msg = "Operando não numérico!";
        }

        return msg;
    }

    /**
     * Método isNumeric - verifica se a string representa um número válido.
     * @param str String a ser verificada.
     * @return true se for numérica, false caso contrário.
     */
    public boolean isNumeric(String str) {
        if (str == null || str.isEmpty()) {
            return false;
        }

        boolean foundDecimal = false;
        for (char c : str.toCharArray()) {
            if (!Character.isDigit(c)) {
                if (c == '.' && !foundDecimal) {
                    foundDecimal = true;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
    
    /**
     * Método fatorial - calcula o fatorial de um número inteiro.
     * @param fat Número inteiro para cálculo do fatorial.
     * @return Resultado do fatorial.
     */
    public static int fatorial(int fat) {
        int resultado = 1;
        for (int i = 1; i <= fat; i++) {
            resultado *= i;
        }
        return resultado;
    }
    
    /**
     * Método seno - calcula o seno de um ângulo em graus.
     * @param angulo Ângulo em graus.
     * @return Valor do seno do ângulo.
     */
    public static double seno(double angulo) {
        double rad = angulo * Math.PI / 180;
        return Math.sin(rad);
    }
}