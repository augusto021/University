package src;
import java.util.Objects;

public class idEquipa{
    private String nameEq;
    private String treinador;

    public idEquipa(){
        this.nameEq = "";
        this.treinador = "";
    }

    public idEquipa(String name, String treinador){
        this.nameEq = name;
        this.treinador = treinador;
    }

    public idEquipa(idEquipa id_equipa){
        this.nameEq = id_equipa.getNameEq();
        this.treinador = id_equipa.getTreinador();
    }

    public String getNameEq() { return nameEq; }
    public String getTreinador() { return treinador; }
    public void setNameEq(String nameEq) { this.nameEq = nameEq; }
    public void setTreinador(String treinador) { this.treinador = treinador; }

    public idEquipa clone(){ return new idEquipa(this); }

    public String toString() {
        return nameEq +
                "\nTreinador: " + treinador ;
    }


    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        idEquipa idEquipa = (idEquipa) o;
        return Objects.equals(getNameEq(), idEquipa.getNameEq()) && Objects.equals(getTreinador(), idEquipa.getTreinador());
    }

}

