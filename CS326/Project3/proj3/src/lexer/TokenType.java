package lexer;

// Represents the tokens recognized by the scanner.
public enum TokenType {

   EOF,
   INVALID,        // Not a valid keyword/operator

   // ===---------------------------------------===
   // Keywords:
   IMPORT,         // import
   FROM,           // from
   IN,             // in
   DEF,            // def
   IF,             // if
   ELIF,           // elif
   ELSE,           // else
   WHILE,          // while
   FOR,            // foreach
   TRY,            // try
   EXCEPT,         // except
   FINALLY,        // finally
   PASS,           // pass
   TRUE,           // true
   FALSE,          // false
   PRINT,          // print
   INPUT,          // input
   BREAK,          // break
   RETURN,         // return
   CLASS,          // class
   VAR,            // var
   INT,            // int
   REAL,           // real
   BOOL,           // bool
   STRING,         // string
   NONE,           // none
   VOID,           // void

   // ===---------------------------------------===
   // Others:
   IDENT,          // Identifier
   INT_LITERAL,    // Literal
   REAL_LITERAL,
   STRING_LITERAL,
   NONE_LITERAL,
   COMMENT,

   // ===---------------------------------------===
   // Operators:
   PLUS,            // +
   MINUS,           // -
   MUL,             // *
   DIV,             // /
   MOD,             // %
   BIT_AND,         // &
   BIT_OR,          // |
   XOR,             // ^
   POWER,           // **

   ASSIGN,          // =
   PLUS_EQUAL,      // +=
   MINUS_EQUAL,     // -=
   MUL_EQUAL,       // *=
   DIV_EQUAL,       // /=
   MOD_EQUAL,       // %=
   POWER_EQUAL,     // **=

   PARENL,          // (
   PARENR,          // )
   CURLYL,          // {
   CURLYR,          // }
   BRACKL,          // [
   BRACKR,          // ]

   COLON,           // :
   SEMI,            // ;
   COMMA,           // ,
   DOT,             // .

   EQUAL,           // ==
   NOT_EQUAL,       // <>
   LT,              // <
   LE,              // <=
   GT,              // >
   GE,              // >=
   SHIFT_RIGHT,     // >>
   SHIFT_LEFT,      // <<
   AND,             // and
   OR,              // or

   NEG,             // ~
   IS,              // is
   NOT,             // not
   AT,              // @
   ;
}
