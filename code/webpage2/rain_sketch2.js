var img;
var drops = [];

//total number of drops we want to use
var totalDrops = 0;

function setup() {
  var myCanvas = createCanvas(windowWidth, 400);
  myCanvas.parent('sketch');
  //tint(255, 10); //making it transparent
  img = loadImage('images/ApplePika_crop.PNG')
}

function draw() {
  var c = color('#03A9F4')
  background(c);

  // Initialize one drop
  drops[totalDrops] = new Drop();
  // Increment totalDrops
  totalDrops++ ;
  // If we hit the end of the array
  if (totalDrops >= 300) {
    totalDrops = 0; //Start over
  }

  // Move and display drops
  for (var i = 0; i < totalDrops; i++ ) { 
    drops[i].move();
    drops[i].display();
    drops[i].wind();
  }
}