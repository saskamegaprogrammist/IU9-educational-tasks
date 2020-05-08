package compiler.token;

import compiler.Position;
import compiler.Utils;

public class IdentToken extends Token {
    private String attribute;
    public IdentToken(String ident, Position start, Position end) {
        super(Utils.TOKEN_TAG.IDENT, start, end);
        this.setAttribute(ident);
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