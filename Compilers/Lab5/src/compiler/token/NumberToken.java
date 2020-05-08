package compiler.token;

import compiler.Position;
import compiler.Utils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class NumberToken extends Token {
    private String leadingZeros = "^0*";

    public NumberToken(String number, Position start, Position end) {
        super(Utils.TOKEN_TAG.NUMBER, start, end);
        this.setAttribute(number);
    }

    @Override
    protected void setAttribute(String token) {
        super.setAttribute(token);
        Pattern pattern = Pattern.compile(leadingZeros);
        Matcher matcher = pattern.matcher(token);
        if (matcher.find()) {
            token = matcher.replaceAll("");
        }
        this.attribute = token;
    }

    @Override
    public String toString() {
        return super.toString() + ": " + attribute;
    }
}