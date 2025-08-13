package ast.statement;

import java.util.ArrayList;
import java.util.List;

import ast.expression.Name;
import ast.Parameter;
import ast.types.Type;
import tools.Fry;

/**
 * Represents a function of the form:
 * <pre>
 *   def name ( [argument] ) type {
 *     body
 *     [return expression]
 *   }
 * </pre>
 * where {@code argument} is optional.
 */
public class Function extends Statement {

   public Name name;
   public List<Parameter> parameters;
   public Type returnType;
   public List<Statement> body;

   public Function() {
      this(null, new ArrayList<>(), null, new ArrayList<>());
   }

   public Function(Name name, List<Parameter> parameters, Type returnType, List<Statement> body) {
      this.name = name;
      this.parameters = parameters;
      this.returnType = returnType;
      this.body = body;

      addChild(name);
      parameters.forEach(this::addChild);
      addChild(returnType);
      body.forEach(this::addChild);
   }

   @Override
   public boolean isFunction() {
      return true;
   }

   @Override
   public Function asFunction() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
