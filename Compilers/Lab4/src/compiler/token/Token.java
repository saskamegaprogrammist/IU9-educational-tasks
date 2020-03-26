package compiler.token;

import compiler.Fragment;
import compiler.Position;
import compiler.Utils;


class Token {
    private Fragment coordinates;
    private Utils.TOKEN_TAG tag;

    public Token(Utils.TOKEN_TAG tag, Position start, Position end) {
        this.coordinates = new Fragment(start, end);
        this.tag = tag;
    }

    @Override
    public String toString() {
        return tag + " " + coordinates.toString();
    }
}
