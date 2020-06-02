package token;

import lexer.Fragment;
import lexer.Position;


public class Token {
    private Fragment coordinates;
    protected Utils.TOKEN_TAG tag;
    protected String attribute;

    public Token(Utils.TOKEN_TAG tag, Position start, Position end) {
        this.coordinates = new Fragment(start, end);
        this.tag = tag;
    }

    protected void setAttribute(String attribute) {
    }

    public String getAttribute() {
        return this.attribute;
    }

    public Utils.TOKEN_TAG getTag() {
        return tag;
    }

    @Override
    public String toString() {
        return tag + " " + coordinates.toString();
    }
}
