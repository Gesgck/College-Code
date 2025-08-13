package ast.statement;

import java.util.List;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents a catch-block in a try-block statement.
 */
public class Except extends Statement {

   public Expression variable;
   public List<Statement> body;

   public Except(Expression variable, List<Statement> body) {
      this.variable = variable;
      this.body = body;

      addChild(variable);
      body.forEach(this::addChild);
   }

   @Override
   public boolean isExcept() {
      return true;
   }

   @Override
   public Except asExcept() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
