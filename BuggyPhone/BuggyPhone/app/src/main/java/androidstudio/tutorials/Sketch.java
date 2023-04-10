package androidstudio.tutorials;

import processing.core.PApplet;
public class Sketch extends PApplet {

    Client laptop;

    int x = 250;
    int y = 300;
    int w = 500;
    int h = 200;

    int x2 = 250;
    int y2 = 600;
    int w2 = 500;
    int h2 = 200;

    int x3 = 250;
    int y3 = 900;
    int w3 = 500;
    int h3 = 200;

//    int xup = 125;
//    int yup = 1000;
//    int wup = 500;
//    int hup = 200;
//
//    int xdown = 125;
//    int ydown = 1500;
//    int wdown = 500;
//    int hdown = 200;
//
      int xleft = 25;
      int yleft = 1200;
      int wleft = 450;
      int hleft = 200;
//
    int xright = 525;
    int yright = 1200;
    int wright = 450;
    int hright = 200;





    int gobuttoncolor = color(255);
    int stopbuttoncolor = color(255);
    int firebuttoncolor = color(255);
    int leftcontrolbuttoncolor = color(255);
    int rightcontrolbuttoncolor = color(255);

    String whatServerSaid;
    String go = "go";
    String stop = "stop";
    String fire = "fire";

    String left = "left";
    String right = "right";


//    String upTurret = "upTurret";
//    String downTurret = "downTurret";
//    String leftTurret = "leftTurret";
//    String rightTurret = "rightTurret"

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

        laptop = new Client(this, "192.168.167.230", 5204);
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

        fill(leftcontrolbuttoncolor);
        rect(xleft, yleft, wleft, hleft);

        fill(rightcontrolbuttoncolor);
        rect(xright, yright, wright, hright);

        fill(0);

        textAlign(CENTER, CENTER);
        text("GO", x + w /2, y + h/2);
        text("STOP", x2 + w2/2, y2+h2/2);
        text("FIRE",x3 + w3/2, y3+h3/2);
        text("LEFT", xleft + wleft/2, yleft + hleft/2);
        text("RIGHT", xright + wright/2, yright + hright/2);

        if (laptop.active()){
            status = "Connected";
            statusColor = color(0, 255, 0);
        } else {
            status = "No Connection";
            statusColor = color(255, 0 ,255);
        }

        textSize(36);
        text("Connection Status: ", 300, 100);


        if (status == "Connected") {
            statusColor = color(0, 255, 0);
            fill(statusColor);
        }
        if (status == "No Connection") {
            statusColor = color(255, 0, 0);
            fill(statusColor);
        }

        text(status, 600, 100);



        if (laptop.available() > 0) {
            whatServerSaid = laptop.readString();
            println("Message from Laptop: " + whatServerSaid);
        }

        if(millis() - click > changeTime) {
            gobuttoncolor = color(255);
            stopbuttoncolor = color(255);
            firebuttoncolor = color(255);
            leftcontrolbuttoncolor = color(255);
            rightcontrolbuttoncolor = color(255);

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
        if(mouseX>xleft && mouseX <xleft+wleft && mouseY>yleft && mouseY <yleft+hleft){
            println("Left");
            click = millis();
            laptop.write(left);
            leftcontrolbuttoncolor = color(140, 140, 255);

        }
        if(mouseX>xright && mouseX <xright+wright && mouseY>yright && mouseY <yright+hright){
            println("Right");
            click = millis();
            laptop.write(right);
            rightcontrolbuttoncolor = color(140, 140, 255);

        }
    }
}