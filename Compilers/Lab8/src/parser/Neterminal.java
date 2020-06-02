package parser;

import java.util.Objects;

public class Neterminal implements Comparable<Neterminal>{
    private String name;

    public Neterminal(String name) {
        this.name = name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public int compareTo(Neterminal n) {
        return this.name.compareTo(n.name);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Neterminal)) return false;
        Neterminal n = (Neterminal) o;
        return getName().equals(n.getName());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getName());
    }
}
