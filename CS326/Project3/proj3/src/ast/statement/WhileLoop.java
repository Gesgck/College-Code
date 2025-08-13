package ast.statement;

import java.util.ArrayList;
import java.util.List;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents a while statement of the form:
 * <pre>
 *   while expression {
 *     body
 *   }
 * </pre>
 */
public class WhileLoop extends Statement {

   public Expression condition;
   public List<Statement> body;

   public WhileLoop() {
      this(null, new ArrayList<>());
   }

   public WhileLoop(Expression condition, List<Statement> body) {
      this.condition = condition;
      this.body = body;

      addChild(condition);
      body.forEach(this::addChild);
   }

   @Override
   public boolean isWhile() {
      return true;
   }

   @Override
   public WhileLoop asWhileLoop() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
