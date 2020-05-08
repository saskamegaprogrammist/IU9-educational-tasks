package compiler.token;

import compiler.Position;
import compiler.Utils;

public class HexNumberToken extends Token {
    private String attribute;
    public HexNumberToken(String hexnum, Position start, Position end) {
        super(Utils.TOKEN_TAG.HEXNUMBER, start, end);
        this.setAttribute(hexnum);
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
