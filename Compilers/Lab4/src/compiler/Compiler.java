package compiler;

import java.util.ArrayList;

public class Compiler {
    private Scanner scanner;
    private ArrayList<Message> messages;
    private ArrayList<Object> tokens;

    public Compiler() {
        this.scanner = new Scanner();
    }

    public void runLexAn(String programm) {
        scanner.analyzeProgramm(programm);
        this.messages = scanner.getMessages();
        this.tokens = scanner.getTokens();
    }

    public void printTokens() {
        tokens.forEach(System.out::println);
    }
    public void printMessages() {
        messages.forEach(System.out::println);
    }
}
