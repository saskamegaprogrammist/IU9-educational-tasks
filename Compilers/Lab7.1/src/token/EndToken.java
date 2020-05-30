package token;

import lexer.Position;

public class EndToken extends Token {

    public EndToken(Position start, Position end) {
        super(Utils.TOKEN_TAG.END, start, end);
        this.setAttribute(Utils.END_TOKEN);
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