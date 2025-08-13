package ast.expression;

import tools.Fry;

/**
 * Represents an array access expression of the form:
 * <pre>
 *   name[index]
 * </pre>
 */
public class ArrayAccess extends Expression {

   public Expression name;
   public Expression index;

   public ArrayAccess(Expression name, Expression index) {
      this.name = name;
      this.index = index;

      addChild(name);
      addChild(index);
   }

   @Override
   public boolean isArrayAccess() {
      return true;
   }

   @Override
   public ArrayAccess asArrayAccess() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
