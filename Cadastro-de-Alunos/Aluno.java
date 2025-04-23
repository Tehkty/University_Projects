/** Atividade3: Cadastro de alunos
    Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

    Aplicacao para cadastro de alunos
*/
public class Aluno extends Pessoa {
    // Atributos/Variaveis de instancia
    String ra;
    String curso;
    int periodo;

    public Aluno(String nome, int idade, String rg, String ra, String curso, int periodo){
        super(nome, idade, rg); // Chama contrutor da classe pai (Pessoa)
        
        // Preenche dados do aluno
        setRa(ra);
        setCurso(curso);
        setPeriodo(periodo);
    }

    /**
     * Aluno Constroi um aluno a partir de outro
     *
     * @param a (Aluno)
     */
    public Aluno(Aluno a){
        super(a.getNome(), a.getIdade(), a.getId()); // Chama contrutor da classe pai (Pessoa)
        
        // Preenche dados do aluno
        setRa(a.getRa());
        setCurso(a.getCurso());
        setPeriodo(a.getPeriodo());
    }
    
    private void setRa(String ra){
        this.ra = ra;
    }

    private void setCurso(String curso){
        this.curso = curso;
    }

    private void setPeriodo(int periodo){
        this.periodo = periodo;
    }

    /**
     * Retorna o Ra do aluno
     *
     * @return (String) ra do aluno
     */
    public String getRa(){
        return(this.ra);
    }

    /**
     * Retorna o curso do aluno
     *
     * @return (String) curso do aluno
     */
    public String getCurso(){
        return(this.curso);
    }

    /**
     * Retorna o periodo do aluno
     *
     * @return (int) periodo do aluno
     */
    public int getPeriodo(){
        return(this.periodo);
    }

    /**
     *  Retorna dados do aluno
     *  @return (String) Dados de um aluno
     */
    public String toString(){
        String str = super.toString();
        str = str + "\nRa: " + getRa();
        str = str + "\nCurso: " + getCurso();
        str = str + "\nPeriodo: " + getPeriodo();
        return str;
    }
}

