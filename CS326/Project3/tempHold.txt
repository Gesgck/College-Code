import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import interpreter.Interpreter;
import semantics.SemanticAnalysis;

public class Main {

   public static void main(String[] args) throws IOException {

      String test1 = """
             def binomial(n int) string {
                def fac(x int) int {
                   if (x == 0) { return 1 }
                   else { return x * fac(x - 1) }
                }
                def choose(n int, k int) int {
                   return fac(n) / fac(n - k) * fac(k)
                }
             
                print "(1 + x)^"
                print n
                print " = 1 + "
                print n
                print "x + "
             
                var out string = ""
                var k int = 2
                while k < n {
                   print choose(n, k)
                   print "x^"
                   print k
                   k = k + 1
                   print " + "
                }
                print "x^"
                print n
             
                return ""
             }
             
             print binomial(4)
             """;

      String test2 = """
             def sqrt(x real) real {
               def x(y real) real {
                 return 0.5 * (y + x/y)
               }
             
               var y real = x
               var i real = 30.0
               while i > 0.0 {
                 y = x(y)
                 i = i - 1.0
               }
               return y
             }
             
             print sqrt(2)
             """;

      String test3 = """
             def fac(n int) int {
                if n == 0 { return 1 }
                else return n * fac(n - 1)
             }
             
             print fact(5)
             """;

      String test4 = """
             print "hello world!"
             """;

//    var scanner = new lexer.Lexer(text12);
//    lexer.Token token;
//    do {
//      token = scanner.nextToken();
//      System.out.println(token);
//    } while (token.type() != lexer.TokenType.EOF);
//    var parser = new parser.Parser(scanner);
//    var script = parser.parse();
//    var analyser = new semantics.SemanticAnalysis();
//    analyser.openScope();
//    script.visit(analyser);
//    analyser.closeScope();
//    System.out.println(tools.AstUtils.toJsTree(script));

      var reader = new BufferedReader(new InputStreamReader(System.in));
      SemanticAnalysis analyser = new SemanticAnalysis();
      Interpreter interpreter = new Interpreter();
      String ast = "";

      analyser.openScope();
      interpreter.openScope();

      System.out.println("\033[1mJython\033[0m 1.0.0 -- Oct 20th, 2024.");
      System.out.println("Type '#help' for more information.");

      label:
      while (true) {
         String input = "";
         StringBuilder program = new StringBuilder();
         boolean isExpression = false;
         System.out.print("\n>>> _\b");
         input = reader.readLine();

         // quit
         switch (input) {
            case "#quit":
               break label;
            case "#help":
               System.out.println("Welcome to \033[1mJython\033[0m 1.0.0 -- Benjamin Cisneros");
               System.out.println("Made with lots of coffee...\n");
               System.out.println("To use this interactive environment, just type in Jython commands");
               System.out.println("and hit enter. You can also make use of the following commands:\n");
               System.out.println("#load \033[3mfile-path\033[0m    Loads variables, functions, and classes");
               System.out.println("                   from a specified file into memory, e.g.");
               System.out.println("                   >>> #load \033[3mhello_world.jy\033[0m\n");
               System.out.println("#quit              Exits the environment.\n");
               System.out.println("#showtree          Displays the AST.\n");
               System.out.println("#clear             Clears the terminal window.");
               break;
            case "#clear":
               System.out.println("\n".repeat(50));
               break;
            case "#showtree":
               if (!ast.isEmpty()) {
                  System.out.println(ast);
               } else {
                  System.out.println("Cannot produce an AST from an empty Jython program.");
               }
               break;
            default:
               program.append(input);
               int tabs = 0;
               tabs += input.length() - input.replace("{", "").length();
               tabs -= input.length() - input.replace("}", "").length();
               while (tabs > 0) {
                  System.out.print("... ");
                  input = reader.readLine();
                  tabs += input.length() - input.replace("{", "").length();
                  tabs -= input.length() - input.replace("}", "").length();
                  program.append(input).append("\n");
               }
               try {
                  var lexer = new lexer.Lexer(program.toString());
                  var parser = new parser.Parser(lexer);
                  var script = parser.parse();
                  ast = tools.AstUtils.toAstTree(script);

                  try {
                     analyser.overHere(script);
                     interpreter.overHere(script);
                  } catch (Exception e) {
//              e.printStackTrace();
//              break label;
                     throw new RuntimeException(e.getMessage());
                  }
               } catch (Exception e) {
//            e.printStackTrace();
//            break label;
                  System.out.println(e.getMessage());
               }
               break;
         }
      }

      analyser.closeScope();
      interpreter.closeScope();
   }
}