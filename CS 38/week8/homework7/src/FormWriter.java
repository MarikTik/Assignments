public class FormWriter 
{
     public static Draw writeLines(Draw screen, int x, int y, String []lines){
          int yOffset = screen.getFont().getSize();
          y += yOffset;
          for (var line : lines){ 
              screen.textLeft(x, y, line);
              y += yOffset;
          }
  
          return screen;
     }
  
     // accepts newlines as a way to split a single line into pieces
     public static Draw writeLine(Draw screen, int x, int y, String line){
         writeLines(screen, x, y, line.split("[\n]"));
         return screen;
     }

     public static Draw writeCenterAutoShifted(Draw screen, int width, int height, String line){
          screen.text(width / 2, shifter, line);
          shifter += screen.getFont().getSize();
          return screen;
     }
     public static void resetShifter()
     {
          shifter = 10;
     }
     private static int shifter = 10;
      
}
