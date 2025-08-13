package ast.types;

import tools.Fry;

/**
 * Represents the int type.
 */
public class IntType extends Type {

   @Override
   public boolean isIntType() {
      return true;
   }

   @Override
   public IntType asIntType() {
      return this;
   }

   @Override
   public String toString() {
      return "int";
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
