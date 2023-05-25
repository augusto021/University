package src;

mport java.util.ArrayList;

public class lateral extends jogador {
    public int cruzamento;

    public lateral() {
        super();
        this.cruzamento = 0;
    }

    public lateral(int velocidade, int resistencia, int destreza, int impulsao, int cabeca, int remate, int passe, idJogador infoNew, int cruzamento) {
        super(velocidade, resistencia, destreza, impulsao, cabeca, remate, passe, infoNew);
        this.cruzamento = cruzamento;
    }

    public lateral(lateral lat) {
        super(lat);
        this.cruzamento = lat.getCruzamento();

    }


    public int getCruzamento() {
        return cruzamento;
    }

    public void setCruzamento(int cruzamento) {
        this.cruzamento = cruzamento;
    }

    public String toString() {
        return this.getInfoJogador() + "\n_________________________"+"\nLateral\n" +
                "\nVelocidade: " + this.getVelocidade() +
                "\nResistencia: " + this.getResistencia() +
                "\nDestreza: " + this.getDestreza() +
                "\nImpulsao: " + this.getImpulsao() +
                "\nCabeca: " + this.getCabeca() +
                "\nRemate: " + this.getRemate() +
                "\nPasse: " + this.getPasse() +
                "\nCruzamento: " + cruzamento;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        lateral lateral = (lateral) o;
        return getCruzamento() == lateral.getCruzamento();
    }

    public int calculaAtributos(){
        return ((this.getPasse()+this.getRemate()+this.getCabeca()+this.getImpulsao()+this.getDestreza()+this.getResistencia()+this.getVelocidade()+this.getCruzamento())/8);
    }

    public static lateral parse(String input,String team,String titOrsup){
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
        int cruzamento = Integer.parseInt(campos[9]);

        ArrayList<String> historial = new ArrayList<>();
        historial.add(team);

        idJogador idJog = new idJogador(nome,team,titOrsup,numCamisola,historial);

        return new lateral(velocidade,resistencia,destreza,impulsao,cabeca,remate,passe,idJog,cruzamento);
    }


}

