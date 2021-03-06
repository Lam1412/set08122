#include <stdio.h>
#include <stdlib.h>

//Alogrithm and Data Structures Coursework - Connect 4 Project - Liam Harper - 40437497

//Classes for the game
void game();
void insert();
void gameBoard();
void saveandexit();
int winCheck();

//Global varibles used in mutliple classes
int save;
int col;
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

//Arrays that are used for the positions of the game board
char pos [43] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};;
char *colour[43] = { "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m"};;

int main()
{
	/* Clears the console and displays the main menu for the 
	game that gives the users options */
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
		//Takes the users choice and decides what to do with it
		int menuChoice = 0;
		scanf("%d", &menuChoice);
		
		if(menuChoice == 1)
		{
			/* If there is anything in the arrays they are replaced 
			with starting values for a new game */
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
			save = 0;
			
			//Clears the console and displays the save slot menu
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
			printf("#       9 = Return                        #\n");
			printf("#                                         #\n");
			printf("###########################################\n");
			
			
			//Takes an input and opens the corresponding .txt file
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
			
			else if(save == 9)
			{
				main();
			}
			
			/* If an invalid character is entered this clears it 
			and allows the user to input again */
			else
			{
				while(getchar() != '\n');
				printf("\nError! Please enter a number between 1 and 5.\nPress any key to continue...");
				getch();
				main();
			}
			
			/*If the save file doesnt exist or can't be found this error is 
			displayed and the user must pick a menu option again*/
			if(saveGame == NULL)
			{
				printf("Error! Could not find file\nPress any key to return to menu...");
				getch();
				main();
			}
			
			//Reads in the contents of the save file and correctly colours them
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
		
		//Simply closes the game and returns user to console
		else if(menuChoice == 3)
		{
			system("cls");
			exit(0);
		}
		
		/* If an invalid character is entered this clears it 
		and allows the user to input again */
		else
		{
			while(getchar() != '\n');
			printf("\nError! Please enter a number between %d and %d.\nPress any key to continue...", 1, 3);
			getch();
			main();
		}
	}
	//Repeats until a valid menu option is selected
	while(menuChoice != 1 || menuChoice != 2 || menuChoice != 3);
}

void game()
{
	//Game logic that repeats until a win, draw or exit is detected
	do
	{
		//calls classes in order to play game
		gameBoard();
		insert();
		state = winCheck();
	}
	while(state == 1);
	
	gameBoard();
	
	/* selects the correct player to display a win for
	unless the game is a draw*/
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
	
	//If the game was a saved game once the game is done the save file is cleared
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
	else
	{
		printf("Press any key to return to menu...");
		getch();
		main();
	}
	
	//loop that clears the game board and save file
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
	/*code that inserts the players choices into 
	the array which shows on the gameboard*/
	col = 0;
	char piece;
	
	//decides the piece to be put on the game board
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
	
	/* takes the users input and either saves the game, 
	places a piece on the board or displays an error */
	printf("Player %d pick a column - ", player);
	scanf("%d", &col);

	if(col == 9)
	{
		saveandexit();
	}

	else if(col == 1 || col == 2 || col == 3 || col == 4 || col == 5 || col == 6 || col == 7)
	{
		/* loops through the column that the user selected to put 
		the piece in the lowest spot on the game board */
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
			
			//if the column is full displays this
			if(pos[col] != ' ')
			{
				printf("\nColumn %d is full! Press any key and pick again...", col);
				getch();
				break;
			}
		}
	}
	
	/* If an invalid character is entered this clears it 
	and allows the user to input again */
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
	
	//shows the user the save slots
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
	printf("#       9 = Return to menu                #\n");
	printf("#                                         #\n");
	printf("###########################################\n");
	
	//Takes an input and opens the corresponding .txt file
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
	
	else if(save == 9)
	{
		game();
	}
	
	/* If an invalid character is entered this clears it 
	and allows the user to input again */
	else
	{
		while(getchar() != '\n');
		printf("\nError! Please enter a number between 1 and 5.\nPress any key to continue...");
		getch();
		game();
	}
	
	//prints the contents of the array to a .txt file
	for(i = 1; i <= sizeof(pos); i++)
	{
		fprintf(saveGame, "%c", pos[i]);
	}
	
	fclose(saveGame);
	main();
}

void gameBoard()
{
	/* clears the console and displays the connect 4 game board that 
	orders the contents of the array*/
	system("cls");
	printf("\n");
	printf("                 C0NNECT 4\n\n");
	printf("        Player 1 = \033[31mX\033[0m & Player 2 = \033[34mO\033[0m\n\n");
	printf("     9 = saves game and returns to menu\n");
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
	
	//the loop to check all possible horizontal wins
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
	
	//the loop to check all possible vertical wins
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
	
	//the loop to check all possible diagonal wins
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

	//checks to see if the game board is full
	if(pos[1] != ' ' && pos[2] != ' ' && pos[3] != ' ' && pos[4] != ' '&& pos[5] != ' ' && pos[6] != ' ' && pos[7] != ' ')
	{
		return 3;
	}
	
	else
	{
		return 1;
	}
}