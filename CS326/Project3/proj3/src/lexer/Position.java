package lexer;

public class Position implements Comparable<Position> {

   public int line;
   public int column;

   public Position() {
      this(1, 1);
   }

   public Position(int line, int column) {
      this.line = line;
      this.column = column;
   }

   public void lines(int count) {
      if (count > 0) {
         column = 1;
         line = add(line, count);
      }
   }

   public void columns(int count) {
      column = add(column, count);
   }

   private int add(int lhs, int rhs) {
      return Math.max(lhs + rhs, 1);
   }

   public Position addWith(int width) {
      var result = new Position(line, column);
      result.columns(width);
      return result;
   }

   public Position subtractWidth(int width) {
      return addWith(-width);
   }

   public boolean isAfter(Position position) {
      if (line == position.line) {
         return column > position.column;
      }
      return line > position.line;
   }

   public boolean isBefore(Position position) {
      if (line == position.line) {
         return column < position.column;
      }
      return line < position.line;
   }

   public boolean isAfterOrEqual(Position position) {
      return isAfter(position) || equals(position);
   }

   public boolean isBeforeOrEqual(Position position) {
      return isBefore(position) || equals(position);
   }

   @Override
   public String toString() {
      return line + "." + column;
   }

   @Override
   public int compareTo(Position other) {
      return isBefore(other) ? -1 : isAfter(other) ? 1 : 0;
   }

   @Override
   public boolean equals(Object obj) {
      if (this == obj) {
         return true;
      }
      if (!(obj instanceof Position other)) {
         return false;
      }
      return line == other.line && column == other.column;
   }
}
