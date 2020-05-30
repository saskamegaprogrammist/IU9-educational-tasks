package syntaxan;

import token.Utils;

import java.util.Objects;

public class Cell {
    private String neterminalAttribute;
    private token.Utils.TOKEN_TAG tokenTag;

    public Cell(String neterminalAttribute, token.Utils.TOKEN_TAG tokenTag) {
        this.tokenTag = tokenTag;
        this.neterminalAttribute = neterminalAttribute;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Cell)) return false;
        Cell cell = (Cell) o;
        return getNeterminalAttribute().equals(cell.getNeterminalAttribute()) &&
                getTokenTag() == cell.getTokenTag();
    }

    @Override
    public int hashCode() {
        return Objects.hash(getNeterminalAttribute(), getTokenTag());
    }

    public String getNeterminalAttribute() {
        return neterminalAttribute;
    }

    public Utils.TOKEN_TAG getTokenTag() {
        return tokenTag;
    }
}
