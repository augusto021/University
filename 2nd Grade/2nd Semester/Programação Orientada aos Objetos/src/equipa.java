package src;
import java.util.ArrayList;
import java.util.List;

public class equipa {
    private idEquipa info;
    private ArrayList<jogador> titulares;
    private ArrayList<jogador> suplentes;

    public equipa(){
        this.info = new idEquipa();
        this.titulares = new ArrayList<>();
        this.suplentes = new ArrayList<>();
    }

    public equipa(idEquipa info, ArrayList<jogador> titulares, ArrayList<jogador> suplentes){
        this.info = new idEquipa(info);
        this.titulares = new ArrayList<>();
        this.titulares.addAll(titulares);
        this.suplentes = new ArrayList<>();
        this.suplentes.addAll(suplentes);
    }

    public equipa(equipa team){
        this.info = team.getInfoEquipa();
        this.titulares = team.getTitulares();
        this.suplentes = team.getSuplentes();
    }

    public idEquipa getInfoEquipa() { return info; }
    public void setInfoEquipa(idEquipa info) { this.info = info; }
    public ArrayList<jogador> getTitulares() { return this.titulares; }
    public void setTitulares(ArrayList<jogador> titulares) { this.titulares = titulares; }
    public ArrayList<jogador> getSuplentes() { return this.suplentes; }
    public void setSuplentes(ArrayList<jogador> suplentes) { this.suplentes = suplentes; }


    public equipa clone(){
        return new equipa(this);
    }

    public String toString() {
        List<String> nomesTit = new ArrayList<>();
        StringBuilder sbT = new StringBuilder();
        StringBuilder sbS = new StringBuilder();

        for(int i = 0; i < this.titulares.size();i++){
            String name = titulares.get(i).getInfoJogador().getNome();
            nomesTit.add(name);
            sbT.append("\t"+name+"\n");
        }

        List<String> nomesSup = new ArrayList<>();
        for(int i = 0; i < this.suplentes.size();i++){
            String name = suplentes.get(i).getInfoJogador().getNome();
            nomesSup.add(name);
            sbS.append("\t"+name+"\n");
        }

        return "\n_______"+getInfoEquipa().getNameEq()+"_______" + "\nTreinador: "+getInfoEquipa().getTreinador()+"\n\nTitulares:\n"+ sbT.toString() + "\nSuplentes:\n"+ sbS.toString();
    }

    public boolean equals(Object object) {
        if (this == object) return true;
        if (object == null || getClass() != object.getClass()) return false;
        if (!super.equals(object)) return false;
        equipa team = (equipa) object;
        return team.getInfoEquipa().equals(this.info) &&
                team.getTitulares().equals(this.titulares) &&
                team.getSuplentes().equals(this.suplentes);
    }
}
