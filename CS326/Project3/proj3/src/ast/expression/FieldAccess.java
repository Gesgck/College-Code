package ast.expression;

import tools.Fry;

/**
 * Represents a member access expression of form:
 * <pre>
 *   object.field
 * </pre>
 * where {@code field} can be a variable or a function.
 */
public class FieldAccess extends Expression {

   public Expression object;
   public Expression field;

   public FieldAccess(Expression object, Expression field) {
      this.object = object;
      this.field = field;

      addChild(object);
      addChild(field);
   }

   @Override
   public boolean isFieldAccess() {
      return true;
   }

   @Override
   public FieldAccess asFieldAccess() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
