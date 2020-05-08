package compiler.token;

import compiler.Position;
import compiler.Utils;

public class CommentToken extends Token {

    public CommentToken(String string,  Position start, Position end) {
        super(Utils.TOKEN_TAG.COMMENT, start, end);
        this.setAttribute(string);

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