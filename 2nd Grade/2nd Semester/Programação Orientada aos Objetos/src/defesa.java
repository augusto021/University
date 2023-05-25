package src;

import java.util.ArrayList;

public class defesa extends jogador{
    private int corte;

    public defesa(){
        super();
        this.corte = 0;
    }

    public defesa(int velocidade, int resistencia, int destreza, int impulsao, int cabeca, int remate, int passe, idJogador infoNew, int corte){
        super(velocidade, resistencia, destreza, impulsao, cabeca, remate, passe, infoNew);
        this.corte = corte;
    }

    public defesa(defesa safe){
        super(safe);
        this.corte = safe.getCorte();
    }

    public int getCorte() { return corte; }
    public void setCorte(int corte) { this.corte = corte; }

    public String toString() {
        return  this.getInfoJogador() + "\n_________________________"+"\nDefesa\n" +
                "\nVelocidade: " + this.getVelocidade() +
                "\nResistência: " + this.getResistencia() +
                "\nDestreza: " + this.getDestreza() +
                "\nImpulsao: " + this.getImpulsao() +
                "\nCabeca: " + this.getCabeca() +
                "\nRemate: " + this.getRemate() +
                "\nPasse: " + this.getPasse() +
                "\nCorte: " + corte;
    }

    public int calculaAtributos(){
        return ((this.getPasse()+this.getRemate()+this.getCabeca()+this.getImpulsao()+this.getDestreza()+this.getResistencia()+this.getVelocidade()+this.getCorte())/8);
    }

    public static defesa parse(String input,String team,String titOrsup){
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
        int corte = Integer.parseInt(campos[9]);

        ArrayList<String> historial = new ArrayList<>();
        historial.add(team);

        idJogador idJog = new idJogador(nome,team,titOrsup,numCamisola,historial);

        return new defesa(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,idJog,corte);
    }

}
