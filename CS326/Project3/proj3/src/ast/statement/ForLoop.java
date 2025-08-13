package ast.statement;

import java.util.ArrayList;
import java.util.List;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents a for-statement of the form:
 * <pre>
 *   for identifier in expression {
 *     body
 *   }
 * </pre>
 */
public class ForLoop extends Statement {

   public Var variable;
   public Expression expression;
   public List<Statement> body;

   public ForLoop() {
      this(null, null, new ArrayList<>());
   }

   public ForLoop(Var variable, Expression expression, List<Statement> body) {
      this.variable = variable;
      this.expression = expression;
      this.body = body;

      addChild(variable);
      addChild(expression);
      body.forEach(this::addChild);
   }

   @Override
   public boolean isForLoop() {
      return true;
   }

   @Override
   public ForLoop asForLoop() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
