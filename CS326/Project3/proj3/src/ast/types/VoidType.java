package ast.types;

import tools.Fry;

public class VoidType extends Type {

   @Override
   public String toString() {
      return "void";
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
