package ast.expression;

import java.util.List;

import tools.Fry;

/**
 * Represents an instance of a class.
 */
public class ObjectLiteral extends Expression {

   public List<Expression> arguments;

   public ObjectLiteral(List<Expression> arguments) {
      this.arguments = arguments;

      arguments.forEach(this::addChild);
   }

   @Override
   public boolean isObjectLiteral() {
      return true;
   }

   @Override
   public ObjectLiteral asObjectLiteral() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
