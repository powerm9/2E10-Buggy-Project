     
    import processing.net.*;
    Server myServer;
      
    float x = 150;
    float y = 50;
    float w = 200;
    float h = 100;
    String go = "go";
    
    float x2 = 150;
    float y2 = 180;
    float w2 = 200;
    float h2 = 100;
    String stop = "stop";
    
    float x3 = 150;
    float y3 = 310;
    float w3 = 200;
    float h3 = 100;
    String fire = "fire";
   
    
    int gobuttoncolor = color(255);
    int stopbuttoncolor = color(255);
    int firebuttoncolor = color(255);
    
    int changeTime = 100;
    int click = 0;
    
    String status;
    int statusColor;
    
    
    
   
    void setup(){
     size(500,500);
     stroke(0);
   
     
     myServer = new Server(this, 5204);
    }

    void draw(){
     background(245);
     textSize(36);
 
     fill(gobuttoncolor);
     rect(x,y,w,h);
     
     fill(stopbuttoncolor);
     rect(x2,y2,w2,h2);
     
     fill(firebuttoncolor);
     rect(x3,y3,w3,h3);
     
     fill(0);
     
     text("FIRE", 220, 370);
     text("GO", 225, 110);
     text("STOP", 210, 245); 
     
     Client thisClient = myServer.available();

     
     if (thisClient !=null) {
       String whatClientSaid = thisClient.readString();
         if (whatClientSaid != null) {
           println("Button pressed on phone: " +whatClientSaid);
             if(whatClientSaid.equals(go) ==  true) {
               click = millis();
               gobuttoncolor = color(0, 255, 0);
               
             }
             if(whatClientSaid.equals(stop) ==  true) {
               click = millis();
               stopbuttoncolor = color(255, 0, 0);
               
             }
             if(whatClientSaid.equals(fire) ==  true) {
               click = millis();
               firebuttoncolor = color(255, 139, 15);
               
             }
         }
       }
        
       if(millis() - click > changeTime) {
         gobuttoncolor = color(255);
         stopbuttoncolor = color(255);
         firebuttoncolor = color(255);
         
       }
       
       if (myServer.active()){
            status = "Connected";
            statusColor = color(0, 255, 0);
        } else {
            status = "No Connection";
            statusColor = color(255, 0, 0);
        }
        
        textSize(16);
        text("Connection Status: ", 1, 15);


        if (status == "Connected") {
            statusColor = color(0, 255, 0);
            fill(statusColor);
        }
        if (status == "No Connection") {
            statusColor = color(255, 0, 0);
            fill(statusColor);
        }
        text(status, 520, 200);
       
    }
      
    
    void mouseReleased() {
      if(mouseX>x && mouseX <x+w && mouseY>y && mouseY <y+h){
       println("Go");
       click = millis();
       myServer.write("Go Button was pressed");
       gobuttoncolor = color(0, 255, 0);
    }
     if(mouseX>x2 && mouseX <x2+w2 && mouseY>y2 && mouseY <y2+h2){
       println("Stop");
       click = millis();
       myServer.write("Stop button was pressed");
       stopbuttoncolor = color(255, 0 , 0);
   }
    if(mouseX>x3 && mouseX <x3+w3 && mouseY>y3 && mouseY <y3+h3){
       println("Fire");
       click = millis();
       myServer.write("Fire button was pressed!");
       firebuttoncolor = color(255, 139, 15);
   }
    }
 
   void serverEvent(Server someServer, Client someClient) {
        println("Phone Connection Successfull: " + someClient.ip());
}

  
