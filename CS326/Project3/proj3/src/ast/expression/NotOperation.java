package ast.expression;

import tools.Fry;

/**
 * Represents a not expression of the form:
 * <pre>
 *   not expression
 * </pre>
 */
public class NotOperation extends Expression {

   public Expression expression;

   public NotOperation(Expression expression) {
      this.expression = expression;

      addChild(expression);
   }

   @Override
   public boolean isNotOperation() {
      return true;
   }

   @Override
   public NotOperation asNotOperation() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
