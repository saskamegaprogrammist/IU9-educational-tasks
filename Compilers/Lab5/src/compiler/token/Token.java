package compiler.token;

import compiler.Fragment;
import compiler.Position;
import compiler.Utils;


class Token {
    private Fragment coordinates;
    private Utils.TOKEN_TAG tag;
    protected String attribute;

    public Token(Utils.TOKEN_TAG tag, Position start, Position end) {
        this.coordinates = new Fragment(start, end);
        this.tag = tag;
    }

    protected void setAttribute(String attribute) {
    }

    @Override
    public String toString() {
        return tag + " " + coordinates.toString();
    }
}
