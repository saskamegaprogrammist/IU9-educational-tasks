package token;

import lexer.Position;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TerminalToken extends Token {

    private String charEscaped = "\\\\[(|)|.|||=|\\[|\\]|+|*|?]";
    private String escape = "\\\\";
    private String emptyString = "";

    public TerminalToken(String number, Position start, Position end) {
        super(Utils.TOKEN_TAG.TERMINAL, start, end);
        this.setAttribute(number);
    }

    @Override
    protected void setAttribute(String token) {
        super.setAttribute(token);
        StringBuffer newToken = new StringBuffer(token.length());
        Pattern pattern = Pattern.compile(charEscaped);
        Matcher matcher = pattern.matcher(token);
        while (matcher.find()) {
            String text = matcher.group();
            text.replace(escape, emptyString);
            matcher.appendReplacement(newToken, text);
        }
        matcher.appendTail(newToken);
        this.attribute = newToken.toString();
    }

    @Override
    public String toString() {
        return super.toString() + ": " + attribute;
    }

}