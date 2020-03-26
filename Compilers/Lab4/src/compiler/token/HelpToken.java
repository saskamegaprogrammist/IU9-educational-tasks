package compiler.token;

import compiler.Position;
import compiler.Utils;

public class HelpToken extends Token {
    public HelpToken(Utils.TOKEN_TAG tag, Position start, Position end) throws Exception {
        super(tag, start, end);
        if (tag != Utils.TOKEN_TAG.EOF) throw new Exception("wrong token tag");
    }
}
