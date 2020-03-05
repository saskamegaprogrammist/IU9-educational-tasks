import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Position {
    private String file;
    private int index = 0;
    private int line = 1;
    private int position = 1;

    public Position(String file) {
        this.file = file;
    }

    public int getIndex() {
        return this.index;
    }

    public String getString() {
        return this.file.substring(index);
    }

    public void addIndex(int length) {
        this.index+=length;
        this.position += length;
        Matcher m = Pattern.compile("^[\\n\\r]").matcher(this.file.substring(index));
        if (m.find()) {
            this.line++;
            this.position = 1;
            this.index++;
        }
    }

    public void next() {
        this.addIndex(1);
    }

    @Override
    public String toString() {
        return "(" + line + "," + position + ")" ;
    }
}
