package ast.statement;

import java.util.ArrayList;
import java.util.List;

import tools.Fry;

/**
 * Represents the optional final catch-block of a try-block statement.
 */
public class Finally extends Statement {

   public List<Statement> body;

   public Finally() {
      this(new ArrayList<>());
   }

   public Finally(List<Statement> body) {
      this.body = body;

      body.forEach(this::addChild);
   }

   @Override
   public boolean isFinally() {
      return true;
   }

   @Override
   public Finally asFinally() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
