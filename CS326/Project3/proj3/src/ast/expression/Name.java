package ast.expression;

import tools.Fry;

/**
 * Represents a variable name.
 */
public class Name extends Expression {

   public String identifier;

   public Name(String identifier) {
      this.identifier = identifier;
   }

   @Override
   public String toString() {
      return identifier;
   }

   @Override
   public boolean isName() {
      return true;
   }

   @Override
   public Name asName() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
