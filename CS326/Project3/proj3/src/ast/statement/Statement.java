package ast.statement;

import ast.Node;

/**
 * Represents a statement.
 */
public abstract class Statement extends Node {

   public boolean isAssignment() {
      return false;
   }

   public Assignment asAssignment() {
      throw new ClassCastException("Illegal class cast type for a non Assignment statement.");
   }

   public boolean isExcept() {
      return false;
   }

   public Except asExcept() {
      throw new ClassCastException("Illegal class cast type for a non Except statement.");
   }

   public boolean isExpressionStatement() {
      return false;
   }

   public ExpressionStat asExpressionStatement() {
      throw new ClassCastException("Illegal class cast type for a non Expression statement.");
   }

   public boolean isFinally() {
      return false;
   }

   public Finally asFinally() {
      throw new ClassCastException("Illegal class cast type for a non Finally statement.");
   }

   public boolean isForLoop() {
      return false;
   }

   public ForLoop asForLoop() {
      throw new ClassCastException("Illegal class cast type for a non ForLoop statement.");
   }

   public boolean isFunction() {
      return false;
   }

   public Function asFunction() {
      throw new ClassCastException("Illegal class cast type for a non Function statement.");
   }

   public boolean isIfElse() {
      return false;
   }

   public IfElse asIfElse() {
      throw new ClassCastException("Illegal class cast type for a non If statement.");
   }

   public boolean isImport() {
      return false;
   }

   public Import asImport() {
      throw new ClassCastException("Illegal class cast type for a non Import statement.");
   }

   public boolean isPass() {
      return false;
   }

   public Pass asPass() {
      throw new ClassCastException("Illegal class cast type for a non Pass statement.");
   }

   public boolean isPrint() {
      return false;
   }

   public Print asPrint() {
      throw new ClassCastException("Illegal class cast type for a non Print statement.");
   }

   public boolean isReturn() {
      return false;
   }

   public Return asReturn() {
      throw new ClassCastException("Illegal class cast type for a non Return statement.");
   }

   public boolean isTry() {
      return false;
   }

   public Try asTry() {
      throw new ClassCastException("Illegal class cast type for a non Try statement.");
   }

   public boolean isVar() {
      return false;
   }

   public Var asVar() {
      throw new ClassCastException("Illegal class cast type for a non Var statement.");
   }

   public boolean isWhile() {
      return false;
   }

   public WhileLoop asWhileLoop() {
      throw new ClassCastException("Illegal class cast type for a non WhileLoop statement.");
   }

   @Override
   public void addChild(Node child) {
      children.add(child);
   }
}
