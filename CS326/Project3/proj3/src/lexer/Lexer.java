package lexer;

public class Lexer {

   public static final char EOF = (char) -1;

   String input;
   int pos;
   char ch;
   Location loc;
   boolean addSemicolon;

   public Lexer(String input) {
      this.input = input;
      this.ch = input.charAt(0);
      this.addSemicolon = false;
      this.loc = new Location();
   }

   public void consume() {
      pos++;
      if (pos >= input.length()) {
         ch = EOF;
      } else {
         ch = input.charAt(pos);
      }
   }

   boolean isEOF() {
      return pos >= input.length();
   }

   boolean isDigit() {
      return ch >= '0' && ch <= '9';
   }

   boolean isLetter() {
      return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
   }

   boolean isAlpha() {
      return isLetter() || isDigit() || ch == '_';
   }

   public Token nextToken() {
      if (isEOF()) {
         return new Token(TokenType.EOF, "EOF", loc.copy());
      }
      while (true) {
         switch (ch) {
            case ' ', '\t', '\r':
               while (ch == ' ' || ch == '\t' || ch == '\r') {
                  loc.columns(1);
                  loc.step();
                  consume();
               }
               break;

            case '\n': {
               loc.lines(1);
               loc.step();
               consume();
               boolean addSemicolon = this.addSemicolon;
               this.addSemicolon = false;
               if (addSemicolon) {
                  return new Token(TokenType.SEMI, ";", loc.copy());
               }
               break;
            }

            case '"':
               addSemicolon = true;
               consume();
               loc.columns(1);
               if (ch == '"') {
                  consume();
                  return new Token(TokenType.STRING_LITERAL, "", loc.copy());
               }
               return string();

            case '=':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.EQUAL, "==", loc.copy());
               }
               return new Token(TokenType.ASSIGN, "=", loc.copy());

            case '+':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.PLUS_EQUAL, "+=", loc.copy());
               }
               return new Token(TokenType.PLUS, "+", loc.copy());

            case '-':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.MINUS_EQUAL, "-=", loc.copy());
               }
               return new Token(TokenType.MINUS, "-", loc.copy());

            case '*':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '*') {
                  consume();
                  loc.columns(1);
                  if (ch == '=') {
                     consume();
                     loc.columns(1);
                     return new Token(TokenType.POWER_EQUAL, "**=", loc.copy());
                  }
                  return new Token(TokenType.POWER, "**", loc.copy());
               }
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.MUL_EQUAL, "*=", loc.copy());
               }
               return new Token(TokenType.MUL, "*", loc.copy());

            case '/':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.DIV_EQUAL, "/=", loc.copy());
               }
               return new Token(TokenType.DIV, "/", loc.copy());

            case '%':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.MOD_EQUAL, "%=", loc.copy());
               }
               return new Token(TokenType.MOD, "%", loc.copy());

            case '&':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.BIT_AND, "&", loc.copy());

            case '|':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.BIT_OR, "|", loc.copy());

            case '^':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.XOR, "^", loc.copy());

            case '(':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.PARENL, "(", loc.copy());

            case ')':
               addSemicolon = true;
               consume();
               loc.columns(1);
               return new Token(TokenType.PARENR, ")", loc.copy());

            case '{':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.CURLYL, "{", loc.copy());

            case '}':
               addSemicolon = true;
               loc.columns(1);
               consume();
               return new Token(TokenType.CURLYR, "}", loc.copy());

            case '[':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.BRACKL, "[", loc.copy());

            case ']':
               addSemicolon = true;
               consume();
               loc.columns(1);
               return new Token(TokenType.BRACKR, "]", loc.copy());

            case ':':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.COLON, ":", loc.copy());

            case ';':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.SEMI, ";", loc.copy());

            case ',':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.COMMA, ",", loc.copy());

            case '.':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.DOT, ".", loc.copy());

            case '<':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '<') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.SHIFT_LEFT, "<<", loc.copy());
               }
               if (ch == '>') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.NOT_EQUAL, "<>", loc.copy());
               }
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.LE, "<=", loc.copy());
               }
               return new Token(TokenType.LT, "<", loc.copy());

            case '>':
               addSemicolon = false;
               consume();
               loc.columns(1);
               if (ch == '>') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.SHIFT_RIGHT, ">>", loc.copy());
               }
               if (ch == '=') {
                  consume();
                  loc.columns(1);
                  return new Token(TokenType.GE, ">=", loc.copy());
               }
               return new Token(TokenType.GT, ">", loc.copy());

            case '@':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.AT, "@", loc.copy());

            case '~':
               addSemicolon = false;
               consume();
               loc.columns(1);
               return new Token(TokenType.NEG, "~", loc.copy());

            case '#':
               consume();
               loc.columns(1);
               return comment();

            case '0', '1', '2', '3', '4',
                 '5', '6', '7', '8', '9':
               addSemicolon = true;
               return number();

            case 'A', 'B', 'C', 'D', 'E', 'F':
            case 'G', 'H', 'I', 'J', 'K', 'L':
            case 'M', 'N', 'O', 'P', 'Q', 'R':
            case 'S', 'T', 'U', 'V', 'W', 'X':
            case 'Y', 'Z':
            case 'a', 'b', 'c', 'd', 'e', 'f':
            case 'g', 'h', 'i', 'j', 'k', 'l':
            case 'm', 'n', 'o', 'p', 'q', 'r':
            case 's', 't', 'u', 'v', 'w', 'x':
            case 'y', 'z':
            case '_':
               return identifier();

            default:
               return new Token(TokenType.INVALID, "", loc.copy());
         }
      }
   }

   Token comment() {
      var strb = new StringBuilder();
      do {
         strb.append(ch);
         consume();
      } while (ch != '\n');
      loc.columns(strb.length());
      return new Token(TokenType.COMMENT, strb.toString(), loc.copy());
   }

   Token number() {
      var strb = new StringBuilder();
      while (isDigit()) {
         strb.append(ch);
         consume();
      }
      if (ch == '.') {
         addSemicolon = true;
         do {
            strb.append(ch);
            consume();
         } while (isDigit());
      }
      String str = strb.toString();
      loc.columns(str.length());
      if (str.contains(".")) {
         return new Token(TokenType.REAL_LITERAL, str, loc.copy());
      }
      return new Token(TokenType.INT_LITERAL, str, loc.copy());
   }

   Token string() {
      var strb = new StringBuilder();
      loc.step();
      do {
         strb.append(ch);
         consume();
         if (isEOF()) {
            return new Token(TokenType.INVALID, "Unexpected type: " + strb + ".", loc.copy());
         }
      } while (ch != '"');
      consume();
      loc.columns(strb.length());
      var token = new Token(TokenType.STRING_LITERAL, strb.toString(), loc.copy());
      loc.columns(1);
      return token;
   }

   Token identifier() {
      var strb = new StringBuilder();
      loc.step();
      do {
         strb.append(ch);
         consume();
      } while (isAlpha());
      String str = strb.toString();
      loc.columns(str.length());
      addSemicolon = false;
      return switch (str) {
         case "import":
            yield new Token(TokenType.IMPORT, "import", loc.copy());
         case "from":
            yield new Token(TokenType.FROM, "from", loc.copy());
         case "in":
            yield new Token(TokenType.IN, "in", loc.copy());
         case "def":
            yield new Token(TokenType.DEF, "def", loc.copy());
         case "if":
            yield new Token(TokenType.IF, "if", loc.copy());
         case "elif":
            yield new Token(TokenType.ELIF, "elif", loc.copy());
         case "else":
            yield new Token(TokenType.ELSE, "else", loc.copy());
         case "while":
            yield new Token(TokenType.WHILE, "while", loc.copy());
         case "for":
            yield new Token(TokenType.FOR, "for", loc.copy());
         case "try":
            yield new Token(TokenType.TRY, "try", loc.copy());
         case "except":
            yield new Token(TokenType.EXCEPT, "except", loc.copy());
         case "finally":
            yield new Token(TokenType.FINALLY, "finally", loc.copy());
         case "pass":
            addSemicolon = true;
            yield new Token(TokenType.PASS, "pass", loc.copy());
         case "true":
            yield new Token(TokenType.TRUE, "true", loc.copy());
         case "false":
            yield new Token(TokenType.FALSE, "false", loc.copy());
         case "print":
            yield new Token(TokenType.PRINT, "print", loc.copy());
         case "input":
            yield new Token(TokenType.INPUT, "input", loc.copy());
         case "break":
            addSemicolon = true;
            yield new Token(TokenType.BREAK, "break", loc.copy());
         case "is":
            yield new Token(TokenType.IS, "is", loc.copy());
         case "and":
            yield new Token(TokenType.AND, "and", loc.copy());
         case "or":
            yield new Token(TokenType.OR, "or", loc.copy());
         case "not":
            yield new Token(TokenType.NOT, "not", loc.copy());
         case "return":
            addSemicolon = true;
            yield new Token(TokenType.RETURN, "return", loc.copy());
         case "class":
            yield new Token(TokenType.CLASS, "class", loc.copy());
         case "None":
            yield new Token(TokenType.NONE_LITERAL, "None", loc.copy());
         case "var":
            yield new Token(TokenType.VAR, "var", loc.copy());
         case "int":
            yield new Token(TokenType.INT, "int", loc.copy());
         case "real":
            yield new Token(TokenType.REAL, "real", loc.copy());
         case "bool":
            yield new Token(TokenType.BOOL, "bool", loc.copy());
         case "string":
            yield new Token(TokenType.STRING, "string", loc.copy());
         case "none":
            yield new Token(TokenType.NONE, "none", loc.copy());
         case "void":
            yield new Token(TokenType.VOID, "void", loc.copy());
         default: {
            if (!Character.isJavaIdentifierStart(str.charAt(0))) {
               yield new Token(TokenType.INVALID, "Unexpected type: " + str + ".", loc.copy());
            }
            addSemicolon = true;
            yield new Token(TokenType.IDENT, str, loc.copy());
         }
      };
   }
}
