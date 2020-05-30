package token;

import lexer.Position;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class AxiomToken  extends Token {

    private String openBracket = "\\(\\s*";
    private String closeBracket = "\\s*\\)";
    private String emptyString = "";


    public AxiomToken(String number, Position start, Position end) {
        super(Utils.TOKEN_TAG.AXIOM, start, end);
        this.setAttribute(number);
    }

    @Override
    protected void setAttribute(String token) {
        super.setAttribute(token);
        Pattern pattern = Pattern.compile(openBracket);
        Matcher matcher = pattern.matcher(token);
        if (matcher.find()) {
            token = matcher.replaceAll(emptyString);
        }
        pattern = Pattern.compile(closeBracket);
        matcher = pattern.matcher(token);
        if (matcher.find()) {
            token = matcher.replaceAll(emptyString);
        }
        this.attribute = token;
    }

    @Override
    public String toString() {
        return super.toString() + ": " + attribute;
    }

}