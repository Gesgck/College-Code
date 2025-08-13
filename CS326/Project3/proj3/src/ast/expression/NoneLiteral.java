package ast.expression;

import tools.Fry;

/**
 * Represents the null literal value.
 */
public class NoneLiteral extends Literal {

   public Object value;

   public NoneLiteral() {
      this.value = null;
   }

   @Override
   public String toString() {
      return String.valueOf(value);
   }

   @Override
   public boolean isNoneLiteral() {
      return true;
   }

   @Override
   public NoneLiteral asNoneLiteral() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
