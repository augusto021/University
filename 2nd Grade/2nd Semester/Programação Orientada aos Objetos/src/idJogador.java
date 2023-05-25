package src;
import java.util.ArrayList;
import java.util.Objects;

public class idJogador extends id {
    private String equipa;
    private String titOrSup;
    private int numCamisola;
    private ArrayList<String> historial;

    public idJogador() {
        super();
        this.equipa = "";
        this.titOrSup = "";
        this.numCamisola = 0;
        this.historial = new ArrayList<>();
    }

    public idJogador(String nome,String equipa,String inout,int numC, ArrayList<String> historial) {
        super(nome);
        this.equipa = equipa;
        this.titOrSup = inout;
        this.numCamisola = numC;
        this.historial = new ArrayList<>();
        this.historial.addAll(historial);
    }

    public idJogador(idJogador id_Jogador) {
        super(id_Jogador);
        this.equipa = id_Jogador.getEquipa();
        this.titOrSup = id_Jogador.getTitorSup();
        this.numCamisola = id_Jogador.getNumCamisola();
        this.historial = new ArrayList<>();
        this.historial.addAll(id_Jogador.getHistorial());
    }


    public int getNumCamisola() { return this.numCamisola; }
    public void setNumCamisola(int numCamisola) { this.numCamisola = numCamisola; }

    public String getTitorSup() { return titOrSup; }
    public void setInOut(String titOrSup) { this.titOrSup = titOrSup; }

    public void setEquipa(String equipa) {
        this.equipa = equipa;
    }
    public String getEquipa() {
        return this.equipa;
    }

    public void setHistorial(ArrayList<String> historial) {
        this.historial = historial;
    }
    public ArrayList<String> getHistorial() {
        return this.historial;
    }

    public idJogador clone() {
        return new idJogador(this);
    }

    @Override
    public String toString() {
        return "\n_______" + equipa + "_______"+
                "\nTitular ou Suplente: " + titOrSup +
                "\nNúmero da camisola: " + numCamisola +
                "\nHistorial: " + historial;
    }


    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        idJogador idJogador = (idJogador) o;
        return Objects.equals(getEquipa(), idJogador.getEquipa()) && Objects.equals(getHistorial(), idJogador.getHistorial());
    }
}
