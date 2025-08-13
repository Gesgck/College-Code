package tools;

import ast.expression.ArrayAccess;
import ast.statement.Assignment;
import ast.expression.BinaryOperation;
import ast.expression.BoolLiteral;
import ast.expression.Call;
import ast.Class;
import ast.statement.Except;
import ast.statement.ExpressionStat;
import ast.expression.FieldAccess;
import ast.statement.Finally;
import ast.statement.ForLoop;
import ast.statement.Function;
import ast.expression.Group;
import ast.statement.IfElse;
import ast.statement.Import;
import ast.expression.IntLiteral;
import ast.expression.ArrayLiteral;
import ast.expression.Name;
import ast.expression.NoneLiteral;
import ast.expression.NotOperation;
import ast.expression.ObjectLiteral;
import ast.Parameter;
import ast.statement.Pass;
import ast.statement.Print;
import ast.expression.RealLiteral;
import ast.statement.Return;
import ast.Program;
import ast.expression.StringLiteral;
import ast.statement.Try;
import ast.expression.UnaryOperation;
import ast.statement.Var;
import ast.statement.WhileLoop;
import ast.types.ArrayType;
import ast.types.BoolType;
import ast.types.IntType;
import ast.types.NoneType;
import ast.types.RealType;
import ast.types.StringType;
import ast.types.VoidType;

/**
 * This interface defines the actions Fry should take based on the
 * specific object class that calls him, much like how Fry adapts
 * his behavior depending on whether he's interacting with a robot,
 * a human, or an alien. Each type of object determines a unique
 * response from Fry, showcasing his versatility and charm in any
 * situation.
 */
public interface Fry {

   // Expressions

   void overHere(ArrayAccess node);

   void overHere(Assignment node);

   void overHere(BinaryOperation node);

   void overHere(BoolLiteral node);

   void overHere(Call node);

   void overHere(FieldAccess node);

   void overHere(Group node);

   void overHere(IntLiteral node);

   void overHere(ArrayLiteral node);

   void overHere(Name node);

   void overHere(NoneLiteral node);

   void overHere(NotOperation node);

   void overHere(ObjectLiteral node);

   void overHere(RealLiteral node);

   void overHere(StringLiteral node);

   void overHere(UnaryOperation node);

   // Statements

   void overHere(Except node);

   void overHere(ExpressionStat node);

   void overHere(Finally node);

   void overHere(ForLoop node);

   void overHere(Function node);

   void overHere(IfElse node);

   void overHere(Import node);

   void overHere(Pass node);

   void overHere(Print node);

   void overHere(Return node);

   void overHere(Try node);

   void overHere(WhileLoop node);

   void overHere(Var node);

   // Types

   void overHere(IntType node);

   void overHere(RealType node);

   void overHere(BoolType node);

   void overHere(StringType node);

   void overHere(ArrayType node);

   void overHere(NoneType node);

   void overHere(VoidType node);

   // Nodes

   void overHere(Program node);

   void overHere(Class node);

   void overHere(Parameter node);
}
