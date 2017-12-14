# Final Project - Physical Computing and the Internet of Things

*Name: Jo (Joungwon) Kwon

*Date: December 14, 2017

## Project:  Data Go Energy Go

This project's objective is to highlight Pokemon Go's data privacy issue. In order to help people effectively learn the information, a story of Pikachu’s ecosystem is included. Pikachu is a crucial part of Pokemon Go and it is used as an object to criticize Pokemon Go’s privacy policies. 

### Detailed Project Description

“Data Go, Energy Go” project is a story telling stage for people to learn about Pokemon Go’s privacy data flow and ecology’s energy flow. It allows people to be aware of their information used in Pokemon Go with 5 steps. The data and energy flow is self-explanatory in the tables with the 5 steps. The following images show the 5 steps: 

![final index](images/final_index.GIF)
![final2](images/final_2.GIF)
![final3](images/final_3.GIF)
![final4](images/final_4.GIF)
![final5](images/final_5.GIF)
![final6](images/final_6.GIF)

“Data Go, Energy Go” project is a story telling stage for people to learn about Pokemon Go’s privacy data flow and ecology’s energy flow. It allows people to be aware of their information used in Pokemon Go with 5 steps. The data and energy flow is self-explanatory in the tables with the 5 steps. 
The following images show the 5 steps: 
The last step includes a link to choose to delete the account. It may seem extreme but the only choice to avoid personal information to be given to third entities seem to be deleting the account or sending an email to Niantic. However, the response to Niantic would be a suggestion to delete the account. It is clearly stated in Niantic’s webpage about this procedure. 

In 2016 and the beginning of 2017, Pokemon Go was popular among many people in different countries and ages. The game made people to walk around and catch pokemons in various places. People stated that Pokemon Go had many pros such as making people exercise and meet new people. Even though privacy issues were raised, people did not take it seriously and continued their journey to catch pokemons. 

There were many risks in providing personal information to other entities. The personal information was not just given to Niantic and Nintendo (Pokemon companies). Niantic stated that it gave the information to companies that help them with its service such as Google Maps Pin, Google Play, and Apple. In addition, Niantic gave the information to third party service providers such as Adobe Analytics (Omniture) and Typekit by Adobe. These are only a few examples of third party services stated in the webpage. It also stated that the company gave information to businesses that users may like according to users’ preferences. There were speculations in Korea that pokemon stops in the game were usually near companies that had connections to Niantic. John Hanke, the founder of Niantic, has another company that is financially supported by the CIA’s venture capital arm. This fact may hint that CIA may have some connection to Pokemon Go. Users are not aware of this and they do not take to read all this information. In order to alert the users of this fact, this project is created. The only solution for now is to delete the account and stop using Niantic’s service. The issue about privacy should be brought up and other solutions should be made. 

### Technical Description

*What are the hardware components?

-Sparkfun 
1. Potentiometer
2. Infrared Sensor
3. 1 yellow LED, 3 red LEDs
4. 2 buttons
5. Sevor motor

-3D Prints
1. Pikachu
2. Green Pepper
3. Tree

*What are the software components? 
1. Particle
2. Javascript
3. p5.js

*How do they interact with each other?
1. When the potentiometer is used, the servor motor moves and the page is changed (javascript).
2. When sevor motor moves and makes the sun move, the sun is detected by the infrared sensor which lights up the 3 red LEDs. The page also changes with the change in the servor motor. 
3. When the red apple button is pressed, the page is changed. 
4. When the green pepper button is used, the yellow LED lights up and the page is changed. 
5. When the potentiometer is used to get the sun down, the page is changed with many images of Pikachu eating apples (p5.js). 

#### Hardware Wiring Diagram

![Wiring Diagram](images/finalwiredredboard_pikachu.png)

*Description
1. Potentiometer connected to A4 analog pin
2. Infrared Sensor conneted to A0
3. Yellow LED is connected to D1
4  3 Red LEDs are connected to D4, D5, D6
5. Button pin is connected to D7
6. Button pin2 is connected to D0
7. Servor motor connected to D2

#### Code

1. Define values (I worked on infrared sensor, the two buttons for changing the pages, and javascript for changing the pages)
```c++
// Servo motor(Sun comes up)
Servo myservo;  // create servo object to control a servo
int potpin = A4;  // A4 analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int mappedVal; // mapped value for servo

// ButtonLED(Pikachu eats Apple)
int buttonPin1 = D7;

// ButtonLED(Thunder bolt)
int ledPin = D1;
int buttonPin2 = D0;//pepper button

// HTML(On Going)
int page = 1; //starts with 1.html
```
2. Setup the functions 
```c++
void setup(){
    Serial.begin(9600);
// HTML
    Particle.variable("page", page);

// InfraIR
   for(int i=4; i<7; i++){
        pinMode(i, OUTPUT); //D4, D5, D6
    }
// ButtonLED(Pikachu eats Apple)
    pinMode(buttonPin1, INPUT_PULLUP);

// ButtonLED(Thunder bolt)
    pinMode(buttonPin2, INPUT_PULLUP); 
    pinMode(ledPin, OUTPUT); 
    pinMode(potpin, INPUT);
}
```
3. How the function works?
```c++
void loop()
{
    Serial.print("Page: ");
    Serial.println(page);
    // servo motor
    val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
    Serial.println(val);
    mappedVal = map(val, 0, 4095, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(mappedVal);                  // sets the servo position according to the scaled value
    delay(15);                           // waits for the servo to get there

    if(val >= 5  && val < 500)
    {
        page=2;//html
    } //change to page 2
    
    if(val >= 500 && val < 1000)
    {
        page=3;//html
    } //change to page 3 when the value is between these two numbers
    // InfraIR
    reading = analogRead(sensorPin); //read the sensorPin
    int dist_cm = SharpIR.distance();  
        
    if(dist_cm>=0 && dist_cm<11) //read when less then 11cm
    {
        for(int i=4; i<7; i++)
        {
            digitalWrite(i, HIGH); //all lights are ON 
        }
        Particle.publish("light_status", "less than 10cm");
    }
    else
    {
        for(int i=4; i<7; i++)
        {
            digitalWrite(i, LOW); //D4, D5, D6 is OFF
        }
    }
    delay(50);
    
    //Button change page
    int buttonState1 = digitalRead(buttonPin1);
    if(buttonState1 == LOW)
    {
        page=4; //html
    }//change to page 4
    
    //ButtonLED (thunder)
    int buttonState2 = digitalRead(buttonPin2);
    if(buttonState2 == LOW)
    {
        digitalWrite(ledPin, HIGH);
        page=5; //html
    }else
    {
        digitalWrite(ledPin, LOW);
    }//change to page 5 when button is pressed
    
    //potentionmeter state sun down
    if(val>=3000)    
    {
        page=6; //html
    }//change to page 6
}
```
[my_code.ino](code/my_code.ino)

4. Javascript and p5.js codes
```javascript
	<a href="1.html" target="bottom">START THE DAY OVER</a></h2></font>
	<iframe width="100%" height= "95%" src="1.html" name="bottom"></iframe> 
	   <script type="text/javascript">
        var deviceID    = "430053001151353338363333";
        var accessToken = "9fe41d708a5453d5b7edbd576398dd6afaf9ef4f";
        var var2get = "page";
        var lastPage = 0; // set both to zero for starting
        var newPage = 0; 

        function check4pageTurn() {
            var requestURL = "https://api.particle.io/v1/devices/" +deviceID + "/" + var2get + "/?access_token=" + accessToken;
            $.getJSON(requestURL, function(json) {
                newPage = json.result;
                if (newPage != lastPage){
                    swapFrame(newPage);
                }
            });
            lastPage = newPage;
        }

        function swapFrame(page) {
            console.log("Changed page to " + page);
            self.frames['bottom'].location.href = page + '.html';
        } 
        setInterval(check4pageTurn, 500);
    </script>
	</body>
</html>
```

```javascript
<html>
	<head>
		<title>Step 5</title>
		<script type="text/javascript" src="./p5.js"></script>
		<script type="text/javascript" src="./rain_sketch2.js"></script>
		<script type="text/javascript" src="./rain.js"></script>
	</head>
	<body bgcolor="#03A9F4">
		<font face="Verdana" color="#33333">
		<div id="sketch"></div>
		<h1>Oh no...Everyone seems to know that I love apples. Why am I getting emails about Apple's products? 
		<img src="applepic.png" alt="Apple Logo" width="30" height="30">
		<br>
		<br>
		MAKE A CHOICE TODAY!<br>
		To remove your personal information, log into 
		<a href="http://support.pokemon.com">support.pokemon.com</a> and submit a customer service request, or contact The Pokemon Company International, Inc.<br>
		</h1>
		</font>
	</body>
</html>
```

### Design / Form
1. Pikachu model was downloaded and modified. It was challenging to create a hole because Fusion because 3D Max did not allow boolean substract. Ultimately, I had to use Meshmixer to create the hole. Although I inputted the precise measurements for the hole, the 3D print result was different. After printing several Pikachu models with the change in measurements, the perfect size of the hole was printed. The button on Pikachu was chosen red and painted with a green leaf so that it looks like an apple. 
2. The green button with the pepper on the top was printed as an oval shape and painted as green to look like a pepper for the part of the story for "Energy Go."

![pikachu](images/pika4.jpg)
![stage](images/pika5.jpg)
Source: [Pikachu Model] https://www.thingiverse.com/thing:670032

3. The tree was designed in Fusion and modgepodged with brown paper. Cotton was added to hide the red LED lights and to look like a tree.

![tree](images/treemodel.png)
![tree](images/tree.jpg)

4. The descriptions for the story was necessary so the text is in a large font to be visible. The story required a user to engage with Pikachu's activities in his ecosystem so instructions were given on the screen. The background color is gradually changed from light blue to darker blue to show the chronological change in the story. 
In order to show Pikachu's data was given to many entities, I used p5.js to visualize Pikachu's love for apples.


### Evaluation / Reflection

The goals for the initial idea of this project to enable people to acknowlegdge the fact about Pokemon Go's use of personal data was accomplished. Although instructions are given by Pikachu with the screen, the intuitive use for the potentiometer or buttons may not be clear. People wanted to turn the potentiometer or push the button not in order. The sequential use of these objects should be more intuitive. 

I learned how to modify and create 3D models. Printing the exact 3D model was a challenge. I would like to learn more about creating precise measurements. I also learned how to use javascript and html. I did not know how to create a website with javascript and html prior to this class. Learning css will be my future goal. In the part for the particle, I learned how to use the Sharp Infrared sensor and how to create function to change the pages of the website after an input is made by a user. 

If I had more time for the project, I would like to use a larger screen. The idea of this stage with two stories intertwined came from science museums. Science museums have multiple larger screens that allow people to interact and learn new information. Having a larger scale with a longer sequence would be my goal for the future. With a larger screen, text would be easier to read. In addition, spending more time to sharpen the physical appearance of the stage and the interface of the text would make the project better.
