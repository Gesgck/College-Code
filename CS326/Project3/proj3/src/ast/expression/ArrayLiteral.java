package ast.expression;

import java.util.List;

import tools.Fry;

public class ArrayLiteral extends Literal {

   public List<Expression> expressions;

   public ArrayLiteral(List<Expression> expressions) {
      this.expressions = expressions;

      expressions.forEach(this::addChild);
   }

   @Override
   public boolean isArrayLiteral() {
      return true;
   }

   @Override
   public ArrayLiteral asArrayLiteral() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
