package ast.statement;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents a statement with an expression in it.
 */
public class ExpressionStat extends Statement {

   public Expression expression;

   public ExpressionStat(Expression expression) {
      this.expression = expression;

      addChild(expression);
   }

   @Override
   public boolean isExpressionStatement() {
      return true;
   }

   @Override
   public ExpressionStat asExpressionStatement() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
