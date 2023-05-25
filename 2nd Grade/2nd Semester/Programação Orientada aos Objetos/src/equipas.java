package src;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.io.IOException;

public class equipas{
    private ArrayList<equipa> teams;
    private List<jogo> jogos;

    public equipas(){
        this.teams = new ArrayList<>();
        this.jogos = new ArrayList<>();
    }

    public equipas(ArrayList<equipa> teams,List<jogo> jogos){
        this.teams = new ArrayList<>();
        this.teams.addAll(teams);
        this.jogos = new ArrayList<>();
        this.jogos.addAll(jogos);
    }

    public equipas(equipas eqT){
        this.teams = new ArrayList<>();
        this.teams = eqT.getTeams();
        this.jogos = new ArrayList<>();
        this.jogos = eqT.getJogos();
    }

    public ArrayList<equipa> getTeams() { return this.teams; }
    public void setTeams(ArrayList<equipa> teams) { this.teams = teams; }

    public List<jogo> getJogos() { return this.jogos; }
    public void setJogos(List<jogo> jogos) { this.jogos = jogos; }

    public String toString() {
        ArrayList<String> nomesEq = new ArrayList<>();
        for(int i = 0; i < this.teams.size();i++){
            nomesEq.add(teams.get(i).getInfoEquipa().getNameEq());
        }
        return "Equipas do Log" + "\n" + nomesEq +
                "Jogos" + this.jogos;
    }



    public static List<String> lerFicheiro(String nomeFich) {
        List<String> lines;
        try { lines = Files.readAllLines(Paths.get(nomeFich), StandardCharsets.UTF_8); }
        catch(IOException exc) { lines = new ArrayList<>(); }
        return lines;
    }

    public equipas loadFile() {
        ArrayList<equipa> op = new ArrayList<>();
        List<jogo> games = new ArrayList<>();
        equipa now = new equipa();
        String rel;
        jogador jog = new jogador();

        int flag = 1;

        List<String> linhas = lerFicheiro("logsV2.txt");
        String[] linhaPartida;
        for(String linha : linhas){
            linhaPartida = linha.split(":",2);

            switch(linhaPartida[0]){
                case "Equipa":
                    idEquipa id = new idEquipa(linhaPartida[1],"");
                    equipa team = new equipa();
                    team.setInfoEquipa(id);
                    now = team;
                    op.add(now);
                    flag = 1;
                    break;
                case "Treinador":
                    flag++;
                    String coach = linhaPartida[1];
                    now.getInfoEquipa().setTreinador(coach);
                    break;
                case "Lateral":
                    flag++;
                    if(flag >= 3 && flag <= 13) rel = "Titular";
                    else rel = "Suplente";
                    jog = lateral.parse(linhaPartida[1],now.getInfoEquipa().getNameEq(),rel);
                    if(rel.equals("Titular")) now.getTitulares().add(jog);
                    else now.getSuplentes().add(jog);
                    break;
                case "Avancado":
                    flag++;
                    if(flag >= 3 && flag <= 13) rel = "Titular";
                    else rel = "Suplente";
                    jog= avancado.parse(linhaPartida[1],now.getInfoEquipa().getNameEq(),rel);
                    if(rel.equals("Titular")) now.getTitulares().add(jog);
                    else now.getSuplentes().add(jog);
                    break;
                case "Medio":
                    flag++;
                    if(flag >= 3 && flag <= 13) rel = "Titular";
                    else rel = "Suplente";
                    jog = medio.parse(linhaPartida[1],now.getInfoEquipa().getNameEq(),rel);
                    if(rel.equals("Titular")) now.getTitulares().add(jog);
                    else now.getSuplentes().add(jog);
                    break;
                case "Defesa":
                    flag++;
                    if(flag >= 3 && flag <= 13) rel = "Titular";
                    else rel = "Suplente";
                    jog = defesa.parse(linhaPartida[1],now.getInfoEquipa().getNameEq(),rel);
                    if(rel.equals("Titular")) now.getTitulares().add(jog);
                    else now.getSuplentes().add(jog);
                    break;
                case "Guarda-Redes":
                    flag++;
                    if(flag >= 3 && flag <= 13) rel = "Titular";
                    else rel = "Suplente";
                    jog = gk.parse(linhaPartida[1],now.getInfoEquipa().getNameEq(),rel);
                    if(rel.equals("Titular")) now.getTitulares().add(jog);
                    else now.getSuplentes().add(jog);
                    break;
                case "Jogo":
                    jogo jo = jogo.parse(linhaPartida[1]);
                    games.add(jo);
                    break;
                default:
                    System.out.println("Linha inválida.");
                    break;
            }
        }
        equipas log = new equipas(op,games);
        System.out.println("Ficheiro carregado com êxito!!");
        return log;
    }

}
