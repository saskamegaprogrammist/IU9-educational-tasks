package syntaxan;

import token.Token;

public class Message {
    private String text;
    private Token atToken;
    private TreeNode atNode;

    public Message(String text, TreeNode node, Token token) {
        this.text = text;
        this.atNode = node;
        this.atToken = token;
    }

    @Override
    public String toString() {
        if (atNode.getType() == Utils.TreeNodeType.TERMINAL) {
            return "ERROR: " + text + " Terminal: " + ((Terminal)atNode).getTokenTag() + " Token: "+ atToken.toString();
        } else {
            return "ERROR: " + text + " Neterminal: " + ((Neterminal)atNode).getName() + " Token: "+ atToken.toString();

        }
    }
}
