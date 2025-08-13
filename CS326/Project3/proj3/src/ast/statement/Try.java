package ast.statement;

import java.util.ArrayList;
import java.util.List;

import tools.Fry;

/**
 * Represents a try-catch block of the form
 * <pre>
 *   try {
 *     body
 *   } catch expression {
 *     body
 *   } [finally {
 *     body
 *   }]
 * </pre>
 * where {@code finally} is optional.
 */
public class Try extends Statement {

   public List<Statement> body;
   public List<Statement> excepts;
   public Finally finalBlock;

   public Try(List<Statement> body) {
      this(body, new ArrayList<>(), null);
   }

   public Try(List<Statement> body, List<Statement> excepts, Finally finalBlock) {
      this.body = body;
      this.finalBlock = finalBlock;
      this.excepts = excepts;

      body.forEach(this::addChild);
      excepts.forEach(this::addChild);
      if (finalBlock != null) {
         addChild(finalBlock);
      }
   }

   @Override
   public boolean isTry() {
      return true;
   }

   @Override
   public Try asTry() {
      return this;
   }

   @Override
   public void fryCall(Fry v) {
      v.overHere(this);
   }
}
