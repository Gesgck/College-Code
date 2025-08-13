package ast.statement;

import tools.Fry;

/**
 * Represents a pass statement in a statement.
 */
public class Pass extends Statement {

   @Override
   public String toString() {
      return "pass";
   }

   @Override
   public boolean isPass() {
      return true;
   }

   @Override
   public Pass asPass() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
