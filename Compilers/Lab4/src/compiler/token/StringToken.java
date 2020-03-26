package compiler.token;

import compiler.Position;
import compiler.Utils;

public class StringToken extends Token {
    private String string;
    public StringToken(String string,  Position start, Position end) {
        super(Utils.TOKEN_TAG.STRING, start, end);
        this.string = string;
    }

    @Override
    public String toString() {
        return super.toString() + ": " + string;
    }
}