package ast.types;

import tools.Fry;

/**
 * Represents the string type.
 */
public class StringType extends Type {

   @Override
   public boolean isStringType() {
      return true;
   }

   @Override
   public StringType asStringType() {
      return this;
   }

   @Override
   public String toString() {
      return "string";
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
