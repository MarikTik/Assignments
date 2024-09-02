public class Program {
    
    private static Draw screen = new Draw();

   

    public static void bonus(){
        int width = 640;
        int height = 640;
        screen.setTitle("Mark Tikhonov");
        screen.setCanvasSize(width, height);
        screen.setXscale(0, width);
        screen.setYscale(0, height);
        screen.clear(Draw.LIGHT_GRAY);
        screen.setPenColor(Draw.BLACK);
        int poleXoffset = 185, poleYoffset = 0, poleHeight = 400, poleWidth = 5;
        screen.filledRectangle(poleXoffset, poleYoffset, poleWidth, poleHeight);
        int ballRadius = 30;

        screen.filledCircle(
            poleXoffset,
            poleYoffset + poleHeight + ballRadius,
            ballRadius
        );

        int textXoffset = 10;
        int textYOffset = 300;
        screen.text(textXoffset, textYOffset, "Mark Tikhonov", 90);

        int flagRectangleWidth = 35;
        int flagRectangleHeight = 60;
        int flagYoffset = 340;
        int flagXoffset = poleXoffset + poleWidth + flagRectangleWidth;

        screen.setPenColor(Draw.BLUE);
        screen.filledRectangle(flagXoffset, flagYoffset, flagRectangleWidth, flagRectangleHeight);
        screen.setPenColor(Draw.WHITE);
        screen.filledRectangle(flagXoffset + flagRectangleWidth * 2, flagYoffset, flagRectangleWidth, flagRectangleHeight);
        screen.setPenColor(Draw.RED);
        screen.filledRectangle(flagXoffset + flagRectangleWidth * 4, flagYoffset, flagRectangleWidth, flagRectangleHeight);

        
    }
    public static void main(String[] args){
        bonus();

    }
}
