package ast.expression;

import tools.Fry;

/**
 * Represents a binary expression of the form:
 * <pre>
 *   expression operator expression
 * </pre>
 */
public class BinaryOperation extends Expression {

   public Expression left;
   public Expression right;
   public String operator;

   public BinaryOperation(Expression left, Expression right, String operator) {
      this.left = left;
      this.right = right;
      this.operator = operator;

      addChild(left);
      addChild(right);
   }

   @Override
   public boolean isBinaryOperation() {
      return true;
   }

   @Override
   public BinaryOperation asBinaryOperation() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
