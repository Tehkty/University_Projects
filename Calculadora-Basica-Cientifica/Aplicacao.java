/** Atividade1: calculadora modo texto (console)/ modo grafico (janela)
    Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.
    
    Solicita operandos e operadores ao usuario, processa os calculos e exibe os resultados.
    Suporta entrada grafica e textual.
*/

public class Aplicacao {
    /**
     * Método main - principal: inicia um programa em Java
     * @param args - vetor de strings (recebe dados do SO)
     */
    
    public static void main(String args[]) {
        String operando1;
        String operador;
        String operando2;
        // Verifica se existem parâmetros vindos do SO (args)
        if (args.length == 0) {
            do {
                operando1 = EntradaGrafica.lerString("Forneça operando1: ");

                if (!operando1.equals("sair")) {
                    operador = EntradaGrafica.lerString("Forneça operador: ");

                    if (operador.equals("!") || operador.equals("sen") || operador.equals("sqrt")) {
                        operando2 = "0";
                    } else {
                        operando2 = EntradaGrafica.lerString("Forneça operando2:");
                    }

                    // Chamada do método local (calcular)
                    SaidaGrafica.mostrarMsg(calcular(operando1, operador, operando2));
                }
            } while (!operando1.equals("sair"));

        } else {
            if (args[0].equals("texto")) {
                Entrada ent = new Entrada();
                do {
                    operando1 = ent.lerString("Forneça operando1: ");

                    if (!operando1.equals("sair")) {
                        operador = ent.lerString("Forneça operador: ");

                        if (operador.equals("!") || operador.equals("sen") || operador.equals("sqrt")) {
                            operando2 = "0";
                        } else {
                            operando2 = ent.lerString("Forneça operando2:");
                        }

                        Saida.mostrarMsg(calcular(operando1, operador, operando2));
                    }
                } while (!operando1.equals("sair"));
            } else {
                do {
                    operando1 = EntradaGrafica.lerString("Forneça operando1: ");

                    if (!operando1.equals("sair")) {
                        operador = EntradaGrafica.lerString("Forneça operador: ");

                        if (operador.equals("!") || operador.equals("sen") || operador.equals("sqrt")) {
                            operando2 = "0";
                        } else {
                            operando2 = EntradaGrafica.lerString("Forneça operando2:");
                        }

                        // Chamada do método local (calcular)
                        SaidaGrafica.mostrarMsg(calcular(operando1, operador, operando2));
                    }
                } while (!operando1.equals("sair"));
            }
        }
    }

    public static String calcular(String s1, String s2, String s3) {
        // Cria instância da classe CalcBasica
        CalcBasica cb = new CalcBasica();
        // Aciona o método calcular (passa o vetor de strings como parâmetro)
        return cb.calcular(s1, s2, s3);
    }
}