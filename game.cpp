#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"
#include <time.h>
#include <windows.h>

#define BOARDPOSITION 34
#define CUBESPOSITION 1
#define HELLOX 7
#define HELLOY 7
#define MAXNUMBEROFELEMENTS 24
#define SECONDCUBEPOS 16
#define DRAWINGLINE1	for (int i = BOARDPOSITION; i <= BOARDPOSITION + 68; i++)
#define DRAWINGLINE2	for (int i = BOARDPOSITION+70; i <= BOARDPOSITION + 83; i++)
#define WHENMORENUMB1 & AtLeastOne, numb1, scores
#define WHENMORENUMB2 & AtLeastOne, numb2, scores
#define WHENMORENUMB12 & AtLeastOne, numb1+numb2, scores


using namespace std;
//definiction of structure
struct gameState
{
	int firstPlayerWon=0;
	int secondPlayerWon=0;
	int positions[MAXNUMBEROFELEMENTS] = { -2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2 };
	int onHome[2] = { 0,0 };
	int onBar[2] = { 0,0 };
	int whoseRound = 0;
};
//drawing board
void puttingPawnsInHome(struct gameState scores)
{
	int gate = scores.onHome[0], exit = 0;
	if (scores.onHome[0] > 0)
	{
			gotoxy(BOARDPOSITION + 72, 10);
			printf("%d", scores.onHome[0]);
			for (int i = 10; i > 6; i--)
			{
				for (int j = 0; j < 4; j++)
				{
					gotoxy(BOARDPOSITION + 75 + j, i);
					printf("@");
					gate--;
					if (gate == 0)
					{
						exit = 1;
						break;
					}
				}
				if (exit)break;
			}
	}
	exit = 0;
	gate = scores.onHome[1];
	if (scores.onHome[1] > 0)
	{
			gotoxy(BOARDPOSITION + 72, 14);
			printf("%d", scores.onHome[1]);
			for (int i = 14; i < 18; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					gotoxy(BOARDPOSITION + 75 + j, i);
					printf("*");
					gate--;
					if (gate == 0)
					{
						exit = 1;
						break;
					}
				}
				if (exit)break;
			}
	}
}

void drawingHome()
{
	gotoxy(BOARDPOSITION, 2);
	DRAWINGLINE1
		printf("_");
	gotoxy(BOARDPOSITION, 22);
	DRAWINGLINE1
		printf("_");
	gotoxy(BOARDPOSITION+70, 2);
	DRAWINGLINE2
		printf("_");
	for (int i = 3; i <= 22; i++)
	{
		gotoxy(BOARDPOSITION + 69, i);
		cputs("|              |");
		gotoxy(BOARDPOSITION - 1, i);
		cputs("|");
	}
	gotoxy(BOARDPOSITION + 70, 22);
	DRAWINGLINE2
		printf("_");
	gotoxy(BOARDPOSITION + 75, 12);
	cputs("HOME");
}

void topbotNumbersOfBoardMode(int *startNumber, int mode)
{
	if(mode==1)
		printf("%d   ", (*startNumber)++);
	if (mode == -1)
	{
		if (*startNumber / 10 == 1)
			printf("%d   ", (*startNumber)--);
		else 
			printf("%d    ", (*startNumber)--);
	}
}

void topbotNumbersOfBoard(int startNumber, int mode, int row)
{
	gotoxy(BOARDPOSITION + 4, row);
	for (int i = 0; i < 6; i++)
	{
		topbotNumbersOfBoardMode(&startNumber,mode);
	}
	printf("     ");
	for (int i = 0; i < 6; i++)
		topbotNumbersOfBoardMode(&startNumber,mode);
}

void insideBoardMode(int mode)
{
	if(mode==1)
		printf(" %s / ", "\\");
	if(mode==-1)
		printf(" %c \\ ",'/');
}

void insideBoard(int row,int mode)
{
	gotoxy(BOARDPOSITION, row);
	printf("::");
	for (int i = 0; i < 6; i++)
		insideBoardMode(mode);
	printf(" ||| ");
	for (int i = 0; i < 6; i++)
		insideBoardMode(mode);
	printf("::");
}

void topbotBorder(int row)
{
	gotoxy(BOARDPOSITION, row);
	printf(":");
	for (int i = 0; i < 33; i++)
	{
		printf("=");
	}
	printf("0");
	for (int i = 0; i < 33; i++)
		printf("=");
	printf(":");
}

void drawBar()
{
	printf("::");
	for (int i = 0; i < 30; i++)
		printf(" ");
	printf("[BAR]");
	for (int i = 0; i < 30; i++)
		printf(" ");
	printf("::");
}

void midBoard(int row,int mode,struct gameState *scores)
{
	gotoxy(BOARDPOSITION, row);
	switch (mode)
	{
		case 0:
			drawBar();
			break;
		case 1:
			printf("::");
			for (int i = 0; i < 65; i++)
				printf(" ");
			printf("::");
			break;
		case 2:
			printf("::");
			for (int i = 0; i < 31; i++)
				printf(" ");
			printf("@ %d", scores->onBar[0]);
			for (int i = 0; i < 31; i++)
				printf(" ");
			printf("::");
			break;
		case 3:
			printf("::");
			for (int i = 0; i < 31; i++)
				printf(" ");
			printf("* %d", scores->onBar[1]);
			for (int i = 0; i < 31; i++)
				printf(" ");
			printf("::");
			break;
	}
}

void dynamicMidBoard(struct gameState* scores)
{
	if (scores->onBar[0] == 0 && scores->onBar[1] == 0)
	{
		midBoard(11, 1, scores);
		midBoard(12, 0, scores);
		midBoard(13, 1, scores);
	}
	else if (scores->onBar[1] == 0)
	{
		midBoard(11, 2, scores);
		midBoard(12, 0, scores);
		midBoard(13, 1, scores);
	}
	else if (scores->onBar[0] == 0)
	{
		midBoard(11, 1, scores);
		midBoard(12, 0, scores);
		midBoard(13, 3, scores);
	}
	else
	{
		midBoard(11, 2, scores);
		midBoard(12, 0, scores);
		midBoard(13, 3, scores);
	}
}

void drawingBoard(struct gameState* scores)
{
	gotoxy(BOARDPOSITION, 1);
	cputs("Game of Backgammon");
	gotoxy(BOARDPOSITION+51, 1);
	printf("Score: P1 %d, P2 %d", scores->firstPlayerWon, scores->secondPlayerWon);
	topbotNumbersOfBoard(13,1,3);
	topbotBorder(4);
	for (int i = 5; i <= 10; i++)
		insideBoard(i,1);
	dynamicMidBoard(scores);
	for (int i = 14; i <= 19; i++)
		insideBoard(i,-1);
	topbotBorder(20);
	topbotNumbersOfBoard(12, -1, 21);
	drawingHome();
	puttingPawnsInHome(*scores);
}
//the end of functions drawing board

unsigned int randomNumber1_6(unsigned int *number)
{
	*number = rand() % 6 + 1;
	return *number;
}

void drawingMenu()
{
	gotoxy(BOARDPOSITION+7, 24);
	cputs("Select: p(lay) l(oad) n(ew) g(raphic) q(uit)");
	gotoxy(BOARDPOSITION + 7, 25);
}

void drawingMenuInGame()
{
	gotoxy(BOARDPOSITION - 4, 24);
	cputs("Select: p(lay) esc(start screen) s(ave) l(oad) n(ew) m(ake move) s(k)ip s(w)ap");
	gotoxy(BOARDPOSITION - 4, 25);
}
//function to draw cubes
void drawing1Cube(const int pos)
{
	gotoxy(CUBESPOSITION + 6 + pos, 8);
	cputs("###");
}

void drawing2Cube(const int pos)
{
	gotoxy(CUBESPOSITION + 3 + pos, 10);
	cputs("###");
	gotoxy(CUBESPOSITION + 9 + pos, 6);
	cputs("###");
}

void drawing3Cube(const int pos)
{
	for (int i = 3, j = 10; i <= 9; i += 3, j -= 2)
	{
		gotoxy(CUBESPOSITION + i + pos, j);
		cputs("###");
	}
}

void drawing4Cube(const int pos)
{
	for (int i = 3; i <= 9; i += 6)
		for (int j = 6; j <= 10; j += 4)
		{
			gotoxy(CUBESPOSITION + i + pos, j);
			cputs("###");
		}
}

void drawing5Cube(const int pos)
{
	for (int i = 2, j = 10; i <= 10; i += 4, j -= 2)
	{
		gotoxy(CUBESPOSITION + i + pos, j);
		cputs("###");
	}
	gotoxy(CUBESPOSITION + 2 + pos, 6);
	cputs("###");
	gotoxy(CUBESPOSITION + 10 + pos, 10);
	cputs("###");
}

void drawing6Cube(const int pos)
{
	for (int j = 3; j <= 10; j += 7)
		for (int i = 6; i <= 10; i += 2)
		{
			gotoxy(CUBESPOSITION + j + pos, i);
			cputs("##");
		}
}

void whichCube(const int pos, int arg)
{
	if (arg == 0);
	if (arg == 1)drawing1Cube(pos);
	if (arg == 2)drawing2Cube(pos);
	if (arg == 3)drawing3Cube(pos);
	if (arg == 4)drawing4Cube(pos);
	if (arg == 5)drawing5Cube(pos);
	if (arg == 6)drawing6Cube(pos);
}

void drawingCube(const int pos, int arg)
{
	gotoxy(CUBESPOSITION + 13, 2);
	cputs("CUBES");
	gotoxy(CUBESPOSITION + 1 + pos, 4);
	cputs("_____________");
	for (int i = 0; i < 7; i++)
	{
		gotoxy(CUBESPOSITION + pos, 4 + i + 1);
		cputs("|             |");
	}
	gotoxy(CUBESPOSITION + 1 + pos, 11);
	cputs("_____________");
	whichCube(pos, arg);
}
//the end of funciotns that draws cubes
//putting pawns on board
void puttingBot(int** t)
{
	int j = 19, gate = 0;
	for (int i = 65; i >= 5; i -= 5)
	{
		int k = 0;
		if (i == 35)gate = 0;
		else gate = 1;
		if (gate)
		{
			if (*t != 0)
			{
				j = 19 - abs(**t) + 1;
				if (abs(**t) > 7)j = 19 - 7 + 1;
				for (; j <= 19; j++)
				{
					if (abs(**t) <= 6)k++;
					gotoxy(BOARDPOSITION + i - 1, j);
					if (!(abs(**t) > 6&& j == 19 - 7 + 1))
					{
						if (**t > 0 && k >= 1)cputs("*");
						else if (k >= 1) cputs("@");
					}
					else
					{
						gotoxy(BOARDPOSITION + i - 2, j);
						printf("+%d", abs(**t) - 6);
						gotoxy(BOARDPOSITION + i - 1, j);
						k++;
					}
				}
			}
			(*t)++;
		}
	}
}

void puttingTop(int** t)
{
	int j = 5, gate = 0;
	for (int i = 5; i <= 65; i += 5)
	{
		int k = 0;
		if (i == 35)gate = 0;
		else gate = 1;
		if (gate)
		{
			if (*t != 0)
			{
				j = 5 + abs(**t) - 1;
				if (abs(**t) > 7)j = 5 + 7 - 1;
				for (; j >= 5; j--)
				{
					if (abs(**t) <= 6)k++;
					gotoxy(BOARDPOSITION + i - 1, j);
					if (!(abs(**t) > 6 && j == 5 + 7 - 1))
					{
						if (**t > 0&&k>=1)cputs("*");
						else if(k >= 1) cputs("@");
					}
					else
					{
						gotoxy(BOARDPOSITION + i - 2, j);
						printf("+%d", abs(**t) - 6);
						gotoxy(BOARDPOSITION + i - 1, j);
						k++;
					}
				}
			}
			(*t)++;
		}
	}
}

void puttingPawnsOnBoard(int *t)
{
	puttingBot(&t);
	puttingTop(&t);
}
//the end of putting pawns
//the information and big hello
void welcomingAndExtraInfo()
{
	gotoxy(HELLOX, HELLOY);
	cputs("# # ### #   #    #");
	gotoxy(HELLOX, HELLOY+1);
	cputs("# # #   #   #   # #");
	gotoxy(HELLOX, HELLOY+2);
	cputs("### ### #   #   # #");
	gotoxy(HELLOX, HELLOY+3);
	cputs("# # #   #   #   # #");
	gotoxy(HELLOX, HELLOY+4);
	cputs("# # ### ### ###  #");
	gotoxy(HELLOX-3, HELLOY + 6);
	cputs("For more information about");
	gotoxy(HELLOX - 3, HELLOY + 7);
	cputs("a game and how to play it");
	gotoxy(HELLOX-5, HELLOY + 8);
	cputs("click i(nfo) for Polish manual");
	gotoxy(HELLOX -4, HELLOY + 9);
	cputs("or in(f)o for English manual");
}

//menu in grafic menu
void selectGraphicText()
{
	gotoxy(46, 1);
	cputs("Here are things you can change:");
	gotoxy(37, 3);
	cputs("1. To change background color click enter button");
	gotoxy(37, 4);
	cputs("2.   To change font color click space button");
	gotoxy(37, 5);
	cputs("3.   To change all above to default click d");
	gotoxy(42, 7);
	cputs("To return to main menu click Esc button");
}

void GraphicMenu(int zn, int* attr, int* back)
{
	clrscr();
	do
	{
		selectGraphicText();
		zn = getch();
		if (zn == ' ') *attr = (*attr + 1) % 16;
		else if (zn == 0x0d) *back = (*back + 1) % 16;
		if (zn == 'd')
		{
			*attr = 2;
			*back = 0;
		}
		textcolor(*attr);
		textbackground(*back);
		if (kbhit())
		{
			zn = getch();
		}
	} while (zn != 27);
}

//action when g is clicked
void selectGraphic(int zn,int *attr, int *back)
{
	if (zn == 'g')
		GraphicMenu(zn, attr, back);
}
//instruction how to back to main menu
void selectInfoText()
{
	gotoxy(50, 1);
	cputs("Here are all rules:");
	gotoxy(2, 1);
	cputs("To return to main menu click Esc button");
}
//putting on screen what is inside a text file with manual in Polish
void selectPolishInfo(int zn)
{
	char linia[400];
	unsigned int i = 3;
	const char* FileName = "zasady_gry.txt";
	FILE* file = fopen(FileName, "r");
	clrscr();
	do
	{
		selectInfoText();
		if (file == NULL) {
			gotoxy(46, 26);
			printf("File cannot be open: %s\n", FileName);
			Sleep(4000);
		}
		else
		{
			while (fgets(linia, sizeof(linia), file) != NULL) {
				gotoxy(1, i++);
				printf(" %s", linia);
			}
			fclose(file);
		}
		if (kbhit())
		{
			zn = getch();
		}
	} while (zn != 27);
}
//the same but in English
void selectEnglishInfo(int zn)
{
	char linia[400];
	unsigned int i = 3;
	const char* FileName = "manual.txt";
	FILE* file = fopen(FileName, "r");
	clrscr();
	do
	{
		selectInfoText();
		if (file == NULL) {
			gotoxy(46, 26);
			printf("File cannot be open: %s\n", FileName);
			Sleep(4000);
		}
		else
		{
			while (fgets(linia, sizeof(linia), file) != NULL) {
				gotoxy(2, i++);
				printf("%s", linia);
			}
			fclose(file);
		}
		if (kbhit())
		{
			zn = getch();
		}
	} while (zn != 27);
}

void selectInfo(int zn)
{
	if (zn == 'i')
		selectPolishInfo(zn);
	else if (zn == 'f') selectEnglishInfo(zn);
}

void clrInfoInGameT() // clearing text infoformations on screen
{
	for (int i = 25; i < 30; i++)
	{
		gotoxy(BOARDPOSITION + 2, i);
		cputs("                                                                                        ");
	}
}
//outside boreder for informations during the game
void informationsInGameText(const int pos)
{
	gotoxy(pos, 25);
	for (int i = 0; i < 43; i++)
		printf("_");
	for (int j = 0; j < 3; j++)
	{
		gotoxy(pos - 1, 26 + j);
		printf("|");
		for (int i = 0; i < 43; i++)
			printf(" ");
		printf("|");
	}
	gotoxy(pos, 28);
	for (int i = 0; i < 43; i++)
		printf("_");
}
//removing save and All Moves files
void removeSaveFile() {
	if (remove("game_state.txt") != 0 && remove("AllMoves.txt") != 0)
	{
		gotoxy(38, 27);
		perror("Error removing file");
		Sleep(2000);
	}

}
//text to informations
void infGame(int w,const int pos)
{
	informationsInGameText(pos);
	gotoxy(pos+5, 27);
	if (w == 1)cputs("Game has been successfully saved.");
	if (w == 2)cputs("Game has been successfully loaded.");
	if (w == 3)cputs("You have bitten opponents pawn.");
	if (w == 4)cputs("Two same cubes, you get extra move.");
	if (w == 5)cputs("No possible move, next player move");
	if (w == 6)cputs("You have just skipped your move.");
	if (w == 7)cputs("You have just skipped first cube.");
	Sleep(3000);
	clrInfoInGameT();
}

void infGame2(int w, const int pos)
{
	informationsInGameText(pos);
	gotoxy(pos + 5, 27);
	if (w == 8)
	{
		gotoxy(pos + 2, 27);
		cputs("Pawn from the bar returned to the game.");
	}
	if (w == 9)
	{
		gotoxy(pos + 8, 27);
		cputs("You have swapped your cubes.");
	}
	if (w == 10)
	{
		gotoxy(pos + 5, 27);
		cputs("You have moved your pawn to home.");
	}
	Sleep(3000);
	clrInfoInGameT();
}
//text to filesaving error
void fileSavingOrLoadingErrorText(int w,const int pos)
{
	if (w == 1)
	{
		gotoxy(pos - 4, 27);
		perror("File saving failed");
		Sleep(3000);
	}
	else if (w == 2)
	{
		gotoxy(pos - 4, 27);
		perror("Error reading data from file");
		Sleep(3000);
	}
}
//module for printing all moves to the text file
void movesToFile(struct gameState* scores, unsigned int numb, int* i, unsigned int c, int mode, FILE* file,int sign) //c is column
{
	if (c - 48 != 25 && c - 48 != 0)
	{
		fprintf(file, "%d. Player %d: ", *i, scores->whoseRound);
		(*i)++;
	}
	if (mode == 1)fprintf(file, "BAR -> %d", c + 1);
	else if (mode == 2)fprintf(file, "%d -> HOME", c);
	else if (mode == 3)
	{
		if (c - 48 == 25 || c - 48 == 0)fprintf(file, "BAR -> %d X", c + numb * sign - 48);
		else fprintf(file, "%d -> %d X", c - 48, c + numb * sign - 48);
	}
	else if (mode == 4 && c - 48 != 25 && c - 48 != 0)fprintf(file, "%d -> %d", c - 48, c + numb * sign - 48);
	fprintf(file, "\n");
	fclose(file);
}

void savingMoves(struct gameState* scores, unsigned int numb, int* i, unsigned int column, int mode)
{
	int sign = 0;
	if (scores->whoseRound == 1)sign = 1;
	else sign = -1;
	char p;
	if (sign == 1)p = '@';
	else p = '*';
	const int pos = 47;
	FILE* file = fopen("AllMoves.txt", "a");
	if (file != NULL) {
		movesToFile(scores, numb, i, column, mode, file, sign);
	}
	else {
		fileSavingOrLoadingErrorText(1, pos);
	}
}

void savingGameState(struct gameState* scores)
{
	const int pos = 47;
	FILE* file = fopen("game_state.txt", "w");
	if (file != NULL) {
		fprintf(file, "%d %d", scores->firstPlayerWon, scores->secondPlayerWon);
		for (int i = 0; i < MAXNUMBEROFELEMENTS; i++) {
			fprintf(file, " %d", scores->positions[i]);
		}
		fprintf(file, " %d %d %d %d %d",scores->onHome[0], scores->onHome[1],scores->onBar[0], scores->onBar[1],scores->whoseRound);

		fclose(file);
		infGame(1, pos);
	}
	else {
		fileSavingOrLoadingErrorText(1, pos);
	}
}
//action for s clicked
void selectSave(int zn,struct gameState* scores)
{
	if (zn == 's')
		savingGameState(scores);
}
//cannot open file text information
void cannotOpenText(const int pos)
{
	gotoxy(pos - 4, 27);
	perror("File cannot be opened");
	Sleep(4000);
}
//error and info box
void ifErrorOrElse(FILE*file,struct gameState*scores,const int pos,int *zn)
{
	if (fscanf(file, " %d %d %d %d %d", &(scores->onHome[0]), &(scores->onHome[1]), &(scores->onBar[0]), &(scores->onBar[1]), &(scores->whoseRound)) != 5)
	{
		fileSavingOrLoadingErrorText(2, pos);
	}
	else
	{
		fclose(file);
		infGame(2, pos);
		*zn = 'p';
	}
}

void loadingGameState(int* zn, struct gameState* scores)
{
	const int pos = 47;
	FILE* file = fopen("game_state.txt", "r");
	if (file == NULL)
	{
		cannotOpenText(pos);
	}
	else
	{
		if (fscanf(file, "%d %d", &(scores->firstPlayerWon), &(scores->secondPlayerWon)) != 2)
		{
			fileSavingOrLoadingErrorText(2, pos);
		}
		else
		{
			for (int i = 0; i < MAXNUMBEROFELEMENTS; i++)
			{
				if (fscanf(file, " %d", &(scores->positions[i])) != 1)
				{
					fileSavingOrLoadingErrorText(2, pos);
					break;
				}
			}
			ifErrorOrElse(file, scores, pos, zn);
		}
	}
}

void selectLoad(int *zn, struct gameState* scores)
{
	if (*zn == 'l')
		loadingGameState(zn,scores);
}
//view of the game used to refresh view after changes
void gameView(struct gameState** scores)
{
	unsigned int numb = 0;
	drawingBoard(*scores);
	drawingCube(0, randomNumber1_6(&numb));
	drawingCube(SECONDCUBEPOS, randomNumber1_6(&numb));
	drawingMenuInGame();
	puttingPawnsOnBoard((*scores)->positions);
}
//question for starting a new game
void newQuestionText(const int pos)
{
	gotoxy(pos+6, 12);
	cputs("Are you sure you want to start");
	gotoxy(pos+3, 13);
	cputs("a new game and delete your game save?");
	gotoxy(pos + 10, 15);
	cputs("y(es)");
	gotoxy(pos + 29, 15);
	cputs("n(o)");
}
//border for above
void newQuestionBorder(const int pos)
{
	gotoxy(pos, 10);
	for (int i = 0; i < 43; i++)
		printf("_");
	for (int j = 0; j < 6; j++)
	{
		gotoxy(pos - 1, 11 + j);
		printf("|");
		for (int i = 0; i < 43; i++)
			printf(" ");
		printf("|");
	}
	gotoxy(pos, 16);
	for (int i = 0; i < 43; i++)
		printf("_");
}
//reseting game state after new game choice
void resetGameState(struct gameState* scores,const int reset[MAXNUMBEROFELEMENTS])
{
	for (int i = 0; i < 24; i++)
	{
		scores->positions[i] = reset[i];
	}
	scores->firstPlayerWon = 0;
	scores->secondPlayerWon = 0;
	scores->onBar[0] = 0;
	scores->onBar[1] = 0;
	scores->onHome[0] = 0;
	scores->onHome[1] = 0;
	scores->whoseRound = 0;
}
//reset game state after winnig a game
void resetGameStateForContinue(struct gameState* scores, const int reset[MAXNUMBEROFELEMENTS])
{
	for (int i = 0; i < 24; i++)
	{
		scores->positions[i] = reset[i];
	}
	scores->onBar[0] = 0;
	scores->onBar[1] = 0;
	scores->onHome[0] = 0;
	scores->onHome[1] = 0;
	scores->whoseRound = 0;
}

void selectNew(int *zn, struct gameState* scores, const int reset[MAXNUMBEROFELEMENTS],int *j)
{
	const int pos = 42;
	if (*zn == 'n')
	{
		clrscr();
		newQuestionBorder(pos);
		newQuestionText(pos);
		*zn = getch();
		if (*zn == 'y')
		{
			resetGameState(scores, reset);
			removeSaveFile();
			*j = 0;
			*zn = 'p';
		}
	}
}
//view in main menu
void firstView(struct gameState* scores)
{
	drawingBoard(scores);
	welcomingAndExtraInfo();
	drawingMenu();
	puttingPawnsOnBoard(scores->positions);
}
//clearing space for text during moves
void clearingSpace()
{
	gotoxy(2, 13);
	cputs("                             ");
	gotoxy(2, 14);
	cputs("                             ");
}

void preparingSpace1(int mode)
{
	if(mode==0)Sleep(1500);
	gotoxy(2, 13);
	clearingSpace();
	gotoxy(2, 13);
}

void decideWho(struct gameState* scores, unsigned int numb1, unsigned int numb2)
{
	if (numb1 > numb2)
	{
		preparingSpace1(0);
		cputs("Player 1 (@) starts.");
		scores->whoseRound = 1;
	}
	else
	{
		preparingSpace1(0);
		cputs("Player 2 (*) starts.");
		scores->whoseRound = 2;
	}
}

void whoseRoundText(unsigned int numb1, unsigned int numb2)
{
	drawingCube(0, 0);
	drawingCube(SECONDCUBEPOS, 0);
	preparingSpace1(0);
	cputs("Who get a higher number");
	gotoxy(2, 14);
	cputs("on one cube starts...");
	Sleep(1500);
	preparingSpace1(0);
	printf("Player 1 (@) gets: %d", numb1);
	gotoxy(2, 13);
	drawingCube(0, numb1);
	drawingCube(SECONDCUBEPOS, 0);
	Sleep(1500);
	gotoxy(2, 14);
	printf("Player 2 (*) gets: %d", numb2);
	drawingCube(0, numb1);
	drawingCube(SECONDCUBEPOS, numb2);
	preparingSpace1(0);
}

void whoseRound(struct gameState* scores)
{
	unsigned int numb1 = 0, numb2 = 0;
	preparingSpace1(1);
	if (scores->whoseRound != 0)
	{
		if(scores->whoseRound==1)
		cputs("Player number 1 (@) is moving.");
		else cputs("Player number 2 (*) is moving.");
	}
	else
	{
		do {
			randomNumber1_6(&numb1);
			randomNumber1_6(&numb2);
			whoseRoundText(numb1, numb2);
			if (numb1 == numb2)cputs("Both players got same number.");
		}while(numb1==numb2);
		decideWho(scores, numb1, numb2);
	}
}

void cubsThrow(unsigned int *numb1, unsigned int *numb2)
{
	drawingCube(0,0);
	drawingCube(SECONDCUBEPOS, 0);
	gotoxy(12, 3);
	cputs("throwing...");
	Sleep(1000);
	drawingCube(0, randomNumber1_6(&(*numb1)));
	Sleep(1000);
	drawingCube(SECONDCUBEPOS, randomNumber1_6(&(*numb2)));
	gotoxy(12, 3);
	Sleep(1000);
	cputs("             ");
}

void clrTF(int p, int o, int k)//clear text field with changable position
{
	gotoxy(2, p);
	cputs("                              ");
	gotoxy(2, o);
	cputs("                              ");
	gotoxy(2, k);
}
//action after choosing 
void selectMoveMod(unsigned int *mode, unsigned int numb1, unsigned int numb2)
{
	gotoxy(2, 18);
	cputs("Using (choose): 1 or 2 cubes?");
	_setcursortype(_SOLIDCURSOR);
	gotoxy(2, 19);
	*mode = getch();
	if (*mode != 'k')
	{
		while (*mode != '1' && *mode != '2')
		{
			printf("You cannot choose: %c", *mode);
			Sleep(1000);
			gotoxy(2, 19);
			cputs("                          ");
			gotoxy(2, 19);
			*mode = getch();
		}
		printf("%c", *mode);
		Sleep(1000);
	}
	_setcursortype(_NOCURSOR);
}
//reading a column number with proper input
void readingColumn(unsigned int* column)
{
	unsigned int helper = 0;
	*column = getch();
 	printf("%c", *column);
	if (*column != 'k' && *column != 'w')
	{
		helper = getch();
		if (helper >= '1' && helper <= '9')
		{
			printf("%d", helper - 48);
			*column = ((*column - 48) * 10 + helper - 48) + 48;
		}
	}
}

void gettingColumn(unsigned int *column,const int pos)
{
	_setcursortype(_SOLIDCURSOR);
	printf("Pick column (for one");
	gotoxy(2, pos);
	printf("digit => digit+space): ");
	readingColumn(column);
	if (*column != 'k' && *column != 'w')
	{
		while (*column > '24' && *column < '1')
		{
			printf("You cannot choose: %d", int(*column - 48));
			readingColumn(column);
			clrTF(pos - 1, pos, pos - 1);
		}
	}
	_setcursortype(_NOCURSOR);

}

int isThereProperPawns(unsigned int column,struct gameState* scores)
{
	column -= 48;
	int sign = 0, toreturn=0;
	if (scores->whoseRound == 1)sign = -1;
	else if (scores->whoseRound == 2)sign = 1;
	if (scores->positions[column - 1] * sign > 0)toreturn = 1;
	else if (scores->positions[column - 1] * sign == 0)toreturn = 0;
	if (scores->positions[column - 1] * sign < 0)toreturn = -1;
	return toreturn;
}

int ifFBar(struct gameState* scores)//if from bar taking
{
	int sign = 0;
	if (scores->whoseRound == 1)sign = -1;
	else sign = 1;
	if (sign == -1 && scores->onBar[0] > 0)return 1;
	else if (sign == 1 && scores->onBar[1] > 0)return 1;
	return 0;
}
//checking if it is impossible to move from bar
int cannotBeMovedTakingFromBar(struct gameState* scores, unsigned int numb, int* sign, unsigned int column1)
{
	if (*sign == -1 && numb > 6)return 1;
	else if (*sign == -1 && scores->positions[numb - 1] > 1)return 1;
	if (*sign == 1 && numb > 6)return 1;
	else if (*sign == 1 && scores->positions[24 - numb] < -1)return 1;
	return 0;
}
//checking other posibilities
int cannotBeMovedAllPossibilities(struct gameState* scores, unsigned int numb, int* sign, unsigned int column1)
{
	if (*sign == -1 && column1 + numb - 49 > 23)return 1;
	else if (*sign == -1 && scores->positions[column1 + numb - 49] > 1)return 1;
	if (*sign == 1 && (column1 - numb < 49))return 1;
	else if (*sign == 1 && scores->positions[column1 - numb - 49] < -1)return 1;
	return 0;
}
//grouping function
int cannotBeMovedModule(struct gameState* scores, unsigned int numb, int* sign,unsigned int column1)
{
	if (scores->whoseRound == 1)*sign = -1;
	else if (scores->whoseRound == 2)*sign = 1;
	if (ifFBar(scores))
	{
		if (cannotBeMovedTakingFromBar(scores, numb, sign, column1))return 1;
	}
	else 
	{
		if (cannotBeMovedAllPossibilities(scores, numb, sign, column1))return 1;
	}
	return 0;
}
//checking a capture ability
int ifBeatable(int sign, unsigned int column1, unsigned int numb, struct gameState* scores)
{
	int beatable = 0;
	if (abs(scores->positions[column1 + numb * (-sign) - 49]) == 1)
		if (scores->positions[column1 + numb * (-sign) - 49] * sign < 0)beatable = 1;
	return beatable;
}
//checking possible capture
unsigned int checkingIfPossibleBeat(struct gameState* scores,unsigned int column, unsigned int numb,unsigned int *wh)//wh ->whichcolumnshloudbe
{
	int sign = 0;
	unsigned int lastCell;
	if (scores->whoseRound == 1)sign = -1;
	else if (scores->whoseRound == 2)sign = 1;
	if(sign==-1)
	{
		lastCell = 23;
		for (unsigned int i = 0; i <= lastCell - numb; i++)
		{
			if (scores->positions[i] * sign > 0)
				if (ifBeatable(sign, i + 49, numb, scores))
				{
					*wh = i;
					return 1;
				}
		}
	}
	else if (sign == 1)
	{
		lastCell = 0;
		for (unsigned int i = 23; i >= lastCell + numb; i--)
		{
			if (scores->positions[i] * sign > 0)
				if (ifBeatable(sign, i + 49, numb, scores))
				{
					*wh = i;
					return 1;
				}
		}
	}
	return 0;
}

void beatingModule(int sign,unsigned int column1, unsigned int numb, struct gameState* scores,int *i)
{
	const int pos = 47;
	if (ifBeatable(sign, column1, numb, scores))
	{
		if (scores->positions[column1 + numb * (-sign) - 49] == -1)scores->onBar[0] += 1;
		else if (scores->positions[column1 + numb * (-sign) - 49] == 1)scores->onBar[1] += 1;
		scores->positions[column1 + numb * (-sign) - 49] -= -sign;
		infGame(3, pos);
		clrInfoInGameT();
		savingMoves(scores, numb, i, column1, 3);
	}
	else savingMoves(scores, numb, i, column1, 4);
}

void movingPawnsFromBarModule(int sign, unsigned int numb, struct gameState* scores, int* i)
{
	if (cannotBeMovedModule(scores, numb, &sign, 0) == 0)
	{
		if (sign == 1)
		{
			beatingModule(sign, 24 + 49, numb, scores,i);
			scores->positions[24 + 49 + numb * (-sign) - 49] += sign;
			scores->onBar[1]--;
			savingMoves(scores, numb, i, 24 + numb * (-sign), 1);
		}
		else
		{
			beatingModule(sign, -1 + 49, numb, scores,i);
			scores->positions[-1 + 49 + numb * (-sign) - 49] += sign;
			scores->onBar[0]--;
			savingMoves(scores, numb, i, -1 + numb * (-sign), 1);
		}
		infGame2(8, 47);
		clrInfoInGameT();
	}
}

int ifTHome(struct gameState* scores)//if to home going
{
	int sum = 0;
	if (scores->whoseRound == 1)
	{
		for (int i = 0; i <= 17; i++)
			if(scores->positions[i]<0)
				sum += scores->positions[i];
		if (sum==0)return 1;
	}
	else
	{
		for (int i = 6; i <= 23; i++)
			if(scores->positions[i]>0)
			sum += scores->positions[i];
		if (sum==0)return 1;
	}
	return 0;
}

int theFurthestPawnInCourt(struct gameState* scores)
{
	if (scores->whoseRound == 1)
		for (int i = 18; i <= 23; i++)
			if (scores->positions[i]<0)return i;
	if(scores->whoseRound == 2)
		for (int i = 5; i >= 0; i--)
			if (scores->positions[i]>0)return i;
}
//moving to home by player 1
void movingPawnsToHomeP1(int *AtLeastOne, unsigned int numb, struct gameState* scores,int *j)
{
	if (numb <= 6)
	{
		if (scores->positions[24 - numb] < 0)
		{
			scores->positions[24 - numb]++;
			scores->onHome[0]++;
			*AtLeastOne = 1;
			savingMoves(scores, numb, j, 24 - numb, 2);
		}
		else
		{
			for (int i = 24 - numb + 1; i <= 23; i++)
				if (scores->positions[i] < 0 && theFurthestPawnInCourt(scores) == i)
				{
					scores->positions[i]++;
					scores->onHome[0]++;
					*AtLeastOne = 1;
					savingMoves(scores, numb, j, i, 2);
					break;
				}
		}
	}
}
//moving to home by player 2
void movingPawnsToHomeP2(int* AtLeastOne, unsigned int numb, struct gameState* scores,int *j)
{
	if (numb <= 6)
	{
		if (scores->positions[-1 + numb] > 0)
		{
			scores->positions[-1 + numb]--;
			scores->onHome[1]++;
			*AtLeastOne = 1;
			savingMoves(scores, numb, j, -1 + numb, 2);
		}
		else
		{
			for (int i = -1 + numb - 1; i >= 0; i--)
				if (scores->positions[i] > 0 && theFurthestPawnInCourt(scores) == i)
				{
					scores->positions[i]--;
					scores->onHome[1]++;
					*AtLeastOne = 1;
					savingMoves(scores, numb, j, i, 2);
					break;
				}
		}
	}
}

void movingPawnsToHomeModule(unsigned int numb, struct gameState* scores,int *j)
{
	int AtLeastOne = 0;
	if (scores->whoseRound == 1)
	{
		movingPawnsToHomeP1(&AtLeastOne, numb, scores,j);
	}
	else if (scores->whoseRound == 2)
	{
		movingPawnsToHomeP2(&AtLeastOne, numb, scores,j);
	}
	if (AtLeastOne)
	{
		infGame2(10, 47);
		clrInfoInGameT();
	}
}

void movingPawnsOnBoard(int sign,unsigned int column1, unsigned int numb,struct gameState* scores,int *i)
{
	if (scores->whoseRound == 1)sign = -1;
	else if (scores->whoseRound == 2)sign = 1;
	if (ifFBar(scores))
	{
		movingPawnsFromBarModule(sign, numb, scores,i);
	}
	else if (ifTHome(scores))
	{
		movingPawnsToHomeModule(numb, scores,i);
	}
	else
	{
		scores->positions[column1 - 49] -= sign;
		beatingModule(sign, column1, numb, scores,i);
		scores->positions[column1 + numb * (-sign) - 49] += sign;
	}
}

void checkingGettingColumnText(int mode)
{
	switch (mode)
	{
	case 1:
		clrTF(19, 20, 20);
		cputs("There are no pawns of yours!");
		Sleep(1500);
		clrTF(19, 20, 19);
		break;
	case 2:
		clrTF(19, 20, 20);
		cputs("You cannot do it!");
		Sleep(1500);
		clrTF(19, 20, 19);
		break;
	case 3:
		clrTF(19, 20, 19);
		cputs("You must capture");
		gotoxy(2, 20);
		cputs("the closest pawn!");
		Sleep(1500);
		clrTF(19, 20, 19);
		break;
	default:
		break;
	}
}
//checking all cases for one cube move
void ifByOne(unsigned int numb, struct gameState* scores, int* sign, unsigned int* column) //one cubes checking
{
	unsigned int whichColumnShouldBe = 0;
	while (isThereProperPawns(*column, scores) == 0 || isThereProperPawns(*column, scores) == -1)
	{
		checkingGettingColumnText(1);
		gettingColumn(column, 20);
	}
	while (cannotBeMovedModule(scores, numb, sign, *column))
	{
		checkingGettingColumnText(2);
		gettingColumn(column, 20);
	}
	while (checkingIfPossibleBeat(scores, *column, numb, &whichColumnShouldBe))
	{
		if (*column == '1' + whichColumnShouldBe)break;
		checkingGettingColumnText(3);
		gettingColumn(column, 20);
	}
}
//same but for two cubes move
void ifByTwo(int mode,unsigned int numb,unsigned int numb2, struct gameState* scores,int *sign,unsigned int *column) //two cubes checking
{
	while (mode && cannotBeMovedModule(scores, numb - numb2, sign, *column) && cannotBeMovedModule(scores, numb2, sign, *column))
	{
		checkingGettingColumnText(2);
		gettingColumn(column, 20);
	}
}

void inputCheck(struct gameState* scores, unsigned int numb, int mode, unsigned int numb2,int *sign,unsigned int *column1)
{
	ifByOne(numb, scores, sign, column1);
	ifByTwo(mode, numb, numb2, scores, sign, column1);
	Sleep(500);
}

void PawnsInMoveM(int* gate2,int *sign,unsigned int *column,unsigned int numb, struct gameState* scores,int *i)
{
	movingPawnsOnBoard(*sign, *column, numb, scores,i);
	clrTF(18, 20, 18);
	clrTF(19, 20, 18);
	*gate2 = 0;
}

void MoveModule(struct gameState* scores,unsigned int numb,int mode,unsigned int numb2,int *gate,int *gate2, int* gate3,int *j)
{
	unsigned int column1 = 0;
	int sign = 0, i = 0;
	if (ifFBar(scores) || ifTHome(scores))
	{
		PawnsInMoveM(gate2, &sign, &column1, numb, scores,j);
	}
	else
	{
		clrTF(18, 19, 18);
		cputs("FROM");
		gotoxy(2, 19);
		gettingColumn(&column1, 20);
		if ((column1 != 'k' && column1 != 'w') || *gate2 == 1)
		{
			if (column1 != 'k')
			{
				inputCheck(scores, numb, mode, numb2, &sign, &column1);
				PawnsInMoveM(gate2, &sign, &column1, numb, scores,j);
			}
			else *gate = 1;
		}
		else if (column1 == 'k')
		{
			*gate = 1;
		}
		else
		{
			*gate2 = 1;
		}
	}
	if (*gate2)*gate3 = 1;
}

void afterMove(struct gameState* scores, int* gate2, int* gate3)
{

	Sleep(500);
	drawingBoard(scores);
	puttingPawnsOnBoard(scores->positions);
	*gate2 = 1;
	*gate3 = 0;
}
//one cube move module
void mode1(unsigned int* mode, struct gameState* scores, unsigned int numb1, unsigned int numb2, int* gate, int* gate2, int* gate3,int *swaps,int *i)
{
	MoveModule(scores, numb1, 0, numb2, gate, gate2, gate3,i);
	if (*gate == 1 || *gate2 == 1)
	{
		gotoxy(25, 20);
		cputs(" ");
		if (*gate == 1 && *gate3 == 1)
		{
			infGame(6, 47);
			*gate = 0;
			*swaps = 1;
		}
		else if (*gate == 1)
		{
			infGame(7, 47);
			*gate = 0;
			MoveModule(scores, numb2, 0, numb2, gate, gate2, gate3,i);
		}
		if (*gate2 == 1)
		{
			infGame2(9, 47);
			*swaps = 1;
		}
	}
	else
	{
		afterMove(scores, gate2, gate3);
		MoveModule(scores, numb2, 0, numb2, gate, gate2, gate3,i);
	}
}
//diffrent actions if one cube or two cubes move
void whichM(unsigned int *mode, struct gameState* scores, unsigned int numb1, unsigned int numb2,int *gate,int *gate2,int *gate3,int *i) //which mode to move
{
	int swaps = 0;
	if (!(*gate == 1 || *mode == 'k' ))
	{
		if (*mode == '1')
		{
			mode1(mode, scores, numb1, numb2, gate, gate2, gate3,&swaps,i);
		}
		else if (*mode == '2' && swaps!=1)MoveModule(scores, numb1 + numb2, 1, numb2, gate,gate2,gate3,i);
	}
	else
	{
		infGame(6, 47);
	}
}
//alternative action
void mainAlt(const int pos, struct gameState* scores)
{
	infGame(4, pos);
	clrInfoInGameT();
	drawingBoard(scores);
	puttingPawnsOnBoard(scores->positions);
}

void nextRoundMod(int gate, struct gameState* scores, const int pos)
{
	if (gate)
	{
		infGame(6, pos);
		if (scores->whoseRound == 1)scores->whoseRound = 2;
		else scores->whoseRound = 1;
	}
	else
	{
		if (scores->whoseRound == 1)scores->whoseRound = 2;
		else scores->whoseRound = 1;
	}
}

int ifCanMoveToHomeP1(int* AtLeastOne, unsigned int numb, struct gameState* scores)
{
	if (scores->positions[24 - numb] < 0)
		return 1;
	else
		for (int i = 24 - numb + 1; i <= 23; i++)
			if (scores->positions[i] < 0 && theFurthestPawnInCourt(scores) == i)
				return 1;
	return 0;
}

int ifCanMoveToHomeP2(int* AtLeastOne, unsigned int numb, struct gameState* scores)
{
	if (scores->positions[-1 + numb] > 0)
		return 1;
	else
		for (int i = -1 + numb - 1; i <<= 23 >= 0; i--)
			if (scores->positions[i] > 0 && theFurthestPawnInCourt(scores) == i)
				return 1;
	return 0;
}
//checking the best move option
int whenMore(struct gameState* scores, unsigned int numb1, unsigned int numb2)
{

	int AtLeastOne = 0, sum = 0;
	if (scores->whoseRound == 1)
	{
		if (ifCanMoveToHomeP1(WHENMORENUMB1) + ifCanMoveToHomeP1(WHENMORENUMB2) >= ifCanMoveToHomeP1(WHENMORENUMB12))return '1';
		else 
			return '2';
	}
	else if (scores->whoseRound == 2)
	{
		if (ifCanMoveToHomeP2(WHENMORENUMB1) + ifCanMoveToHomeP2(WHENMORENUMB2) >= ifCanMoveToHomeP2(WHENMORENUMB12))return '1';
		else 
			return '2';
	}
	
}
//dublet and next round
void alterAct(int gate, int *gate2,int *gate3,unsigned int *mode,unsigned int numb1, unsigned int numb2,const int pos, struct gameState* scores,int *i) //aleternative actions, dublet move
{
	if (!gate)
	{
		if (numb1 == numb2)
		{	
			mainAlt(pos, scores);
			if(ifTHome(scores)==1)
			{
				*mode = whenMore(scores,numb1,numb2);
				whichM(mode, scores, numb1, numb2, &gate, gate2, gate3,i);
			}
			else
			{
				selectMoveMod(mode, numb1, numb2);
				whichM(mode, scores, numb1, numb2, &gate, gate2, gate3,i);
			}
		}
		if (scores->whoseRound == 1)scores->whoseRound = 2;
		else scores->whoseRound = 1;
	}
	else { nextRoundMod(gate, scores, pos); }
}

int M2MoveH(unsigned int homeForCheck, struct gameState* scores)
{
	if (scores->whoseRound == 1)
	{
		if (homeForCheck == scores->onHome[0])return 1;
	}
	else if (scores->whoseRound == 2)
	{
		if (homeForCheck == scores->onHome[1])return 1;
	}
	return 0;
}

void firstStep(struct gameState* scores,unsigned int *numb1, unsigned int *numb2)
{
	clrscr();
	gameView(&scores);
	whoseRound(scores);
	cubsThrow(numb1, numb2);
}

void hCkInit(unsigned int *homeForCheck, struct gameState* scores)
{
	if (scores->whoseRound == 1)*homeForCheck = scores->onHome[0];
	else *homeForCheck = scores->onHome[1];
}

void swapMod(unsigned int *numb1, unsigned int *numb2,int *gate2)
{
	unsigned int swaps = 0;
	swaps = *numb1;
	*numb1 = *numb2;
	*numb2 = swaps;
	drawingCube(0, *numb1);
	drawingCube(SECONDCUBEPOS, *numb2);
	*gate2 = 0;
}

void swapModule(int* gate, int* gate2, int* gate3, unsigned int *numb1, unsigned int *numb2, unsigned int* mode, struct gameState* scores,int *i)
{
	if (*gate2 == 1 && *gate3 == 1)
	{
		swapMod(numb1, numb2, gate2);
		*mode = '1';
		whichM(mode, scores, *numb1, *numb2, gate, gate2, gate3,i);
	}
}

void M2MoveHModule(int* gate, int* gate2, int* gate3, unsigned int* numb1, unsigned int* numb2, unsigned int* mode, struct gameState* scores, unsigned int* hCk,int *i)
{
	if (M2MoveH(*hCk, scores))
	{
		*mode = '2';
		whichM(mode, scores, *numb1, *numb2, gate, gate2, gate3,i);
	}
}

void selectMakeMove(int zn,struct gameState* scores,int *i)
{
	int gt1 = 0, gate2 = 0, gate3=0;//gt1 -> gateForSkip, gate2 -> gateForSwap, gate3 -> gateForNotSwapAfter
	unsigned int numb1 = 0, numb2 = 0, mod = 0, hCk = 100; // hCk -> checking posibility of not moving by one cube to move two cubes
	const int pos = 47;
	if (zn == 'm')
	{
		firstStep(scores, &numb1, &numb2);
		if (ifFBar(scores)||ifTHome(scores))
		{
			mod = '1';
			if(ifTHome(scores))hCkInit(&hCk, scores);
			whichM(&mod, scores, numb1, numb2, &gt1, &gate2, &gate3,i);
		}
		else
		{
			selectMoveMod(&mod, numb1, numb2);
			whichM(&mod, scores, numb1, numb2, &gt1, &gate2, &gate3,i);
		}
		swapModule(&gt1, &gate2, &gate3, &numb1, &numb2, &mod, scores,i);
		M2MoveHModule(&gt1, &gate2, &gate3, &numb1, &numb2, &mod, scores, &hCk,i);
		alterAct(gt1, &gate2, &gate3, &mod, numb1, numb2, pos, scores,i);
	}
}

void dialogForWinningGameText(const int pos,unsigned int whoWon,struct gameState *scores)
{
	gotoxy(pos + 8, 12);
	printf("PLAYER %d HAVE WON THE GAME!",whoWon);
	gotoxy(pos + 7, 13);
	cputs("Do you want to play next one?");
	gotoxy(pos + 10, 15);
	cputs("y(es)");
	gotoxy(pos + 29, 15);
	cputs("n(o)");
}

void dialogForWinningGameBorder(const int pos)
{
	gotoxy(pos, 10);
	for (int i = 0; i < 43; i++)
		printf("_");
	for (int j = 0; j < 6; j++)
	{
		gotoxy(pos - 1, 11 + j);
		printf("|");
		for (int i = 0; i < 43; i++)
			printf(" ");
		printf("|");
	}
	gotoxy(pos, 16);
	for (int i = 0; i < 43; i++)
		printf("_");
}

void dialogWindowAfterWinning(struct gameState* scores)
{
	int whoWon = 0;
	if (scores->onHome[0] == 15)whoWon = 1;
	else whoWon = 2;
	const int pos = 42;
	dialogForWinningGameBorder(pos);
	dialogForWinningGameText(pos, whoWon, scores);
}

void howManyPointsFromWin(struct gameState* scores)
{
	if (scores->onHome[0] == 15)
	{
		if(scores->onHome[1]==0)scores->firstPlayerWon+=2;
		else if(scores->onBar[1]>0)scores->firstPlayerWon += 3;
		else scores->firstPlayerWon++;
	}
	else 
	{
		if (scores->onHome[0] == 0)scores->firstPlayerWon += 2;
		else if (scores->onBar[0] > 0)scores->firstPlayerWon += 3;
		else scores->firstPlayerWon++;
	}
}

void winTheGame(struct gameState *scores,const int reset[24],int *zn,int *i)
{
	if (scores->onHome[0] == 15 || scores->onHome[1] == 15)
	{
		*i = 0;
		Sleep(2000);
		clrscr();
		dialogWindowAfterWinning(scores);
		howManyPointsFromWin(scores);
		*zn = getch();
		if (*zn == 'y')
		{
			resetGameStateForContinue(scores, reset);
			*zn = 'p';
		}
		else if (*zn == 'n')
		{
			resetGameStateForContinue(scores, reset);
			*zn = 27;
		}
	}
}

void selectPlay(int zn,struct gameState* scores, const int reset[MAXNUMBEROFELEMENTS],int *i)
{
	if (zn == 'p')
	{
		do
		{
			clrscr();
			gameView(&scores);
			whoseRound(scores);
			zn = getch();
			selectSave(zn, scores);
			selectLoad(&zn, scores);
			selectNew(&zn, scores, reset,i);
			selectMakeMove(zn, scores,i);
			winTheGame(scores,reset,&zn,i);
			if (kbhit())
			{
				zn = getch();
			}
		} while (zn != 27);
	}
}

int main()
{
#ifndef __cplusplus
	Conio2_Init();
#endif
	struct gameState scores;
	SetConsoleOutputCP(CP_UTF8);
	Conio2_Init();
	settitle("Krzysztof, Taraszkiewicz, 197796");
	srand(time(NULL));
	const int reset[MAXNUMBEROFELEMENTS] = {-2,0,0,0,0,5,0,3,0,0,0,-5,5,0,0,0,-3,0,-5,0,0,0,0,2};
	int zn = 0, attr = 7, back = 0, whichMoves = 1;
	textcolor(2);
	do
	{
		_setcursortype(_NOCURSOR);
		firstView(&scores);
		zn = getch();
		selectInfo(zn);
		selectGraphic(zn,&attr, &back);
		selectLoad(&zn, &scores);
		selectNew(&zn, &scores, reset,&whichMoves);
		selectPlay(zn,&scores,reset,&whichMoves);
		gotoxy(1, 1);
		clrscr();
	} while (zn != 'q');
}
