public class Lecture2 {
    public static void drawTransitionArrow(){
        Draw screen = new Draw();
        int width = 300, height = 640;
        screen.setCanvasSize(width, height);
        screen.setXscale(0, width);
        screen.setYscale(0, height);

        int arrowWidth = 100;
        int arrowHeight = 30;
        int arrowXoffset = 30 + arrowWidth;
        int arrowYOffset = height / 2;

        screen.setPenColor(Draw.BLACK);
        screen.filledRectangle(arrowXoffset, arrowYOffset, arrowWidth, arrowHeight);
        screen.filledPolygon(
            new double[]{230, 230, 280},
            new double[]{arrowYOffset + 50, arrowYOffset -50, arrowYOffset}
        );
        screen.setLocationOnScreen(640 + width / 2, 200);
    }

    public static void setDefaultCanvas(Draw canvas){
        int canvasWidth = 640, canvasHeight = 640;
        canvas.setCanvasSize(canvasWidth, canvasHeight);
        canvas.setXscale(0, (double)canvasWidth);
        canvas.setYscale(0, (double)canvasHeight);
    }
    public static void puzzle1(){
        Draw originalPuzzle = new Draw();
        int canvasWidth = 640, canvasHeight = 640;
        setDefaultCanvas(originalPuzzle);
        originalPuzzle.picture(canvasWidth / 2, canvasHeight / 2, "week2/lecture/images/puzzle1.png", canvasWidth, canvasHeight);
        originalPuzzle.setLocationOnScreen(100, 200);
        drawTransitionArrow();
        
        Draw editedPuzzle = new Draw();
        setDefaultCanvas(editedPuzzle);
        editedPuzzle.picture(canvasWidth / 2, canvasHeight / 2, "week2/lecture/images/puzzle1.png", canvasWidth, canvasHeight);
        
        editedPuzzle.setLocationOnScreen(canvasWidth * 2, 200);
        
        // solve the puzzle
       
        int bigRectArea = 42;
        int smallRectWidth = 4;
        int bigRectWidth = smallRectWidth + 3;
        int bigRectHeight = bigRectArea / bigRectWidth;
        int smallRectHeight = 10 - bigRectHeight;
        int smallRectArea = smallRectHeight * smallRectWidth; // solution

        editedPuzzle.setPenColor(Draw.GRAY);
        editedPuzzle.filledRectangle(200, 400, 80, 80);
        editedPuzzle.setPenColor(Draw.BLACK);
        editedPuzzle.text(230, 420, "area = " + smallRectArea + " in^2" );
       }

    public static void puzzle2(){

    }
    public static void main(String []args){
        puzzle1();
    }
}
