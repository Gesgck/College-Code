package scope;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.Stack;

public class Symboltable<T> {

   Map<String, Stack<T>> entries;
   Stack<Set<String>> scopeVariables;

   public Symboltable() {
      this.entries = new HashMap<>();
      this.scopeVariables = new Stack<>();
   }

   public T lookup(String name) {
      // WRITEME: Replace with code if necessary
      // 1.) Check if the name is in the entries table
      if(entries.containsKey(name)){
         // 2.) Return the top most element associated with name
         return entries.get(name).peek(); //CHECK THIS LATER !!!!!!!!!!!!!!!!! <-----------
      }
      return null;
   }

   public boolean bind(String name, T value) {
      // WRITEME: Replace with code if necessary
      // 1.) Check if the name is in the scope variables
      if(scopeVariables.search(name) == -1){
         // 2.) Bind the value to the name by pushing the value on the stack
         //     associated with name

         //make a new stack for entires
         Stack<T> entriesStack = new Stack<>();
         entriesStack.push(value);
         entries.put(name, entriesStack);
         
         //push name to scopeVariables
         Set<String> scopeStack = new HashSet<>();
         scopeStack.add(name);
         scopeVariables.push(scopeStack);
         
         // 3.) Print "INFO: Binding variable " + name + " in scope."
         System.out.print("INFO: Binding variable " + name + " in scope.\n");
         return true;
      }else{
         // 4.) Otherwise, print "ERROR: Variable " + name + " already bound."
         //     if name is already in the scope
         System.out.print("ERROR: Variable " + name + " already bound.\n");
      }

      return false;
   }

   public void rebind(String name, T value) {
      // WRITEME: Replace with code if necessary
      // 1.) Check if name is in the entries table
      if(entries.containsKey(name)){
         // 2.) Push the value onto the stack associated with name
         Stack<T> temp = entries.get(name);
         temp.push(value);
      }else{
         // 3.) Print "ERROR: No binding for variable " + name + " exists."
         //     if name does not exist
         System.out.print("ERROR: No binding for variable " + name + " exists.\n");
      }
      
      
   }

   public void openScope() {
      scopeVariables.push(new HashSet<>());
   }

   public void closeScope() {
      if (!scopeVariables.isEmpty()) {
         for (String name : scopeVariables.pop()) {
            System.out.println("INFO: Removing variable " + name + " from stack.");
            if (entries.containsKey(name)) {
               Stack<T> values = entries.get(name);
               if (values != null) {
                  values.pop();
               } else {
                  System.out.println("ERROR: Variable " + name + " was never bound.");
               }
            } else {
               System.out.println("ERROR: Variable " + name + " not in scope.");
            }
         }
      }
   }
}
