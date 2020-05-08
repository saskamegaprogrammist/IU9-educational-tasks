package compiler.token;

import compiler.Position;
import compiler.Utils;

public class KeywordToken extends Token {

    protected String attribute;
    public KeywordToken(String token, Position start, Position end) {
        super(Utils.TOKEN_TAG.KEYWORD, start, end);
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
