package lexer;

public class Position implements Cloneable {
    private String file;
    private int fileLength;
    private int index = 0;
    private int line = 1;
    private int position = 1;

    public Position(String file) {
        this.file = file;
        this.fileLength = file.length();
    }

    public Position(Position pos) {
        this.file = pos.getFile();
        this.fileLength = this.file.length();
        this.index = pos.getIndex();
        this.line = pos.getLine();
        this.position = pos.getPosition();

    }
    public String getFile() {
        return this.file;
    }
    public int getIndex() {
        return this.index;
    }
    public int getLine() {
        return this.line;
    }
    public int getPosition() {
        return this.position;
    }

    public boolean isNewLine() {
        if (this.index == this.fileLength) { //end of file is end of line
            return true;
        }
        if (this.file.charAt(this.index) == '\r' && this.index+1 < this.fileLength) { //in some systems new line is \r\n
            return (this.file.charAt(this.index+1) == '\n');
        }
        return (this.file.charAt(this.index) == '\n');
    }

    public int getCurrentPosition() {
        if (this.index == this.fileLength) {
            return -1;
        }
        return this.file.charAt(this.index);
    }

    public boolean isWhiteSpace() {
        return (this.index != this.fileLength && Character.isWhitespace(this.file.charAt(this.index)));
    }

    public boolean isDigit() {
        return (this.index != this.fileLength && Character.isDigit(this.file.charAt(this.index)));
    }

    public boolean isSymbol() {
        return (this.index != this.fileLength && Utils.symbols.contains(this.file.charAt(this.index)));
    }

    public boolean isKeySymbol() {
        if (this.index != this.fileLength) {
            char value = this.file.charAt(this.index);
            return value == Utils.delimiter ||
                    value == Utils.dot || value == Utils.equals;
        }
        return false;
    }

    public boolean isDot() {
        return (this.index != this.fileLength && this.file.charAt(this.index) == Utils.dot);
    }


    public boolean isEquals() {
        return (this.index != this.fileLength && this.file.charAt(this.index) == Utils.equals);
    }

    public boolean isDelimiter() {
        return (this.index != this.fileLength && this.file.charAt(this.index) == Utils.delimiter);
    }

    public boolean isCloseBracket() {
        return (this.index != this.fileLength && this.file.charAt(this.index) == Utils.closeBracket);
    }

    public boolean isOpenBracket() {
        return (this.index != this.fileLength && this.file.charAt(this.index) == Utils.openBracket);
    }

    public boolean isEscapeChar() {
        return (this.index != this.fileLength && this.file.charAt(this.index) == Utils.escape);
    }

    public boolean isLetter() {
        return (this.index != this.fileLength && Character.isLetter(this.file.charAt(this.index)));
    }

    public boolean isLetterOrDigit() {
        return this.isDigit() || this.isLetter();
    }


    public boolean isCapLetter() {
        if (this.index != this.fileLength) {
            char value = this.file.charAt(this.index);
            return  ((value >= 'A' && value <= 'Z'));
        }
        return false;
    }

    public boolean isSmallLetter() {
        if (this.index != this.fileLength) {
            char value = this.file.charAt(this.index);
            return  ((value >= 'a' && value <= 'z'));
        }
        return false;
    }


    public void next() {
        if (this.index < this.fileLength) {
            if (this.isNewLine()) {
                if (this.getCurrentPosition() == '\r') this.index++; //in some systems new line is \r\n
                this.line++;
                this.position = 1;
            } else {
                this.position++;
            }
            this.index++;
        }

    }

    @Override
    public String toString() {
        return "(" + line + "," + position + ")" ;
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        return super.clone();
    }
}
