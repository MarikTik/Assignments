public class Program {
    public static void bonus(){
        Draw screen = new Draw();
        int width = 640;
        int height = 640;
        screen.setTitle("Mark Tikhonov");
        screen.setCanvasSize(width, height);
        screen.setXscale(0, width);
        screen.setYscale(0, height);
        screen.clear(Draw.LIGHT_GRAY);
        screen.setPenColor(Draw.BLACK);
        int poleXoffset = 185, poleYoffset = 0, poleHeight = 400, poleWidth = 5;
        screen.filledRectangle(poleXoffset, poleYoffset, poleWidth, poleHeight); // drawing the flag pole
        int ballRadius = 30;

        screen.filledCircle( // setting the black circle on top of the flag
            poleXoffset,
            poleYoffset + poleHeight + ballRadius,
            ballRadius
        );

        int textXoffset = 10;
        int textYOffset = 300;
        screen.text(textXoffset, textYOffset, "Mark Tikhonov",90); // setting my name to the given offset and rotating it by 90 degrees

        int flagRectangleWidth = 35;
        int flagRectangleHeight = 60;
        int flagYoffset = 340;
        int flagXoffset = poleXoffset + poleWidth + flagRectangleWidth;

        // this part draws the colorful rectangles which make the flag
        screen.setPenColor(Draw.BLUE);
        screen.filledRectangle(flagXoffset, flagYoffset, flagRectangleWidth, flagRectangleHeight);
        screen.setPenColor(Draw.WHITE);
        screen.filledRectangle(flagXoffset + flagRectangleWidth * 2, flagYoffset, flagRectangleWidth, flagRectangleHeight);
        screen.setPenColor(Draw.RED);
        screen.filledRectangle(flagXoffset + flagRectangleWidth * 4, flagYoffset, flagRectangleWidth, flagRectangleHeight);

        
    }

    public static void q3_13(){
        System.out.println("Enter your annual income: ");
        String annualIncomeStr = System.console().readLine();
        double annualIncome = Double.parseDouble(annualIncomeStr);
    }

    public static void qChallange(){
        Draw screen = new Draw();
        int width = 400;
        int height = 400;
        screen.setCanvasSize(width, height);
        screen.setXscale(0, width);
        screen.setYscale(0, height);
        screen.clear(Draw.WHITE);
        screen.setPenColor(Draw.BLACK);
        screen.filledRectangle(width * 0.75, height * 0.25, width * 0.25, height * 0.25);
        screen.filledRectangle(width * 0.375, height * 0.75, width * 0.125, height * 0.25);
        screen.filledRectangle(width * 0.125, height * 0.25, width * 0.125, height * 0.25);
    }
    public static void main(String[] args){

        //q3_13();
        //qChallange();
        //bonus();
    }
}
