package ast.statement;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents a return statement of the form:
 * <pre>
 *   return [expression]
 * </pre>
 * where {@code expression} is optional.
 */
public class Return extends Statement {

   public Expression expression;

   public Return() {
      this(null);
   }

   public Return(Expression expression) {
      this.expression = expression;

      if (expression != null) {
         addChild(expression);
      }
   }

   @Override
   public String toString() {
      return expression != null ? expression.toString() : "None";
   }

   @Override
   public boolean isReturn() {
      return true;
   }

   @Override
   public Return asReturn() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
