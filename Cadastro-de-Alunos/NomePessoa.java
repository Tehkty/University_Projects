/** Atividade3: Cadastro de alunos
Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

Aplicacao para cadastro de alunos
 */
public class NomePessoa extends Texto{
    // Atributos
    private String nome;

    // Construtores
    public NomePessoa(String nome){
        super(nome);
        setNome(nome);
    }

    /**
     * Getter para ler o nome
     * @return the nome
     */
    public String getNome() {
        return this.getTxt();
    }

    /**
     * Setter para definir o nome
     * @param nome the nome to set
     */
    protected void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Retorna quantidade de palavras do nome
     * @return qtd numero de palavras
     */
    public int getQtdePalavras(){
        return this.getQtdePalavras();
    }

    /**
     * Retorna nome invertido
     * @return sInv nome invertido
     */
    public String getNomeInvertido(){
        return this.inverterTexto();
    }

    /**
     * Retorna nome bibliografico
     * @return sBib nome bibliografico
     */
    public String getNomeBiblio(){
        // Separa as palavras
        String vts[] = this.getTxt().split(" ");
        int qtd = vts.length;

        String sBib = vts[qtd-1] + ", "; // ultimo nome + a virgula
        // Monta o texto
        for (int i=0; i < (qtd-1); i++){
            String pal = vts[i].toLowerCase(); // pega palavra
            if(!verificaStr(pal)){ // Se nao for preposicao concatena
                sBib = sBib + vts[i].toUpperCase().charAt(0) + ". ";
            }
        }
        return sBib;
    }

    /**
     * Verifica se string eh uma "preposicao"
     * @param s string a ser verificada
     * @return true eh preposicao false nao eh preposicao
     */
    private boolean verificaStr(String s){
        // Vetor de strings a serem retiradas
        final String sRet[]={"da", "de", "do", "di", "das", "dos", "e",};

        for (int i = 0; i < sRet.length; i++){
            if(sRet[i].equals(s)){
                return true;
            }
        }
        return false;
    }

    /**
     * Retorna os atributos como string
     */
    public String toString(){
        return this.getTxt();
    }
}