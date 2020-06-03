package parser;

import java.util.ArrayList;

public class Rule implements Comparable<Rule> {
    private Neterminal neterminal;
    private ArrayList<Terminal> FIRST = null;
    private int oldFirstSize = 0;
    private int newFirstSize = 0;
    private boolean changedFirst = false;
    private boolean hasEps = false;


    public Rule(Neterminal n) {
        this.neterminal = n;
        FIRST = new ArrayList<>();
    }

    public boolean isEmptyFirst() {
        return newFirstSize == 0;
    }

    public String getName() {
        return neterminal.getName();
    }

    public void setNeterminal(Neterminal neterminal) {
        this.neterminal = neterminal;
    }

    public Neterminal getNeterminal() {
        return neterminal;
    }

    public boolean isChangedFirst() {
        return changedFirst;
    }

    private void setNewFirstSize() {
        this.newFirstSize = this.FIRST.size();
        this.changedFirst = this.newFirstSize - this.oldFirstSize > 0;
    }

    public ArrayList<Terminal> getFIRST() {
        return FIRST;
    }

    public ArrayList<Terminal> getFIRSTwoEps() {
        ArrayList <Terminal> cleanFirst = new ArrayList<>();
        for(Terminal t: FIRST) {
            if (!(t instanceof Epsilon)) {
                cleanFirst.add(t);
            }
        }
        return cleanFirst;
    }

    public void removeEps() {
        this.setOldFirstSize();
        if (hasEps) {
            FIRST.removeIf(t -> (t instanceof Epsilon));
        }
        hasEps = false;
        this.setNewFirstSize();
    }

    private void setOldFirstSize() {
        this.oldFirstSize = this.FIRST.size();
    }

    public void addToFirst(Terminal terminal) {
        this.setOldFirstSize();
        if (!this.FIRST.contains(terminal)) {
            this.FIRST.add(terminal);
        }
        if (terminal instanceof Epsilon) {
            hasEps = true;
        }
        this.setNewFirstSize();
    }

    public boolean hasEps() {
        return hasEps;
    }

    public void addToFirst(ArrayList<Terminal> first) {
        this.setOldFirstSize();
        for (Terminal term: first) {
            this.addToFirst(term);
        }
        this.setNewFirstSize();
    }

    @Override
    public int compareTo(Rule r) {
        return this.neterminal.getName().compareTo(r.neterminal.getName());
    }

    public void printFirst() {
        System.out.print(this.neterminal.getName() + ": ");
        System.out.println(this.FIRST);
    }
}
