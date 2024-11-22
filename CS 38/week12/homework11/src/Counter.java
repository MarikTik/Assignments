import java.awt.Font;
public class Counter {

     public void click(){
          count++;
     }
     public void reset(){
          count = 0;
     }
     public int getCount(){
          return count;
     }
     private void drawClock(Draw screen){
          screen.clear();
          var clockData = String.format("%04d", count);
          screen.text(200, 200, clockData);
          screen.show();
     }

     // better version of drawMe() in the assignment
     public Draw clock(){
          var screen = Form.defaultForm();
          screen.setFont(new Font("Arial", Font.PLAIN, 92));
          screen.enableDoubleBuffering();
          drawClock(screen);
          screen.addListener(new DrawListener() {
               @Override
               public void mouseClicked(double x, double y) {
                    click();
                    drawClock(screen);
               }

               @Override
               public void mouseDragged(double x, double y) {
                    reset();
                    drawClock(screen);
               }
          });
          return screen;
     }

     private int count = 0;
}
