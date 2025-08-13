package ast;

import java.util.ArrayList;
import java.util.List;

import ast.expression.Name;
import ast.statement.Statement;
import tools.Fry;

/**
 * Represents a class declaration of the form:
 * <pre>
 *   class name {
 *     body
 *   }
 * </pre>
 */
public class Class extends Statement {

   public Name name;
   public List<Statement> body;

   public Class() {
      this(null, new ArrayList<>());
   }

   public Class(Name name, List<Statement> body) {
      this.name = name;
      this.body = body;

      addChild(name);
      body.forEach(this::addChild);
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
