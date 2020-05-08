package compiler;

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

    public boolean isStringInnerQuote() {
        if (this.index != this.fileLength) {
            if (this.file.charAt(this.index) == '"') {
                if (this.index + 1 < this.fileLength) {
                    return (this.file.charAt(this.index + 1) == '"');
                }
                return true;
            }
        }
        return false;
    }

    public boolean isStringDelimiter() {
        if (this.index != this.fileLength) {
            if (this.file.charAt(this.index) == '"') {
                if (this.index + 1 < this.fileLength) {
                    return !(this.file.charAt(this.index + 1) == '"');
                }
                return true;
            }
        }
        return false;
    }

    public boolean isStringNewLineSymbol() {
        return  (this.index != this.fileLength && this.file.charAt(this.index) == '\\');
    }

    public boolean isDigit() {
        return (this.index != this.fileLength && Character.isDigit(this.file.charAt(this.index)));
    }

    public boolean isLetter() {
        return (this.index != this.fileLength && Character.isLetter(this.file.charAt(this.index)));
    }

    public boolean isHexLetter() {
        if (this.index != this.fileLength) {
            char value = this.file.charAt(this.index);
            return  ((value >= 'A' && value <= 'F') || (value >= 'a' && value <= 'f'));
        }
        return false;
    }

    public boolean isLetterOrDigit() {
        return this.isDigit() || this.isLetter();
    }

    public boolean isHex() {
        return this.isDigit() || this.isHexLetter();
    }

    public boolean isHexNumberDelimiter() {
        return (this.index != this.fileLength && this.file.charAt(this.index) == '$');
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
