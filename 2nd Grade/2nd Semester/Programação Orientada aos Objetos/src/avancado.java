package src;

import java.util.ArrayList;

public class avancado extends jogador{
    private int penalti;

    public avancado(){
        super();
        this.penalti = 0;
    }

    public avancado(int velocidade, int resistencia, int destreza, int impulsao, int cabeca, int remate, int passe, idJogador infoNew, int penalti){
        super(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,infoNew);
        this.penalti = penalti;
    }

    public avancado(avancado at){
        super(at);
        this.penalti = at.getPenalti();
    }

    public int getPenalti() { return penalti; }
    public void setPenalti(int penalti) { this.penalti = penalti; }

    public String toString() {
        return  this.getInfoJogador() + "\n_________________________"+"\nAvançado\n" +
                "\nVelocidade: " + this.getVelocidade() +
                "\nResistência: " + this.getResistencia() +
                "\nDestreza: " + this.getDestreza() +
                "\nImpulsao: " + this.getImpulsao() +
                "\nCabeca: " + this.getCabeca() +
                "\nRemate: " + this.getRemate() +
                "\nPasse: " + this.getPasse() +
                "\nPenalti: " + penalti;
    }
    public int calculaAtributos(){
        return ((this.getPasse()+this.getRemate()+this.getCabeca()+this.getImpulsao()+this.getDestreza()+this.getResistencia()+this.getVelocidade()+this.getPenalti())/8);
    }
    public static avancado parse(String input,String team,String titOrsup){
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
        int penalti = Integer.parseInt(campos[9]);

        ArrayList<String> historial = new ArrayList<>();
        historial.add(team);

        idJogador idJog = new idJogador(nome,team,titOrsup,numCamisola,historial);

        return new avancado(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,idJog,penalti);
    }

}
