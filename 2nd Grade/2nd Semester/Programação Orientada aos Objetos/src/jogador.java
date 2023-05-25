package src;
import java.util.Objects;


public class jogador {
    private int velocidade;
    private int resistencia;
    private int destreza;
    private int impulsao;
    private int cabeca;
    private int remate;
    private int passe;
    private idJogador info;

    public jogador(){
        this.velocidade = 0;
        this.resistencia = 0;
        this.destreza = 0;
        this.impulsao = 0;
        this.cabeca = 0;
        this.remate = 0;
        this.passe = 0;
        this.info = new idJogador();
    }

    public jogador(int velocidade, int resistencia, int destreza, int impulsao, int cabeca, int remate, int passe, idJogador infoNew){
        this.velocidade = velocidade;
        this.resistencia = resistencia;
        this.destreza = destreza;
        this.impulsao = impulsao;
        this.cabeca = cabeca;
        this.remate = remate;
        this.passe = passe;
        this.info = infoNew;
    }
    public jogador(jogador player){
        this.velocidade = player.getVelocidade();
        this.resistencia = player.getResistencia();
        this.destreza = player.getDestreza();
        this.impulsao = player.getImpulsao();
        this.cabeca = player.getCabeca();
        this.remate = player.getRemate();
        this.passe = player.getPasse();
        this.info = player.getInfoJogador();
    }

    public void setVelocidade(int velocidade){
        this.velocidade = velocidade;
    }
    public int getVelocidade(){
        return this.velocidade;
    }
    public void setResistencia(int resistencia){
        this.resistencia = resistencia;
    }
    public int getResistencia(){
        return this.resistencia;
    }
    public void setDestreza(int destreza){
        this.destreza = destreza;
    }
    public int getDestreza(){
        return this.destreza;
    }
    public void setImpulsao(int impulsao){
        this.impulsao = impulsao;
    }
    public int getImpulsao(){
        return this.impulsao;
    }
    public void setCabeça(int cabeca){
        this.cabeca = cabeca;
    }
    public int getCabeca(){
        return this.cabeca;
    }
    public void setRemate(int remate){
        this.remate = remate;
    }
    public int getRemate(){
        return this.remate;
    }
    public void setPasse(int passe){
        this.passe = passe;
    }
    public int getPasse(){
        return this.passe;
    }
    public void setInfoJogador(idJogador infoNew){ this.info = infoNew; }
    public idJogador getInfoJogador(){return this.info; }


    public jogador clone(){ return new jogador(this); }

    public String toString() {
        return "Jogador:: " +
                info +
                "\nvelocidade: " + velocidade +
                "\nresistencia: " + resistencia +
                "\ndestreza: " + destreza +
                "\nimpulsao: " + impulsao +
                "\ncabeca: " + cabeca +
                "\nremate: " + remate +
                "\npasse: " + passe;
    }


    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        jogador jogador = (jogador) o;
        return getVelocidade() == jogador.getVelocidade() &&
                getResistencia() == jogador.getResistencia() &&
                getDestreza() == jogador.getDestreza() &&
                getImpulsao() == jogador.getImpulsao() &&
                getCabeca() == jogador.getCabeca() &&
                getRemate() == jogador.getRemate() &&
                getPasse() == jogador.getPasse() && Objects.equals(getInfoJogador(), jogador.getInfoJogador());
    }

    public int calculaAtributos(){
        return ((this.getPasse()+this.getRemate()+this.getCabeca()+this.getImpulsao()+this.getDestreza()+this.getResistencia()+this.getVelocidade())/8);
    }
}
