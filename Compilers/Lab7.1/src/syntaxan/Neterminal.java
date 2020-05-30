package syntaxan;

import java.util.ArrayList;

public class Neterminal extends TreeNode {
    private String name;
    private ArrayList<TreeNode> childNodes = new ArrayList<>();
    private int ruleId = Utils.ERROR_ID;


    public Neterminal(String name) {
        this.type = Utils.TreeNodeType.NETERMINAL;
        this.name = name;
    }

    public Neterminal(String name, Neterminal parent) {
        this.type = Utils.TreeNodeType.NETERMINAL;
        this.name = name;
        this.setParent(parent);
    }

    public Neterminal(String name, int ruleId) {
        this.type = Utils.TreeNodeType.NETERMINAL;
        this.name = name;
        this.ruleId = ruleId;
    }

    public Neterminal(String name, int ruleId, Neterminal parent) {
        this.type = Utils.TreeNodeType.NETERMINAL;
        this.name = name;
        this.ruleId = ruleId;
        this.setParent(parent);
    }

    public String getName() {
        return name;
    }

    public ArrayList<TreeNode> getChildNodes() {
        return childNodes;
    }

    public void printSelf(int nameParent) {
        String name = this.name + " " ;
        System.out.print(name);
        int nameSize = name.length() + nameParent;
        int counter = 0;
        if (childNodes.size() == 0) {
            System.out.print("eps");
        } else {
            for (TreeNode node : childNodes) {
                if (counter != 0) {
                    for (int j = 0; j < nameSize; j++) {
                        System.out.print(" ");
                    }
                }
                if (node.getType() == Utils.TreeNodeType.TERMINAL) {
                    ((Terminal) node).printSelf();
                } else {
                    ((Neterminal) node).printSelf(nameSize);
                }
                counter++;
                System.out.println();
            }
        }
    }

    public boolean isRuleSet() {
        return this.ruleId != Utils.ERROR_ID;
    }

    public void addChild(TreeNode tN) {
        this.childNodes.add(tN);
    }
}
