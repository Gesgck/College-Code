package tools;

import java.util.ArrayList;
import java.util.List;

import ast.Node;

public class AstUtils {

   public static String toAstTree(Node node) {
      var strb = new StringBuilder();
      var list = new ArrayList<Node>();
      list.add(node);
      var child = new ArrayList<List<Node>>();
      child.add(list);
      while (!child.isEmpty()) {
         var curr = child.get(child.size() - 1);
         if (curr.isEmpty()) {
            child.remove(child.size() - 1);
         } else {
            node = curr.remove(0);
            var text = node.getClass().getSimpleName() + (node.children.isEmpty() ? ": " + node.toString() : "");
            var strb2 = new StringBuilder();
            for (int i = 0; i < child.size() - 1; i++) {
               strb2.append(!child.get(i).isEmpty() ? "│  " : "   ");
            }
            strb.append(strb2).append(curr.isEmpty() ? "'-" : "│-").append(text).append("\n");
            if (!node.children.isEmpty()) {
               child.add(new ArrayList<>(node.children));
            }
         }
      }
      return strb.toString();
   }
}
