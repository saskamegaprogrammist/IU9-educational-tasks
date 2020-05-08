package compiler.token;

import compiler.Position;
import compiler.Utils;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class StringToken extends Token {
    private String quote = "\"";
    private String doubleQuote = "\"\"";
    private String newLineOne = "\\\\\\r\\n";
    private String newLineOneReplace = "\r\n";
    private String newLineTwo = "\\\\\\n";
    private String newLineTwoReplace = "\n";

    public StringToken(String string,  Position start, Position end) {
        super(Utils.TOKEN_TAG.STRING, start, end);
        this.setAttribute(string);

    }

    @Override
    protected void setAttribute(String token) {
        super.setAttribute(token);
        Pattern pattern = Pattern.compile(doubleQuote);
        Matcher matcher = pattern.matcher(token);
        if (matcher.find()) {
            token = matcher.replaceAll(quote);
        }
        pattern = Pattern.compile(newLineOne);
        matcher = pattern.matcher(token);
        if (matcher.find()) {
            token = matcher.replaceAll(newLineOneReplace);
        }
        pattern = Pattern.compile(newLineTwo);
        matcher = pattern.matcher(token);
        if (matcher.find()) {
            token = matcher.replaceAll(newLineTwoReplace);
        }
        this.attribute = token;
    }

    @Override
    public String toString() {
        return super.toString() + ": " + attribute;
    }
}