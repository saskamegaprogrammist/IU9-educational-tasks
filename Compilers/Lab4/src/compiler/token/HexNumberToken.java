package compiler.token;

import compiler.Position;
import compiler.Utils;

public class HexNumberToken extends Token {
    private String hexnum;
    public HexNumberToken(String hexnum, Position start, Position end) {
        super(Utils.TOKEN_TAG.HEXNUMBER, start, end);
        this.hexnum = hexnum;
    }
    @Override
    public String toString() {
        return super.toString() + ": " + hexnum;
    }
}
