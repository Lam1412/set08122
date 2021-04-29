#include <stdio.h>
#include <stdlib.h>

/* 
Alogrithm and Data Structures Coursework - Connect 4 Project - Liam Harper - 40437497
cd C:\Users\lharp\Documents\set08122
*/ 

void game();
void insert();
void gameBoard();
void saveandexit();
int winCheck();

int maxcol = 7;
int maxrow = 6;
int player = 1;
int state = 1;
int menuChoice;
int i;
FILE *saveGame;
char normal[] = "\033[0m";
char red[] = "\033[31m";
char blue[] = "\033[34m";

char pos [43] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};;
char *colour[43] = { "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m"};;

int main()
{
	system("cls");
	printf("\n                 CONNECT 4\n\n");
	printf("        Player 1 = \033[31mX\033[0m & Player 2 = \033[34mO\033[0m\n\n");
	printf("###########################################\n");
	printf("#                                         #\n");
	printf("#   Please select one of the following    #\n");
	printf("#         following options below         #\n");
	printf("#                                         #\n");
	printf("#       1 = New game                      #\n");
	printf("#       2 = Resume previous game          #\n");
	printf("#       3 = Exit                          #\n");
	printf("#                                         #\n");
	printf("###########################################\n");
	
	do
	{
		int menuChoice = 0;
		scanf("%d", &menuChoice);
		
		if(menuChoice == 1)
		{
			player = 1;
			for(i = 0; i <= sizeof(pos); i++)
			{
				pos[i] = ' ';
				colour[i] = "\033[0m";
			}
			game();
		}
		
		else if(menuChoice == 2)
		{
			int save;
			
			system("cls");
			printf("\n                 CONNECT 4\n\n");
			printf("###########################################\n");
			printf("#                                         #\n");
			printf("#   Please select one of the following    #\n");
			printf("#         following options below         #\n");
			printf("#                                         #\n");
			printf("#       1 = Save Slot 1                   #\n");
			printf("#       2 = Save Slot 2                   #\n");
			printf("#       3 = Save Slot 3                   #\n");
			printf("#       4 = Save Slot 4                   #\n");
			printf("#       5 = Save Slot 5                   #\n");
			printf("#       0 = Return                        #\n");
			printf("#                                         #\n");
			printf("###########################################\n");
			
			scanf("%d", &save);
			
			if(save == 1)
			{
				saveGame = fopen("SavedGame1.txt","r");
			}
			
			else if(save == 2)
			{
				saveGame = fopen("SavedGame2.txt","r");
			}
			
			else if(save == 3)
			{
				saveGame = fopen("SavedGame3.txt","r");
			}
			
			else if(save == 4)
			{
				saveGame = fopen("SavedGame4.txt","r");
			}
			
			else if(save == 5)
			{
				saveGame = fopen("SavedGame5.txt","r");
			}
			
			else if(save == 0)
			{
				main();
			}
			
			else
			{
				while(getchar() != '\n');
				printf("\nError! Please enter a number between 1 and 5.\nPress any key to continue...");
				getch();
				main();
			}
			
			if(saveGame == NULL)
			{
				fclose(saveGame);
				printf("Error! Could not find file\nPress any key to return to menu...");
				getch();
				main();
			}
			
			else
			{
				char ch;
				i = 1;
				do 
				{
					ch = fgetc(saveGame);
					if(feof(saveGame))
					{
						break;
					}
					pos[i] = ch;
					
					if(pos[i] == 'X')
					{
						colour[i] = red;
					}
					else if(pos[i] == 'O')
					{
						colour[i] = blue;
					}
					else
					{
						colour[i] = normal;
					}
					i++;
				}
				while(1);
				fclose(saveGame);
				game();
			}
		}
		
		else if(menuChoice == 3)
		{
			system("cls");
			exit(0);
		}
		
		else
		{
			while(getchar() != '\n');
			printf("\nError! Please enter a number between %d and %d.\nPress any key to continue...", 1, 3);
			getch();
		}
	}
	while(menuChoice != 1 || menuChoice != 2 || menuChoice != 3);
}

void game()
{
	do
	{
		gameBoard();
		insert();
		state = winCheck();
	}
	while(state == 1);
	
	gameBoard();
	
	if(player == 1)
	{
		player ++;
	}
	else
	{
		player--;
	}
	
	if(state == 2)
	{
		printf("\nPlayer %d has won the game!\n", player);
	}
	else
	{
		printf("\nGame board full! Game tied.\n");
	}
	
	saveGame = fopen("SavedGame.txt","w");
	for(i = 0; i <= sizeof(pos); i++)
	{
		pos[i] = ' ';
		colour[i] = "\033[0m";
		fprintf(saveGame, "%c", pos[i]);
	}
	fclose(saveGame);
	
	printf("Press any key to return to menu...");
	getch();
	main();
}

void insert()
{
	int col = 0;
	char piece;
	
	if(player == 1 || player == 3)
	{
		player = 1;
		piece = 'X';
	}
	
	else
	{
		piece = 'O';
	}
	
	int i = 1;
	
	printf("Player %d pick a column - ", player);
	scanf("%d", &col);
	
	if(col == 0)
	{
		saveandexit();
	}
	
	else if(col > 0 || col < maxcol + 1)
	{
		for(i = maxrow - 1; i >= 0; i--)
		{
			if(pos[maxcol * i + col] == ' ')
			{
				if(player == 1)
				{
					colour[maxcol * i + col] = red;
				}
				else
				{
					colour[maxcol * i + col] = blue;
				}
				pos[maxcol * i + col] = piece;
				player++;
				break;
			}
			
			if(pos[col] != ' ')
			{
				printf("\nColumn %d is full! Press any key and pick again...", col);
				getch();
				break;
			}
		}
	}
	
	else
	{
		while(getchar() != '\n');
		printf("\nError! Please enter a number between %d and %d.\nPress any key to continue...", 1, maxcol);
		getch();
		game();
	}
}

void saveandexit()
{
	int save;
	
	system("cls");
	printf("\n                 CONNECT 4\n\n");
	printf("###########################################\n");
	printf("#                                         #\n");
	printf("#   Please select one of the following    #\n");
	printf("#         following options below         #\n");
	printf("#                                         #\n");
	printf("#       1 = Save Slot 1                   #\n");
	printf("#       2 = Save Slot 2                   #\n");
	printf("#       3 = Save Slot 3                   #\n");
	printf("#       4 = Save Slot 4                   #\n");
	printf("#       5 = Save Slot 5                   #\n");
	printf("#       0 = Return to menu                #\n");
	printf("#                                         #\n");
	printf("###########################################\n");
	
	scanf("%d", &save);
	
	if(save == 1)
	{
		saveGame = fopen("SavedGame1.txt","w");
	}
	
	else if(save == 2)
	{
		saveGame = fopen("SavedGame2.txt","w");
	}
	
	else if(save == 3)
	{
		saveGame = fopen("SavedGame3.txt","w");
	}
	
	else if(save == 4)
	{
		saveGame = fopen("SavedGame4.txt","w");
	}
	
	else if(save == 5)
	{
		saveGame = fopen("SavedGame5.txt","w");
	}
	
	else if(save == 0)
	{
		game();
	}
	
	else
	{
		while(getchar() != '\n');
		printf("\nError! Please enter a number between 1 and 5.\nPress any key to continue...");
		getch();
		game();
	}
	
	for(i = 1; i <= sizeof(pos); i++)
	{
		fprintf(saveGame, "%c", pos[i]);
	}
	
	fclose(saveGame);
	main();
}

void gameBoard()
{
	system("cls");
	printf("\n");
	printf("                 C0NNECT 4\n\n");
	printf("        Player 1 = \033[31mX\033[0m & Player 2 = \033[34mO\033[0m\n\n");
	printf(" 0 (zero) = saves game and returns to menu\n");
	printf("###########################################\n");
	printf("#     |     |     |     |     |     |     #\n");
	printf("#  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  #\n", colour[1], pos[1], normal, colour[2], pos[2], normal, colour[3], pos[3], normal, colour[4], pos[4], normal, colour[5], pos[5], normal, colour[6], pos[6], normal, colour[7], pos[7], normal);
	printf("#_____|_____|_____|_____|_____|_____|_____#\n");
	printf("#     |     |     |     |     |     |     #\n");
	printf("#  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  #\n", colour[8], pos[8], normal, colour[9], pos[9], normal, colour[10], pos[10], normal, colour[11], pos[11], normal, colour[12], pos[12], normal, colour[13], pos[13], normal, colour[14], pos[14], normal);
	printf("#_____|_____|_____|_____|_____|_____|_____#\n");
	printf("#     |     |     |     |     |     |     #\n");
	printf("#  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  #\n", colour[15], pos[15], normal, colour[16], pos[16], normal, colour[17], pos[17], normal, colour[18], pos[18], normal, colour[19], pos[19], normal, colour[20], pos[20], normal, colour[21], pos[21], normal);
	printf("#_____|_____|_____|_____|_____|_____|_____#\n");
	printf("#     |     |     |     |     |     |     #\n");
	printf("#  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  #\n", colour[22], pos[22], normal, colour[23], pos[23], normal, colour[24], pos[24], normal, colour[25], pos[25], normal, colour[26], pos[26], normal, colour[27], pos[27], normal, colour[28], pos[28], normal);
	printf("#_____|_____|_____|_____|_____|_____|_____#\n");
	printf("#     |     |     |     |     |     |     #\n");
	printf("#  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  #\n", colour[29], pos[29], normal, colour[30], pos[30], normal, colour[31], pos[31], normal, colour[32], pos[32], normal, colour[33], pos[33], normal, colour[34], pos[34], normal, colour[35], pos[35], normal);
	printf("#_____|_____|_____|_____|_____|_____|_____#\n");
	printf("#     |     |     |     |     |     |     #\n");
	printf("#  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  |  %s%c%s  #\n", colour[36], pos[36], normal, colour[37], pos[37], normal, colour[38], pos[38], normal, colour[39], pos[39], normal, colour[40], pos[40], normal, colour[41], pos[41], normal, colour[42], pos[42], normal);
	printf("#     |     |     |     |     |     |     #\n");
	printf("###########################################\n");
	printf("   1     2     3     4     5     6     7 \n");
}

int winCheck()
{
	int i;
	int j;
	int win;
	
	//horizontal
	for(i = 0; i < maxrow; i++)
	{
		for(j = 1; j < maxcol - 2; j++)
		{
			win = maxcol * i + j;
			if(pos[win] == pos[win + 1] && pos[win + 1] == pos[win + 2] && pos[win + 2] == pos[win + 3] && pos[win] != ' ')
			{
				return 2;
			}
		}
	}
	
	//vertical
	for(i = 1; i < maxrow - 2; i++)
	{
		for(j = 0; j < maxcol; j++)
		{
			win = maxcol * i + j;
			if(pos[win] == pos[win + maxcol] && pos[win + maxcol] == pos[win + maxcol * 2] && pos[win + maxcol * 2] == pos[win + maxcol * 3] && pos[win] != ' ')
			{
				return 2;
			}
		}
	}
	
	//diagonal
	for(i = 0; i < maxrow; i++)
	{
		for(j = 1; j < maxcol - 2; j++)
		{
			win = maxcol * i + j;
			if(i < 3 && pos[win] == pos[win + 8] && pos[win + 8] == pos[win + 16] && pos[win + 16] == pos[win + 24] && pos[win] != ' ' || i > 3 && pos[win] == pos[win - 6] && pos[win - 6] == pos[win - 12] && pos[win -12] == pos[win -18] && pos[win] != ' ')
			{
				return 2;
			}
		}
	}

	//full board
	if(pos[1] != ' ' && pos[2] != ' ' && pos[3] != ' ' && pos[4] != ' '&& pos[5] != ' ' && pos[6] != ' ' && pos[7] != ' ')
	{
		return 3;
	}
	
	else
	{
		return 1;
	}
}