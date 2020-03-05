public class Token {
    private String tokenType;
    private String position;
    private String value;

    public Token(String tokenType,String position, String value) {
        this.position = position;
        this.tokenType = tokenType;
        this.value = value;
    }

    @Override
    public String toString() {
        return this.tokenType + " " +  this.position + ": " + this.value;
    }
}
