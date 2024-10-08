package androidstudio.tutorials;

import processing.core.PApplet;

public class Sketch extends PApplet {
    Client laptop; // Client for communication
    Button[] buttons; // Array to hold button instances
    int click = 0; // Timestamp for button clicks
    String status; // Connection status message
    int statusColor = color(0); // Color for the status text

    // Set up the canvas size and orientation
    public void settings() {
        fullScreen();
    }

    // Initialize settings for the sketch
    public void setup() {
        background(245); // Set background color
        stroke(0); // Set stroke color
        laptop = new Client(this, "192.168.164.62", 5204); // Initialize the client connection

        // Create buttons with positions, labels, commands, and default colors
        buttons = new Button[]{
            new Button(300, 300, "GO", 'G', color(255)),
            new Button(300, 600, "STOP", 'S', color(255)),
            new Button(300, 900, "FIRE", 'F', color(255)),
            new Button(50, 1200, "LEFT", 'L', color(255)),
            new Button(575, 1200, "RIGHT", 'R', color(255)),
            new Button(50, 1700, "TLEFT", 'T', color(255)),
            new Button(575, 1700, "TRIGHT", 'Y', color(255)),
            new Button(575, 1450, "DOWN", 'D', color(255)),
            new Button(50, 1450, "UP", 'U', color(255))
        };
    }

    // Main draw loop
    public void draw() {
        background(245); // Clear background
        for (Button button : buttons) {
            button.display(); // Draw each button
        }
        updateConnectionStatus(); // Check and update connection status
        displayStatus(); // Display connection status on screen
    }

    // Update connection status and color based on laptop's active state
    private void updateConnectionStatus() {
        // Check if the laptop connection is active
        status = laptop.active() ? "Connected" : "No Connection";
        statusColor = laptop.active() ? color(0, 255, 0) : color(255, 0, 0); // Set color accordingly
    }

    // Display the current connection status on the screen
    private void displayStatus() {
        textSize(36); // Set text size
        fill(statusColor); // Set fill color for the status text
        text("Connection Status: " + status, 450, 50); // Draw the status text

        // Read any incoming messages from the laptop
        if (laptop.available() > 0) {
            String message = laptop.readString(); // Read message
            println("Message from Laptop: " + message); // Print message to console
        }

        resetButtonColors(); // Reset button colors if needed
    }

    // Reset button colors if a certain time has passed since the last click
    private void resetButtonColors() {
        if (millis() - click > 100) { // Check if enough time has passed
            for (Button button : buttons) {
                button.resetColor(); // Reset button color to default
            }
        }
    }

    // Check for mouse press events
    public void mousePressed() {
        // Iterate through buttons and check if any are hovered
        for (Button button : buttons) {
            if (button.isHovered(mouseX, mouseY)) {
                button.action(laptop); // Perform the button action
                click = millis(); // Update the click timestamp
            }
        }
    }

    // Button class to encapsulate properties and behaviors of a button
    class Button {
        int x, y, w = 500, h = 200; // Button position and size
        String label; // Button label
        char command; // Command to send on button press
        int buttonColor; // Current color of the button

        // Constructor to initialize button properties
        Button(int x, int y, String label, char command, int buttonColor) {
            this.x = x;
            this.y = y;
            this.label = label;
            this.command = command;
            this.buttonColor = buttonColor; // Set initial button color
        }

        // Display the button on the screen
        void display() {
            fill(buttonColor); // Set button fill color
            rect(x, y, w, h); // Draw the button rectangle
            fill(0); // Set text color
            textAlign(CENTER, CENTER); // Center align text
            text(label, x + w / 2, y + h / 2); // Draw button label
        }

        // Check if the mouse is hovering over the button
        boolean isHovered(int mouseX, int mouseY) {
            return mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h;
        }

        // Perform the action when the button is pressed
        void action(Client laptop) {
            laptop.write(command); // Send command to the laptop
            buttonColor = color(140, 140, 255); // Change button color on press
            println(label); // Print button action to console
        }

        // Reset button color to default
        void resetColor() {
            buttonColor = color(255); // Set to default color
        }
    }
}
