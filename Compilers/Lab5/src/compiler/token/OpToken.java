package compiler.token;

import compiler.Position;
import compiler.Utils;

public class OpToken extends Token {
    protected String attribute;
    public OpToken(String token, Position start, Position end) {
        super(Utils.TOKEN_TAG.OP, start, end);
        this.setAttribute(token);
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
