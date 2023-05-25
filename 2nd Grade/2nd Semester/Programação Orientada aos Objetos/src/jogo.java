package src;
import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

public class jogo {
    private String equipaCasa;
    private String equipaFora;
    private int golosCasa;
    private int golosFora;
    private LocalDate date;
    private List<Integer> jogadoresCasa;
    private List<Integer> jogadoresFora;
    Map<Integer, Integer> substituicoesCasa;
    Map<Integer, Integer> substitucoesFora;

    public jogo(){
        this.equipaCasa = "";
        this.equipaFora = "";
        this.golosCasa = 0;
        this.golosFora = 0;
        this.date = LocalDate.now();
        this.jogadoresCasa = new ArrayList<>();
        this.jogadoresFora = new ArrayList<>();
        this.substituicoesCasa = new HashMap<>();
        this.substitucoesFora = new HashMap<>();

    }

    public String getEquipaFora() {
        return equipaFora;
    }

    public void setEquipaFora(String equipaFora) {
        this.equipaFora = equipaFora;
    }

    public String getEquipaCasa() {
        return equipaCasa;
    }

    public void setEquipaCasa(String equipaCasa) {
        this.equipaCasa = equipaCasa;
    }

    public jogo (String ec, String ef, int gc, int gf, LocalDate d, List<Integer> jc, Map<Integer, Integer> sc, List<Integer> jf, Map<Integer, Integer> sf){
        this.equipaCasa = ec;
        this.equipaFora = ef;
        this.golosCasa = gc;
        this.golosFora = gf;
        this.date = d;
        this.jogadoresCasa = new ArrayList<>(jc);
        this.jogadoresFora = new ArrayList<>(jf);
        this.substituicoesCasa = new HashMap<>(sc);
        this.substitucoesFora = new HashMap<>(sf);
    }

    public int getGolosCasa() {
        return golosCasa;
    }

    public LocalDate getDate() {
        return date;
    }

    public List<Integer> getJogadoresCasa() {
        return jogadoresCasa;
    }

    public List<Integer> getJogadoresFora() {
        return jogadoresFora;
    }

    public void setJogadoresFora(List<Integer> jogadoresFora) {
        this.jogadoresFora = jogadoresFora;
    }

    public Map<Integer, Integer> getSubstituicoesCasa() {
        return substituicoesCasa;
    }

    public Map<Integer, Integer> getSubstitucoesFora() {
        return substitucoesFora;
    }

    public void setSubstitucoesFora(Map<Integer, Integer> substitucoesFora) {
        this.substitucoesFora = substitucoesFora;
    }

    public void setSubstituicoesCasa(Map<Integer, Integer> substituicoesCasa) {
        this.substituicoesCasa = substituicoesCasa;
    }

    public void setJogadoresCasa(List<Integer> jogadoresCasa) {
        this.jogadoresCasa = jogadoresCasa;
    }

    public void setDate(LocalDate date) {
        this.date = date;
    }

    public int getGolosFora() {
        return golosFora;
    }

    public void setGolosFora(int golosFora) {
        this.golosFora = golosFora;
    }

    public void setGolosCasa(int golosCasa) {
        this.golosCasa = golosCasa;
    }

    public static jogo parse(String input){
        String[] campos = input.split(",");
        String[] data = campos[4].split("-");
        List<Integer> jc = new ArrayList<>();
        List<Integer> jf = new ArrayList<>();
        Map<Integer, Integer> subsC = new HashMap<>();
        Map<Integer, Integer> subsF = new HashMap<>();
        for (int i = 5; i < 16; i++){
            jc.add(Integer.parseInt(campos[i]));
        }
        for (int i = 16; i < 19; i++){
            String[] sub = campos[i].split("->");
            subsC.put(Integer.parseInt(sub[0]), Integer.parseInt(sub[1]));
        }
        for (int i = 19; i < 30; i++){
            jf.add(Integer.parseInt(campos[i]));
        }
        for (int i = 30; i < 33; i++){
            String[] sub = campos[i].split("->");
            subsF.put(Integer.parseInt(sub[0]), Integer.parseInt(sub[1]));
        }
        return new jogo(campos[0], campos[1], Integer.parseInt(campos[2]), Integer.parseInt(campos[3]),
                LocalDate.of(Integer.parseInt(data[0]), Integer.parseInt(data[1]), Integer.parseInt(data[2])),
                jc, subsC, jf, subsF);
    }

    public String toString() {
        return  "Jogo:" + equipaCasa + " - " + equipaFora
        + " -> " + substituicoesCasa.toString()
        + " -> " + substitucoesFora.toString();
    }


    public int apreTeam(equipa team){
        return (team.getTitulares().stream().mapToInt(jogador::calculaAtributos).sum())/11;
    }

    public int numAvancados(equipa team){
        return (int)(team.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("avancado")).count());
    }

    public avancado getAvancado(equipa team,int idx){
        List <jogador> temp = new ArrayList<>();
        temp = team.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("avancado")).collect(Collectors.toList());
        avancado retorn = new avancado();
        retorn = (avancado) temp.get(idx);
        return retorn;
    }

    public int numMedios(equipa team){
        return (int)(team.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("medio")).count());
    }

    public medio getMedio(equipa team,int idx){
        List <jogador> temp = new ArrayList<>();
        temp = team.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("medio")).collect(Collectors.toList());
        medio retorn = new medio();
        retorn = (medio) temp.get(idx);
        return retorn;
    }

    public int numDefesas(equipa team){
        return (int)(team.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("defesa")).count());
    }

    public defesa getDefesa(equipa team,int idx){
        List <jogador> temp = new ArrayList<>();
        temp = team.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("defesa")).collect(Collectors.toList());
        defesa retorn = new defesa();
        retorn = (defesa) temp.get(idx);
        return retorn;
    }


    public int confrontoAvancadoMedio(avancado av,medio med){
        int probabAvancado = (av.getVelocidade()+av.getDestreza())/2;
        int probabMedio = (med.getVelocidade()+med.getRecupBola())/2;

        int resultado = (int)(Math.random() * (probabAvancado+probabMedio));
        if(resultado>=0 && resultado<probabAvancado) return 1;
        else return 0;
    }

    public int confrontoAvancadoDefesa(avancado av,defesa def){
        int probabAvancado = (av.getVelocidade()+av.getDestreza())/2;
        int probabDefesa = def.getCorte();

        int resultado = (int)(Math.random() * (probabAvancado+probabDefesa));
        if(resultado>=0 && resultado<probabAvancado) return 1;
        else return 0;
    }

    public int verificaGolo(avancado av,gk keeper,int prob){
        int probabAvancado = av.getRemate();
        int probabGK = (keeper.getElasticidade()+keeper.getDestreza())/2;

        int resultado = (int)(Math.random() * (probabAvancado+probabGK));
        int marcar = (int)( Math.random() * 100);
        if(resultado>=0 && resultado<probabAvancado && marcar>=prob) return 1;
        else return 0;
    }

    public int verificaPenalti(avancado av,gk keeper){
        int probabAvancado = av.getPenalti();
        int probabGK = (keeper.getElasticidade()+keeper.getDestreza())/2;

        int resultado = (int)(Math.random() * (probabAvancado+probabGK));
        if(resultado>=0 && resultado<probabAvancado) return 1;
        else return 0;
    }

    public List<Integer> getNumCam(equipa team){
        List<Integer> tshr = team.getTitulares().stream().map(jogador -> jogador.getInfoJogador().getNumCamisola()).collect(Collectors.toList());
        return tshr;
    }


    public jogo confrontoEntreTeams(equipa team1, equipa team2){
        Scanner scan = new Scanner(System.in);
        int apreTeam1 = apreTeam(team1);
        int aprTeam2 = apreTeam(team2);
        int oportunidadeJogo;
        int penalti;
        avancado avan = new avancado();
        medio md = new medio();
        defesa df = new defesa();
        gk keeper = new gk();

        int numAv,numMed,numDef;
        int whichA, whichM,whichD;

        jogo game = new jogo();


        System.out.println("------------------------------ Primeira Parte ------------------------------");
        for(int i = 0,notGolo = 30;i < 9;i++,notGolo += 2){
            oportunidadeJogo = (int) (Math.random() * (apreTeam1+aprTeam2));
            if(oportunidadeJogo>=0 && oportunidadeJogo<apreTeam1){
                numAv = numAvancados(team1);
                numMed = numMedios(team2);
                numDef = numDefesas(team2);

                whichA = (int)(Math.random() * numAv);
                avan = getAvancado(team1,whichA);

                whichM = (int)(Math.random() * numMed);
                md = getMedio(team1,whichM);

                whichD = (int)(Math.random() * numDef);
                df = getDefesa(team1,whichD);

                keeper = (gk)team2.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("gk")).findAny().get();

                if(confrontoAvancadoMedio(avan,md) == 1 && confrontoAvancadoDefesa(avan,df) == 1&& verificaGolo(avan,keeper,notGolo) == 1){ System.out.println("\tGolo para a Equipa " + team1.getInfoEquipa().getNameEq() + ": " +avan.getInfoJogador().getNome());game.golosCasa++;}


                penalti = (int) (Math.random() * 150);
                if(penalti==0){ System.out.println("\tPenalti para o Jogador: "+avan.getInfoJogador().getNome()); if(verificaPenalti(avan,keeper) == 1){ System.out.println("\tGolo de Penalti!!!"); game.golosCasa++; }else System.out.println("\tE falhou um penalti fácil!");}

            }
            else{
                numAv = numAvancados(team2);
                numMed = numMedios(team1);
                numDef = numDefesas(team1);

                whichA = (int)(Math.random() * numAv);
                avan = getAvancado(team2,whichA);

                whichM = (int)(Math.random() * numMed);
                md = getMedio(team1,whichM);

                whichD = (int)(Math.random() * numDef);
                df = getDefesa(team1,whichD);

                keeper = (gk)team1.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("gk")).findAny().get();

                if(confrontoAvancadoMedio(avan,md) == 1 && confrontoAvancadoDefesa(avan,df) == 1&& verificaGolo(avan,keeper,notGolo) == 1){ System.out.println("\tGolo para a Equipa " + team2.getInfoEquipa().getNameEq() + ": " +avan.getInfoJogador().getNome()); game.golosFora++;}

                penalti = (int) (Math.random() * 150);
                if(penalti==0){ System.out.println("\tPenalti para o Jogador: "+avan.getInfoJogador().getNome()); if(verificaPenalti(avan,keeper) == 1){ System.out.println("\tGolo de Penalti!!!");game.golosFora++; }else System.out.println("\tE falhou um penalti fácil!");}
            }

        }
        System.out.println("\nCasa : "+game.golosCasa + "  ||||  Fora: " +game.golosFora);
        System.out.println("\nInsira ENTER para continuar");
        scan.nextLine();



        System.out.println("\n------------------------------ Segunda Parte ------------------------------");
        for(int j = 0,notGolo1 = 50;j < 9;j++,notGolo1 += 2){
            oportunidadeJogo = (int) (Math.random() * (apreTeam1+aprTeam2));
            if(oportunidadeJogo>=0 && oportunidadeJogo<apreTeam1){
                numAv = numAvancados(team1);
                numMed = numMedios(team2);
                numDef = numDefesas(team2);

                whichA = (int)(Math.random() * numAv);
                avan = getAvancado(team1,whichA);

                whichM = (int)(Math.random() * numMed);
                md = getMedio(team1,whichM);

                whichD = (int)(Math.random() * numDef);
                df = getDefesa(team1,whichD);

                keeper = (gk)team2.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("gk")).findAny().get();

                if(confrontoAvancadoMedio(avan,md) == 1 && confrontoAvancadoDefesa(avan,df) == 1&& verificaGolo(avan,keeper,notGolo1) == 1) {
                    System.out.println("\tGolo para a Equipa " + team1.getInfoEquipa().getNameEq() + ": " +avan.getInfoJogador().getNome());
                    game.golosCasa++;
                }

                penalti = (int) (Math.random() * 150);
                if(penalti==0){
                    System.out.println("\tPenalti para o Jogador: "+avan.getInfoJogador().getNome());
                    if(verificaPenalti(avan,keeper) == 1){ System.out.println("\tGolo de Penalti!!!");game.golosCasa++;}
                    else System.out.println("\tE falhou um penalti fácil!");
                }

            }
            else{
                numAv = numAvancados(team2);
                numMed = numMedios(team1);
                numDef = numDefesas(team1);

                whichA = (int)(Math.random() * numAv);
                avan = getAvancado(team2,whichA);

                whichM = (int)(Math.random() * numMed);
                md = getMedio(team1,whichM);

                whichD = (int)(Math.random() * numDef);
                df = getDefesa(team1,whichD);

                keeper = (gk)team1.getTitulares().stream().filter(jogador -> jogador.getClass().getSimpleName().equals("gk")).findAny().get();

                if(confrontoAvancadoMedio(avan,md) == 1 && confrontoAvancadoDefesa(avan,df) == 1&& verificaGolo(avan,keeper,notGolo1) == 1){
                    System.out.println("\tGolo para a Equipa " + team2.getInfoEquipa().getNameEq() + ":" +avan.getInfoJogador().getNome());
                    game.golosFora++;
                }

                penalti = (int) (Math.random() * 150);
                if(penalti == 0){ System.out.println("\tPenalti para o Jogador: "+avan.getInfoJogador().getNome()); if(verificaPenalti(avan,keeper) == 1){
                    System.out.println("\tGolo de Penalti!!!"); game.golosFora++; } else System.out.println("\tE falhou um penalti fácil!"); }
            }

        }
        System.out.println("\nCasa : "+game.golosCasa + "  ||||  Fora: " +game.golosFora);
        System.out.println("\nInsira ENTER para continuar");
        scan.nextLine();


        game.equipaCasa = team1.getInfoEquipa().getNameEq();
        game.equipaFora = team2.getInfoEquipa().getNameEq();
        game.jogadoresCasa = getNumCam(team1);
        game.jogadoresFora = getNumCam(team2);

        return game;
    }
    
}
