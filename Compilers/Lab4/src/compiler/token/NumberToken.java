package compiler.token;

import compiler.Position;
import compiler.Utils;

public class NumberToken extends Token {
    private Integer number;
    public NumberToken(String number, Position start, Position end) {
        super(Utils.TOKEN_TAG.NUMBER, start, end);
        this.number = Integer.parseInt(number);
    }

    @Override
    public String toString() {
        return super.toString() + ": " + number.toString();
    }
}