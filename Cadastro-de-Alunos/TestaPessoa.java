/** Atividade3: Cadastro de alunos
Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

Aplicacao para cadastro de alunos
 */

import javax.swing.JOptionPane;
public class TestaPessoa
{
    /**
     * Main para testar os atributos da pessoa
     */
    public static void main(String args[]){

        // Entrada de um nome do aluno (atraves do teclado)
        String nome = JOptionPane.showInputDialog("Forneca o nome da pessoa: ");

        // Entrada da idade do aluno (atraves do teclado)
        int idade = Integer.parseInt(JOptionPane.showInputDialog("Forneca a idade da pessoa: "));

        // Entrada de uma identificacao do aluno (atraves do teclado)
        String rg = JOptionPane.showInputDialog("Forneca o rg da pessoa: ");

        // Criacao de uma instancia da classe Aluno
        Pessoa p = new Pessoa(nome, idade, rg);

        // Mostra os dados
        System.out.println("Dados da pessoa             : " + p);
    }
}