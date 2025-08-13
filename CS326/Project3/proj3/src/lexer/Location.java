package lexer;

public class Location {

   public Position begin;
   public Position end;

   public Location() {
      this(1, 1);
   }

   public Location(int line, int column) {
      begin = new Position(line, column);
      end = begin;
   }

   public Location(Position begin, Position end) {
      if (begin == null || end == null) {
         throw new IllegalArgumentException("The begin position and end position cannot be null");
      }
      if (end.isBefore(begin)) {
         var temp = begin;
         begin = end;
         end = temp;
      }
      this.begin = begin;
      this.end = end;
   }

   public void step() {
      begin = end;
   }

   public void columns(int count) {
      end = end.addWith(count);
   }

   public void lines(int count) {
      end.lines(count);
   }

   public Location addLocation(Location loc) {
      return new Location(begin, loc.end);
   }

   public Location addWith(int width) {
      var result = new Location(begin, end);
      result.columns(width);
      return result;
   }

   public Location subtractWidth(int width) {
      return addWith(-width);
   }

   public Location copy() {
      var begin_ = new Position(begin.line, begin.column);
      var end_ = new Position(end.line, end.column);
      return new Location(begin_, end_);
   }

   @Override
   public String toString() {
      int endColumn = 0 < end.column ? end.column - 1 : 0;
      String str = begin.toString();
      if (begin.line < end.line) {
         str += "-" + end.line + "." + endColumn;
      }
      if (begin.column < endColumn) {
         str += "-" + endColumn;
      }
      return str;
   }
}
