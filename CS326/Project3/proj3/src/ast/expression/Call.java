package ast.expression;

import java.util.List;

import tools.Fry;

/**
 * Represents a function call of the form:
 * <pre>
 *   name ( expression )
 * </pre>
 */
public class Call extends Expression {

   public Expression qualifier;
   public List<Expression> arguments;

   public Call(Expression qualifier, List<Expression> arguments) {
      this.qualifier = qualifier;
      this.arguments = arguments;

      addChild(qualifier);
      arguments.forEach(this::addChild);
   }

   @Override
   public boolean isCall() {
      return true;
   }

   @Override
   public Call asCall() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
