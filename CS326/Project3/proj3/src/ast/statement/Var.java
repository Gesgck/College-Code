package ast.statement;

import ast.types.Type;
import ast.expression.Expression;
import ast.expression.Name;
import tools.Fry;

/**
 * Represents a variable declaration of the form:
 * <pre>
 *   var name type [= expression]
 * </pre>
 * where {@code = expression} is optional.
 */
public class Var extends Statement {

   public Name name;
   public Type type;
   public Expression value;

   public Var(Name name, Type type) {
      this(name, type, null);
   }

   public Var(Name name, Type type, Expression value) {
      this.name = name;
      this.type = type;
      this.value = value;

      addChild(name);
      addChild(type);
      if (value != null) {
         addChild(value);
      }
   }

   @Override
   public boolean isVar() {
      return true;
   }

   @Override
   public Var asVar() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
