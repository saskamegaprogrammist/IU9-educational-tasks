package compiler.token;

import compiler.Position;
import compiler.Utils;

public class IdentToken extends Token {
    private String ident;
    public IdentToken(String ident, Position start, Position end) {
        super(Utils.TOKEN_TAG.IDENT, start, end);
        this.ident = ident;
    }

    @Override
    public String toString() {
        return super.toString() + ": " + ident;
    }
}