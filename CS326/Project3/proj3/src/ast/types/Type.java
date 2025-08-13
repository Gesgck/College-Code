package ast.types;

import ast.Node;

/**
 * Base class for all types in the language.
 */
public abstract class Type extends Node {

   public boolean isArrayType() {
      return false;
   }

   public ArrayType asArrayType() {
      throw new ClassCastException("Illegal class cast type for a non Array type.");
   }

   public boolean isIntType() {
      return false;
   }

   public IntType asIntType() {
      throw new ClassCastException("Illegal class cast type for a non Int type.");
   }

   public boolean isBoolType() {
      return false;
   }

   public BoolType asBoolType() {
      throw new ClassCastException("Illegal class cast type for a non Bool type.");
   }

   public boolean isRealType() {
      return false;
   }

   public RealType asRealType() {
      throw new ClassCastException("Illegal class cast type for a non Real type.");
   }

   public boolean isStringType() {
      return false;
   }

   public StringType asStringType() {
      throw new ClassCastException("Illegal class cast type for a non String type.");
   }

   public boolean isNoneType() {
      return false;
   }

   public NoneType asNoneType() {
      throw new ClassCastException("Illegal class cast type for a non None type.");
   }

   @Override
   public void addChild(Node child) {
      children.add(child);
   }
}
