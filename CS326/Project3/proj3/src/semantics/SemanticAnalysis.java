package semantics;

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
import java.util.ArrayList;
import scope.Symboltable;
import tools.Fry;

// SemanticAnalysis Visitor Functions: These are the functions
// you will complete to build the symbol table and type check
// the program. Not all functions must have code, many may be
// left empty. Complete the functions that contain the message
// "WRITEME: Replace with code if necessary"
public class SemanticAnalysis implements Fry {

   public Type currentExprType;
   public Function currentFunction;
   public Symboltable<Type> variableTable;
   public Symboltable<Function> functionTable;

   public SemanticAnalysis() {
      this.variableTable = new Symboltable<>();
      this.functionTable = new Symboltable<>();
   }

   void compareArrayTypes(Type t1, Type t2) {
      if (t1.isArrayType() && t2.isArrayType()) {
         var len1 = t1.asArrayType().length.asIntLiteral().value;
         var len2 = t2.asArrayType().length.asIntLiteral().value;
         if (len1 != len2) {
            throw new RuntimeException("ERROR: Expected array of length " + len1 + ", but found "
                   + "one with length " + len2 + ".");
         }
         compareArrayTypes(t1.asArrayType().type, t2.asArrayType().type);
      } else if ((!t1.isIntType() || !t2.isIntType()) && (!t1.isRealType() || !t2.isRealType()) &&
             (!t1.isBoolType() || !t2.isBoolType()) && (!t1.isStringType() || !t2.isStringType())) {
         throw new RuntimeException("ERROR: Types must match for arrays. Found array of type " + t1
                + " and one with type " + t2 + ".");
      }
   }

   Type resolveArrayType(Type t) {
      if (!t.isArrayType()) return t;
      return resolveArrayType(t.asArrayType().type);
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
      node.index.fryCall(this);
      if (currentExprType != null && !currentExprType.isIntType()) {
         throw new RuntimeException("ERROR: Expected integral type for array index, but found "
                + currentExprType + ".");
      }
      node.name.fryCall(this);
      if (!currentExprType.isArrayType()) {
         throw new RuntimeException("ERROR: Expected array type for array name, but found "
                + currentExprType + ".");
      }
      currentExprType = currentExprType.asArrayType().type;
   }

   @Override
   public void overHere(Assignment node) {
      String op = node.operator;
      node.expression.fryCall(this);
      var vType = currentExprType;
      node.identifier.fryCall(this);
      var eType = currentExprType;

      if (vType == null || eType == null) {
         throw new RuntimeException("ERROR: Expected types cannot be null for assignment compatibility.");
      }

      // WRITEME: Replace with code if necessary
      switch (op) {
         case "-=", "*=", "/=":
            // The error message that should be thrown here.
            // 1.) throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator. Found "
            //                + vType + " and " + eType + ".");
            if (!vType.isIntType() && !vType.isRealType() || !eType.isIntType() && !eType.isRealType()){
               throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator. Found "
                               + vType + " and " + eType + ".");
            }
            if(vType.isIntType() && eType.isIntType()){
               node.nodeType = new IntType();
            }else{
               node.nodeType = new RealType();
            }
            break;

         case "+=":
            // No error message is thrown here.
            if(vType.isStringType()){
               if(eType.isBoolType() || eType.isIntType() || eType.isRealType() || eType.isStringType()){
                  node.nodeType = new StringType();
               }
            }
            break;

         case "**=", "%=":
            // The error message that should be thrown here.
            // 1.) throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator.");
            if(vType.isIntType()){
               if(eType.isIntType()){
                  node.nodeType = new IntType();
               }else if(eType.isRealType()){
                  node.nodeType = new RealType();
               }else{
                  throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator."); 
               }
            }else{
               throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator."); 
            }

            break;

         case "=":
            // These are the error messages that should be throw here.
            // 1.) throw new RuntimeException("ERROR: Operand types must match for the = operator. Found " + vType
            //                  + " and " + eType + ".");
            // 2.) throw new RuntimeException("ERROR: Operand types must match for the = operator. Found " + vType
            //                + " and " + eType + ".");
            if(eType.isArrayType()){
               if(vType.isArrayType()){
                  compareArrayTypes(eType, vType);
               }else{
                  throw new RuntimeException("ERROR: Operand types must match for the = operator. Found " + vType
                              + " and " + eType + ".");
               }
            }
            //below does not work with != only ==
            if(eType == vType){
               throw new RuntimeException("ERROR: Operand types must match for the = operator. Found " + vType
                            + " and " + eType + ".");
            }
            break;

         default:
            throw new RuntimeException("ERROR: Unknown semantic error in assignment operator.");
      }
   }

   @Override
   public void overHere(BinaryOperation node) {
      String op = node.operator;
      node.left.fryCall(this);
      var lType = currentExprType;
      node.right.fryCall(this);
      var rType = currentExprType;

      if (lType == null || rType == null) {
         throw new RuntimeException("ERROR: Expected types cannot be null for assignment compatibility.");
      }

      // WRITEME: Replace with code if necessary
      switch (op) {
         // This only work for int/real
         case "*", "/", "-", "**":
            // The error message that should be thrown here.
            // 1.) throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator. Found "
            if(!lType.isIntType() && !lType.isRealType() || !rType.isIntType() && !rType.isRealType()){
               throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator. Found "
               + lType + " on the left and " + rType + " on the right.");
            }
            if(lType.isIntType() && rType.isIntType()){
               node.nodeType = new IntType();
            }else{
               node.nodeType = new RealType();
            }
            break;

         // + works for all types except booleans
         case "+":
            // These are the error messages that should be thrown here.
            // 1.) throw new RuntimeException("ERROR: Invalid operand for + operator. Expected numerical or string.");
            // 2.) throw new RuntimeException("ERROR: Invalid operand for + operator. Found " + lType
            //                + " on the left, but " + rType + " on the right.");
            // 3.) throw new RuntimeException("ERROR: Invalid operand for + operator. Found " + lType
            //                + " on the left, but " + rType + " on the right.");
            // 4.) throw new RuntimeException("ERROR: Invalid operand for + operator. Expected numerical or string.");
            if(lType.isBoolType() || rType.isBoolType()){
               throw new RuntimeException("ERROR: Invalid operand for + operator. Expected numerical or string.");
            }
            if(lType.isStringType() && rType.isStringType()){
               node.nodeType = new StringType();
               break;
            }
            if(lType.isStringType() && !rType.isStringType() || !lType.isStringType() && rType.isStringType()){
               throw new RuntimeException("ERROR: Invalid operand for + operator. Found " + lType
                            + " on the left, but " + rType + " on the right.");
            }
            if(lType.isArrayType() || rType.isArrayType()){
               throw new RuntimeException("ERROR: Invalid operand for + operator. Expected numerical or string.");
            }

            if(lType.isIntType() && rType.isIntType()){
               node.nodeType = new IntType();
            }else{
               node.nodeType = new RealType();
            }

            break;

         // and/or only work for booleans
         case "and", "or":
            // The error message that should be thrown here.
            // 1.) throw new RuntimeException("ERROR: Expected two boolean type operands for " + op + " operator.");
            if(!lType.isBoolType() || !rType.isBoolType()){
               throw new RuntimeException("ERROR: Expected two boolean type operands for " + op + " operator.");
            }else{
               node.nodeType = new BoolType();
            }
            break;

         // relational operators only work for numeric types
         case "<", ">", "<=", ">=":
            // The error message that should be thrown here.
            // 1.) throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator.");
            if (!lType.isIntType() && !lType.isRealType() || !rType.isIntType() && !rType.isRealType()) {
               throw new RuntimeException("ERROR: Expected numerical operands for " + op + " operator.");
            }else{
               node.nodeType = new BoolType();
            }
            break;

         // == and <> work for like types
         case "==", "<>":
            // There error message that should be thrown here.
            // 1.) throw new RuntimeException("ERROR: Expected arguments of the same type for " + op + " operator.");
            if(rType != lType){
               if(lType.isIntType() || lType.isIntType()){
                  if(rType.isIntType() || rType.isRealType()){
                     node.nodeType = new BoolType();
                     break;
                  }
               }
               throw new RuntimeException("ERROR: Expected arguments of the same type for " + op + " operator.");
            }else{
               node.nodeType = new BoolType();
            }
            break;

         default:
            throw new RuntimeException("ERROR: Unknown semantic error in binary operator.");
      }
   }

   @Override
   public void overHere(BoolLiteral node) {
      currentExprType = new BoolType();
   }

   @Override
   public void overHere(Call node) {
      // WRITEME: Replace with code if necessary
      // These are the error messages that should be thrown here.
      // 1.) throw new RuntimeException("ERROR: Invocation has " + argTypes.size() + " arguments. Function "
      //                   + currentFunction.name + " takes " + paramTypes.size() + " arguments.");
      // 2.) throw new RuntimeException("ERROR: Expected argument type to be " + pType + ", but found " + aType + ".");
      // 3.) throw new RuntimeException("ERROR: Unknown semantic error in function call.");
      
      //process the qualifier
      if(node.qualifier != null){
         node.qualifier.fryCall(this);
      }
      
      //check if function is not recognized
      if(currentFunction == null){
         throw new RuntimeException("ERROR: Unknown semantic error in function call.");
      }

      //create lists to hold types
      ArrayList<Type> argTypes = new ArrayList<>(node.arguments.size());
      ArrayList<Type> paramTypes = new ArrayList<>(currentFunction.parameters.size());
      
      for(int i = 0; i < node.arguments.size(); i++){
         node.arguments.get(i).fryCall(this);
         argTypes.add(i, currentExprType);
      }
      for(int i = 0; i < currentFunction.parameters.size(); i++){
         currentFunction.parameters.get(i).fryCall(this);
         paramTypes.add(i, currentExprType);
      }
      if(argTypes.size() != paramTypes.size()){
         throw new RuntimeException("ERROR: Invocation has " + argTypes.size() + " arguments. Function "
                   + currentFunction.name + " takes " + paramTypes.size() + " arguments.");
      }

      for(int i = 0; i<argTypes.size(); i++){
         if(argTypes.get(i).isArrayType() || paramTypes.get(i).isArrayType()){
            //below only works with == not !=
            if(paramTypes.get(i) == argTypes.get(i)){
               compareArrayTypes(argTypes.get(i), paramTypes.get(i));
            }
            else{
               throw new RuntimeException("ERROR: Expected argument type to be " + paramTypes.get(i) + 
                        ", but found " + argTypes.get(i) + ".");
            }
         }
         if(argTypes.get(i) == paramTypes.get(i)){
            throw new RuntimeException("ERROR: Expected argument type to be " + paramTypes.get(i) + 
                     ", but found " + argTypes.get(i) + ".");
         }
      }

      currentExprType = currentFunction.returnType;
      
   }

   @Override
   public void overHere(FieldAccess node) {
      node.object.fryCall(this);
      node.field.fryCall(this);
   }

   @Override
   public void overHere(Group node) {
      node.expression.fryCall(this);
   }

   @Override
   public void overHere(IntLiteral node) {
      currentExprType = new IntType();
   }

   @Override
   public void overHere(ArrayLiteral node) {
      node.expressions.get(0).fryCall(this);
      var type = currentExprType;
      var length = 0;
      for (int i = 1; i < node.expressions.size(); i++) {
         node.expressions.get(i).fryCall(this);
         var eType = currentExprType;
         if (type.getClass() != eType.getClass()) {
            throw new RuntimeException("ERROR: Expected types of array literal to be of the same type, "
                   + "but found " + type + " and " + eType + ".");
         }
         length++;
      }
      currentExprType = new ArrayType(currentExprType, new IntLiteral(length + 1));
   }

   @Override
   public void overHere(Name node) {
      // WRITEME: Replace with code if necessary
      // The error message that should be thrown here.
      // 1.) throw new RuntimeException("ERROR: Identifier " + node.identifier + " was never declared.");

         if(functionTable.lookup(node.identifier) != null){
            currentFunction = functionTable.lookup(node.identifier);
         }
         else if(variableTable.lookup(node.identifier) != null){
            currentExprType = variableTable.lookup(node.identifier);
         }else{
            throw new RuntimeException("ERROR: Identifier " + node.identifier + " was never declared.");
         }
   }

   @Override
   public void overHere(NoneLiteral node) {
      currentExprType = new NoneType();
   }

   @Override
   public void overHere(NotOperation node) {
      node.expression.fryCall(this);
   }

   @Override
   public void overHere(ObjectLiteral node) {
      currentExprType = null;
   }

   @Override
   public void overHere(RealLiteral node) {
      currentExprType = new RealType();
   }

   @Override
   public void overHere(StringLiteral node) {
      currentExprType = new StringType();
   }

   @Override
   public void overHere(UnaryOperation node) {
      String op = node.operator;
      node.expression.fryCall(this);

      // WRITEME: Replace with code if necessary
      // These are the error messages that should be thrown during execution
      // 1.) throw new RuntimeException("ERROR: Operator " + op + " in front of numerical expression.");
      // 2.) throw new RuntimeException("ERROR: Operator " + op + " in front of boolean expression.");
      // 3.) throw new RuntimeException("ERROR: Incompatible unary operator " + op + " in front of expression.");
      if(currentExprType.isIntType() || currentExprType.isRealType()){
         if(op != "+" && op != "-"){
            throw new RuntimeException("ERROR: Operator " + op + " in front of numerical expression.");
         }
      }
      else if(currentExprType.isBoolType()){
         if(op != "not"){
            throw new RuntimeException("ERROR: Operator " + op + " in front of boolean expression.");
         }
      }
      else{
         throw new RuntimeException("ERROR: Incompatible unary operator " + op + " in front of expression.");
      }
   }

   // Statements

   @Override
   public void overHere(Except node) {
      node.variable.fryCall(this);
      variableTable.openScope();
      node.body.forEach(stat -> stat.fryCall(this));
      variableTable.closeScope();
   }

   @Override
   public void overHere(ExpressionStat node) {
      node.expression.fryCall(this);
   }

   @Override
   public void overHere(Finally node) {
      variableTable.openScope();
      node.body.forEach(stat -> stat.fryCall(this));
      variableTable.closeScope();
   }

   @Override
   public void overHere(ForLoop node) {
      node.expression.fryCall(this);
      var eType = currentExprType;
      node.variable.fryCall(this);
      var vType = currentExprType;
      if (!vType.isArrayType() && eType.isArrayType()) {
         eType = resolveArrayType(eType);
         compareArrayTypes(vType, eType);
      }
      variableTable.openScope();
      node.body.forEach(stat -> stat.fryCall(this));
      variableTable.closeScope();
   }

   @Override
   public void overHere(Function node) {
      // WRITEME: Replace with code if necessary
      // The error message that should be thrown here.
      // 1.) throw new RuntimeException("ERROR: Function " + node.name.identifier + " already exists.");
      if(functionTable.lookup(node.name.identifier) != null){
         throw new RuntimeException("ERROR: Function " + node.name.identifier + " already exists.");
      }
      functionTable.bind(node.name.identifier, node);
      openScope();

      //process parameters
      for(int i = 0; i < node.parameters.size(); i++){
         node.parameters.get(i).fryCall(this);
      }
      //NEEDS TO BE WORKED ON
      //WRITEME !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

      //process body
      node.body.forEach(stat -> stat.fryCall(this));

      closeScope();
   }

   @Override
   public void overHere(IfElse node) {
      node.condition.fryCall(this);
      if (currentExprType != null && !currentExprType.isBoolType()) {
         throw new RuntimeException("ERROR: Expected condition to be a boolean expression for "
                + "if stat, but found " + currentExprType);
      }
      variableTable.openScope();
      node.body.forEach(stat -> stat.fryCall(this));
      variableTable.closeScope();
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
   }

   @Override
   public void overHere(Return node) {
      if (node.expression != null) {
         node.expression.fryCall(this);
      }
   }

   @Override
   public void overHere(Try node) {
      variableTable.openScope();
      node.body.forEach(stat -> stat.fryCall(this));
      variableTable.closeScope();
      node.excepts.forEach(stat -> stat.fryCall(this));
      if (node.finalBlock != null) {
         node.finalBlock.fryCall(this);
      }
   }

   @Override
   public void overHere(WhileLoop node) {
      node.condition.fryCall(this);
      if (currentExprType != null && !currentExprType.isBoolType()) {
         throw new RuntimeException("ERROR: Expected condition to be a boolean expression for "
                + "while loop, but found " + currentExprType);
      }
      variableTable.openScope();
      node.body.forEach(stat -> stat.fryCall(this));
      variableTable.closeScope();
   }

   @Override
   public void overHere(Var node) {
      node.type.fryCall(this);
      var vType = currentExprType;
      var success = variableTable.bind(node.name.identifier, vType);
      if (!success) return;
      node.name.fryCall(this);
      if (node.value != null) {
         node.value.fryCall(this);
         var eType = currentExprType;
         if (eType.isArrayType()) {
            if (vType.isArrayType()) {
               compareArrayTypes(vType, eType);
            } else {
               throw new RuntimeException("ERROR: Operand types must match for the = operator. Found "
                      + vType + " and " + eType + ".");
            }
         } else if ((!vType.isIntType() || !eType.isIntType()) && (!vType.isRealType() || !eType.isRealType()) &&
                (!vType.isBoolType() || !eType.isBoolType()) && (!vType.isStringType() || !eType.isStringType())) {
            throw new RuntimeException("ERROR: Operand types must match for the = operator. Found "
                   + vType + " and " + eType + ".");
         }
      }
   }

   // Types

   @Override
   public void overHere(IntType node) {
      currentExprType = node;
   }

   @Override
   public void overHere(RealType node) {
      currentExprType = node;
   }

   @Override
   public void overHere(BoolType node) {
      currentExprType = node;
   }

   @Override
   public void overHere(StringType node) {
      currentExprType = node;
   }

   @Override
   public void overHere(ArrayType node) {
      currentExprType = node;
   }

   @Override
   public void overHere(NoneType node) {
      currentExprType = node;
   }

   @Override
   public void overHere(VoidType node) {
      currentExprType = node;
   }

   // Nodes

   @Override
   public void overHere(Program node) {
      node.children.forEach(stat -> stat.fryCall(this));
   }

   @Override
   public void overHere(Class node) {
      variableTable.openScope();
      node.body.forEach(stat -> stat.fryCall(this));
      variableTable.closeScope();
   }

   @Override
   public void overHere(Parameter node) {
      node.type.fryCall(this);
      variableTable.bind(node.name.identifier, currentExprType);
   }
}
