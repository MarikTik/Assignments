//package week3.homework2.src;
//package week3.homework.src;

import java.util.Scanner;
import java.awt.Color;


public class HW2MarkTikhonov {

     class ScreenSettings{
          int width;
          int height;
          Color backgroundColor;
          String title;
          public ScreenSettings(int width, int height, Color backgroundColor, String title){
               this.width = width;
               this.height = height;
               this.backgroundColor = backgroundColor;
               this.title = title;
          }
     }
     public static Draw standardScreen(Color backgroundColor){
          Draw screen = new Draw();
          int width = 400;
          int height = 400;
          screen.setCanvasSize(width, height);
          screen.setXscale(0, width);
          screen.setYscale(height, 0);
          screen.setTitle(null);
          screen.clear(backgroundColor);
          return screen;
     }
     public static void main(String []args){
          static ScreenSettings defaultSettings = ScreenSettings(
               400,
               400,
               Color.GRAY,
               "CH 2 #1 Name, Age and Annual Income by Mark Tikhonov"
          );
          Draw draw = standardScreen(Color.RED);

     }
}
