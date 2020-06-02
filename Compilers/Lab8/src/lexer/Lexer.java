package lexer;

import token.*;

import java.util.ArrayList;

public class Lexer {

    private Position position;
    private ArrayList<Message> messages;
    private ArrayList<Token> tokens;
    private String programm;

    public Lexer() {
        this.tokens = new ArrayList<>();
        this.messages = new ArrayList<>();
    }

    public void analyzeProgramm(String programm) {
        this.programm = programm;
        this.position = new Position(programm);
        this.iterateProgramm();
    }

    private void iterateProgramm() {
        while (this.position.getCurrentPosition() != -1) {
            while (this.position.isWhiteSpace()) {
                this.position.next();
            }
            Position start = new Position(position);
            if (this.position.isOpenBracket()) {
                this.position.next();
                while (this.position.isWhiteSpace()) {
                    this.position.next();
                }
                if (this.position.isCloseBracket()) {
                    this.messages.add(new Message("neterminal needs a name", true, new Position(this.position)));
                    this.position.next();
                    this.tokens.add(new NeterminalToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                    continue;
                }
                if (this.position.isSmallLetter() || this.position.isDigit() || this.position.isSymbol()) {
                    this.messages.add(new Message("neterminal token name must look like: T1", false, new Position(this.position)));
                    if (this.position.isLetterOrDigit() || this.position.isSymbol()) {
                        while (this.position.isLetterOrDigit() || this.position.isSymbol()) this.position.next();
                    }
                    while (this.position.isWhiteSpace()) {
                        this.position.next();
                    }
                    if (!this.position.isCloseBracket()) {
                        this.messages.add(new Message("token needs close bracket", true, new Position(this.position)));
                    } else {
                        this.position.next();
                    }
                    this.tokens.add(new NeterminalToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                    continue;
                }

                if (this.position.isCapLetter()) {
                    while (this.position.isCapLetter()) this.position.next();
                    if (this.position.isDigit()) {
                        while (this.position.isDigit()) this.position.next();
                    }
                    if (this.position.isSmallLetter() || this.position.isSymbol()) {
                        this.messages.add(new Message("neterminal token name must look like: T1", false, new Position(this.position)));
                        while (this.position.isLetterOrDigit() || this.position.isSymbol()) this.position.next();
                    }
                    while (this.position.isWhiteSpace()) {
                        this.position.next();
                    }
                    if (!this.position.isCloseBracket()) {
                        this.messages.add(new Message("neterminal token needs close bracket", true, new Position(this.position)));
                    } else  {
                        this.position.next();
                    }
                    this.tokens.add(new NeterminalToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                    continue;
                }
                else {
                    this.messages.add(new Message("wrong neterminal or axiom token", true, new Position(this.position)));
                    this.tokens.add(new NeterminalToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                    continue;
                }
            }
            if (this.position.isKeySymbol()){
                this.tokens.add(new OperatorToken(programm.substring(start.getIndex(), this.position.getIndex()+1), start, new Position(this.position)));
                this.position.next();
                continue;
            }
            if (this.position.isEscapeChar()) {
                this.position.next();
                if (this.position.isKeySymbol() || this.position.isCloseBracket() || this.position.isOpenBracket()) {
                    this.tokens.add(new TerminalToken(programm.substring(start.getIndex(), this.position.getIndex()+1), start, new Position(this.position)));
                    this.position.next();
                } else {
                    this.tokens.add(new TerminalToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                }
                continue;
            }
            if (this.position.isCloseBracket()) {
                this.messages.add(new Message("must be escaped", true, new Position(this.position)));
                this.position.next();
                this.tokens.add(new TerminalToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                continue;
            }
            if (this.position.getCurrentPosition() != -1) {
                while ((this.position.isSymbol() || this.position.isLetterOrDigit()) && !this.position.isWhiteSpace() && this.position.getCurrentPosition() != -1) {
                    this.position.next();
                }
                this.tokens.add(new TerminalToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
            }
        }
        this.tokens.add(new EndToken(new Position(this.position), new Position(this.position)));
    }

    public ArrayList<Message> getMessages() {
        return this.messages;
    }

    public ArrayList<Token> getTokens() {
        return this.tokens;
    }

    public void printTokens() {
        tokens.forEach(System.out::println);
    }
    public void printMessages() {
        messages.forEach(System.out::println);
    }

}
