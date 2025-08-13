package ast.types;

import tools.Fry;

/**
 * Represents the boolean type.
 */
public class BoolType extends Type {

   @Override
   public boolean isBoolType() {
      return true;
   }

   @Override
   public BoolType asBoolType() {
      return this;
   }

   @Override
   public String toString() {
      return "bool";
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
