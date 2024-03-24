#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET - 1
#define OLED_I2C_ADDRESS 0x3C
#define PLAYER_PADDLE_HEIGHT 20
#define BALL_RADIUS 3
#define PADDLE_WIDTH 1
#define MAX_POINTS 10
#define BALL_START_X 64
#define BALL_START_Y 32
#define PADDLE_READ_SCALE 11
#define WIN_TEXT_SIZE 2
#define GAME_TEXT_SIZE 1
#define TEXT_COLOR SSD1306_WHITE
#define GAMESPEED 3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & Wire, OLED_RESET);

int ballX = BALL_START_X;
int ballY = BALL_START_Y;

bool hitWall = false;
bool hitCeiling = false;

int playerOnePoints = 0;
int playerTwoPoints = 0;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS);
  Serial.begin(9600);
  display.clearDisplay();
}

void loop() {
  playGame();
  display.display();
  display.clearDisplay();
}

void playGame() {
  if (playerOnePoints != MAX_POINTS && playerTwoPoints != MAX_POINTS) {
    updateGame();
  } else {
    displayEndGame();
  }
}

void updateGame() {
  int paddleOnePosition = analogRead(A0) / PADDLE_READ_SCALE;
  int paddleTwoPosition = analogRead(A1) / PADDLE_READ_SCALE;

  drawPaddlesAndBall(paddleOnePosition, paddleTwoPosition);
  updateScoreAndPosition(paddleOnePosition, paddleTwoPosition);
}

void drawPaddlesAndBall(int paddleOnePosition, int paddleTwoPosition) {
  display.drawFastVLine(0, paddleOnePosition, PLAYER_PADDLE_HEIGHT, PADDLE_WIDTH);
  display.drawFastVLine(SCREEN_WIDTH - 1, paddleTwoPosition, PLAYER_PADDLE_HEIGHT, PADDLE_WIDTH);
  display.drawCircle(ballX, ballY, BALL_RADIUS, TEXT_COLOR);
  displayScore();
}

void updateScoreAndPosition(int paddleOnePosition, int paddleTwoPosition) {

  if ((ballX <= 2 && ballX >= 0) && (paddleOnePosition) < ballY && ballY < ((paddleOnePosition) + 20)) {
    hitWall = false;
  }

  if ((ballX <= 125 && ballX >= 123) && (paddleTwoPosition) < ballY && ballY < ((paddleTwoPosition) + 20)) {
    hitWall = true;
  }

  if (ballX <= -2) {
    playerTwoPoints++;
    ballX = 64;
    ballY = 32;
  }

  if (ballX >= 127) {
    playerOnePoints++;
    ballX = 64;
    ballY = 32;
  }

  if (ballY <= 2) {
    hitCeiling = true;
  }

  if (ballY >= 61) {
    hitCeiling = false;
  }

  if (hitWall) {
    ballX = ballX - GAMESPEED;
  } else {
    ballX = ballX + GAMESPEED;
  }

  if (hitCeiling) {
    ballY = ballY + GAMESPEED;
  } else {
    ballY = ballY - GAMESPEED;
  }

}

void displayScore() {
  display.setTextSize(GAME_TEXT_SIZE);
  display.setTextColor(TEXT_COLOR);
  display.setCursor(50, 1); // Consider making these magic numbers constants too
  display.println(String(playerOnePoints) + " | " + String(playerTwoPoints));
}

void displayEndGame() {
  String winnerText = playerOnePoints > playerTwoPoints ? "Player 1 Wins!" : "Player 2 Wins!";
  display.setTextSize(WIN_TEXT_SIZE);
  display.setTextColor(TEXT_COLOR);
  display.setCursor(10, 10); // Adjust as necessary for better centering
  display.println(winnerText);
}