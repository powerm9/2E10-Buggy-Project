package androidstudio.tutorials;

import processing.core.PApplet;
public class Sketch extends PApplet {

    Client laptop;

    int x = 300;
    int y = 300;
    int w = 500;
    int h = 200;

    int x2 = 300;
    int y2 = 1000;
    int w2 = 500;
    int h2 = 200;

    String whatServerSaid;
    String go = "go";
    String stop = "stop";

    public void settings() {
        size(1000, 2000);
    }

    public void setup() {
        background(0);
        stroke(0);
        noFill();
        laptop = new Client(this, "192.168.88.230", 5204);
    }

    public void draw() {
        
        background(0);
        rect(x, y, w, h);
        rect(x2, y2, w2, h2);
        fill(255);
        if (laptop.available() > 0) {
            whatServerSaid = laptop.readString();
            println("Message from Laptop: " + whatServerSaid);
        }
    }

    public void mousePressed() {
        if (mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h) {
            println("Go button pressed");
            laptop.write(go);
        }
        if (mouseX > x2 && mouseX < x2 + w2 && mouseY > y2 && mouseY < y2 + h2) {
            println("Stop button was pressed");
            laptop.write(stop);
        }
    }
}





