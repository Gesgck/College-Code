package interpreter;

import java.util.ArrayList;

import ast.Class;
import ast.Parameter;
import ast.Program;
import ast.expression.ArrayAccess;
import ast.expression.ArrayLiteral;
import ast.expression.BinaryOperation;
import ast.expression.BoolLiteral;
import ast.expression.Call;
import ast.expression.FieldAccess;
import ast.expression.Group;
import ast.expression.IntLiteral;
import ast.expression.Name;
import ast.expression.NoneLiteral;
import ast.expression.NotOperation;
import ast.expression.ObjectLiteral;
import ast.expression.RealLiteral;
import ast.expression.StringLiteral;
import ast.expression.UnaryOperation;
import ast.statement.Assignment;
import ast.statement.Except;
import ast.statement.ExpressionStat;
import ast.statement.Finally;
import ast.statement.ForLoop;
import ast.statement.Function;
import ast.statement.IfElse;
import ast.statement.Import;
import ast.statement.Pass;
import ast.statement.Print;
import ast.statement.Return;
import ast.statement.Try;
import ast.statement.Var;
import ast.statement.WhileLoop;
import ast.types.ArrayType;
import ast.types.BoolType;
import ast.types.IntType;
import ast.types.NoneType;
import ast.types.RealType;
import ast.types.StringType;
import ast.types.Type;
import ast.types.VoidType;
import scope.Symboltable;
import tools.Fry;

public class Interpreter implements Fry {

   public Type currExprType;
   public Name currExprName;
   public Symboltable<Object> variableTable;
   public Symboltable<Function> functionTable;
   Object currExprValue;
   boolean inReturn = false;

   public Interpreter() {
      this.variableTable = new Symboltable<>();
      this.functionTable = new Symboltable<>();
   }

   public void openScope() {
      this.variableTable.openScope();
      this.functionTable.openScope();
   }

   public void closeScope() {
      this.variableTable.closeScope();
      this.functionTable.closeScope();
   }

   // Expressions

   @Override
   public void overHere(ArrayAccess node) {
      node.name.fryCall(this);
      String identifier = currExprName.identifier;
      node.index.fryCall(this);
      var array = (ArrayList<?>) variableTable.lookup(identifier);
      var index = (int) currExprValue;
      currExprValue = array.get(index);
      if (currExprValue instanceof Integer) {
         currExprType = new IntType();
      } else if (currExprValue instanceof Double) {
         currExprType = new RealType();
      } else if (currExprValue instanceof String) {
         currExprType = new StringType();
      } else if (currExprValue instanceof Boolean) {
         currExprType = new BoolType();
      }
   }

   @Override
   public void overHere(Assignment node) {
      String op = node.operator;
      node.identifier.fryCall(this);
      String identifier = currExprName.identifier;
      var lType = currExprType;
      var lValue = currExprValue;
      node.expression.fryCall(this);
      var rType = currExprType;
      var rValue = currExprValue;

      switch (op) {
         case "=":
            if (lType.isIntType() && rType.isIntType()) {
               variableTable.rebind(identifier, rValue);
               currExprType = new IntType();
            } else if (lType.isRealType() && rType.isRealType()) {
               variableTable.rebind(identifier, rValue);
               currExprType = new RealType();
            } else if (lType.isStringType() && rType.isStringType()) {
               variableTable.rebind(identifier, rValue);
               currExprType = new StringType();
            } else if (lType.isBoolType() && rType.isBoolType()) {
               variableTable.rebind(identifier, rValue);
               currExprType = new BoolType();
            } else if (lType.isArrayType() && rType.isArrayType()) {
               variableTable.rebind(identifier, rValue);
               currExprType = lType;
            }
            break;

         case "+=":
            if (lType.isIntType() && rType.isIntType()) {
               int l = (int) variableTable.lookup(identifier);
               l += (int) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new IntType();
            } else if (lType.isRealType() && rType.isRealType()) {
               double l = (double) variableTable.lookup(identifier);
               l += (double) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new RealType();
            } else if (lType.isStringType() && (rType.isIntType() || rType.isRealType() || rType.isBoolType() || rType.isStringType())) {
               String l = "" + variableTable.lookup(identifier);
               if (rType.isIntType()) {
                  l += rValue;
               } else if (rType.isRealType()) {
                  l += rValue;
               } else if (rType.isBoolType()) {
                  l += rValue;
               } else {
                  l += rValue;
               }
               variableTable.rebind(identifier, l);
               currExprType = new StringType();
            }
            break;

         case "-=":
            if (lType.isIntType() && rType.isIntType()) {
               int l = (int) variableTable.lookup(identifier);
               l -= (int) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new IntType();
            } else if (lType.isRealType() && rType.isRealType()) {
               double l = (double) variableTable.lookup(identifier);
               l -= (double) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new RealType();
            }
            break;

         case "*=":
            if (lType.isIntType() && rType.isIntType()) {
               int l = (int) variableTable.lookup(identifier);
               l *= (int) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new IntType();
            } else if (lType.isRealType() && rType.isRealType()) {
               double l = (double) variableTable.lookup(identifier);
               l *= (double) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new RealType();
            }
            break;

         case "/=":
            if (lType.isIntType() && rType.isIntType()) {
               int l = (int) variableTable.lookup(identifier);
               l /= (int) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new IntType();
            } else if (lType.isRealType() && rType.isRealType()) {
               double l = (double) variableTable.lookup(identifier);
               l /= (double) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new RealType();
            }
            break;

         case "%=":
            if (lType.isIntType() && rType.isIntType()) {
               int l = (int) variableTable.lookup(identifier);
               l %= (int) rValue;
               variableTable.rebind(identifier, l);
               currExprType = new IntType();
            }
            break;

         case "**=":
            if (lType.isIntType() && rType.isIntType()) {
               int l = (int) variableTable.lookup(identifier);
               l = (int) Math.pow(l, (int) rValue);
               variableTable.rebind(identifier, l);
               currExprType = new IntType();
            } else if (lType.isRealType() && rType.isRealType()) {
               double l = (double) variableTable.lookup(identifier);
               l = Math.pow(l, (double) rValue);
               variableTable.rebind(identifier, l);
               currExprType = new RealType();
            }
            break;
      }
   }

   @Override
   public void overHere(BinaryOperation node) {
      String op = node.operator;
      node.left.fryCall(this);
      var lType = currExprType;
      var lValue = currExprValue;
      node.right.fryCall(this);
      var rType = currExprType;
      var rValue = currExprValue;

      switch (op) {
         case "+", "-", "*", "/", "%", "**":
            if (lType.isIntType() && rType.isIntType()) {
               int l = (int) lValue;
               int r = (int) rValue;
               currExprType = new IntType();
               switch (op) {
                  case "+" -> currExprValue = l + r;
                  case "-" -> currExprValue = l - r;
                  case "*" -> currExprValue = l * r;
                  case "/" -> currExprValue = l / r;
                  case "%" -> currExprValue = l % r;
                  default -> currExprValue = (int) Math.pow(l, r);
               }
               break;
            } else if (lType.isRealType() && rType.isRealType()) {
               double l = (double) lValue;
               double r = (double) rValue;
               currExprType = new RealType();
               switch (op) {
                  case "+" -> currExprValue = l + r;
                  case "-" -> currExprValue = l - r;
                  case "*" -> currExprValue = l * r;
                  case "/" -> currExprValue = l / r;
                  case "%" -> currExprValue = l % r;
                  default -> currExprValue = Math.pow(l, r);
               }
               break;
            } else if ((lType.isStringType() && (rType.isIntType() || rType.isRealType() || rType.isBoolType() ||
                   rType.isStringType())) || (rType.isStringType() && (lType.isIntType() || lType.isRealType() ||
                   lType.isBoolType() || lType.isStringType()))) {
               if (op.equals("+")) {
                  String l = "";
                  String r = "";
                  if (lType.isStringType()) {
                     l = (String) lValue;
                     if (rType.isIntType()) {
                        r += rValue;
                     } else if (rType.isRealType()) {
                        r += rValue;
                     } else if (rType.isBoolType()) {
                        r += rValue;
                     } else {
                        r += rValue;
                     }
                  } else if (rType.isStringType()) {
                     r = (String) rValue;
                     if (lType.isIntType()) {
                        l += lValue;
                     } else if (lType.isRealType()) {
                        l += lValue;
                     } else if (lType.isBoolType()) {
                        l += lValue;
                     } else {
                        l += lValue;
                     }
                  }
                  currExprValue = l + r;
                  currExprType = new StringType();
               }
               break;
            }

         case "and", "or": {
            currExprType = new BoolType();
            boolean l = (boolean) lValue;
            boolean r = (boolean) rValue;
            switch (op) {
               case "and" -> currExprValue = l && r;
               case "or" -> currExprValue = l || r;
            }
            break;
         }

         default: {
            currExprType = new BoolType();
            if (lType.isBoolType()) {
               boolean l = (boolean) lValue;
               boolean r = (boolean) rValue;
               switch (op) {
                  case "==" -> currExprValue = l == r;
                  case "<>" -> currExprValue = l != r;
               }
            } else if (lType.isStringType()) {
               String l = (String) lValue;
               String r = (String) rValue;
               switch (op) {
                  case "==" -> currExprValue = l.equals(r);
                  case "<>" -> currExprValue = !l.equals(r);
               }
            } else if (lType.isIntType()) {
               int l = (int) lValue;
               int r = (int) rValue;
               switch (op) {
                  case "==" -> currExprValue = l == r;
                  case "<>" -> currExprValue = l != r;
                  case "<" -> currExprValue = l < r;
                  case ">" -> currExprValue = l > r;
                  case "<=" -> currExprValue = l <= r;
                  case ">=" -> currExprValue = l >= r;
               }
            } else if (lType.isRealType()) {
               double l = (double) lValue;
               double r = (double) rValue;
               switch (op) {
                  case "==" -> currExprValue = l == r;
                  case "<>" -> currExprValue = l != r;
                  case "<" -> currExprValue = l < r;
                  case ">" -> currExprValue = l > r;
                  case "<=" -> currExprValue = l <= r;
                  case ">=" -> currExprValue = l >= r;
               }
            }
         }
      }
   }

   @Override
   public void overHere(BoolLiteral node) {
      currExprValue = node.value;
      currExprType = new BoolType();
   }

   @Override
   public void overHere(Call node) {
      node.qualifier.fryCall(this);
      String identifier = currExprName.identifier;
      var arguments = new ArrayList<>();
      node.arguments.forEach(arg -> {
         arg.fryCall(this);
         arguments.add(currExprValue);
      });
      var function = functionTable.lookup(identifier);
      variableTable.openScope();
      for (int i = 0; i < arguments.size(); i++) {
         var param = function.parameters.get(i);
         variableTable.bind(param.name.identifier, arguments.get(i));
      }
      for (var s : function.body) {
         if (inReturn) break;
         s.fryCall(this);
      }
      variableTable.closeScope();
      inReturn = false;
   }

   @Override
   public void overHere(FieldAccess node) {
   }

   @Override
   public void overHere(Group node) {
      node.expression.fryCall(this);
   }

   @Override
   public void overHere(IntLiteral node) {
      currExprValue = node.value;
      currExprType = new IntType();
   }

   @Override
   public void overHere(ArrayLiteral node) {
      var values = new ArrayList<>();
      int length = 0;
      for (var e : node.expressions) {
         e.fryCall(this);
         values.add(currExprValue);
         ++length;
      }
      currExprValue = values;
      currExprType = new ArrayType(currExprType, new IntLiteral(length));
   }

   @Override
   public void overHere(Name node) {
      currExprName = node;
      if (functionTable.lookup(node.identifier) == null) {
         Object value = variableTable.lookup(node.identifier);
         if (value instanceof Integer i) {
            currExprValue = i;
            currExprType = new IntType();
         } else if (value instanceof Double d) {
            currExprValue = d;
            currExprType = new RealType();
         } else if (value instanceof Boolean b) {
            currExprValue = b;
            currExprType = new BoolType();
         } else if (value instanceof String s) {
            currExprValue = s;
            currExprType = new StringType();
         } else if (value instanceof ArrayList<?> a) {
            int len = a.size();
            Type type = null;
            if (a.get(0) instanceof Integer i) {
               type = new IntType();
            } else if (a.get(0) instanceof Double d) {
               type = new RealType();
            } else if (a.get(0) instanceof Boolean b) {
               type = new BoolType();
            } else if (a.get(0) instanceof String s) {
               type = new StringType();
            }
            currExprValue = a;
            currExprType = new ArrayType(type, new IntLiteral(len));
         } else {
            throw new RuntimeException("ERROR: Unknown semantic error during name resolution.");
         }
      }
   }

   @Override
   public void overHere(NoneLiteral node) {
      currExprValue = node.value;
      currExprType = new NoneType();
   }

   @Override
   public void overHere(NotOperation node) {
      node.expression.fryCall(this);
      currExprValue = !(boolean) currExprValue;
      currExprType = new BoolType();
   }

   @Override
   public void overHere(ObjectLiteral node) {
   }

   @Override
   public void overHere(RealLiteral node) {
      currExprValue = node.value;
      currExprType = new RealType();
   }

   @Override
   public void overHere(StringLiteral node) {
      currExprValue = node.value;
      currExprType = new StringType();
   }

   @Override
   public void overHere(UnaryOperation node) {
      String op = node.operator;
      node.expression.fryCall(this);
      switch (op) {
         case "+", "-":
            if (currExprType.isIntType() && "-".equals(op)) {
               currExprValue = (int) currExprValue * -1;
            } else if (currExprType.isRealType() && "-".equals(op)) {
               currExprValue = (double) currExprValue * -1.0;
            }
            break;
      }
   }

   // Statements

   @Override
   public void overHere(Except node) {

   }

   @Override
   public void overHere(ExpressionStat node) {
      node.expression.fryCall(this);
   }

   @Override
   public void overHere(Finally node) {

   }

   @Override
   public void overHere(ForLoop node) {
      node.expression.fryCall(this);
      node.variable.fryCall(this);
      variableTable.openScope();
      if (currExprValue instanceof ArrayList<?> list) {
         var type = currExprType.asArrayType().type;
         for (Object o : list) {
            currExprValue = o;
            currExprType = type;
            variableTable.rebind(node.variable.name.identifier, o);
            node.body.forEach(s -> s.fryCall(this));
         }
      } else {
         throw new RuntimeException("ERROR: Unknown semantic error during loop resolution.");
      }
      variableTable.closeScope();
   }

   @Override
   public void overHere(Function node) {
      functionTable.bind(node.name.identifier, node);
   }

   @Override
   public void overHere(IfElse node) {
      node.condition.fryCall(this);
      if ((boolean) currExprValue) {
         node.body.forEach(stat -> stat.fryCall(this));
      } else {
         if (!node.orElse.isEmpty()) {
            node.orElse.forEach(stat -> stat.fryCall(this));
         }
      }
   }

   @Override
   public void overHere(Import node) {
   }

   @Override
   public void overHere(Pass node) {
   }

   @Override
   public void overHere(Print node) {
      node.expression.fryCall(this);
      if (currExprType.isIntType()) {
         System.out.println((int) currExprValue);
      } else if (currExprType.isRealType()) {
         System.out.println((double) currExprValue);
      } else if (currExprType.isBoolType()) {
         System.out.println((boolean) currExprValue);
      } else if (currExprType.isStringType()) {
         System.out.println((String) currExprValue);
      } else {
         throw new RuntimeException("ERROR: Unknown semantic error during I/O resoltion.");
      }
   }

   @Override
   public void overHere(Return node) {
      if (node.expression != null) {
         node.expression.fryCall(this);
      }
      inReturn = true;
   }

   @Override
   public void overHere(Try node) {
   }

   @Override
   public void overHere(WhileLoop node) {
      node.condition.fryCall(this);
      while ((boolean) currExprValue) {
         node.body.forEach(stat -> stat.fryCall(this));
         node.condition.fryCall(this);
      }
   }

   @Override
   public void overHere(Var node) {
      if (node.value != null) {
         node.value.fryCall(this);
         if (currExprType.isIntType()) {
            variableTable.bind(node.name.identifier, (int) currExprValue);
         } else if (currExprType.isRealType()) {
            variableTable.bind(node.name.identifier, (double) currExprValue);
         } else if (currExprType.isBoolType()) {
            variableTable.bind(node.name.identifier, (boolean) currExprValue);
         } else if (currExprType.isStringType()) {
            variableTable.bind(node.name.identifier, (String) currExprValue);
         } else if (currExprType.isArrayType()) {
            variableTable.bind(node.name.identifier, (ArrayList<?>) currExprValue);
         } else {
            throw new RuntimeException("ERROR: Unknown semantic error during variable resolution.");
         }
      } else {
         variableTable.bind(node.name.identifier, null);
      }
   }

   // Types

   @Override
   public void overHere(IntType node) {
      currExprType = node;
   }

   @Override
   public void overHere(RealType node) {
      currExprType = node;
   }

   @Override
   public void overHere(BoolType node) {
      currExprType = node;
   }

   @Override
   public void overHere(StringType node) {
      currExprType = node;
   }

   @Override
   public void overHere(ArrayType node) {
      currExprType = node;
   }

   @Override
   public void overHere(NoneType node) {
      currExprType = node;
   }

   @Override
   public void overHere(VoidType node) {
      currExprType = node;
   }

   // Nodes

   @Override
   public void overHere(Program node) {
      node.children.forEach(stat -> stat.fryCall(this));
   }

   @Override
   public void overHere(Class node) {

   }

   @Override
   public void overHere(Parameter node) {
      node.type.fryCall(this);
      variableTable.bind(node.name.identifier, currExprType);
   }
}
