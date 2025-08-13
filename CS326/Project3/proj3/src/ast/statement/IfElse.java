package ast.statement;

import java.util.ArrayList;
import java.util.List;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents an if-else statement of the form:
 * <pre>
 *   if expression {
 *     body
 *   } [elif expression {
 *     body
 *   }] [else {
 *     body
 *   }]
 * </pre>
 * where the {@code elif} and {@code else} statements are optionals.
 */
public class IfElse extends Statement {

   public Expression condition;
   public List<Statement> body;
   public List<Statement> orElse;

   public IfElse() {
      this(null, new ArrayList<>());
   }

   public IfElse(Expression condition, List<Statement> body) {
      this(condition, new ArrayList<>(), new ArrayList<>());
   }

   public IfElse(Expression condition, List<Statement> body, List<Statement> orElse) {
      this.condition = condition;
      this.body = body;
      this.orElse = orElse;

      addChild(condition);
      body.forEach(this::addChild);
      orElse.forEach(this::addChild);
   }

   @Override
   public boolean isIfElse() {
      return true;
   }

   @Override
   public IfElse asIfElse() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
