/** Atividade3: Cadastro de alunos
Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

Aplicacao para cadastro de alunos
*/

import javax.swing.JOptionPane;
public class MenuGrafico implements IMenu {
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

        // Entrada de uma opcao selecionada (atraves do teclado)
        String s = JOptionPane.showInputDialog(menuOpcoes);

        return(s);

    }

    /**
     * Mostra a lista de alunos
     */
    public void listaDeAlunos(String str){
        JOptionPane.showMessageDialog(null,str);
    }

    /**
     * Verifica se a string e numerica
     */
    public  boolean isNumeric(String str) {
        if (str == null || str.length() == 0) {
            return false;
        }

        boolean foundDecimal = false;
        for (char c : str.toCharArray()) { // percorre a string
            if (!Character.isDigit(c)) { // verifica se eh digito
                if (c == '.' && !foundDecimal) { // verifica se existe um unico ponto
                    foundDecimal = true;
                } else {
                    return false;
                }
            }
        }            
        return true;
    }

    /**
     * Retorna a string
     */
    public void mostra(String str) {

        JOptionPane.showMessageDialog(null, str);
    }

    /**
     * Solicita os dados ao usuario
     */
    public String pedir(String str) {

        String resposta = JOptionPane.showInputDialog(str);

        return(resposta);
    }
}