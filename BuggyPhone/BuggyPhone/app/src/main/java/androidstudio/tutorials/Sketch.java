package androidstudio.tutorials;

import processing.core.PApplet;
public class Sketch extends PApplet {

    Client laptop;

    int x = 300;
    int y = 300;
    int w = 500;
    int h = 200;

    int x2 = 300;
    int y2 = 600;
    int w2 = 500;
    int h2 = 200;

    int x3 = 300;
    int y3 = 900;
    int w3 = 500;
    int h3 = 200;



    int gobuttoncolor = color(255);
    int stopbuttoncolor = color(255);
    int firebuttoncolor = color(255);

    String whatServerSaid;
    String go = "go";
    String stop = "stop";
    String fire = "fire";

    int changeTime = 100;
    int click = 0;
    String status;
    int statusColor = color(0);

    public void settings() {
        size(1000, 2000);
    }

    public void setup() {
        background(245);
        stroke(0);

        laptop = new Client(this, "192.168.88.230", 5204);
    }

    public void draw() {

        background(245);
        textSize(72);



        fill(gobuttoncolor);
        rect(x,y,w,h);

        fill(stopbuttoncolor);
        rect(x2,y2,w2,h2);

        fill(firebuttoncolor);
        rect(x3,y3,w3,h3);

        fill(0);

        text("GO", 490, 425);
        text("STOP", 460, 725);
        text("FIRE",470, 1025);

        if (laptop.active()){
            status = "Connected";
            statusColor = color(0, 255, 0);
        } else {
            status = "No Connection";
            statusColor = color(255, 0 ,255);
        }

        textSize(36);
        text("Connection Status: ", 100, 100);


        if (status == "Connected") {
            statusColor = color(0, 255, 0);
            fill(statusColor);
        }
        if (status == "No Connection") {
            statusColor = color(255, 0, 0);
            fill(statusColor);
        }
        text(status, 520, 200);



        if (laptop.available() > 0) {
            whatServerSaid = laptop.readString();
            println("Message from Laptop: " + whatServerSaid);
        }

        if(millis() - click > changeTime) {
            gobuttoncolor = color(255);
            stopbuttoncolor = color(255);
            firebuttoncolor = color(255);

        }
    }

    public void mousePressed() {
        if (mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h) {
            println("Go");
            click = millis();
            laptop.write(go);
            gobuttoncolor = color(0, 255, 0);
        }
        if (mouseX > x2 && mouseX < x2 + w2 && mouseY > y2 && mouseY < y2 + h2) {
            println("Stop");
            click = millis();
            laptop.write(stop);
            stopbuttoncolor = color(255, 0 , 0);
        }
        if(mouseX>x3 && mouseX <x3+w3 && mouseY>y3 && mouseY <y3+h3){
            println("Fire");
            click = millis();
            laptop.write(fire);
            firebuttoncolor = color(255, 139, 15);

        }
    }
}





