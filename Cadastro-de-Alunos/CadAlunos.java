/** Atividade3: Cadastro de alunos
Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

Aplicacao para cadastro de alunos
 */
public class CadAlunos {

    public Aluno alunosCadastrados[];

    private int qtdAlunos;

    /**
     * Construtor CadAlunos
     * @Inicializa o contador qtdAlunos
     * @Inicializa Aluno com 100 posicoes disponiveis
     */

    public CadAlunos() {
        alunosCadastrados = new Aluno[100];
        qtdAlunos = 0;
    }

    /**
     * Funcao inserir
     * @Input para dados do aluno
     */
    public boolean inserir(IMenu mn) {
        if (qtdAlunos >= alunosCadastrados.length) return false;

        String nome = "";
        boolean nomeValido = false;
        while (!nomeValido) {
            nome = mn.pedir("Forneça o nome:");
            if (nome == null) return false;
            if (nome.trim().equals("")) {
                mn.mostra("Esse campo e obrigatorio");
                continue;
            }

            nomeValido = true;
            for (int i = 0; i < nome.length(); i++) {
                char c = nome.charAt(i);
                if (!Character.isLetter(c) && c != ' ') {
                    mn.mostra("Formato invalido");
                    nomeValido = false;
                    break;
                }
            }
        }

        String idadeTexto = "";
        int idade = 0;
        boolean idadeValida = false;
        while (!idadeValida) {
            idadeTexto = mn.pedir("Forneça a idade:");
            if (idadeTexto == null) return false;
            if (idadeTexto.trim().equals("")) {
                mn.mostra("Esse campo e obrigatorio");
                continue;
            }
            try {
                idade = Integer.parseInt(idadeTexto);
                idadeValida = true;
            } catch (NumberFormatException e) {
                mn.mostra("A idade deve ser um numero inteiro");
            }
        }

        String rg = "";
        boolean rgValido = false;
        while (!rgValido) {
            rg = mn.pedir("Forneça o RG:");
            if (rg == null) return false;
            if (rg.trim().equals("")) {
                mn.mostra("Esse campo e obrigatorio");
                continue;
            }
            rgValido = true;
        }

        String ra = "";
        boolean raValido = false;
        while (!raValido) {
            ra = mn.pedir("Forneça o RA:");
            if (ra == null) return false;
            if (ra.trim().equals("")) {
                mn.mostra("Esse campo e obrigatorio");
                continue;
            }
            raValido = true;
        }

        String curso = "";
        boolean cursoValido = false;
        while (!cursoValido) {
            curso = mn.pedir("Forneça o curso:");
            if (curso == null) return false;
            if (curso.trim().equals("")) {
                mn.mostra("Esse campo e obrigatorio");
                continue;
            }

            cursoValido = true;
            for (int i = 0; i < curso.length(); i++) {
                char c = curso.charAt(i);
                if (!Character.isLetter(c) && c != ' ') {
                    mn.mostra("O curso nao pode ter letras");
                    cursoValido = false;
                    break;
                }
            }
        }

        String periodoTexto = "";
        int periodo = 0;
        boolean periodoValido = false;
        while (!periodoValido) {
            periodoTexto = mn.pedir("Forneça o período:");
            if (periodoTexto == null) return false;
            if (periodoTexto.trim().equals("")) {
                mn.mostra("Esse campo e obrigatorio");
                continue;
            }
            try {
                periodo = Integer.parseInt(periodoTexto);
                periodoValido = true;
            } catch (NumberFormatException e) {
                mn.mostra("O periodo deve ser um numero inteiro");
            }
        }

        alunosCadastrados[qtdAlunos++] = new Aluno(nome, idade, rg, ra, curso, periodo);
        return true;
    }

    /**
     * Funcao remover Aluno
     * @Tira aluno da array e marca posicao como NULL
     */
    public boolean remover(String ra, IMenu mn){
        if(qtdAlunos == 0) {
            mn.mostra("nao tem");
            return false;
        }
        for (int i = 0; i < qtdAlunos; i++) {
            if (alunosCadastrados[i] != null && alunosCadastrados[i].getRa().equals(ra)) {
                for(int j = i; j < qtdAlunos - 1; j++) {
                    alunosCadastrados[j] = alunosCadastrados[j + 1];
                }
                alunosCadastrados[qtdAlunos - 1] = null;
                qtdAlunos--;
                return true;
            }
        }
        mn.mostra("RA nao encontrado");
        return false;
    }

    /**
     * Retorna a lista das informacoes dos alunos cadastrados
     * @return lista de alunos cadastrados
     */
    public String listar() {
        String lista = "";
        boolean encontrou = false;

        for (int i = 0; i < alunosCadastrados.length; i++) {
            if (alunosCadastrados[i] != null) {
                Aluno a = alunosCadastrados[i];
                lista = lista + "Aluno " + (i + 1) + ":\n";
                lista = lista + "Nome: " + a.getNome() + "\n";
                lista = lista + "Idade: " + a.getIdade() + "\n";
                lista = lista + "RG: " + a.getId() + "\n";
                lista = lista + "RA: " + a.getRa() + "\n";
                lista = lista + "Curso: " + a.getCurso() + "\n";
                lista = lista + "Período: " + a.getPeriodo() + "\n\n";
                encontrou = true;
            }
        }

        if (!encontrou) {
            lista = "Nao existem alunos cadastrados";
        }

        return lista;
    }

    /**
     * Retorna os atributos como string
     */
    public String toString(){
        String s = "";

        for (int i = 0; i < alunosCadastrados.length; i++){
            if (alunosCadastrados[i] != null ){
                s += "\n--------";
                s += alunosCadastrados[i].toString();
            }
        }
        return s;
    }
}