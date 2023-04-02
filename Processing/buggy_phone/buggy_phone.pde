     
    import processing.net.*;
    Server myServer;
      
    float x = 100;
    float y = 50;
    float w = 150;
    float h = 80;
    String go = "go";
    
    
    void setup(){
     size(500,500);
     background(255);
     stroke(0);
     noFill();
     
     myServer = new Server(this, 5204);
    }

    void draw(){
     background(255);
     rect(x,y,w,h);
     fill(255);
     
     Client thisClient = myServer.available();
     if (thisClient !=null) {
       String whatClientSaid = thisClient.readString();
         if (whatClientSaid != null) {
           println("Message from client: in" +whatClientSaid);
             if(whatClientSaid =  "go") {
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
