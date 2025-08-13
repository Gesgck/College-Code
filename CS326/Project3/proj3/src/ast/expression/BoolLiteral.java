package ast.expression;

import tools.Fry;

/**
 * Represents a boolean literal value.
 */
public class BoolLiteral extends Literal {

   public boolean value;

   public BoolLiteral(boolean value) {
      this.value = value;
   }

   @Override
   public String toString() {
      return String.valueOf(value);
   }

   @Override
   public boolean isBoolLiteral() {
      return true;
   }

   @Override
   public BoolLiteral asBoolLiteral() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
