import controlP5.*;
import processing.net.*;

//Make sure to \.net.*;
//Create instances of each
ControlP5 cp5;
Client arduino;
int data;
color c;
String stop="stop";
String start="go";

void setup() {
  size(1440, 3200);
  background(255,100,100);
  //Connect to arduino server using the IP address and port
  arduino = new Client(this, "192.168.192.39", 80);
  //arduino.write("peepeepoopoo");
  cp5 = new ControlP5(this);
  // Create buttons
  cp5.addButton("Start_Motor")
    .setValue(0)
    .setPosition(100,100)
    .setSize(200,19);
  cp5.addButton("Stop_Motor")
    .setValue(0)
    .setPosition(100,300)
    .setSize(200,19);;
  
  
}

void draw() {
data = arduino.read();
  if(data > 0 && data < 20) {
    println("Stopped moving due to an obstacle at " + data + "cm");
    //println(data);
  }
  background(c);
}
/*void clientEvent(Client arduino) {
  print("Buggy aint movin' pal:  ");
  data = arduino.read();
  println(data);
  print("cm ");
  redraw();
}*/
//This function gets called everytime any button is pressed
public void controlEvent(ControlEvent theEvent){
 println(theEvent.getController().getName());
}
// Start button sends start string
public void Start_Motor(int theValue){
  if (arduino.active()){
    arduino.write(start);
    println("started motor fam");
  }else{
    println("sorry fam motor not connected");
  }
}

public void Stop_Motor(){
  if (arduino.active()){
    println("stopped motor fam");
    arduino.write(stop);
  }else{
    println("sorry fam motor not connected");
  }
}
