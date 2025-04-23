/** Atividade3: Cadastro de alunos
Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

Aplicacao para cadastro de alunos
*/

import java.util.Scanner;
public class MenuConsole implements IMenu {
    // Armazena as opcoes do menu
    private static String opcoes[] = {"(1) Inserir", "(2) Remover", "(3) Listar", "(4) Sair"};

    /**
     * Cria as opcoes do menu
     */
    public String criarMenu(){
        String menuOpcoes = "";
        for (int i = 0; i < opcoes.length; i++){
            menuOpcoes += opcoes[i] + "\n";
        }
        return menuOpcoes;
    }

    /**
     * Leitura das opcoes do menu
     */
    public  String lerOpcaoMenu(){
        // Monta menu
        String menuOpcoes = criarMenu();
        // Mostra msg na console
        System.out.print(menuOpcoes);

        // Cria um objeto da classe Scanner, para leitura pelo teclado
        Scanner sc = new Scanner(System.in);

        // Entrada de uma opcao selecionada (atraves do teclado)
        String opcao = sc.nextLine();

        return(opcao);

    }

    /**
     * Mostra a lista de alunos
     */
    public void listaDeAlunos(String str) {
        System.out.println(str);
    }

    /**
     * Retorna a string
     */
    public void mostra(String str) {

        System.out.println(str);
    }

    /**
     * Solicita os dados ao usuario
     */
    public String pedir(String str) {

        System.out.println(str);

        // Cria um objeto da classe Scanner, para leitura pelo teclado
        Scanner sc = new Scanner(System.in);

        // Entrada de uma opcao selecionada (atraves do teclado)
        String resposta = sc.nextLine();

        return(resposta);
    }
}

