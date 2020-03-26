package compiler;

import compiler.token.IdentToken;
import jdk.nashorn.internal.parser.Token;

import java.util.ArrayList;
import java.util.Map;

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
