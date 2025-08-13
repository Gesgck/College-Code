package lexer;

public record Token(TokenType type, String lexeme, Location location) {

   @Override
   public String toString() {
      String str = lexeme;
      str = str.replace("\n", "\\n");
      str = str.replace("\r", "\\r");
      return "['" + str + "'," + type.name() + "," + location + "]";
   }
}
