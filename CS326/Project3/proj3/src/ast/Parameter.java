package ast;

import ast.expression.Name;
import ast.types.Type;
import tools.Fry;

/**
 * Represents a parameter in a function.
 */
public class Parameter extends Node {

   public Name name;
   public Type type;

   public Parameter(String name, Type type) {
      this(new Name(name), type);
   }

   public Parameter(Name name, Type type) {
      this.name = name;
      this.type = type;

      addChild(name);
      addChild(type);
   }

   @Override
   public String toString() {
      return name.toString() + type;
   }

   @Override
   public void addChild(Node child) {
      children.add(child);
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
