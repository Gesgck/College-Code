package ast;

import java.util.List;

import ast.statement.Statement;
import tools.Fry;

/**
 * Represents the source file.
 */
public class Program extends Node {

   public Program(List<Statement> statements) {
      statements.forEach(this::addChild);
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
