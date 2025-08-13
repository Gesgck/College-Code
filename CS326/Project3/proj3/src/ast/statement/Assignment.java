package ast.statement;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents an assignment of the form:
 * <pre>
 *   identifier = expression
 * </pre>
 */
public class Assignment extends Statement {

   public Expression identifier;
   public Expression expression;
   public String operator;

   public Assignment(Expression identifier, Expression expression, String operator) {
      this.identifier = identifier;
      this.expression = expression;
      this.operator = operator;

      addChild(identifier);
      addChild(expression);
   }

   @Override
   public boolean isAssignment() {
      return true;
   }

   @Override
   public Assignment asAssignment() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
