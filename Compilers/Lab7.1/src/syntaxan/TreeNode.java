package syntaxan;

public class TreeNode {
    protected Utils.TreeNodeType type;
    private Neterminal parent = null;

    public Utils.TreeNodeType getType() {
        return type;
    }

    public void setParent(Neterminal parent) {
        this.parent = parent;
    }

    public Neterminal getParent() {
        return parent;
    }
}
