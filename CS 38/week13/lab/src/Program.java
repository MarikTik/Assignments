public class Program {
    public static void main(String []args){
        //DiceDemoMT.demo(20);
        //Puzzle.demo();
        
        var screen = Form.defaultForm();
        Ornament ornament1 = new Ornament(screen, 100, 100, 20);
        Tree tree = new Tree(screen, 200, 200, 100, 200);

        while(true){
            ornament1.update();
        }
                
        
        
    }
}
