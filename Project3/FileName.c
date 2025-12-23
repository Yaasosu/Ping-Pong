#include "raylib.h"
#include <string.h>

int main(void)
{
	const int width = 1000;
	const int height = 550;

	int leftPaddleX = 10;
	int leftPaddleY = height / 2 - 60;
	int paddleWidth = 25;
	int paddleHeight = 120;

	int rightPaddleX = width - 35;
	int rightPaddleY = height / 2 - 60;
	
	//м€ч
	int ballSpeedX = 5;
	int ballSpeedY = 5;
	int ballRadius = 15;

	int ballX = 500;
	int ballY = 275;

	//score
	int leftScore = 0;
	int rightScore = 0;

	//стены
	const int wallThickness = 10;
	Rectangle top = {0, 0, width, wallThickness };
	Rectangle floor = {0, height - wallThickness, width, wallThickness };

	InitWindow(width, height, "PingPong");
	SetTargetFPS(60);

	while (WindowShouldClose() == false) {
		BeginDrawing();

		//м€ч
		DrawCircle(ballX, ballY, ballRadius, WHITE);


		//ракетки
		DrawRectangle(leftPaddleX, leftPaddleY, paddleWidth, paddleHeight, WHITE);
		DrawRectangle(rightPaddleX, rightPaddleY, paddleWidth, paddleHeight, WHITE);


		//средн€€ лини€
		DrawLine(width / 2, 0, width / 2, height, WHITE);

		//верхн€€ и нижн€€ стены
		DrawRectangleRec(top, WHITE);
		DrawRectangleRec(floor, WHITE);


		//счет
		DrawText(TextFormat("%d", leftScore),  400, 25 , 75, WHITE);
		DrawText(TextFormat("%d", rightScore), 550, 25, 75, WHITE);


		ballX += ballSpeedX;
		ballY += ballSpeedY;

		//  оллизи€ с верхней стеной
		if (ballY - ballRadius <= top.y + top.height) {
			ballSpeedY = -ballSpeedY;
		}

		//  оллизи€ с нижней стеной
		if (ballY + ballRadius >= floor.y) {
			ballSpeedY = -ballSpeedY;
		}

		//Ћева€ ракетка (управление W и S)

		if (IsKeyDown(KEY_W)) {
			leftPaddleY -= 5;
		}
		if (IsKeyDown(KEY_S)) {
			leftPaddleY += 5;
		}
		if (leftPaddleY <= 0) {
			leftPaddleY = 0;
		}
		if (leftPaddleY + paddleHeight >= GetScreenHeight()) {
			leftPaddleY = GetScreenHeight() - paddleHeight;
		}


		//Ћева€ ракетка (управление стрелками)

		if (IsKeyDown(KEY_UP)) {
			rightPaddleY -= 5;
		}
		if (IsKeyDown(KEY_DOWN)) {
			rightPaddleY += 5;
		}
		if (rightPaddleY <= 0) {
			rightPaddleY = 0;
		}
		if (rightPaddleY + paddleHeight >= GetScreenHeight()) {
			rightPaddleY = GetScreenHeight() - paddleHeight;
		}

		//если попали в ракетку

		if (CheckCollisionCircleRec((Vector2) {(float)ballX, (float)ballY},(float)ballRadius,(Rectangle) {(float)leftPaddleX, (float)leftPaddleY, (float)paddleWidth, (float)paddleHeight})) {
			ballSpeedX = -ballSpeedX;
		}

		if (CheckCollisionCircleRec((Vector2) {(float)ballX, (float)ballY},(float)ballRadius,(Rectangle) {(float)rightPaddleX, (float)rightPaddleY, (float)paddleWidth, (float)paddleHeight})) {
			ballSpeedX = -ballSpeedX;
		}

		//если попали в стену
	
		if (ballX + ballRadius >= GetScreenWidth()) {
			rightScore += 1;
			ballX = width / 2;
			ballY = height / 2;
			ballSpeedX = -5;  
			ballSpeedY = 5;
		}

		if (ballX - ballRadius <= 0) {
			leftScore += 1;
			ballX = width / 2;
			ballY = height / 2;
			ballSpeedX = 5;  
			ballSpeedY = 5;
		}

		//победа
		if (leftScore >= 10) {
			ClearBackground(BLACK);
			ballSpeedX = 0;
			ballSpeedY = 0;
			DrawText(TextFormat("LEFT WON, SCORE: %d! ", leftScore), 130, 230, 75, BLUE);

		}

		if (rightScore >= 10) {
			ClearBackground(BLACK);
			ballSpeedX = 0;
			ballSpeedY = 0;
			DrawText(TextFormat("RIGHT WON, SCORE: %d! ", rightScore), 130, 230, 75, BLUE);

		}

		ClearBackground(BLACK);
		EndDrawing(); 
		
	}

	CloseWindow();
	return 0;
}
