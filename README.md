# OLED Pong Game

https://github.com/s5y-ux/ArduinoPong/assets/59636597/5c1003ea-4323-4022-95d5-a5c81bed3e28

This project guides you through creating a Pong game using an Arduino microcontroller, an OLED display, and two potentiometers for paddle control. This classic game pits two players against each other, each controlling a paddle to hit a ball back and forth. Points are scored when one player fails to return the ball, and the game ends when a player reaches the maximum points.

## Components Requiredd

- Arduino Uno (or any compatible microcontroller)
- OLED display (128x64 pixels, I2C communication)
- 2x Potentiometers (for player controls)
- Breadboard and jumper wires
- Optional: Resistors for potentiometers (depending on your setup)

## Wiring the Components

1. Connect the OLED display to the Arduino's I2C pins:
   - SDA to A4 (on Uno) or the SDA pin of your microcontroller
   - SCL to A5 (on Uno) or the SCL pin of your microcontroller
2. Connect the OLED's VCC and GND to the Arduino's 5V and GND, respectively.
3. Connect each potentiometer's outer pins to 5V and GND for power.
4. Connect the middle pin of the potentiometers to A0 and A1 on the Arduino for player controls.

## Libraries Needed

Before compiling the code, ensure you have the following libraries installed in your Arduino IDE:

- `Adafruit_GFX.h`
- `Adafruit_SSD1306.h`

These libraries provide the necessary functions to control the OLED display.

## The Code

The provided code initializes the display and runs the main game loop, handling:
- Drawing the paddles and ball
- Detecting collisions and updating scores
- Ending the game when a player reaches the maximum points

### Key Variables and Defines

- `SCREEN_WIDTH` and `SCREEN_HEIGHT` set the dimensions of the OLED display.
- `OLED_RESET`, `OLED_I2C_ADDRESS` for display initialization.
- Game mechanics variables such as `PLAYER_PADDLE_HEIGHT`, `BALL_RADIUS`, `GAMESPEED`, etc.

### Setup and Loop

The `setup()` function initializes serial communication and the display. The `loop()` continuously runs the game, updating the display and game state.

### Game Functions

- `playGame()`: Checks if the game should continue or display the end game message.
- `updateGame()`: Reads players' paddle positions and updates the game state.
- `drawPaddlesAndBall()`: Draws the paddles and ball on the display.
- `updateScoreAndPosition()`: Updates the scores and positions of the paddles and ball.
- `displayScore()`: Displays the current score.
- `displayEndGame()`: Displays the end game message with the winner.

## Compiling and Running

After connecting your Arduino to your computer:
1. Open the Arduino IDE.
2. Select your Arduino model and port.
3. Compile and upload the code.

Enjoy your OLED Pong game! Players use the potentiometers to move their paddles up and down, trying to hit the ball back to the other player. The first to reach the maximum points wins the game.

## Customization

Feel free to tweak the game settings such as `GAMESPEED`, `MAX_POINTS`, or paddle and ball sizes to customize your gameplay experience.
