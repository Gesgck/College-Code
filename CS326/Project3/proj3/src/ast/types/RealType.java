package ast.types;

import tools.Fry;

/**
 * Represents the double type.
 */
public class RealType extends Type {

   @Override
   public boolean isRealType() {
      return true;
   }

   @Override
   public RealType asRealType() {
      return this;
   }

   @Override
   public String toString() {
      return "real";
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
