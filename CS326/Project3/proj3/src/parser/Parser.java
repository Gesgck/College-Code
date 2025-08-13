package parser;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import ast.expression.NoneLiteral;
import ast.types.ArrayType;
import ast.types.BoolType;
import ast.types.IntType;
import ast.types.NoneType;
import ast.types.RealType;
import ast.types.StringType;
import ast.types.Type;
import ast.expression.ArrayAccess;
import ast.statement.Assignment;
import ast.expression.BinaryOperation;
import ast.expression.BoolLiteral;
import ast.expression.Call;
import ast.statement.Except;
import ast.Class;
import ast.statement.ExpressionStat;
import ast.expression.Expression;
import ast.expression.FieldAccess;
import ast.statement.Finally;
import ast.statement.ForLoop;
import ast.statement.Function;
import ast.expression.Group;
import ast.statement.IfElse;
import ast.statement.Import;
import ast.expression.IntLiteral;
import ast.expression.ArrayLiteral;
import ast.expression.Name;
import ast.expression.NotOperation;
import ast.Parameter;
import ast.statement.Pass;
import ast.statement.Print;
import ast.expression.RealLiteral;
import ast.statement.Return;
import ast.Program;
import ast.statement.Statement;
import ast.expression.StringLiteral;
import ast.statement.Try;
import ast.expression.UnaryOperation;
import ast.statement.Var;
import ast.statement.WhileLoop;
import ast.types.VoidType;
import lexer.Lexer;
import lexer.Token;
import lexer.TokenType;

public class Parser {

   Lexer input;
   List<Integer> positions;
   List<Token> lookahead;
   int pos;

   public Parser(Lexer input) {
      this.input = input;
      this.positions = new ArrayList<>();
      this.lookahead = new ArrayList<>();
   }

   //
   // Helper Routines.
   //

   void synchronize(int index) {
      if (pos + index - 1 > (lookahead.size() - 1)) {
         int n = (pos + index - 1) - (lookahead.size() - 1);
         fill(n);
      }
   }

   void fill(int n) {
      for (int i = 1; i <= n; ++i) {
         lookahead.add(input.nextToken());
      }
   }

   void consume() {
      pos++;
      if (pos == lookahead.size() && !expects()) {
         pos = 0;
         lookahead.clear();
      }
      synchronize(1);
   }

   void mark() {
      positions.add(pos);
   }

   void release() {
      int marker = positions.get(positions.size() - 1);
      positions.remove(positions.size() - 1);
      seek(marker);
   }

   void seek(int index) {
      pos = index;
   }

   boolean expects() {
      return !positions.isEmpty();
   }

   Token LT(int index) {
      synchronize(index);
      return lookahead.get(pos + index - 1);
   }

   TokenType LA(int index) {
      return LT(index).type();
   }

   void match(TokenType type) {
      if (LA(1) == type) {
         consume();
      } else {
         throw new IllegalArgumentException("ERROR: Expecting " + type + " but found " + LT(1) + ".");
      }
   }

   void match(TokenType... types) {
      var flag = Arrays.stream(types).anyMatch(t -> t == LA(1));
      if (flag) {
         consume();
      } else {
         String str = Arrays.stream(types).map(TokenType::toString).collect(Collectors.joining(" "));
         throw new IllegalArgumentException("ERROR: Expecting " + str + " but found " + LT(1) + ".");
      }
   }

   boolean check(TokenType type) {
      return LA(1) == type;
   }

   boolean check(TokenType... types) {
      return Arrays.stream(types).anyMatch(t -> t == LA(1));
   }

   boolean eatIfPresent(TokenType type) {
      if (LA(1) == type) {
         consume();
         return true;
      }
      return false;
   }

   boolean eatIfPresent(TokenType... types) {
      var flag = Arrays.stream(types).anyMatch(t -> t == LA(1));
      if (flag) {
         consume();
         return true;
      }
      return false;
   }

   //
   // Grammar.
   //

   public Program parse() {
      List<Statement> stmts = new ArrayList<>();
      while (!check(TokenType.EOF)) {
         stmts.add(statement());
      }
      return new Program(stmts);
   }

   public Statement statement() {
      if (check(TokenType.IF, TokenType.WHILE, TokenType.FOR,
             TokenType.DEF, TokenType.CLASS, TokenType.TRY,
             TokenType.RETURN)) {
         return compound_stmt();
      }
      return simple_stmt();
   }

   public Statement simple_stmt() {
      if (LA(1) == TokenType.IDENT
             && (LA(2) == TokenType.ASSIGN
             || LA(2) == TokenType.PLUS_EQUAL
             || LA(2) == TokenType.MINUS_EQUAL
             || LA(2) == TokenType.MUL_EQUAL
             || LA(2) == TokenType.DIV_EQUAL
             || LA(2) == TokenType.MOD_EQUAL
             || LA(2) == TokenType.POWER_EQUAL)) {
         return assignment_stmt();
      }
      if (check(TokenType.VAR)) {
         return declaration_stmt();
      }
      if (check(TokenType.PRINT)) {
         return print_stmt();
      }
      if (check(TokenType.PASS)) {
         return pass_stmt();
      }
      if (check(TokenType.IMPORT, TokenType.FROM)) {
         return import_stmt();
      }
      return expression_stmt();
   }

   public Statement compound_stmt() {
      if (check(TokenType.IF)) {
         return if_stmt();
      }
      if (check(TokenType.WHILE)) {
         return while_stmt();
      }
      if (check(TokenType.FOR)) {
         return for_stmt();
      }
      if (check(TokenType.DEF)) {
         return def_stmt();
      }
      if (check(TokenType.CLASS)) {
         return class_stmt();
      }
      if (check(TokenType.TRY)) {
         return try_stmt();
      }
      return return_stmt();
   }

   public ExpressionStat expression_stmt() {
      var expr = new ExpressionStat(expression());
      if (check(TokenType.SEMI)) {
         match(TokenType.SEMI);
      }
      return expr;
   }

   public Assignment assignment_stmt() {
      var identifier = new Name(LT(1).lexeme());
      match(TokenType.IDENT);
      String operator = LT(1).lexeme();
      match(TokenType.ASSIGN, TokenType.PLUS_EQUAL,
             TokenType.MINUS_EQUAL, TokenType.MUL_EQUAL,
             TokenType.DIV_EQUAL, TokenType.MOD_EQUAL,
             TokenType.POWER_EQUAL);
      var value = expression();
      if (check(TokenType.SEMI)) {
         match(TokenType.SEMI);
      }
      return new Assignment(identifier, value, operator);
   }

   public Var declaration_stmt() {
      match(TokenType.VAR);
      String name = LT(1).lexeme();
      match(TokenType.IDENT);
      var type = type();
      match(TokenType.ASSIGN);
      Expression expr = expression();
      if (check(TokenType.SEMI)) {
         match(TokenType.SEMI);
      }
      return new Var(new Name(name), type, expr);
   }

   public Type type() {
      if (check(TokenType.INT, TokenType.REAL, TokenType.BOOL, TokenType.STRING)) {
         return value_type();
      }
      if (check(TokenType.BRACKL)) {
         return array_type();
      }
      if (check(TokenType.NONE)) {
         match(TokenType.NONE);
         return new NoneType();
      }
      if (check(TokenType.VOID)) {
         match(TokenType.VOID);
         return new VoidType();
      }
      return null;
   }

   public Type value_type() {
      if (check(TokenType.INT)) {
         match(TokenType.INT);
         return new IntType();
      }
      if (check(TokenType.REAL)) {
         match(TokenType.REAL);
         return new RealType();
      }
      if (check(TokenType.STRING)) {
         match(TokenType.STRING);
         return new StringType();
      }
      match(TokenType.BOOL);
      return new BoolType();
   }

   public Type array_type() {
      match(TokenType.BRACKL);
      var length = atom();
      match(TokenType.BRACKR);
      var type = type();
      return new ArrayType(type, length);
   }

   public Print print_stmt() {
      match(TokenType.PRINT);
      Expression expr = expression();
      if (check(TokenType.SEMI)) {
         match(TokenType.SEMI);
      }
      return new Print(expr);
   }

   public Pass pass_stmt() {
      match(TokenType.PASS);
      if (check(TokenType.SEMI)) {
         match(TokenType.SEMI);
      }
      return new Pass();
   }

   public Import import_stmt() {
      if (check(TokenType.IMPORT)) {
         match(TokenType.IMPORT);
         String name = LT(1).lexeme();
         match(TokenType.IDENT);
         if (check(TokenType.SEMI)) {
            match(TokenType.SEMI);
         }
         return new Import(new Name(name));
      }
      match(TokenType.FROM);
      String name = LT(1).lexeme();
      match(TokenType.IDENT);
      match(TokenType.IMPORT);
      String file = LT(1).lexeme();
      match(TokenType.IDENT);
      return new Import(new Name(name), new Name(file));
   }

   public Expression expression() {
      var expr = or_expr();
      if (check(TokenType.ASSIGN)) {
         match(TokenType.ASSIGN);
         var right = expression();
         expr = new BinaryOperation(expr, right, "=");
      }
      return expr;
   }

   public Expression or_expr() {
      var expr = and_expr();
      while (check(TokenType.OR)) {
         String operator = LT(1).lexeme();
         match(TokenType.OR);
         var right = and_expr();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression and_expr() {
      var expr = not_expr();
      while (check(TokenType.AND)) {
         String operator = LT(1).lexeme();
         match(TokenType.AND);
         var right = not_expr();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression not_expr() {
      if (eatIfPresent(TokenType.NOT)) {
         var expr = comparison();
         return new NotOperation(expr);
      }
      return comparison();
   }

   public Expression comparison() {
      var expr = bit_or_expr();
      while (check(TokenType.EQUAL, TokenType.NOT_EQUAL,
             TokenType.LT, TokenType.GT, TokenType.LE,
             TokenType.GE, TokenType.IS)) {
         String operator = LT(1).lexeme();
         if (LA(1) == TokenType.IS && LA(2) == TokenType.NOT) {
            match(TokenType.IS);
            operator += " " + LT(1).lexeme();
            match(TokenType.NOT);
         } else {
            match(TokenType.EQUAL, TokenType.NOT_EQUAL,
                   TokenType.LT, TokenType.GT, TokenType.LE,
                   TokenType.GE, TokenType.IS);
         }
         var right = bit_or_expr();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression bit_or_expr() {
      var expr = xor_expr();
      while (check(TokenType.BIT_OR)) {
         String operator = LT(1).lexeme();
         match(TokenType.BIT_OR);
         var right = xor_expr();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression xor_expr() {
      var expr = bit_and_expr();
      while (check(TokenType.XOR)) {
         String operator = LT(1).lexeme();
         match(TokenType.XOR);
         var right = bit_and_expr();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression bit_and_expr() {
      var expr = shift_expr();
      while (check(TokenType.BIT_AND)) {
         String operator = LT(1).lexeme();
         match(TokenType.BIT_AND);
         var right = shift_expr();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression shift_expr() {
      var expr = arith_expr();
      while (check(TokenType.SHIFT_RIGHT, TokenType.SHIFT_LEFT)) {
         String operator = LT(1).lexeme();
         match(TokenType.SHIFT_RIGHT, TokenType.SHIFT_LEFT);
         var right = arith_expr();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression arith_expr() {
      var expr = term();
      while (check(TokenType.PLUS, TokenType.MINUS)) {
         String operator = LT(1).lexeme();
         match(TokenType.PLUS, TokenType.MINUS);
         var right = term();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression term() {
      var expr = factor();
      while (check(TokenType.MUL, TokenType.DIV, TokenType.MOD)) {
         String operator = LT(1).lexeme();
         match(TokenType.MUL, TokenType.DIV, TokenType.MOD);
         var right = factor();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression factor() {
      if (check(TokenType.PLUS, TokenType.MINUS, TokenType.NEG)) {
         String operator = LT(1).lexeme();
         match(TokenType.PLUS, TokenType.MINUS, TokenType.NEG);
         var right = factor();
         return new UnaryOperation(operator, right);
      }
      return power();
   }

   public Expression power() {
      var expr = atom();
      while (check(TokenType.PARENL, TokenType.BRACKL, TokenType.DOT)) {
         var right = trailer();
         if (right instanceof Call call) {
            call.qualifier = expr;
            expr = new Call(call.qualifier, call.arguments);
         } else if (right instanceof ArrayAccess arrayAccess) {
            arrayAccess.name = expr;
            expr = new ArrayAccess(arrayAccess.name, arrayAccess.index);
         } else if (right instanceof FieldAccess fieldAccess) {
            fieldAccess.object = expr;
            expr = new FieldAccess(fieldAccess.object, fieldAccess.field);
         }
      }
      while (check(TokenType.POWER)) {
         String operator = LT(1).lexeme();
         match(TokenType.POWER);
         var right = factor();
         expr = new BinaryOperation(expr, right, operator);
      }
      return expr;
   }

   public Expression atom() {
      String literal = LT(1).lexeme();
      if (check(TokenType.INT_LITERAL)) {
         match(TokenType.INT_LITERAL);
         var value = Integer.parseInt(literal);
         return new IntLiteral(value);
      }
      if (check(TokenType.REAL_LITERAL)) {
         match(TokenType.REAL_LITERAL);
         var value = Double.parseDouble(literal);
         return new RealLiteral(value);
      }
      if (check(TokenType.STRING_LITERAL)) {
         match(TokenType.STRING_LITERAL);
         return new StringLiteral(literal);
      }
      if (check(TokenType.TRUE, TokenType.FALSE)) {
         match(TokenType.TRUE, TokenType.FALSE);
         return new BoolLiteral(Boolean.parseBoolean(literal));
      }
      if (check(TokenType.IDENT)) {
         String name = LT(1).lexeme();
         match(TokenType.IDENT);
         return new Name(name);
      }
      if (check(TokenType.NONE_LITERAL)) {
         match(TokenType.NONE_LITERAL);
         return new NoneLiteral();
      }
      if (check(TokenType.BRACKL)) {
         match(TokenType.BRACKL);
         var args = argument_list();
         match(TokenType.BRACKR);
         return new ArrayLiteral(args);
      }
      match(TokenType.PARENL);
      var expr = expression();
      match(TokenType.PARENR);
      return new Group(expr);
   }

   public Expression trailer() {
      if (eatIfPresent(TokenType.PARENL)) {
         var args = argument_list();
         match(TokenType.PARENR);
         return new Call(null, args);
      }
      if (eatIfPresent(TokenType.BRACKL)) {
         var expr = expression();
         match(TokenType.BRACKR);
         return new ArrayAccess(null, expr);
      }
      match(TokenType.DOT);
      String name = LT(1).lexeme();
      match(TokenType.IDENT);
      return new FieldAccess(null, new Name(name));
   }

   public List<Expression> argument_list() {
      List<Expression> args = new ArrayList<>();
      while (!check(TokenType.PARENR, TokenType.BRACKR)) {
         args.add(expression());
         if (check(TokenType.COMMA)) {
            match(TokenType.COMMA);
         }
      }
      return args;
   }

   public List<Statement> block() {
      match(TokenType.CURLYL);
      List<Statement> stmts = new ArrayList<>();
      while (!check(TokenType.CURLYR, TokenType.EOF)) {
         stmts.add(statement());
      }
      match(TokenType.CURLYR);
      if (check(TokenType.SEMI)) {
         match(TokenType.SEMI);
      }
      return stmts;
   }

   public IfElse if_stmt() {
      match(TokenType.IF);
      var ifStmt = new IfElse();
      ifStmt.condition = expression();
      ifStmt.body.addAll(block());
      if (eatIfPresent(TokenType.ELIF)) {
         var elifCondition = expression();
         var elifBlock = block();
         var elifStmt = new IfElse(elifCondition, elifBlock);
         ifStmt.orElse.add(elifStmt);
      }
      if (eatIfPresent(TokenType.ELSE)) {
         ifStmt.orElse.addAll(block());
      }
      return new IfElse(ifStmt.condition, ifStmt.body, ifStmt.orElse);
   }

   public WhileLoop while_stmt() {
      match(TokenType.WHILE);
      var condition = expression();
      var body = block();
      return new WhileLoop(condition, body);
   }

   public ForLoop for_stmt() {
      match(TokenType.FOR);
      String name = LT(1).lexeme();
      match(TokenType.IDENT);
      var variable = new Name(name);
      var type = type();
      match(TokenType.IN);
      var condition = expression();
      var body = block();
      return new ForLoop(new Var(variable, type), condition, body);
   }

   public Function def_stmt() {
      match(TokenType.DEF);
      String name = LT(1).lexeme();
      match(TokenType.IDENT);
      var variable = new Name(name);
      match(TokenType.PARENL);
      var params = parameter_list();
      match(TokenType.PARENR);
      var returnType = type();
      var body = block();
      return new Function(variable, params, returnType, body);
   }

   public Class class_stmt() {
      match(TokenType.CLASS);
      String name = LT(1).lexeme();
      match(TokenType.IDENT);
      var variable = new Name(name);
      var body = block();
      return new Class(variable, body);
   }

   public Try try_stmt() {
      match(TokenType.TRY);
      var body = block();
      var excepts = new ArrayList<Statement>();
      while (eatIfPresent(TokenType.EXCEPT)) {
         String name = LT(1).lexeme();
         match(TokenType.IDENT);
         var variable = new Name(name);
         var eBody = block();
         excepts.add(new Except(variable, eBody));
      }
      var finallyBlock = new Finally();
      if (eatIfPresent(TokenType.FINALLY)) {
         var fBody = block();
         finallyBlock = new Finally(fBody);
      }
      return new Try(body, excepts, finallyBlock);
   }

   public List<Parameter> parameter_list() {
      var params = new ArrayList<Parameter>();
      while (check(TokenType.IDENT)) {
         String name = LT(1).lexeme();
         match(TokenType.IDENT);
         var type = type();
         params.add(new Parameter(name, type));
         if (check(TokenType.COMMA)) consume();
         else break;
      }
      return params;
   }

   public Return return_stmt() {
      match(TokenType.RETURN);
      if (!check(TokenType.SEMI)) {
         var expr = expression();
         if (check(TokenType.SEMI))
            match(TokenType.SEMI);
         return new Return(expr);
      }
      if (check(TokenType.SEMI)) {
         match(TokenType.SEMI);
      }
      return new Return();
   }
}
