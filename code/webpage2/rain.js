function Drop() {
  this.r = 50;                 
  this.x = random(width);     
  this.y = -this.r*4;              
  this.speed = random(1, 5);   // Pick a random speed
  this.wind_speed = 0.9;
  this.c = color(50, 100, 150); // Color

  // Move the raindrop down
  this.move = function() {
    this.y += this.speed;
  }

  this.wind = function(){
    this.x += this.wind_speed;
  }

  // Display the raindrop
  this.display = function() {
    // Display the drop
    fill(this.c);
    noStroke();
    image(img, this.x, this.y, this.r*2, this.r*2);
  }
}

