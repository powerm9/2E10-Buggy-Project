     
    import processing.net.*;
    Server myServer;
      
    float x = 150;
    float y = 50;
    float w = 200;
    float h = 100;
    String s;
    String go = "go";
    
    
    void setup(){
     size(500,500);

     stroke(0);
     
     myServer = new Server(this, 5204);
    }

    void draw(){
     background(0);
     rect(x,y,w,h);
     fill(255);
     
     
     Client thisClient = myServer.available();
     
     
     if (thisClient !=null) {
       String whatClientSaid = thisClient.readString();
         if (whatClientSaid != null) {
           println("Button pressed on phone: " +whatClientSaid);
             if(whatClientSaid.equals(go) ==  true) {
               background(23, 252, 3);
              
             }
         }
       } 
    }
    
    void mouseReleased() {
      if(mouseX>x && mouseX <x+w && mouseY>y && mouseY <y+h){
       println("Laptop button pressed");
       fill(0);
       
       myServer.write("Laptop Button was pressed");
       //do stuff 
    }
   }
   
   void serverEvent(Server someServer, Client someClient) {
        println("Phone Connection Successfull: " + someClient.ip());
}
