package ast.statement;

import ast.expression.Name;
import tools.Fry;

/**
 * Represents an import statement of the form:
 * <pre>
 *   import identifier
 * </pre>
 * or
 * <pre>
 *   from identifier import identifier
 * </pre>
 */
public class Import extends Statement {

   public Name module;
   public Name file;

   public Import(Name module) {
      this(module, null);
   }

   public Import(Name module, Name file) {
      this.module = module;
      this.file = file;

      addChild(module);
      if (file != null) {
         addChild(file);
      }
   }

   @Override
   public boolean isImport() {
      return true;
   }

   @Override
   public Import asImport() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
