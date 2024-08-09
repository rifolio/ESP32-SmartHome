// Global variables for sensor data
let temperature = 0;
let humidity = 0;
let lightIntensity = 0;

// p5.js related variables
let socket;
let canvas;

// Boolean function to determine curtain color and sun visibility
function isCurtainGrey() {
    return lightIntensity > 300;
}

function setup() {
    // Create the p5.js canvas and attach it to the 'canvas-container' div
    canvas = createCanvas(700, 500);
    canvas.parent('canvas-container');
    noLoop();

    // Initialize WebSocket connection
    socket = new WebSocket(`ws://${window.location.hostname}:81`);

    socket.onopen = function(event) {
        console.log('WebSocket connection established.');
    };

    socket.onmessage = function(event) {
        let data = JSON.parse(event.data);
        // Update HTML elements with the received sensor data
        document.getElementById('temperature').innerHTML = data.temperature;
        document.getElementById('humidity').innerHTML = data.humidity;
        document.getElementById('light').innerHTML = data.light;
        
        // Update light intensity for p5.js canvas
        lightIntensity = data.light;
        redraw();
    };

    socket.onclose = function(event) {
        console.log('WebSocket connection closed.');
    };

    socket.onerror = function(error) {
        console.error('WebSocket error:', error);
    };
}

function draw() {
    background(220);

    // Floor
    fill(150);
    quad(350, 300, -350, 500, 350, 700, 1050, 500);

    // Left wall
    fill(200);
    quad(350, 300, -350, 500, -350, 100, 350, -100);

    // Right wall
    fill(180);
    quad(350, 300, 1050, 500, 1050, 100, 350, -100);

    // Determine the color of the curtain based on light intensity using the boolean function
    let curtainColor = isCurtainGrey() ? "gray" : "#03A9F4";
    fill(curtainColor);

    // Window
    quad(50, 80, 300, 20, 300, 210, 50, 280);

    // Curtain rod
    fill("#FFC107");
    quad(50, 80, 300, 20, 300, 30, 50, 90);

    // Curtain
    fill(curtainColor);
    quad(50, 90, 70, 85, 70, 275, 50, 280);

    // Sun representation based on light intensity using the boolean function
    if (!isCurtainGrey()) {
        fill("#FFC107");
        noStroke();
        ellipse(175, 150, 100, 100); // Static sun position for simplicity
    }
}
