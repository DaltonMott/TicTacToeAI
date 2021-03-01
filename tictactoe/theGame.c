#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include "theGame.h"

int main(void) {
//declarations
	struct GameInfo gameInfo = {'o', '1', '2', '3', '4', '5', '6', '7', '8', '9', 	//square
								false, 												//win
								false,
								false, 												//O Start
								1, 													//turn Counter
								0, 0, 0, 0, 0, 										//Player Position
								0,
								'X',
								'O'};													//priority



	//the game itself
	gameInfo.OStart = whoFirst();
	gameInfo.hard = difficulty();													waitFor(2);
	rules(&gameInfo);			//O explains the game

	while(!checkEnd(&gameInfo)) {// the game loop
	
		drawBoard(&gameInfo);		//draw and redrawing the screen
		if (gameInfo.OStart) {		//the loop if the game starts
			if (gameInfo.turnCounter % 2 == 1 )
				theGamesTurn(&gameInfo);
			else
				playersTurn(&gameInfo);
		} 
		else {					//the loop if the player starts
			if (gameInfo.turnCounter % 2 == 1)
				playersTurn(&gameInfo);
			else
				theGamesTurn(&gameInfo);
		}
        gameInfo.turnCounter++;		//upping the round counter

	}
	
	drawBoard(&gameInfo);
	
	return 0;
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

bool whoFirst() {
	system("clear");															waitFor(1);
	printf("?: Hello.\n");														waitFor(1);
	printf("?: I will be your opponent. You can call me, O\n");					waitFor(2);
	printf("O: Would you like to start, or shall I?\n");
	printf("Note: enter 'me' or 'you' to choose.\n");

	char str[8];
	scanf("%s",str);
	
	waitFor(2);
	
	if(strcmp(str, "you") == 0) {
		printf("Very well, I will start.\n");
		return true;
	}
	else if(strcmp(str, "me") == 0) {
		printf("very well, You will start.\n");
		return false;
	}
	else if(strcmp(str, "exit") == 0)
		exit(0);
	else {
		printf("O: I'm not sure I understand. You will have to be more clear.\n");
		whoFirst(str);
	}
}

bool difficulty() {
	printf("O: Another thing, would you like moderate or hard difficulty?\n");
	printf("Note: type 'mod' or 'hard'\n");
	
	char str[8];
	scanf("%s",str);
	
	if(strcmp(str, "mod") == 0) {
		printf("O: I see, then I will give you a fair game.\n");
		return false;
	}
	else if(strcmp(str, "hard") == 0) {
		printf("O: I see, so you have chosen to lose.\n");
		return true;
	}
	else if(strcmp(str, "exit") == 0)
		exit(0);
	else {
		printf("O: I'm not sure I understand. You will have to be more clear.\n");
		difficulty(str);
	}
}

void rules(struct GameInfo* gameInfo) {
	
	printf("O: Give me a moment while I set up the board.\n");					waitFor(3);
	printf("O: In the meantime would you like me to explain the rules?\n");
	printf("Note: 'yes' or 'no'\n");
	
	char str[8];
	scanf("%s",str);
	
	waitFor(2);
	
	if(strcmp(str, "yes") == 0) {
    drawBoard(gameInfo);
    printf("O: You see that above me? that's the board.\n");					waitFor(2);
    printf("O: Each of the nine squares is numbered, for your ease.\n");		waitFor(3);
    printf("O: You'll just enter the number you want to place you're X in.\n");	waitFor(3);
    printf("O: After that, I'll update the board then take my turn.\n");		waitFor(3);
    printf("O: Should be simple enough. I hope you got it all because I'm explaining it again.\n");	waitFor(3);
    printf("O: Just about ready, give me a few more seconds."); waitFor(5);
		return; 
	}
	else if(strcmp(str, "no") == 0) {
		printf("very well then, I will get this game started.\n");				waitFor(2);
		return;
	} 
	else if(strcmp(str, "exit") == 0)
		exit(0);
	else {
		printf("O: I'm not sure I understand. You will have to be more clear.\n");
		rules(gameInfo);
	}
}

void drawBoard(struct GameInfo* gameInfo) {
	system("clear");

	printf("\t\t\t _________________ \n");
	printf("\t\t\t|     |     |     |\n");
	printf("\t\t\t|  %c  |  %c  |  %c  |\n", gameInfo->square[1], gameInfo->square[2], gameInfo->square[3]);
    printf("\t\t\t|_____|_____|_____|\n"); 
    printf("\t\t\t|     |     |     |\n");
    printf("\t\t\t|  %c  |  %c  |  %c  |\n", gameInfo->square[4], gameInfo->square[5], gameInfo->square[6]);
    printf("\t\t\t|_____|_____|_____|\n"); 
    printf("\t\t\t|     |     |     |\n");
    printf("\t\t\t|  %c  |  %c  |  %c  |\n", gameInfo->square[7], gameInfo->square[8], gameInfo->square[9]);
    printf("\t\t\t|_____|_____|_____|\n\n\n");

}

bool checkEnd(struct GameInfo* gameInfo)
{
    if (gameInfo->square[1] == gameInfo->square[2] && gameInfo->square[2] == gameInfo->square[3]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[4] == gameInfo->square[5] && gameInfo->square[5] == gameInfo->square[6]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[7] == gameInfo->square[8] && gameInfo->square[8] == gameInfo->square[9]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[1] == gameInfo->square[4] && gameInfo->square[4] == gameInfo->square[7]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[2] == gameInfo->square[5] && gameInfo->square[5] == gameInfo->square[8]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[3] == gameInfo->square[6] && gameInfo->square[6] == gameInfo->square[9]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[1] == gameInfo->square[5] && gameInfo->square[5] == gameInfo->square[9]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[3] == gameInfo->square[5] && gameInfo->square[5] == gameInfo->square[7]) {
    	gameInfo->win = true;
        return true;
        }
    else if (gameInfo->square[1] != '1' && gameInfo->square[2] != '2' && gameInfo->square[3] != '3' &&
        gameInfo->square[4] != '4' && gameInfo->square[5] != '5' && gameInfo->square[6] != '6' 
        && gameInfo->square[7] != '7' && gameInfo->square[8] != '8' && gameInfo->square[9] != '9') {
    	gameInfo->win = false;
        return true;
        }
    else
        return false;
}

int getch (void)
{
        int ch;
        struct termios oldt, newt;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON|ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
}

void playersTurn(struct GameInfo* gameInfo) {// accepts player input for desired square as long as it isn't filled
	int choice;

	printf("O: Your turn, player.\n");
        scanf("%d", &choice);

        if (choice == 1 && gameInfo->square[1] == '1')
            gameInfo->square[1] = gameInfo->playerMark;
        else if (choice == 2 && gameInfo->square[2] == '2')
            gameInfo->square[2] = gameInfo->playerMark;
        else if (choice == 3 && gameInfo->square[3] == '3')
            gameInfo->square[3] = gameInfo->playerMark;
        else if (choice == 4 && gameInfo->square[4] == '4')
            gameInfo->square[4] = gameInfo->playerMark;
        else if (choice == 5 && gameInfo->square[5] == '5')
            gameInfo->square[5] = gameInfo->playerMark;
        else if (choice == 6 && gameInfo->square[6] == '6')
            gameInfo->square[6] = gameInfo->playerMark;
        else if (choice == 7 && gameInfo->square[7] == '7')
            gameInfo->square[7] = gameInfo->playerMark;
        else if (choice == 8 && gameInfo->square[8] == '8')
            gameInfo->square[8] = gameInfo->playerMark;
        else if (choice == 9 && gameInfo->square[9] == '9')
            gameInfo->square[9] = gameInfo->playerMark;
        else
        {
            printf("Invalid move. \n");
            getch();
        }
}

void theGamesTurn(struct GameInfo* gameInfo) {

	//playerState(gameInfo);
	printf("O: hmm, I'll go here.\n"); 	waitFor(3);
			
	if (gameInfo->OStart) {
		if (gameInfo->turnCounter == 1)											//O starts turn 1
			gameInfo->square[1] = gameInfo->OMark;
		else if (gameInfo->turnCounter == 3) {									//O starts turn 2
			if (gameInfo->square[9] != 'X' && gameInfo->square[9] == '9')		
				gameInfo->square[9] = gameInfo->OMark;
			else 
				gameInfo->square[3] = gameInfo->OMark;		
		}
	 
		else if (gameInfo->turnCounter == 5) {									//O starts turn 3
			if (nearWin(gameInfo, gameInfo->OMark))
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if (nearWin(gameInfo, gameInfo->playerMark))	
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else {
				if (!taken(gameInfo, 7))
					gameInfo->square[7] = gameInfo->OMark;
				else if (!taken(gameInfo, 3))
					gameInfo->square[3] = gameInfo->OMark;
			}
		}
		else if (gameInfo->turnCounter == 7) {									//O starts turn 4
			if (nearWin(gameInfo, gameInfo->OMark))
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if (nearWin(gameInfo, gameInfo->playerMark))	
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else {
				if (!taken(gameInfo, 2))
					gameInfo->square[2] = gameInfo->OMark;
				else if (!taken(gameInfo, 4))
					gameInfo->square[4] = gameInfo->OMark;
				else if (!taken(gameInfo, 6))
					gameInfo->square[6] = gameInfo->OMark;
				else if (!taken(gameInfo, 8))
					gameInfo->square[8] = gameInfo->OMark;
			}
		}
		else if (gameInfo->turnCounter == 9 && !gameInfo->hard) {				//O starts turn 5 moderate
			if (nearWin(gameInfo, gameInfo->OMark))							
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if (nearWin(gameInfo, gameInfo->playerMark))	
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else {
				if (!taken(gameInfo, 2))
					gameInfo->square[2] = gameInfo->OMark;
				else if (!taken(gameInfo, 4))
					gameInfo->square[4] = gameInfo->OMark;
				else if (!taken(gameInfo, 6))
					gameInfo->square[6] = gameInfo->OMark;
				else if (!taken(gameInfo, 8))
					gameInfo->square[8] = gameInfo->OMark;
			}
		}
		else if (gameInfo->turnCounter == 9 && gameInfo->hard)	{				//O starts turn 5 hard
			if (nearWin(gameInfo, gameInfo->OMark))
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if ((gameInfo->square[1] == gameInfo->square[3] && gameInfo->square[1] == gameInfo->OMark) 
					||(gameInfo->square[1] == gameInfo->square[2] && gameInfo->square[1] == gameInfo->OMark)) {
				gameInfo->square[2] = gameInfo->OMark;
				gameInfo->square[3] = gameInfo->OMark;
				}
			else if ((gameInfo->square[1] == gameInfo->square[9] && gameInfo->square[1] == gameInfo->OMark) 
					||(gameInfo->square[1] == gameInfo->square[5] && gameInfo->square[1] == gameInfo->OMark)) {
				gameInfo->square[9] = gameInfo->OMark;
				gameInfo->square[5] = gameInfo->OMark;
					
			}
			
		}
	}
	else {
		if (gameInfo->turnCounter == 2) {
			if (!taken(gameInfo, 5))											//O starts turn 1
				gameInfo->square[5] = gameInfo->OMark;
			else
				gameInfo->square[1] = gameInfo->OMark;
		}
		else if (gameInfo->turnCounter == 4)	{								//O starts turn 2
			if (nearWin(gameInfo, gameInfo->playerMark))	
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if (!taken(gameInfo, 4))
				gameInfo->square[4] = gameInfo->OMark;
		}
		else if (gameInfo->turnCounter == 6)	{								//O starts turn 3
			if (nearWin(gameInfo, gameInfo->OMark))
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if (nearWin(gameInfo, gameInfo->playerMark))	
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else {
				if (!taken(gameInfo, 1))
					gameInfo->square[1] = gameInfo->OMark;
				else if (!taken(gameInfo, 3))
					gameInfo->square[3] = gameInfo->OMark;
				else if (!taken(gameInfo, 7))
					gameInfo->square[7] = gameInfo->OMark;
				else if (!taken(gameInfo, 9))
					gameInfo->square[9] = gameInfo->OMark;
				else if (!taken(gameInfo, 2))
					gameInfo->square[2] = gameInfo->OMark;
				else if (!taken(gameInfo, 4))
					gameInfo->square[4] = gameInfo->OMark;
				else if (!taken(gameInfo, 6))
					gameInfo->square[6] = gameInfo->OMark;
				else if (!taken(gameInfo, 8))
					gameInfo->square[8] = gameInfo->OMark;
			}
			
		}
		else if (gameInfo->turnCounter == 8 && !gameInfo->hard)	{				//O starts turn 4 moderate
			if (nearWin(gameInfo, gameInfo->OMark))
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if (nearWin(gameInfo, gameInfo->playerMark))	
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else {
				if (!taken(gameInfo, 1))
					gameInfo->square[1] = gameInfo->OMark;
				else if (!taken(gameInfo, 3))
					gameInfo->square[3] = gameInfo->OMark;
				else if (!taken(gameInfo, 7))
					gameInfo->square[7] = gameInfo->OMark;
				else if (!taken(gameInfo, 9))
					gameInfo->square[9] = gameInfo->OMark;
				else if (!taken(gameInfo, 2))
					gameInfo->square[2] = gameInfo->OMark;
				else if (!taken(gameInfo, 4))
					gameInfo->square[4] = gameInfo->OMark;
				else if (!taken(gameInfo, 6))
					gameInfo->square[6] = gameInfo->OMark;
				else if (!taken(gameInfo, 8))
					gameInfo->square[8] = gameInfo->OMark;
			}
			
		}
		else if (gameInfo->turnCounter == 8 && gameInfo->hard)	{				//O starts turn 4 hard
			if (nearWin(gameInfo, gameInfo->OMark))
				gameInfo->square[gameInfo->priority] = gameInfo->OMark;
			else if ((gameInfo->square[5] == gameInfo->square[4] && gameInfo->square[5] == gameInfo->OMark) 
					||(gameInfo->square[5] == gameInfo->square[6] && gameInfo->square[5] == gameInfo->OMark)) {
				gameInfo->square[6] = gameInfo->OMark;
				gameInfo->square[4] = gameInfo->OMark;
				}
			else if ((gameInfo->square[1] == gameInfo->square[4] && gameInfo->square[1] == gameInfo->OMark) 
					||(gameInfo->square[1] == gameInfo->square[7] && gameInfo->square[1] == gameInfo->OMark)) {
				gameInfo->square[7] = gameInfo->OMark;
				gameInfo->square[4] = gameInfo->OMark;
					
			}
			
		}
	}
}

bool taken(struct GameInfo* gameInfo, int i) {
	if (gameInfo->square[i] == gameInfo->playerMark || gameInfo->square[i] == gameInfo->OMark)
		return true;
	else return false;
}

bool nearWin(struct GameInfo* gameInfo, char mark) { // checks every scenario where the player is a move away from winning

	if (gameInfo->square[1] == '1' && ((gameInfo->square[2] == mark && gameInfo->square[3] == mark)
										|| (gameInfo->square[4] == mark && gameInfo->square[7] == mark)
										|| (gameInfo->square[5] == mark && gameInfo->square[9] == mark))) {
		gameInfo->priority = 1;
		return true;
		}
	else if (gameInfo->square[2] == '2' && ((gameInfo->square[1] == mark && gameInfo->square[3] == mark)
										|| (gameInfo->square[5] == mark && gameInfo->square[8] == mark))) {
		gameInfo->priority = 2;
		return true;
		}
	else if (gameInfo->square[3] == '3' && ((gameInfo->square[1] == mark && gameInfo->square[2] == mark)
										|| (gameInfo->square[6] == mark && gameInfo->square[9] == mark)
										|| (gameInfo->square[5] == mark && gameInfo->square[7] == mark))) {
		gameInfo->priority = 3;
		return true;
		}
	else if (gameInfo->square[4] == '4' && ((gameInfo->square[1] == mark && gameInfo->square[7] == mark)
										|| (gameInfo->square[5] == mark && gameInfo->square[6] == mark))) {
		gameInfo->priority = 4;
		return true;
		}
	else if (gameInfo->square[5] == '5' && ((gameInfo->square[1] == mark && gameInfo->square[9] == mark)
										|| (gameInfo->square[2] == mark && gameInfo->square[8] == mark)
										|| (gameInfo->square[3] == mark && gameInfo->square[7] == mark)
										|| (gameInfo->square[4] == mark && gameInfo->square[6] == mark))) {
		gameInfo->priority = 5;
		return true;
		}
	else if (gameInfo->square[6] == '6' && ((gameInfo->square[3] == mark && gameInfo->square[9] == mark)
										|| (gameInfo->square[4] == mark && gameInfo->square[5] == mark))) {
		gameInfo->priority = 6;
		return true;
		}
	else if (gameInfo->square[7] == '7' && ((gameInfo->square[1] == mark && gameInfo->square[4] == mark)
										|| (gameInfo->square[3] == mark && gameInfo->square[5] == mark)
										|| (gameInfo->square[8] == mark && gameInfo->square[9] == mark))) {
		gameInfo->priority = 7;
		return true;
		}
	else if (gameInfo->square[8] == '8' && ((gameInfo->square[2] == mark && gameInfo->square[5] == mark)
										|| (gameInfo->square[7] == mark && gameInfo->square[9] == mark))) {
		gameInfo->priority = 8;
		return true;
		}
	else if (gameInfo->square[9] == '9' && ((gameInfo->square[1] == mark && gameInfo->square[5] == mark)
										|| (gameInfo->square[7] == mark && gameInfo->square[8] == mark)
										|| (gameInfo->square[3] == mark && gameInfo->square[6] == mark))) {
		gameInfo->priority = 9;
		return true;
		}
	else return false;
}























