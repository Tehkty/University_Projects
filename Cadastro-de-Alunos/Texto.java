/** Atividade3: Cadastro de alunos
Alunos: Giulia M., Pedro H., Sthefany V., Tulio G.

Aplicacao para cadastro de alunos
 */

public class Texto {
    // Atributo da classe ou varáveis de instancia
    private String txt;

    /** 
     * Construtor: armazena o texto e limpa os espaços excedentes
     * @param txt String com o texto que será armazenado
     */
    Texto(String txt){
        setTxt(txt);
        limpaEspacosExcedentes();
    }

    /**
     * Setter para definir o texto
     */
    private void setTxt(String t){
        this.txt = t;
    }

    /**
     * Getter para ler o texto
     */
    public String getTxt(){
        return this.txt;
    }

    /**
     * Retorna um texto invertido
     * @return txtInvertido String contendo o texto invertido
     */
    public String inverterTexto(){
        String txtInvertido = "";
        if(!(this.txt == null || this.txt.equals("") )){
            for (int i=this.txt.length()-1; i >= 0; i--){
                txtInvertido = txtInvertido + this.txt.charAt(i);
            }
        } else {
            return null;
        }
        return txtInvertido;

    }

    /**
     * Retorna quantidade de palavras do nome
     * @return qtd numero de palavras
     */
    public int getQtdePalavras(){
        return (getTxt().split(" ").length);
    }

    /**
     * Retira espacos excedentes de uma string
     * @return s string sem espacos excedentes
     */
    private void limpaEspacosExcedentes(){
        // Elimina espacos do inicio e fim da string
        setTxt(this.txt.trim());

        // Elimina espacos excedentes do meio da string
        String s = "";
        for (int i=0; i < this.txt.length(); i++){
            s = s + this.txt.charAt(i); // pega o caractere da posicao
            if(this.txt.charAt(i) == ' '){
                while(this.txt.charAt(i+1) == ' '){ // avanca se tiver mais espacos
                    i++;
                }
            }
        }
        setTxt(s);
    }

    /**
     * Retorna os atributos como string
     */
    public String toString(){
        return(getTxt());
    }

    /**
     * Transforma a string para maiuscula
     */
    public String maiuscula(){
        return this.txt.toUpperCase();
    }
}
