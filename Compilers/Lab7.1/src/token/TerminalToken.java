package token;

import lexer.Position;

public class TerminalToken extends Token {

    public TerminalToken(String number, Position start, Position end) {
        super(Utils.TOKEN_TAG.TERMINAL, start, end);
        this.setAttribute(number);
    }

    @Override
    protected void setAttribute(String token) {
        super.setAttribute(token);
        this.attribute = token;
    }

    @Override
    public String toString() {
        return super.toString() + ": " + attribute;
    }

}