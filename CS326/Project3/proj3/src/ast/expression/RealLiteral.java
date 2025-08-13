package ast.expression;

import tools.Fry;

/**
 * Represents a double literal value.
 */
public class RealLiteral extends Literal {

   public double value;

   public RealLiteral(double value) {
      this.value = value;
   }

   @Override
   public String toString() {
      return String.valueOf(value);
   }

   @Override
   public boolean isRealLiteral() {
      return true;
   }

   @Override
   public RealLiteral asRealLiteral() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
