package ast.expression;

import tools.Fry;

/**
 * Represents a String literal value.
 */
public class StringLiteral extends Literal {

   public String value;

   public StringLiteral(String value) {
      this.value = value;
   }

   @Override
   public String toString() {
      return value;
   }

   @Override
   public boolean isStringLiteral() {
      return true;
   }

   @Override
   public StringLiteral asStringLiteral() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
