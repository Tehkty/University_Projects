/** Atividade3: Cadastro de alunos
Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

Aplicacao para cadastro de alunos
 */
import java.lang.String;
/**
 * Main
 * @main
 */
public class Main
{
    public static void main(String[] args) {
        IMenu mn = null;
        String opcao;
        CadAlunos cadastro = new CadAlunos();
        try{
            if (args[0]== "t" ||args[0]=="T"){
                mn = new MenuConsole();
            }
        }catch(ArrayIndexOutOfBoundsException e){
            mn = new MenuGrafico();
        }
        do {
            opcao = mn.lerOpcaoMenu();
            try{
                if (opcao != null){
                    switch (opcao){
                        case "1" :
                            cadastro.inserir(mn);
                            break;
                        case "2":
                            String removerRA = mn.pedir("Fale o RA: ");
                            cadastro.remover(removerRA,mn);
                            break;

                        case "3":
                            String lista = cadastro.listar();
                            mn.listaDeAlunos(lista);
                            break;
                        case "4":
                            System.exit(0);
                            break;
                        default:
                            mn.mostra("Opcao invalida");
                            break;  
                    }
                }
            }catch(Exception e){
                mn.mostra("Erro, tente novamente");
            }

        } while (opcao != null && !opcao.equals("4"));

    }

}