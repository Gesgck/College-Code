package ast.expression;

import tools.Fry;

/**
 * Represents a group expression.
 */
public class Group extends Expression {

   public Expression expression;

   public Group(Expression expression) {
      this.expression = expression;

      addChild(expression);
   }

   @Override
   public boolean isGroup() {
      return true;
   }

   @Override
   public Group asGroup() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
