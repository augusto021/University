package src;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

import static java.lang.Integer.parseInt;

public class userInt {
    private menu display;
    private equipas log;

    public static void main(String[] args) {
        new userInt().start();
    }

    private userInt(){
        String[] menuDisplay = {"ShowAllTeams","ShowTeam","ShowPlayer","modifyPlayer","GradePlayer","AddPlayerTeam","ChangePlayerTeam","MakeTeam","Play","Quit"};
        this.display = new menu(menuDisplay);
    }

    private void start(){
        equipas log = new equipas();
        Scanner scan = new Scanner(System.in);
        System.out.println("\n\t\t\t----------------Projecto prático de Programação Orientada aos Objectos----------------");
        System.out.println("\n\nBem vindo ao projeto do grupo 64 no qual usufruir de um sistema de gestão e simulação de equipas de futebol.\nDe seguida irá ter a oportunidade de carregar um ficheiro do sistema no qual já tem equipas e jogos definidos.");
        System.out.println("Porém terá a a chance de adicionar tanto como equipas como jogos em qualquer ocasião.");
        System.out.println("\nDeseja carregar o ficheiro existente? [s/n]");
        String resposta = scan.nextLine();

        while (!resposta.equals("s") && !resposta.equals("n")){
            System.out.println("Por favor insira [s/n]...");
            resposta = scan.nextLine();
        }

        if(resposta.equals("s")){
            this.log = log.loadFile();
        }
        else this.log = log;

        do{
            display.bootUp();
            switch (display.getCommands()){
                case "ShowAllTeams": showAllTeams();break;
                case "ShowTeam": showTeam(); break;
                case "ShowPlayer": showPlayer(); break;
                case "modifyPlayer": modifyPlayer(); break;
                case "GradePlayer": estimatePlayer(); break;
                case "AddPlayerTeam": addPlayerTeam(); break;
                case "ChangePlayerTeam": changePlayerTeam(); break;
                case "MakeTeam": makeTeam(); break;
                case "Play":
                    play();
                    break;

            }
        }while (!display.getCommands().equals("Quit"));


    }

    private void changePlayerTeam(){
        Scanner scan = new Scanner(System.in);
        System.out.println("Indique o nome do Jogador: ");
        String name = scan.nextLine();
        equipa temp = new equipa();
        jogador jog = new jogador();
        equipa old = new equipa();

        if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){
            old = this.log.getTeams().stream().filter(equipa -> equipa.getTitulares().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get();
            jog = this.log.getTeams().stream().filter(equipa -> equipa.getTitulares().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getTitulares().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();
            old.getTitulares().remove(jog);
            System.out.println("Indique o nome da Equipa para qual quer mudar o Jogador: ");
            String team = scan.nextLine();

            if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getInfoEquipa().getNameEq().equals(team))){
                temp = this.log.getTeams().stream().filter(equipa -> equipa.getInfoEquipa().getNameEq().equals(team)).findAny().get();
                System.out.println("Deseja adicionar aos Titulares ou Suplentes?");
                String resposta = scan.nextLine();
                if(resposta.equals("Titulares")){
                    if(temp.getTitulares().stream().count() < 11){ jog.getInfoJogador().setEquipa(team); jog.getInfoJogador().getHistorial().add(team); temp.getTitulares().add(jog); }
                    else System.out.println("A Equipa Titular não tem espaço para adicionar outro Jogador.");
                }
                if(resposta.equals("Suplentes")){
                    if(temp.getSuplentes().stream().count() < 5){ jog.getInfoJogador().setEquipa(team); temp.getSuplentes().add(jog);jog.getInfoJogador().getHistorial().add(team); }
                    else System.out.println("A Equipa Suplente não tem espaço para adicionar outro Jogador.");
                }
            }
            else System.out.println("A Equipa inserida não existe.");
        }


        else if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getSuplentes().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){
            old = this.log.getTeams().stream().filter(equipa -> equipa.getSuplentes().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get();
            jog = this.log.getTeams().stream().filter(equipa -> equipa.getSuplentes().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getSuplentes().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();

            old.getSuplentes().remove(jog);
            System.out.println("Indique o nome da Equipa para qual quer mudar o Jogador: ");
            String team = scan.nextLine();

            if(log.getTeams().stream().anyMatch(equipa -> equipa.getInfoEquipa().getNameEq().equals(team))){
                temp = log.getTeams().stream().filter(equipa -> equipa.getInfoEquipa().getNameEq().equals(team)).findAny().get();
                System.out.println("Deseja adicionar aos Titulares ou Suplentes?");
                String resposta = scan.nextLine();
                if(resposta.equals("Titulares")){
                    if(temp.getTitulares().stream().count() < 11){ jog.getInfoJogador().setEquipa(team); temp.getTitulares().add(jog); jog.getInfoJogador().getHistorial().add(team); }
                    else System.out.println("A Equipa Titular não tem espaço para adicionar outro Jogador.");
                }
                if(resposta.equals("Suplentes")){
                    if(temp.getSuplentes().stream().count() < 5){ jog.getInfoJogador().setEquipa(team); temp.getSuplentes().add(jog); jog.getInfoJogador().getHistorial().add(team); }
                    else System.out.println("A Equipa Suplente não tem espaço para adicionar outro Jogador.");
                }
            }
            else System.out.println("A Equipa inserida não existe.");

        }
        else System.out.println("Não existe o Jogador especificado.");

    }

    private void play(){
        jogo nov = new jogo();
        jogo show = this.log.getJogos().get(0);
        showGa(show,1);
        System.out.println("\n\nBem vindo ao módulo relacionado com os Jogos.\nNesta parte pode observar jogos anteriormente efetuados e planear jogos entre duas equipas.\n\n| ShowGame  ---------- Com este comando pode ver no ecrâ os jogos que fazem parte do Log \n| Play      ---------- Este comando permite simular o resultado entre o confronto de duas equipas e adicioná-lo ao Log existente\n");


        Scanner scan = new Scanner(System.in);
        String resposta = scan.nextLine();

        while(!resposta.equals("Play") && !resposta.equals("ShowGame")){
            System.out.println("Insira uma opção válida.");
            resposta = scan.nextLine();
        }

        if(resposta.equals("Play")){

        System.out.println("\nIndique o nome da Equipa da Casa ");
        String team1 = scan.nextLine();

        System.out.println("\nIndique o nome da Equipa de Fora ");
        String team2 = scan.nextLine();

        if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getInfoEquipa().getNameEq().equals(team1)) && this.log.getTeams().stream().anyMatch(equipa -> equipa.getInfoEquipa().getNameEq().equals(team2))){
            this.log.getJogos().add(nov.confrontoEntreTeams(this.log.getTeams().stream().filter(equipa -> equipa.getInfoEquipa().getNameEq().equals(team1)).findAny().get(),this.log.getTeams().stream().filter(equipa -> equipa.getInfoEquipa().getNameEq().equals(team2)).findAny().get()));
        }
        else System.out.println("Insira Equipas existentes.");}
        if(resposta.equals("ShowGame")){
            System.out.println("\nIndique o número do Jogo: ");
            int num = Integer.parseInt(scan.nextLine());
            showGa(this.log.getJogos().get(num-1),num);

        }


    }

    public void showGa(jogo game,int num){
        System.out.println("\n\n\t\t\t\t//*********  Bem-vindo ao Log de Jogos  *********\\\\\n\n----------------------------------------Jogo " +num+"----------------------------------------");
        System.out.println("\t           Equipa Casa                |                Equipa Fora\n");
        System.out.println("\t\t\t"+game.getEquipaCasa() + "                               "+game.getEquipaFora());
        System.out.println("\nPontuação Final: "+game.getGolosCasa() +" vs "+game.getGolosFora());
        System.out.println("Jogadores da Casa: "+game.getJogadoresCasa()+"\nJogadores de Fora: "+game.getJogadoresFora());
        System.out.println("Substituições da Casa: "+game.getSubstituicoesCasa()+"\nSubstituições de Fora: "+game.getSubstitucoesFora());

    }


    private void estimatePlayer(){
        jogador jog = new jogador();

        System.out.println("\nIndique o nome do Jogador: ");
        Scanner scan = new Scanner(System.in);
        String name = scan.nextLine();
        if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){

            jog = this.log.getTeams().stream().filter(equipa -> equipa.getTitulares().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getTitulares().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();
            Class c = jog.getClass();
            switch(c.getSimpleName()){
                case "lateral":
                    lateral lat = (lateral) jog;
                    System.out.println(jog);
                    System.out.println("A apreciação global do Jogador é: "+ lat.calculaAtributos());
                    break;
                case "avancado":
                    avancado av = (avancado) jog;
                    System.out.println(jog);
                    System.out.println("A apreciação global do Jogador é: "+ av.calculaAtributos());
                    break;
                case "medio":
                    medio md = (medio) jog;
                    System.out.println(jog);
                    System.out.println("A apreciação global do Jogador é: "+ md.calculaAtributos());
                    break;
                case "defesa":
                    defesa df = (defesa) jog;
                    System.out.println(jog);
                    System.out.println("A apreciação global do Jogador é: "+ df.calculaAtributos());
                    break;
                case "gk":
                    gk safer = (gk) jog;
                    System.out.println(jog);
                    System.out.println("A apreciação global do Jogador é: "+ safer.calculaAtributos());
                    break;
                default: break;
            }
        }
        else if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getSuplentes().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){
            jog = this.log.getTeams().stream().filter(equipa -> equipa.getSuplentes().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getSuplentes().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();

            Class cS = jog.getClass();
            switch(cS.getSimpleName()) {
                case "lateral":
                    lateral lat1 = (lateral) jog;
                    System.out.println("A apreciação global do Jogador é: " + lat1.calculaAtributos());
                    break;
                case "avancado":
                    avancado av1 = (avancado) jog;
                    System.out.println("A apreciação global do Jogador é: " + av1.calculaAtributos());
                    break;
                case "medio":
                    medio md1 = (medio) jog;
                    System.out.println("A apreciação global do Jogador é: " + md1.calculaAtributos());
                    break;
                case "defesa":
                    defesa df1 = (defesa) jog;
                    System.out.println("A apreciação global do Jogador é: " + df1.calculaAtributos());
                    break;
                case "gk":
                    gk safer1 = (gk) jog;
                    System.out.println("A apreciação global do Jogador é: " + safer1.calculaAtributos());
                    break;
                default:
                    break;
            }
        }
        else System.out.println("Não existe o Jogador especificado.");

    }

    private void showAllTeams(){
        List<String> names = this.log.getTeams().stream().map(equipa -> equipa.getInfoEquipa().getNameEq()).collect(Collectors.toList());
        System.out.println("\n__________Equipas do Log__________\n");
        if(names.size() != 0){
        for(String name : names){
            System.out.println("-> "+name);
        }}
        else System.out.println("Não existem Equipas criadas no Log.\nPor favor adicione com o comando \"MakeTeam\"");
    }

    private void showTeam(){
        System.out.println("\nIndique o nome da Equipa: ");
        Scanner scan = new Scanner(System.in);
        String teamName = scan.nextLine();
        if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getInfoEquipa().getNameEq().equals(teamName))){
            System.out.println(this.log.getTeams().stream().filter(equipa -> equipa.getInfoEquipa().getNameEq().equals(teamName)).findAny().get());
        }
        else System.out.println("A Equipa inserida não existe.");
    }

    private void showPlayer(){
        jogador jog = new jogador();
        System.out.println("\nIndique o nome do Jogador: ");
        Scanner scan = new Scanner(System.in);
        String name = scan.nextLine();
        if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){
            jog = this.log.getTeams().stream().filter(equipa -> equipa.getTitulares().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getTitulares().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();
            System.out.println(jog);
        }
        else if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getSuplentes().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){
            jog = this.log.getTeams().stream().filter(equipa -> equipa.getSuplentes().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getSuplentes().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();
            System.out.println(jog);
        }
        else System.out.println("Não existe o Jogador especificado.");

    }

    private void makeTeam(){
        Scanner scan = new Scanner(System.in);

        ArrayList<String> historial = new ArrayList<>();
        System.out.println("\nInsira o nome da Equipa: ");
        String nameTeam = scan.nextLine();
        System.out.println("\nInsira o nome do Treinador: ");
        String coach = scan.nextLine();

        ArrayList<jogador> tit = new ArrayList<>();
        ArrayList<jogador> sup = new ArrayList<>();
        idEquipa idE = new idEquipa(nameTeam,coach);


        System.out.println("\nTitulares \nIndique quantos pretende inserir até um máximo de 11: ");
        int num = parseInt(scan.nextLine());
        String inputJog;
        String[] skills;
        for(int i = 0;i < num;i++){
            System.out.println("\nInsira o Jogador: ");
            System.out.println("\tSintaxe-> Guarda-Redes:Pedro Miguel Marques,34,12,74,35,12,85,34,85,35");
            inputJog = scan.nextLine();
            String[] tokens = inputJog.split(":");
            switch (tokens[0]){
                case "Lateral":
                    skills = tokens[1].split(",");

                    String[] finalSkills = skills;
                    if(tit.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkills[0]))){
                        System.out.println("Este Jogador já existe."); i--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJ = new idJogador(skills[0],nameTeam,"Titular",Integer.parseInt(skills[1]),historial);

                    lateral jog1 = new lateral(Integer.parseInt(skills[2]),Integer.parseInt(skills[3]),Integer.parseInt(skills[4]),Integer.parseInt(skills[5]),
                            Integer.parseInt(skills[6]),Integer.parseInt(skills[7]),Integer.parseInt(skills[8]),idJ,Integer.parseInt(skills[9]));
                    
                    tit.add(jog1);
                    }
                    break;
                case "Avancado":
                    skills = tokens[1].split(",");

                    String[] finalSkills1 = skills;
                    if(tit.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkills1[0]))){
                        System.out.println("Este Jogador já existe."); i--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJ1 = new idJogador(skills[0],nameTeam,"Titular",Integer.parseInt(skills[1]),historial);

                    avancado jog2 = new avancado(Integer.parseInt(skills[2]),Integer.parseInt(skills[3]),Integer.parseInt(skills[4]),Integer.parseInt(skills[5]),
                            Integer.parseInt(skills[6]),Integer.parseInt(skills[7]),Integer.parseInt(skills[8]),idJ1,Integer.parseInt(skills[9]));

                    tit.add(jog2);
                    }
                    break;
                case "Defesa":
                    skills = tokens[1].split(",");

                    String[] finalSkills2 = skills;
                    if(tit.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkills2[0]))){
                        System.out.println("Este Jogador já existe."); i--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJ2 = new idJogador(skills[0],nameTeam,"Titular",Integer.parseInt(skills[1]),historial);

                    defesa jog3 = new defesa(Integer.parseInt(skills[2]),Integer.parseInt(skills[3]),Integer.parseInt(skills[4]),Integer.parseInt(skills[5]),
                            Integer.parseInt(skills[6]),Integer.parseInt(skills[7]),Integer.parseInt(skills[8]),idJ2,Integer.parseInt(skills[9]));

                    tit.add(jog3);
                    }
                    break;
                case "Medio":
                    skills = tokens[1].split(",");

                    String[] finalSkills3 = skills;
                    if(tit.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkills3[0]))){
                        System.out.println("Este Jogador já existe."); i--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJ3 = new idJogador(skills[0],nameTeam,"Titular",Integer.parseInt(skills[1]),historial);

                    medio jog4 = new medio(Integer.parseInt(skills[2]),Integer.parseInt(skills[3]),Integer.parseInt(skills[4]),Integer.parseInt(skills[5]),
                            Integer.parseInt(skills[6]),Integer.parseInt(skills[7]),Integer.parseInt(skills[8]),idJ3,Integer.parseInt(skills[9]));

                    tit.add(jog4);
                    }
                    break;
                case "Guarda-Redes":
                    skills = tokens[1].split(",");

                    String[] finalSkills4 = skills;
                    if(tit.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkills4[0]))){
                        System.out.println("Este Jogador já existe."); i--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJ4 = new idJogador(skills[0],nameTeam,"Titular",Integer.parseInt(skills[1]),historial);

                    gk jog5 = new gk(Integer.parseInt(skills[2]),Integer.parseInt(skills[3]),Integer.parseInt(skills[4]),Integer.parseInt(skills[5]),
                            Integer.parseInt(skills[6]),Integer.parseInt(skills[7]),Integer.parseInt(skills[8]),idJ4,Integer.parseInt(skills[9]));

                    tit.add(jog5);
                    }
                    break;
                default:
                    System.out.println("A posição " + tokens[0] + " não é uma posição de Jogador válida.");
                    i--;
            }
        }


        System.out.println("\nSuplentes \nIndique quantos pretende inserir até um máximo de 9: ");
        int suplentes = Integer.parseInt(scan.nextLine());
        String inputJogSup;
        String[] skillsSup;
        for(int j = 0;j < suplentes;j++){
            System.out.println("\nInsira o Jogador: ");
            inputJogSup = scan.nextLine();
            String[] tokens1 = inputJogSup.split(":");
            switch (tokens1[0]){
                case "Lateral":
                    skillsSup = tokens1[1].split(",");

                    String[] finalSkillsSup = skillsSup;
                    if(sup.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkillsSup[0]))){
                        System.out.println("Este Jogador já existe."); j--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJ = new idJogador(skillsSup[0],nameTeam,"Suplente",Integer.parseInt(skillsSup[1]),historial);

                    lateral jogSup1 = new lateral(Integer.parseInt(skillsSup[2]),Integer.parseInt(skillsSup[3]),Integer.parseInt(skillsSup[4]),Integer.parseInt(skillsSup[5]),
                            Integer.parseInt(skillsSup[6]),Integer.parseInt(skillsSup[7]),Integer.parseInt(skillsSup[8]),idJ,Integer.parseInt(skillsSup[9]));

                    sup.add(jogSup1);
                    }
                    break;
                case "Avancado":
                    skillsSup = tokens1[1].split(",");

                    String[] finalSkillsSup1 = skillsSup;
                    if(sup.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkillsSup1[0]))){
                        System.out.println("Este Jogador já existe."); j--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJSup1 = new idJogador(skillsSup[0],nameTeam,"Suplente",Integer.parseInt(skillsSup[1]),historial);

                    avancado jogSup2 = new avancado(Integer.parseInt(skillsSup[2]),Integer.parseInt(skillsSup[3]),Integer.parseInt(skillsSup[4]),Integer.parseInt(skillsSup[5]),
                            Integer.parseInt(skillsSup[6]),Integer.parseInt(skillsSup[7]),Integer.parseInt(skillsSup[8]),idJSup1,Integer.parseInt(skillsSup[9]));

                    sup.add(jogSup2);
                    }
                    break;
                case "Defesa":
                    skillsSup = tokens1[1].split(",");

                    String[] finalSkillsSup2 = skillsSup;
                    if(sup.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkillsSup2[0]))){
                        System.out.println("Este Jogador já existe."); j--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJSup2 = new idJogador(skillsSup[0],nameTeam,"Suplente",Integer.parseInt(skillsSup[1]),historial);

                    defesa jogSup3 = new defesa(Integer.parseInt(skillsSup[2]),Integer.parseInt(skillsSup[3]),Integer.parseInt(skillsSup[4]),Integer.parseInt(skillsSup[5]),
                            Integer.parseInt(skillsSup[6]),Integer.parseInt(skillsSup[7]),Integer.parseInt(skillsSup[8]),idJSup2,Integer.parseInt(skillsSup[9]));

                    sup.add(jogSup3);
                    }
                    break;
                case "Medio":
                    skillsSup = tokens1[1].split(",");

                    String[] finalSkillsSup3 = skillsSup;
                    if(sup.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkillsSup3[0]))){
                        System.out.println("Este Jogador já existe."); j--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJSup3 = new idJogador(skillsSup[0],nameTeam,"Suplente",Integer.parseInt(skillsSup[1]),historial);

                    medio jogSup4 = new medio(Integer.parseInt(skillsSup[2]),Integer.parseInt(skillsSup[3]),Integer.parseInt(skillsSup[4]),Integer.parseInt(skillsSup[5]),
                            Integer.parseInt(skillsSup[6]),Integer.parseInt(skillsSup[7]),Integer.parseInt(skillsSup[8]),idJSup3,Integer.parseInt(skillsSup[9]));

                    sup.add(jogSup4);
                    }
                    break;
                case "Guarda-Redes":
                    skillsSup = tokens1[1].split(",");

                    String[] finalSkillsSup4 = skillsSup;
                    if(sup.stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(finalSkillsSup4[0]))){
                        System.out.println("Este Jogador já existe."); j--;
                    }
                    else{
                    historial = new ArrayList<>();
                    historial.add(nameTeam);
                    idJogador idJSup4 = new idJogador(skillsSup[0],nameTeam,"Suplente",Integer.parseInt(skillsSup[1]),historial);

                    gk jogSup5 = new gk(Integer.parseInt(skillsSup[2]),Integer.parseInt(skillsSup[3]),Integer.parseInt(skillsSup[4]),Integer.parseInt(skillsSup[5]),
                            Integer.parseInt(skillsSup[6]),Integer.parseInt(skillsSup[7]),Integer.parseInt(skillsSup[8]),idJSup4,Integer.parseInt(skillsSup[9]));

                    sup.add(jogSup5);
                    }
                    break;
                default:
                    System.out.println("A posição " + tokens1[0] + " não é uma posição de Jogador válida.");
                    j--;
            }


        }

        equipa eq = new equipa(idE,tit,sup);
        this.log.getTeams().add(eq);
        System.out.println("Equipa criada com sucesso!!");
    }

    private void modifyPlayer(){
        jogador jog = new jogador();
        System.out.println("Indique o nome do Jogador: ");
        Scanner scan = new Scanner(System.in);
        String name = scan.nextLine();
        if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){
            jog = this.log.getTeams().stream().filter(equipa -> equipa.getTitulares().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getTitulares().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();

            System.out.println("O Jogador existe.\nIndique quantos atributos pretende modificar: ");
            int n = parseInt(scan.nextLine());
            String atri;
            String[] atributos;
            for(int k = 0;k<n;k++){
                System.out.println("Insira o novo atributo: ");
                atri = scan.nextLine();
                atributos = atri.split(":");

                switch (atributos[0]){
                    case "Destreza":
                        jog.setDestreza(parseInt(atributos[1]));
                        break;
                    case "Impulsao":
                        jog.setImpulsao(parseInt(atributos[1]));
                        break;
                    case "Velocidade":
                        jog.setVelocidade(parseInt(atributos[1]));
                        break;
                    case "Resistencia":
                        jog.setResistencia(parseInt(atributos[1]));
                        break;
                    case "Remate":
                        jog.setRemate(parseInt(atributos[1]));
                        break;
                    case "Passe":
                        jog.setPasse(parseInt(atributos[1]));
                        break;
                    case "Cabeca":
                        jog.setCabeça(parseInt(atributos[1]));
                        break;
                    default:
                        System.out.println("Insira um atributo válido");k--;

                }
            }
            System.out.println("Atributos do Jogador mudados com sucesso.");
        }


        else if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getSuplentes().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name)))){
            jog = this.log.getTeams().stream().filter(equipa -> equipa.getSuplentes().
                    stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(name))).findAny().get().getSuplentes().stream().
                    filter(jogador -> jogador.getInfoJogador().getNome().equals(name)).findAny().get();

            System.out.println("O Jogador existe.\nIndique quantos atributos pretende modificar: ");
            int n = parseInt(scan.nextLine());
            String atri1;
            String[] atributos1;
            for(int k = 0;k<n;k++){
                System.out.println("Insira o novo atributo: ");
                atri1 = scan.nextLine();
                atributos1 = atri1.split(":");

                switch (atributos1[0]){
                    case "Destreza":
                        jog.setDestreza(parseInt(atributos1[1]));
                        break;
                    case "Impulsao":
                        jog.setImpulsao(parseInt(atributos1[1]));
                        break;
                    case "Velocidade":
                        jog.setVelocidade(parseInt(atributos1[1]));
                        break;
                    case "Resistencia":
                        jog.setResistencia(parseInt(atributos1[1]));
                        break;
                    case "Remate":
                        jog.setRemate(parseInt(atributos1[1]));
                        break;
                    case "Passe":
                        jog.setPasse(parseInt(atributos1[1]));
                        break;
                    case "Cabeca":
                        jog.setCabeça(parseInt(atributos1[1]));
                        break;
                    default:
                        System.out.println("Insira um atributo válido");k--;
                }
            }
            System.out.println("Atributos do Jogador mudados com sucesso.");

        }

        else System.out.println("Não existe o Jogador especificado.");

    }

    private void addPlayerTeam(){
        System.out.println("Indique o nome da Equipa: ");
        Scanner scan = new Scanner(System.in);
        String name = scan.nextLine();
        int op1 = 0,op2 = 0;

        if(this.log.getTeams().stream().anyMatch(equipa -> equipa.getInfoEquipa().getNameEq().equals(name))){
            equipa team = this.log.getTeams().stream().filter(equipa -> equipa.getInfoEquipa().getNameEq().equals(name)).findAny().get();
            if(team.getTitulares().stream().count() == 11){ System.out.println("A equipa Titular desta Equipa já se encontra cheia."); op1++;}
            if(team.getSuplentes().stream().count() == 9){ System.out.println("A equipa Suplente desta Equipa já se econtra cheia."); op2++;}
            if(op1 == 1 && op2 == 1) System.out.println("Não é possível adicionar a esta Equipa uma vez que já se encontra cheia.");
            else{
                System.out.println("Pretende adicionar o Jogador aos Titulares ou Suplentes? ");
                String resposta = scan.nextLine();

                if(resposta.equals("Titulares") && op1 == 0){
                    System.out.println("Insira o jogador: ");
                    String inputAdd = scan.nextLine();
                    String[] tokensAdd = inputAdd.split(":");
                    switch (tokensAdd[0]){
                        case "Lateral":
                            String[] h = tokensAdd[1].split(",");
                            ArrayList<String> empty = new ArrayList<>();
                            empty.add(name);
                            idJogador idJ = new idJogador(h[0],name,"Titular",parseInt(h[1]),empty);
                            lateral op = new lateral(parseInt(h[2]),parseInt(h[3]),parseInt(h[4]),parseInt(h[5]),parseInt(h[6]),parseInt(h[7]),parseInt(h[8]),idJ,parseInt(h[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(op.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(op);
                            break;
                        case "Avancado":
                            String[] h1 = tokensAdd[1].split(",");
                            ArrayList<String> empty1 = new ArrayList<>();
                            empty1.add(name);
                            idJogador idJ1 = new idJogador(h1[0],name,"Titular",parseInt(h1[1]),empty1);
                            avancado opA = new avancado(parseInt(h1[2]),parseInt(h1[3]),parseInt(h1[4]),parseInt(h1[5]),parseInt(h1[6]),parseInt(h1[7]),parseInt(h1[8]),idJ1,parseInt(h1[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opA.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opA);
                            break;
                        case "Medio":
                            String[] h2 = tokensAdd[1].split(",");
                            ArrayList<String> empty2 = new ArrayList<>();
                            empty2.add(name);
                            idJogador idJ2 = new idJogador(h2[0],name,"Titular",parseInt(h2[1]),empty2);
                            medio opM = new medio(parseInt(h2[2]),parseInt(h2[3]),parseInt(h2[4]),parseInt(h2[5]),parseInt(h2[6]),parseInt(h2[7]),parseInt(h2[8]),idJ2,parseInt(h2[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opM.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opM);
                            break;
                        case "Defesa":
                            String[] h3 = tokensAdd[1].split(",");
                            ArrayList<String> empty3 = new ArrayList<>();
                            empty3.add(name);
                            idJogador idJ3 = new idJogador(h3[0],name,"Titular",parseInt(h3[1]),empty3);
                            defesa opD = new defesa(parseInt(h3[2]),parseInt(h3[3]),parseInt(h3[4]),parseInt(h3[5]),parseInt(h3[6]),parseInt(h3[7]),parseInt(h3[8]),idJ3,parseInt(h3[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opD.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opD);
                            break;
                        case "Guarda-Redes":
                            String[] h4 = tokensAdd[1].split(",");
                            ArrayList<String> empty4 = new ArrayList<>();
                            empty4.add(name);
                            idJogador idJ4 = new idJogador(h4[0],name,"Titular",parseInt(h4[1]),empty4);
                            gk opG = new gk(parseInt(h4[2]),parseInt(h4[3]),parseInt(h4[4]),parseInt(h4[5]),parseInt(h4[6]),parseInt(h4[7]),parseInt(h4[8]),idJ4,parseInt(h4[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opG.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opG);
                            break;
                        default:
                            System.out.println("A posição inserida não é válida.");

                    }
                }

                else if(resposta.equals("Suplentes") && op2 == 0){
                    System.out.println("Insira o jogador: ");
                    String inputAdd = scan.nextLine();
                    String[] tokensAdd = inputAdd.split(":");
                    switch (tokensAdd[0]){
                        case "Lateral":
                            String[] h = tokensAdd[1].split(",");
                            ArrayList<String> empty = new ArrayList<>();
                            empty.add(name);
                            idJogador idJ = new idJogador(h[0],name,"Titular",parseInt(h[1]),empty);
                            lateral op = new lateral(parseInt(h[2]),parseInt(h[3]),parseInt(h[4]),parseInt(h[5]),parseInt(h[6]),parseInt(h[7]),parseInt(h[8]),idJ,parseInt(h[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(op.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(op);
                            break;
                        case "Avancado":
                            String[] h1 = tokensAdd[1].split(",");
                            ArrayList<String> empty1 = new ArrayList<>();
                            empty1.add(name);
                            idJogador idJ1 = new idJogador(h1[0],name,"Titular",parseInt(h1[1]),empty1);
                            avancado opA = new avancado(parseInt(h1[2]),parseInt(h1[3]),parseInt(h1[4]),parseInt(h1[5]),parseInt(h1[6]),parseInt(h1[7]),parseInt(h1[8]),idJ1,parseInt(h1[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opA.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opA);
                            break;
                        case "Medio":
                            String[] h2 = tokensAdd[1].split(",");
                            ArrayList<String> empty2 = new ArrayList<>();
                            empty2.add(name);
                            idJogador idJ2 = new idJogador(h2[0],name,"Titular",parseInt(h2[1]),empty2);
                            medio opM = new medio(parseInt(h2[2]),parseInt(h2[3]),parseInt(h2[4]),parseInt(h2[5]),parseInt(h2[6]),parseInt(h2[7]),parseInt(h2[8]),idJ2,parseInt(h2[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opM.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opM);
                            break;
                        case "Defesa":
                            String[] h3 = tokensAdd[1].split(",");
                            ArrayList<String> empty3 = new ArrayList<>();
                            empty3.add(name);
                            idJogador idJ3 = new idJogador(h3[0],name,"Titular",parseInt(h3[1]),empty3);
                            defesa opD = new defesa(parseInt(h3[2]),parseInt(h3[3]),parseInt(h3[4]),parseInt(h3[5]),parseInt(h3[6]),parseInt(h3[7]),parseInt(h3[8]),idJ3,parseInt(h3[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opD.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opD);
                            break;
                        case "Guarda-Redes":
                            String[] h4 = tokensAdd[1].split(",");
                            ArrayList<String> empty4 = new ArrayList<>();
                            empty4.add(name);
                            idJogador idJ4 = new idJogador(h4[0],name,"Titular",parseInt(h4[1]),empty4);
                            gk opG = new gk(parseInt(h4[2]),parseInt(h4[3]),parseInt(h4[4]),parseInt(h4[5]),parseInt(h4[6]),parseInt(h4[7]),parseInt(h4[8]),idJ4,parseInt(h4[9]));

                            if(team.getTitulares().stream().anyMatch(jogador -> jogador.getInfoJogador().getNome().equals(opG.getInfoJogador().getNome()))) System.out.println("Este Jogador já existe.");
                            else team.getTitulares().add(opG);
                            break;
                        default:
                            System.out.println("A posição inserida não é válida.");

                    }
                }

                else System.out.println("Não foi possível inserir.");


            }
        }

    }
}


