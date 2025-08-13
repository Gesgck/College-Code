package ast.types;

import ast.expression.Expression;
import tools.Fry;

/**
 * Represents the array type.
 */
public class ArrayType extends Type {

   public Type type;

   public Expression length;

   public ArrayType(Type type, Expression length) {
      this.type = type;
      this.length = length;

      addChild(type);
      addChild(length);
   }

   @Override
   public boolean isArrayType() {
      return true;
   }

   @Override
   public ArrayType asArrayType() {
      return this;
   }

   @Override
   public String toString() {
      return "[" + length + "]" + type;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
