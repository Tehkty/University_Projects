import javax.swing.JOptionPane;

/** Atividade1: calculadora modo texto (console)/ modo grsfico (janela)
    Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.
    
    Classe responsavel por ler entradas do teclado.
*/

public class EntradaGrafica
{
    public static String lerString(String msg){
        String s = JOptionPane.showInputDialog(msg);
        return s;
    }
}