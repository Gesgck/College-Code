package ast;

import java.util.ArrayList;
import java.util.List;

import ast.types.Type;
import tools.Fry;

// Defined abstract base class for all abstract-syntax tree nodes.
// Note that this also serves to define the visitable "objects"
// (which are instances of this class).
public abstract class Node {

   // All AST nodes have a member which stores their base type
   // (i.e., int, real, bool, string, object), which is useful
   // for semantic analysis
   public Type nodeType;

   // All AST nodes have a member which stores the class name,
   // applicable if the base type is object. Otherwise, this
   // field may be unused
   public String objectClassName;

   // All AST nodes have a member which stores its children
   // (remember an AST node is a tree data structure that can
   // have N number of children)
   public List<Node> children = new ArrayList<>();

   // Appends a child node to the list of children. This method
   // is only used for printing the abstract-syntax tree.
   public abstract void addChild(Node child);

   // A generic way to visit each child of this AST using Fry's
   // way of thinking... Note that this method is defined in
   // each class that extends JsNode.
   public abstract void fryCall(Fry v);
}
