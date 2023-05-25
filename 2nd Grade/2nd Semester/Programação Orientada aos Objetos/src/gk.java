package src;

import java.util.ArrayList;

public class gk extends jogador{
    private int elasticidade;

    public gk(){
        super();
        this.elasticidade = 0;
    }

    public gk(int velocidade, int resistencia, int destreza, int impulsao, int cabeca, int remate, int passe, idJogador infoNew, int elasticidade){
        super(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,infoNew);
        this.elasticidade = elasticidade;
    }

    public gk(gk redes){
        super(redes);
        this.elasticidade = redes.getElasticidade();
    }

    public int getElasticidade() { return this.elasticidade; }
    public void setElasticidade(int elasticidade) { this.elasticidade = elasticidade; }

    public gk clone(){
        return new gk(this);
    }

    public String toString() {
        return  this.getInfoJogador() + "\n_________________________"+"\nGuarda-Redes\n" +
                "\nVelocidade: " + this.getVelocidade() +
                "\nResistência: " + this.getResistencia() +
                "\nDestreza: " + this.getDestreza() +
                "\nImpulsao: " + this.getImpulsao() +
                "\nCabeca: " + this.getCabeca() +
                "\nRemate: " + this.getRemate() +
                "\nPasse: " + this.getPasse() +
                "\nElasticidade: " + elasticidade;
    }

    public boolean equals(Object object) {
        if (this == object) return true;
        if (object == null || getClass() != object.getClass()) return false;
        if (!super.equals(object)) return false;
        gk redes = (gk) object;
        return getElasticidade() == redes.getElasticidade();
    }
    public int calculaAtributos(){
        return ((this.getPasse()+this.getRemate()+this.getCabeca()+this.getImpulsao()+this.getDestreza()+this.getResistencia()+this.getVelocidade()+this.getElasticidade())/8);
    }

    public static gk parse(String input,String team,String titOrsup){
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
        int elasticidade = Integer.parseInt(campos[9]);

        ArrayList<String> historial = new ArrayList<>();
        historial.add(team);

        idJogador idJog = new idJogador(nome,team,titOrsup,numCamisola,historial);

        return new gk(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,idJog,elasticidade);
    }
    
}
