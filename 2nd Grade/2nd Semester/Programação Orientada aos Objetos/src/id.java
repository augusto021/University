package src;

public class id {
    private String nome;

    public id(){
        this.nome = "";
    }

    public id(String nome){
        this.nome = nome;
    }

    public id(id info){
        this.nome = info.getNome();
    }

    public String getNome() { return this.nome; }
    public void setNome(String nome) { this.nome = nome; }

    public id clone(){ return new id(this); }

    public String toString() {
        return "Nome: " + nome;
    }

    public boolean equals(Object object) {
        if (this == object) return true;
        if (object == null || getClass() != object.getClass()) return false;
        if (!super.equals(object)) return false;
        id info = (id) object;
        return getNome().equals(info.getNome());
    }

    
}
