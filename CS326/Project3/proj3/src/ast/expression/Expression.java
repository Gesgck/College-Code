package ast.expression;

import ast.Node;
import ast.statement.Assignment;

/**
 * Represents an expression.
 */
public abstract class Expression extends Node {

   public boolean isArrayAccess() {
      return false;
   }

   public ArrayAccess asArrayAccess() {
      throw new ClassCastException("Illegal class cast type for a non ArrayAccess expression.");
   }

   public boolean isArrayLiteral() {
      return false;
   }

   public ArrayLiteral asArrayLiteral() {
      throw new ClassCastException("Illegal class cast type for a non ArrayLiteral expression.");
   }

   public boolean isAssignment() {
      return false;
   }

   public Assignment asAssignment() {
      throw new ClassCastException("Illegal class cast type for a non Assignment expression.");
   }

   public boolean isBinaryOperation() {
      return false;
   }

   public BinaryOperation asBinaryOperation() {
      throw new ClassCastException("Illegal class cast type for a non BinaryOperation expression.");
   }

   public boolean isBoolLiteral() {
      return false;
   }

   public BoolLiteral asBoolLiteral() {
      throw new ClassCastException("Illegal class cast type for a non BoolLiteral expression.");
   }

   public boolean isCall() {
      return false;
   }

   public Call asCall() {
      throw new ClassCastException("Illegal class cast type for a non Call expression.");
   }

   public boolean isFieldAccess() {
      return false;
   }

   public FieldAccess asFieldAccess() {
      throw new ClassCastException("Illegal class cast type for a non FieldAccess expression.");
   }

   public boolean isGroup() {
      return false;
   }

   public Group asGroup() {
      throw new ClassCastException("Illegal class cast type for a non Group expression.");
   }

   public boolean isIntLiteral() {
      return false;
   }

   public IntLiteral asIntLiteral() {
      throw new ClassCastException("Illegal class cast type for a non IntLiteral expression.");
   }

   public boolean isName() {
      return false;
   }

   public Name asName() {
      throw new ClassCastException("Illegal class cast type for a non Name expression.");
   }

   public boolean isNoneLiteral() {
      return false;
   }

   public NoneLiteral asNoneLiteral() {
      throw new ClassCastException("Illegal class cast type for a non NoneLiteral expression.");
   }

   public boolean isNotOperation() {
      return false;
   }

   public NotOperation asNotOperation() {
      throw new ClassCastException("Illegal class cast type for a non NotOperation expression.");
   }

   public boolean isObjectLiteral() {
      return false;
   }

   public ObjectLiteral asObjectLiteral() {
      throw new ClassCastException("Illegal class cast type for a non ObjectLiteral expression.");
   }

   public boolean isRealLiteral() {
      return false;
   }

   public RealLiteral asRealLiteral() {
      throw new ClassCastException("Illegal class cast type for a non RealLiteral expression.");
   }

   public boolean isStringLiteral() {
      return false;
   }

   public StringLiteral asStringLiteral() {
      throw new ClassCastException("Illegal class cast type for a non StringLiteral expression.");
   }

   public boolean isUnaryOperation() {
      return false;
   }

   public UnaryOperation asUnaryOperation() {
      throw new ClassCastException("Illegal class cast type for a non UnaryOperation expression.");
   }

   @Override
   public void addChild(Node child) {
      children.add(child);
   }
}
