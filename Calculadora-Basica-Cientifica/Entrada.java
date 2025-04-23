import java.util.Scanner;

/** Atividade1: calculadora modo texto (console)/ modo grsfico (janela)
    Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.
    
    Classe responsavel por ler entradas do teclado.
*/

public class Entrada {

    /**
     * Método lerString - le uma string pelo teclado e retorna
     *
     * @param mensagem Mesnsage na console
     * @return s string lida
     */
    
    public String lerString(String mensagem){
        // Cria um objeto da classe Scanner, para leitura pelo teclado
        Scanner sc = new Scanner(System.in);

        // Mostra msg na console
        System.out.print(mensagem);
        
        // Faz a leitura pelo teclado
        String s = sc.nextLine();
        
        // Fecha dispositivo de entrada
        sc.close();
        
        // Retorna a string lida
        return s;
    }
}
