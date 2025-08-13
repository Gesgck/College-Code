package ast.statement;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents a print statement of the form:
 * <pre>
 *   print ( expression )
 * </pre>
 */
public class Print extends Statement {

   public Expression expression;

   public Print(Expression expression) {
      this.expression = expression;

      addChild(expression);
   }

   @Override
   public boolean isPrint() {
      return true;
   }

   @Override
   public Print asPrint() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
