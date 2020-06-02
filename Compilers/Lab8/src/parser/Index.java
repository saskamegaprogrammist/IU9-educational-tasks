package parser;

public class Index {
    public Integer currentIndex = 0;
    public Integer success = Utils.IGNORE;

    public Index(int index, int success) {
        this.currentIndex = index;
        this.success = success;
    }
}
