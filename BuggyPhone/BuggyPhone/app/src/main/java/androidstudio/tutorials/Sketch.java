package androidstudio.tutorials;

import processing.core.PApplet;
public class Sketch extends PApplet {

    Client laptop;

    int x = 300;
    int y = 800;
    int w = 500;
    int h = 200;

    String whatServerSaid;
    String go = "go";

    public void settings(){
        size(1000, 2000);
    }

    public void setup() {
        background(0);
        stroke(0);
        noFill();

        laptop = new Client(this, "192.168.222.230", 5204);
    }

    public void draw() {
        background(0);
        rect(x, y, w, h);
        fill(255);
        if (laptop.available() > 0) {
            whatServerSaid = laptop.readString();
            println("message from server: " + whatServerSaid);
        }

    }

    public void mousePressed() {
        if (mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h) {
            println("Go button pressed");
            fill(0);

            laptop.write(go);

            //do stuff
        }


    }

}



