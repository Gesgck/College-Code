package ast.types;

import tools.Fry;

/**
 * Represents the void type.
 */
public class NoneType extends Type {

   @Override
   public boolean isNoneType() {
      return true;
   }

   @Override
   public NoneType asNoneType() {
      return this;
   }

   @Override
   public String toString() {
      return "none";
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
