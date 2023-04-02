     
    import processing.net.*;
    Server myServer;
      
    float x = 150;
    float y = 50;
    float w = 200;
    float h = 100;
    String s;
    String go = "go";
    
    float x2 = 150;
    float y2 = 180;
    float w2 = 200;
    float h2 = 100;
    String stop = "stop";
    
    
    void setup(){
     size(500,500);
     background(245);
     textSize(36);
     stroke(0);
     
     
   
   
     
     
     myServer = new Server(this, 5204);
    }

    void draw(){
     fill(255);
     rect(x,y,w,h);
     
     rect(x2,y2,w2,h2);
     
     fill(0);
     text("GO", 225, 110);
     text("STOP", 210, 245);
    
     
     
     Client thisClient = myServer.available();
     
     
     if (thisClient !=null) {
       String whatClientSaid = thisClient.readString();
         if (whatClientSaid != null) {
           println("Button pressed on phone: " +whatClientSaid);
             if(whatClientSaid.equals(go) ==  true) {
               stroke(23, 252, 3);
              
             }
         }
       } 
    }
    
    void mouseReleased() {
      if(mouseX>x && mouseX <x+w && mouseY>y && mouseY <y+h){
       println("Go Button was pressed");
       myServer.write("Go Button was pressed");
       stroke(23, 252, 3);

    }
     if(mouseX>x2 && mouseX <x2+w2 && mouseY>y2 && mouseY <y2+h2){
       println("Stop button was pressed");
       myServer.write("Stop button was pressed");
   }
   
  }
   
   void serverEvent(Server someServer, Client someClient) {
        println("Phone Connection Successfull: " + someClient.ip());
}
