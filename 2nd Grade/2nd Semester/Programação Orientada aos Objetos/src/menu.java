package src;

import java.util.Arrays;
import java.util.List;
import java.util.Scanner;


public class menu {
    private List<String> commands;
    private String now;

    public menu(String[] commands){
        this.commands = Arrays.asList(commands);
        this.now = "";
    }

    public void bootUp(){
        do{
            imprimeMenu();
            now = verificarNow();
        }while (this.now.equals("Erro"));
    }

    public void imprimeMenu(){
        System.out.println("\n\n//***  Bem-vindo ao Menu Principal  ***\\\\\n");
        for(String c : this.commands){
            System.out.println("| "+c);
        }
    }

    public String verificarNow(){
        String command = "";
        int n = 0;
        Scanner neaw = new Scanner(System.in);
        System.out.println("Função: ");

        try {
            command = neaw.nextLine();
        }catch(Exception e){
            command = "Erro";
        }
        if(command.equals("Erro") || !this.commands.contains(command)){ System.out.println("Opção Inválida."); command = "Erro";}

        return command;
    }

    public String getCommands() { return this.now; }
}

