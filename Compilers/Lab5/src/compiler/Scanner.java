package compiler;

import compiler.token.*;
import fautomata.DFA;

import java.util.ArrayList;

public class Scanner {
    private Position position;
    private ArrayList<Message> messages;
    private ArrayList<Object> tokens;
    private String programm;
    private DFA dfa;

    public Scanner(DFA dfa) {
        this.tokens = new ArrayList<>();
        this.messages = new ArrayList<>();
        this.dfa = dfa;
    }

    public void analyzeProgramm(String programm) {
            this.programm = programm;
            this.position = new Position(programm);
            this.iterateProgramm();
    }

    private void iterateProgramm() {
        while (this.position.getCurrentPosition() != -1) {
            int currentState = 0;
            Position start = new Position(position);
            Position current = new Position(position);
            int lastFinal = DFA.wrongState;
            int lastState = DFA.wrongState;
            int finalsCounter = 0;
            while (this.position.getCurrentPosition() != -1) {
                currentState = this.dfa.getTransition(currentState, (char) this.position.getCurrentPosition());
                if (currentState == DFA.wrongState) break;
                lastState = currentState;
                if (this.dfa.isFinal(currentState)) {
                    lastFinal = currentState;
                    finalsCounter=0;
                } else {
                    finalsCounter++;
                }
                this.position.next();
                current = new Position(position, current);
            }
            if (this.dfa.isFinal(lastState)) {
                this.addToken(this.dfa.getFinal(lastState), start);
            } else {
                if (lastFinal == DFA.wrongState) {
                    this.messages.add(new Message("wrong token", true, new Position(this.position)));
                    position.next();
                } else {
                    if (this.dfa.isFinal(lastState)) {
                        this.addToken(this.dfa.getFinal(lastState), start);
                    } else {
                        while (finalsCounter != 0) {
                            current = current.getPrev();
                            finalsCounter--;
                        }
                        this.position = current;
                        this.addToken(this.dfa.getFinal(lastFinal), start);
                    }
                }
            }
        }
    }

    private void addToken(String type, Position start) {
        switch (type) {
            case "KEYWORD":
                this.tokens.add(new KeywordToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                break;
            case "NUMBER":
                this.tokens.add(new NumberToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                break;
            case "OP":
                this.tokens.add(new OpToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                break;
            case "ID":
                this.tokens.add(new IdentToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                break;
            case "COMMENT":
                this.tokens.add(new CommentToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                break;
            case "WS":
                this.tokens.add(new WsToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                break;
            default:
                System.out.println("error");


        }
    }

    public ArrayList<Message> getMessages() {
        return this.messages;
    }

    public ArrayList<Object> getTokens() {
        return this.tokens;
    }

}
