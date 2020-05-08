package compiler;

import compiler.token.HexNumberToken;
import compiler.token.IdentToken;
import compiler.token.NumberToken;
import compiler.token.StringToken;

import java.util.ArrayList;

public class Scanner {
    private Position position;
    private ArrayList<Message> messages;
    private ArrayList<Object> tokens;
    private String programm;

    public Scanner() {
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
            if (this.position.isDigit()) {
                this.position.next();
                while (this.position.isDigit()) {
                    this.position.next();
                }
                this.tokens.add(new NumberToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                continue;
            }
            if (this.position.isHexNumberDelimiter()) {
                this.position.next();
                while (this.position.isHex()) {
                    this.position.next();
                }
                this.tokens.add(new HexNumberToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                continue;
            }
            if (this.position.isStringDelimiter()) {
                this.position.next();
                while (!this.position.isStringDelimiter()) {
                    if (this.position.isStringInnerQuote()) {
                        this.position.next();
                        this.position.next();
                        continue;
                    }
                    if (this.position.isStringNewLineSymbol()) {
                        this.position.next();
                        if (this.position.isNewLine()) {
                            this.position.next();
                        }
                        continue;
//                      this.messages.add(new Message("expected newline in string", true, new Position(this.position)));
                    }
                    if (this.position.isNewLine()) {
                        this.messages.add(new Message("expected end of string", true, new Position(this.position)));
                        break;
                    }
                    this.position.next();
                }
                this.position.next();
                this.tokens.add(new StringToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
                continue;
            }
            if (this.position.isLetter()) {
                this.position.next();
                while (this.position.isLetterOrDigit() || this.position.isHexNumberDelimiter()) {
                    this.position.next();
                }
                this.tokens.add(new IdentToken(programm.substring(start.getIndex(), this.position.getIndex()), start, new Position(this.position)));
            }
        }
    }

    public ArrayList<Message> getMessages() {
        return this.messages;
    }

    public ArrayList<Object> getTokens() {
        return this.tokens;
    }

}
