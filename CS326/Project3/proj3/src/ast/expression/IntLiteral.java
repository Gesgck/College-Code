package ast.expression;

import tools.Fry;

/**
 * Represents an integer literal value.
 */
public class IntLiteral extends Literal {

   public int value;

   public IntLiteral(int value) {
      this.value = value;
   }

   @Override
   public String toString() {
      return String.valueOf(value);
   }

   @Override
   public boolean isIntLiteral() {
      return true;
   }

   @Override
   public IntLiteral asIntLiteral() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
