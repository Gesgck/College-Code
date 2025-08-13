package ast.expression;

import tools.Fry;

/**
 * Represents a unary expression of the form:
 * <pre>
 *   operator expression
 * </pre>
 */
public class UnaryOperation extends Expression {

   public String operator;
   public Expression expression;

   public UnaryOperation(String operator, Expression expression) {
      this.operator = operator;
      this.expression = expression;

      addChild(expression);
   }

   @Override
   public String toString() {
      return operator + expression;
   }

   @Override
   public boolean isUnaryOperation() {
      return true;
   }

   @Override
   public UnaryOperation asUnaryOperation() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
