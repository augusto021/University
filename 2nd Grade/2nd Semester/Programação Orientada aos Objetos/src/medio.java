package src;

import java.util.ArrayList;

public class medio extends jogador{
    private int recupBola;

    public medio(){
        super();
        this.recupBola = 0;
    }

    public medio(int velocidade, int resistencia, int destreza, int impulsao, int cabeca, int remate, int passe, idJogador infoNew, int recupBola){
        super(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,infoNew);
        this.recupBola = recupBola;
    }

    public medio(medio mid){
        super(mid);
        this.recupBola = mid.getRecupBola();
    }

    public int getRecupBola() { return recupBola; }
    public void setRecupBola(int recupBola) { this.recupBola = recupBola; }

    public String toString() {
        return "Médio\n" + this.getInfoJogador() +
                "\nVelocidade: " + this.getVelocidade() +
                "\nResistência: " + this.getResistencia() +
                "\nDestreza: " + this.getDestreza() +
                "\nImpulsao: " + this.getImpulsao() +
                "\nCabeca: " + this.getCabeca() +
                "\nRemate: " + this.getRemate() +
                "\nPasse: " + this.getPasse() +
                "\nRecuperação de bola: " + recupBola;
    }
    public int calculaAtributos(){
        return ((this.getPasse()+this.getRemate()+this.getCabeca()+this.getImpulsao()+this.getDestreza()+this.getResistencia()+this.getVelocidade()+this.getRecupBola())/8);
    }

    public static medio parse(String input,String team,String titOrsup){
        String[] campos = input.split(",");
        String nome = campos[0];
        int numCamisola = Integer.parseInt(campos[1]);
        int velocidade = Integer.parseInt(campos[2]);
        int resistencia = Integer.parseInt(campos[3]);
        int destreza = Integer.parseInt(campos[4]);
        int impulsao = Integer.parseInt(campos[5]);
        int cabeca = Integer.parseInt(campos[6]);
        int remate = Integer.parseInt(campos[7]);
        int passe = Integer.parseInt(campos[8]);
        int recupBola = Integer.parseInt(campos[9]);

        ArrayList<String> historial = new ArrayList<>();
        historial.add(team);

        idJogador idJog = new idJogador(nome,team,titOrsup,numCamisola,historial);

        return new medio(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,idJog,recupBola);
    }
}

