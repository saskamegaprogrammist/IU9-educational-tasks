package token;

import lexer.Position;

public class OperatorToken extends Token {

    public OperatorToken(String attribute, Position start, Position end) {
        super(Utils.TOKEN_TAG.END, start, end);
        switch (attribute) {
            case ".":
                this.tag = Utils.TOKEN_TAG.DOT;
                break;
            case "|":
                this.tag = Utils.TOKEN_TAG.DELIMITER;
                break;
            case "=":
                this.tag = Utils.TOKEN_TAG.EQ;
                break;
            case "?":
                this.tag = Utils.TOKEN_TAG.QUESTION;
                break;
            case "*":
                this.tag = Utils.TOKEN_TAG.STAR;
                break;
            case "+":
                this.tag = Utils.TOKEN_TAG.PLUS;
                break;
            case "[":
                this.tag = Utils.TOKEN_TAG.BR_OPEN;
                break;
            case "]":
                this.tag = Utils.TOKEN_TAG.BR_CLOSE;
                break;
        }
        this.setAttribute(attribute);
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