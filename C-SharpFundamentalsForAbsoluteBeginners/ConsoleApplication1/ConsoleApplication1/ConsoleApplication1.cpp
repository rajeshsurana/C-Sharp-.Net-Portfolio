// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include<graphics.h>
#include<dos.h>
#include<time.h>
#define SIZE 8  /* Board size - must be even */
int a, b, X, Y, s, z;
/* Function prototypes */
FILE *f1;
initmouse();
void button(int, char*);
void showmouse();
void hidemouse();
void restrictmouse();
void game();
void display(char board[][SIZE]);
int valid_moves(char board[][SIZE], int moves[][SIZE], char player);
void make_move(char board[][SIZE], int row, int col, char player);
void computer_move(char board[][SIZE], int moves[][SIZE], char player);
int best_move(char board[][SIZE], int moves[][SIZE], char player);
int get_score(char board[][SIZE], char player);
int getscore(char board[][SIZE]);
union REGS i, o;
void front();
void brick();
void loading();
void highscore()
{
	int sc;
	char scc[10];
	int n = 0, d, f, k;
	X = getmaxx() / 2;
	Y = getmaxy() / 2;
	cleardevice();
	//	hidemouse();
	f1 = fopen("high.txt", "r");
	if (f1 == NULL)
	{
	at:
		setcolor(9);
		settextstyle(8, 0, 4);
		outtextxy(35, Y - 35, "\nHIGH SCORE IS NOT AVAILABLE.");
		f1 = fopen("high.txt", "w+");
		fclose(f1);
		delay(1500);
		return;
	}
	fscanf(f1, "%d", &sc);
	if (sc>64)
		goto at;
	sprintf(scc, "%d", sc);
	setcolor(14);
	setfillstyle(SOLID_FILL, 2);
	bar3d(X - 120, 150, X + 120, 150 + 30, 7, 1);
	floodfill(X - 110, 150 + 10, 14);
	setcolor(4);
	settextstyle(4, 0, 3);
	outtextxy(X - 10, 150, scc);
	k = 2 * Y - 50;
	setcolor(14);
	setfillstyle(SOLID_FILL, 10);
	bar3d(X + 140, k, X + 240, k + 20, 7, 1);
	floodfill(X + 150, k + 10, 14);
	setcolor(4);
	settextstyle(8, 0, 1);
	outtextxy(X + 160, k - 5, "BACK");
	initmouse();
	showmouse();
	while (!kbhit())
	{
		n = getmouse(&d, &f);
		if (n != 0)
		{
			if ((d>X + 140 && d<X + 240) && (f>k&&f<k + 20))
			{

				break;
			}
		}
	}
	fclose(f1);
}
void maxscore(int currscore)
{
	int sc;
	f1 = fopen("high.txt", "r");
	fscanf(f1, "%d", &sc);

	//if(feof(f1))
	//	fprintf(f1,"%d",currscore);
	if (sc<currscore)
	{
		fclose(f1);
		f1 = fopen("high.txt", "w");
		fprintf(f1, "%d\n", currscore);
	}
	fclose(f1);


}
void help()
{
	int n = 0, d, f, k, i;
	X = getmaxx() / 2;
	Y = getmaxy() / 2;
	cleardevice();
	hidemouse();
	setbkcolor(0);
	setcolor(14);
	settextstyle(3, 0, 4);
	outtextxy(X - 30, 2, "Help");
	sound(10000);
	for (i = 0; i<40; i++)
	{
		line(X - i, 40, X, 40);
		line(X, 40, X + i, 40);
		delay(15);
	}
	nosound();
	settextstyle(1, 0, 2);
	setcolor(12);
	outtextxy(10, 50, "\nLagno obejective:");
	setcolor(2);
	settextstyle(6, 0, 2);
	outtextxy(50, 80, "The object of Lagno is make as many disc(square) of yours as you can.");
	settextstyle(1, 0, 2);
	setcolor(12);
	outtextxy(10, 130, "To play Lagno");
	settextstyle(6, 0, 2);
	setcolor(2);
	outtextxy(50, 160, "1:Game starts with four discs-two for each player-already ");
	outtextxy(50, 180, "  criss-crossed in the center..");
	outtextxy(50, 210, "2:Black generaly going first.");
	outtextxy(50, 240, "3:Each time, you have to sandwich one or more lines of your ");
	outtextxy(50, 260, "  opponent's discs between your own discs.");
	outtextxy(50, 290, "4:Then the sandwich discs change color and become yours..");
	outtextxy(50, 320, "5:The game continues until neither player can legal ");
	outtextxy(50, 340, "  sandwich any more line(s) of discs");
	initmouse();
	showmouse();
	k = 2 * Y - 50;
	setcolor(15);
	setfillstyle(SOLID_FILL, 6);
	bar3d(X + 140, k, X + 240, k + 20, 7, 1);
	floodfill(X + 150, k + 10, 15);
	setcolor(1);
	settextstyle(8, 0, 1);
	outtextxy(X + 160, k - 5, "BACK");
	while (!kbhit())
	{
		n = getmouse(&d, &f);
		if (n != 0)
		{
			if ((d>X + 140 && d<X + 240) && (f>k&&f<k + 20))
			{

				break;
			}
		}
	}
}
int mouse()
{
	i.x.ax = 0;
	int86(0x33, &i, &o);
	return (i.x.ax);
}

void main()
{

	int gd = DETECT, gm, n, d, f, i;
	char ch;
	clrscr();
	initgraph(&gd, &gm, "c:\\tc\\bgi");
	brick();
	loading();
	X = getmaxx() / 2;
	Y = getmaxy() / 2;
	n = mouse();
	restrictmouse(0, 0, 2 * X, 2 * Y);
go:front();
	showmouse();
	while (!kbhit())
	{
		if (i>400)
			i == 0;
		outtextxy(20, i, "-----");
		n = getmouse(&d, &f);
		if (n != 0)
		{
			if ((d>X - 120 && d<X + 120) && (f>100 && f<130))
			{
				game();
				goto go;
			}
			else if ((d>X - 120 && d<X + 120) && (f>150 && f<180))
			{
				highscore();
				goto go;
			}
			else if ((d>X - 120 && d<X + 120) && (f>200 && f<230))
			{
				hidemouse();
				help();
				goto go;
			}
			else if ((d>X - 120 && d<X + 120) && (f>250 && f<280))
			{
				for (s = 0, z = 0; s<200, z<200; s += 20, z += 15)
				{
					cleardevice();
					setcolor(GREEN);
					settextstyle(4, 0, 3);
					outtextxy(140 + s, 100 + z, "GOOD BYE!!!");
					delay(150);
				}
				delay(700);
				return;
			}

		}
		i++;


	}
	getch();
	closegraph();
	return;
}
void game()
{
	char uscc[5], cscc[5];
	int sc;
	char scc[5];
	char board[SIZE][SIZE] = { 0 };  /* The board           */
	int moves[SIZE][SIZE] = { 0 };    /* Valid moves         */
	int row = 0;                      /* Board row index     */
	int col = 0;                      /* Board column index  */
	int no_of_games = 0;              /* Number of games     */
	int no_of_moves = 0;              /* Count of moves      */
	int invalid_moves = 0;            /* Invalid move count  */
	int comp_score = 0;               /* Computer score      */
	int user_score = 0;               /* Player score        */
	int y = 0;                       /* Column letter       */
	int x = 0;                        /* Row number          */
	char again = 0;                   /* Replay choice input */
	int player = 0;                   /* Player indicator    */
	initmouse();
	cleardevice();
	showmouse();

	/* Prompt for how to play - as before */

	/* The main game loop */
	do
	{
		/* On even games the player starts; */
		/* on odd games the computer starts */
		player = ++no_of_games % 2;
		no_of_moves = 4;                /* Starts with four counters */

		/* Blank all the board squares */
		for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
			board[row][col] = ' ';

		/* Place the initial four counters in the center */
		board[SIZE / 2 - 1][SIZE / 2 - 1] = board[SIZE / 2][SIZE / 2] = 'O';
		board[SIZE / 2 - 1][SIZE / 2] = board[SIZE / 2][SIZE / 2 - 1] = '@';

		/* The game play loop */
		do
		{
			hidemouse();
			initmouse();
			//     showmouse();
			clrscr();
			cleardevice();

			display(board);
			showmouse();
			printf("\n\n\n                      A    B    C    D    E    F    G    H");
			printf("\n\n                 1\n\n                 2\n\n\n                 3\n\n                 4\n\n\n                 5\n\n                 6\n\n\n                 7\n\n                 8");

			setcolor(9);
			outtextxy(X + 210, Y - 170, "Score:");
			setcolor(14);
			rectangle(X + 190, Y - 120, X + 300, Y - 100);
			setfillstyle(SOLID_FILL, 10);
			floodfill(X + 191, Y - 119, 14);
			setcolor(4);
			sc = getscore(board);
			sprintf(scc, "%d", sc);
			settextstyle(7, 0, 1);
			outtextxy(X + 240, Y - 122, scc);
			display(board);             /* Display the board  */
			if (player++ % 2)
			{ /*   It is the player's turn                    */
				if (valid_moves(board, moves, 'O'))
				{
					/* Read player moves until a valid move is entered */
					for (;;)
					{
						fflush(stdin);              /* Flush the keyboard buffer */
						do
						{
						cont: while (kbhit())
						{
								  if (getch() == '\x1B')
									  goto satak;
						}
						} while (getmouse(&x, &y) == 0);
						sound(1000);
						delay(100);
						nosound();
						//getmouse(&x,&y);
						//printf(" %d,%d ",x,y);
						x -= (getmaxx() / 2 - 160);
						y -= (getmaxy() / 2 - 160);
						x /= 40;

						y /= 40;
						if (x >= 0 && y >= 0 && x<SIZE && y<SIZE && moves[x][y])
						{
							make_move(board, x, y, 'O');
							no_of_moves++;              /* Increment move count */
							break;
						}
					}
				}
				else                              /* No valid moves */
				if (++invalid_moves<2)
				{
					fflush(stdin);
					printf("\nYou have to pass, press return");
					scanf("%c", &again);
				}
				else
					printf("\nNeither of us can go, so the game is over.\n");
			}
			else
			{ /* It is the computer's turn */
				if (valid_moves(board, moves, '@')) /* Check for valid moves */
				{
					invalid_moves = 0;               /* Reset invalid count   */
					delay(1000);
					computer_move(board, moves, '@');
					no_of_moves++;                   /* Increment move count  */
					sound(1000);
					delay(100);
					nosound();
				}
				else
				{
					if (++invalid_moves<2)
						printf("\nI have to pass, your go\n"); /* No valid move */
					else
						printf("\nNeither of us can go, so the game is over.\n");
				}
			}
		} while (no_of_moves < SIZE*SIZE && invalid_moves<2);

		/* Game is over */
		display(board);  /* Show final board */

		/* Get final scores and display them */
		comp_score = user_score = 0;
		for (row = 0; row < SIZE; row++)
		for (col = 0; col < SIZE; col++)
		{
			comp_score += board[row][col] == '@';
			user_score += board[row][col] == 'O';
		}
		setcolor(14);
		rectangle(140, 150, 500, 350);
		rectangle(150, 160, 490, 340);
		setfillstyle(SOLID_FILL, 14);
		floodfill(141, 151, 14);
		setfillstyle(SOLID_FILL, 4);
		floodfill(151, 161, 14);
		setcolor(1);
		settextstyle(3, 0, 3);
		outtextxy(175, 205, " FINAL SCORE ");
		outtextxy(175, 225, " COMPUTER:");
		sprintf(cscc, "%d", comp_score);
		outtextxy(310, 225, cscc);
		outtextxy(175, 245, " USER:");
		sprintf(uscc, "%d", user_score);
		outtextxy(250, 245, uscc);
		settextstyle(4, 0, 4);
		if (user_score>comp_score)
			outtextxy(175, 165, "   YOU WIN!!!");
		else
			outtextxy(175, 165, "   YOU LOOSE...");
		delay(5000);

		//printf("The final score is:\n");
		//printf("Computer %d\n    User %d\n\n", comp_score, user_score);

		maxscore(user_score);
		fflush(stdin);
		/* Flush the input buffer */
	satak:  hidemouse();
		clrscr();
		cleardevice();
		setcolor(14);
		rectangle(140, 150, 500, 350);
		rectangle(150, 160, 490, 340);
		setfillstyle(SOLID_FILL, 14);
		floodfill(141, 151, 14);
		setfillstyle(SOLID_FILL, 4);
		floodfill(151, 161, 14);
		initmouse();
		showmouse();

		setcolor(1);
		settextstyle(7, 0, 3);
		outtextxy(175, 205, " Do you want ");
		outtextxy(175, 225, " to play again(y/n)");
		outtextxy(175, 245, " or continue the same(c) ");
		scanf("%c", &again);         /* Get y or n             */
		clrscr();
		cleardevice();
		display(board);
		if (again == 'c')
		{
			goto cont;
		}
	} while (tolower(again) == 'y'); /* Go again on y          */

	// printf("\nGoodbye\n");
}
initmouse()
{
	i.x.ax = 0;
	int86(0x33, &i, &o);
	return (i.x.ax);
}
void showmouse()
{
	i.x.ax = 1;
	int86(0x33, &i, &o);
}
void hidemouse()
{
	i.x.ax = 2;
	int86(0x33, &i, &o);
}
int getmouse(int *d, int *f)
{
	i.x.ax = 3;
	int86(0x33, &i, &o);
	*d = o.x.cx;
	*f = o.x.dx;
	return (o.x.bx);
}
void button(int k, char *s)
{

	setcolor(2);
	setfillstyle(SOLID_FILL, 6);
	bar3d(X - 120, k, X + 120, k + 30, 7, 1);
	floodfill(X - 110, k + 10, 2);
	setcolor(4);
	settextstyle(8, 0, 2);
	outtextxy(X - 80, k + 2, s);
}
void front()
{
	int i;

	hidemouse();
	cleardevice();
	setfillstyle(SOLID_FILL, 0);
	floodfill(X, Y, 10);
	settextstyle(4, 0, 5);//(1,0,4);
	setcolor(2);
	outtextxy(X - 130, 30, "   LAGNO");
	delay(200);
	sound(10000);
	for (i = 0; i<80; i++)
	{
		line(X - i, 80, X, 80);
		line(X, 80, X + 10 + i, 80);
		delay(15);
	}
	nosound();
	button(100, "   NEW GAME");
	button(150, "  HIGH SCORE");
	button(200, "     HELP");
	button(250, "     QUIT");
	showmouse();
}

void restrictmouse(int x1, int y1, int x2, int y2)
{
	i.x.ax = 7;
	i.x.cx = x1;
	i.x.ax = x2;
	int86(0x33, &i, &o);

	i.x.ax = 8;
	i.x.cx = y1;
	i.x.ax = y2;
	int86(0x33, &i, &o);
	return;
}

/***********************************************
* Function to display the board in it's       *
* current state with row numbers and column   *
* letters to identify squares.                *
* Parameter is the board array.               *
***********************************************/
void display(char board[][SIZE])
{
	int i, j, r, c;
	a = getmaxx();
	b = getmaxy();
	setcolor(6);
	//settextstyle()
	setcolor(10);
	for (r = 0, i = a / 2 - 160; i<a / 2 + 160; r++, i += 40)
	for (c = 0, j = b / 2 - 160; j<b / 2 + 140; c++, j += 40)
	{
		switch (board[r][c])
		{
		case '@':

			setfillstyle(SOLID_FILL, 15);
			setlinestyle(0, 1, 1);
			rectangle(i, j, i + 40, j + 40);
			floodfill(i + 20, j + 20, 10);
			break;

		case 'O':

			setfillstyle(SOLID_FILL, 0);
			setlinestyle(0, 1, 1);
			rectangle(i, j, i + 40, j + 40);
			floodfill(i + 20, j + 20, 10);
			break;

		default:

			setfillstyle(SOLID_FILL, 4);
			setlinestyle(0, 1, 1);
			rectangle(i, j, i + 40, j + 40);
			floodfill(i + 20, j + 20, 10);

		}
	}
}

/***********************************************
/* Calculates which squares are valid moves    *
* for player. Valid moves are recorded in the *
* moves array - 1 indicates a valid move,     *
* 0 indicates an invalid move.                *
* First parameter is the board array          *
* Second parameter is the moves array         *
* Third parameter identifies the player       *
* to make the move.                           *
* Returns valid move count.                   *
***********************************************/
int valid_moves(char board[][SIZE], int moves[][SIZE], char player)
{
	int rowdelta = 0;     /* Row increment around a square    */
	int coldelta = 0;     /* Column increment around a square */
	int row = 0;          /* Row index                        */
	int col = 0;          /* Column index                     */
	int x = 0;            /* Row index when searching         */
	int y = 0;            /* Column index when searching      */
	int no_of_moves = 0;  /* Number of valid moves            */

	/* Set the opponent            */
	char opponent = (player == 'O') ? '@' : 'O';

	/* Initialize moves array to zero */
	for (row = 0; row < SIZE; row++)
	for (col = 0; col < SIZE; col++)
		moves[row][col] = 0;

	/* Find squares for valid moves.                           */
	/* A valid move must be on a blank square and must enclose */
	/* at least one opponent square between two player squares */
	for (row = 0; row < SIZE; row++)
	for (col = 0; col < SIZE; col++)
	{
		if (board[row][col] != ' ')   /* Is it a blank square?  */
			continue;                  /* No - so on to the next */

		/* Check all the squares around the blank square  */
		/* for the opponents counter                      */
		for (rowdelta = -1; rowdelta <= 1; rowdelta++)
		for (coldelta = -1; coldelta <= 1; coldelta++)
		{
			/* Don't check outside the array, or the current square */
			if (row + rowdelta < 0 || row + rowdelta >= SIZE ||
				col + coldelta < 0 || col + coldelta >= SIZE ||
				(rowdelta == 0 && coldelta == 0))
				continue;

			/* Now check the square */
			if (board[row + rowdelta][col + coldelta] == opponent)
			{
				/* If we find the opponent, move in the delta direction  */
				/* over opponent counters searching for a player counter */
				x = row + rowdelta;                /* Move to          */
				y = col + coldelta;                /* opponent square  */

				/* Look for a player square in the delta direction */
				for (;;)
				{
					x += rowdelta;                  /* Go to next square */
					y += coldelta;                  /* in delta direction*/

					/* If we move outside the array, give up */
					if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
						break;

					/* If we find a blank square, give up */
					if (board[x][y] == ' ')
						break;
					/*  If the square has a player counter */
					/*  then we have a valid move          */
					if (board[x][y] == player)
					{
						moves[row][col] = 1;   /* Mark as valid */
						no_of_moves++;         /* Increase valid moves count */
						break;                 /* Go check another square    */
					}
				}
			}
		}
	}
	return no_of_moves;
}

/************
* Finds the best move for the computer. This is the move for      *
* which the opponent's best possible move score is a minimum.     *
* First parameter is the board array.                             *
* Second parameter is the moves array containing valid moves.     *
* Third parameter identifies the computer.                        *
************/
void computer_move(char board[][SIZE], int moves[][SIZE], char player)
{
	int row = 0;                          /* Row index               */
	int col = 0;                          /* Column index            */
	int best_row = 0;                     /* Best row index          */
	int best_col = 0;                     /* Best column index       */
	int i = 0;                            /* Loop index              */
	int j = 0;                            /* Loop index              */
	int new_score = 0;                    /* Score for current move  */
	int score = 100;                      /* Minimum opponent score  */
	char temp_board[SIZE][SIZE];          /* Local copy of board     */
	int temp_moves[SIZE][SIZE];           /* Local valid moves array */
	char opponent = (player == 'O') ? '@' : 'O'; /* Identify opponent */

	/* Go through all valid moves */
	for (row = 0; row < SIZE; row++)
	for (col = 0; col < SIZE; col++)
	{
		if (moves[row][col] == 0)
			continue;

		/* First make copies of the board and moves arrays */
		for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++)
			temp_board[i][j] = board[i][j];

		/* Now make this move on the temporary board */
		make_move(temp_board, row, col, player);

		/* find valid moves for the opponent after this move */
		valid_moves(temp_board, temp_moves, opponent);

		/* Now find the score for the opponents best move */
		new_score = best_move(temp_board, temp_moves, opponent);

		if (new_score<score)    /* Is it worse?           */
		{                      /* Yes, so save this move */
			score = new_score;   /* Record new lowest opponent score */
			best_row = row;  /* Record best move row             */
			best_col = col;  /* and column                       */
		}
	}

	/* Make the best move */
	make_move(board, best_row, best_col, player);
}

/************
* Calculates the score for the current board position for the     *
* player. player counters score +1, opponent counters score -1    *
* First parameter is the board array                              *
* Second parameter identifies the player                          *
* Return value is the score.                                      *
************/
int get_score(char board[][SIZE], char player)
{
	int score = 0;      /* Score for current position */
	int row = 0;        /* Row index                  */
	int col = 0;        /* Column index               */
	char opponent = player == 'O' ? '@' : 'O';  /* Identify opponent */

	/* Check all board squares */
	for (row = 0; row < SIZE; row++)
	for (col = 0; col < SIZE; col++)
	{
		score -= board[row][col] == opponent; /* Decrement for opponent */
		score += board[row][col] == player;   /* Increment for player   */
	}
	return score;
}
int getscore(char board[][SIZE])
{
	int score = 0;      /* Score for current position */
	int row = 0;        /* Row index                  */
	int col = 0;        /* Column index               */
	/* Check all board squares */
	for (row = 0; row < SIZE; row++)
	for (col = 0; col < SIZE; col++)
	{
		score += board[row][col] == 'O'; // player;   /* Increment for player   */
	}
	return score;
}

/************
* Calculates the score for the best move out of the valid moves   *
* for player in the current position.                             *
* First parameter is the board array                              *
* Second parameter is the moves array defining valid moves.       *
* Third parameter identifies the player                           *
* The score for the best move is returned                         *
************/
int best_move(char board[][SIZE], int moves[][SIZE], char player)
{
	int row = 0;     /* Row index    */
	int col = 0;     /* Column index */
	int i = 0;       /* Loop index   */
	int j = 0;       /* Loop index   */


	char new_board[SIZE][SIZE] = { 0 };  /* Local copy of board    */
	int score = 0;                       /* Best score             */
	int new_score = 0;                   /* Score for current move */

	/* Check all valid moves to find the best */
	for (row = 0; row<SIZE; row++)
	for (col = 0; col<SIZE; col++)
	{
		if (!moves[row][col])             /* Not a valid move?      */
			continue;                      /* Go to the next         */

		/* Copy the board */
		for (i = 0; i<SIZE; i++)
		for (j = 0; j<SIZE; j++)
			new_board[i][j] = board[i][j];

		/* Make move on the board copy */
		make_move(new_board, row, col, player);

		/* Get score for move */
		new_score = get_score(new_board, player);

		if (score<new_score)         /* Is it better?               */
			score = new_score;  /* Yes, save it as best score  */
	}
	return score;                   /* Return best score           */
}


/*************
* Makes a move. This places the counter on a square,and reverses   *
* all the opponent's counters affected by the move.                *
* First parameter is the board array.                              *
* Second and third parameters are the row and column indices.      *
* Fourth parameter identifies the player.                          *
*************/
void make_move(char board[][SIZE], int row, int col, char player)
{
	int rowdelta = 0;                   /* Row increment              */
	int coldelta = 0;                   /* Column increment           */
	int x = 0;                          /* Row index for searching    */
	int y = 0;                          /* Column index for searching */
	char opponent = (player == 'O') ? '@' : 'O';  /* Identify opponent */

	board[row][col] = player;           /* Place the player counter   */

	/* Check all the squares around this square */
	/* for the opponents counter                */
	for (rowdelta = -1; rowdelta <= 1; rowdelta++)
	for (coldelta = -1; coldelta <= 1; coldelta++)
	{
		/* Don't check off the board, or the current square */
		if (row + rowdelta < 0 || row + rowdelta >= SIZE ||
			col + coldelta < 0 || col + coldelta >= SIZE ||
			(rowdelta == 0 && coldelta == 0))
			continue;

		/* Now check the square */
		if (board[row + rowdelta][col + coldelta] == opponent)
		{
			/* If we find the opponent, search in the same direction */
			/* for a player counter                                  */
			x = row + rowdelta;        /* Move to opponent */
			y = col + coldelta;        /* square           */

			for (;;)
			{
				x += rowdelta;           /* Move to the      */
				y += coldelta;           /* next square      */

				/* If we are off the board give up */
				if (x < 0 || x >= SIZE || y < 0 || y >= SIZE)
					break;

				/* If the square is blank give up */
				if (board[x][y] == ' ')
					break;

				/* If we find the player counter, go backwards from here */
				/* changing all the opponents counters to player         */
				if (board[x][y] == player)
				{
					while (board[x -= rowdelta][y -= coldelta] == opponent) /* Opponent? */
						board[x][y] = player;    /* Yes, change it */
					break;                     /* We are done    */
				}
			}
		}
	}
}
void brick()
{
	int n = 0, k, d, f = 0, i;
	setcolor(13);
	setfillstyle(SOLID_FILL, BROWN);
	rectangle(0, 0, getmaxx(), getmaxy());
	floodfill(getmaxx() / 2, getmaxy() / 2, 13);
	setcolor(15);
	setlinestyle(SOLID_LINE, 0, 5);
	for (d = 0; d<32; d++)
	{
		line(0, 15 + f, getmaxx(), 15 + f);
		f = f + 15;
	}
	k = 0;
	for (i = 0; i<32; i++)
	{
		f = 0;

		for (d = 0; d<32; d++)
		{

			line(40 + f - k, 0 + n, 40 + f - k, 15 + n);
			f = f + 40;

		}
		k = k + 20;
		n = n + 15;

	}

	setcolor(8);
	rectangle(140, 200, 500, 450);
	rectangle(150, 210, 490, 440);
	setfillstyle(SOLID_FILL, 9);
	floodfill(141, 201, 8);
	setfillstyle(SOLID_FILL, 4);
	floodfill(151, 261, 8);
	setcolor(15);
	settextstyle(7, 0, 2);
	outtextxy(230, 240, "DEVELOPED BY");
	settextstyle(8, 0, 2);
	outtextxy(155, 270, "   Mr. Rajesh R. Surana");
	outtextxy(155, 300, "    Mr. Ganesh R. Zilpe");
	settextstyle(7, 0, 2);
	outtextxy(230, 360, "  GUIDED BY");
	settextstyle(8, 0, 2);
	outtextxy(155, 390, "     Mr. R. R. Rathod");
	for (i = 0; i<25; i++)
	{
		while (kbhit())
		{
			if (getche() == 32 || 27)
				goto sanan;
		}
		randomize();
		setcolor(0);
		rectangle(140, 30, 500, 150);
		rectangle(150, 40, 490, 140);
		setfillstyle(SOLID_FILL, 14);
		floodfill(141, 31, 0);
		setfillstyle(SOLID_FILL, 0);
		floodfill(151, 61, 0);
		setcolor(i);//random(100));
		settextstyle(4, 0, 7);
		outtextxy(210, 50, "LAGNO");
		delay(200);
	}
sanan:	return;
}
void loading()
{
	int x = 0, y, d, i;
	clrscr();
	cleardevice();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                  Loading\n\n\n                             setting backup....");
	setcolor(15);
	arc(250, 300, 90, 270, 7);
	arc(350, 300, 270, 90, 7);
	line(250, 292, 350, 292);
	line(250, 308, 350, 308);
	setcolor(BLUE);
	x = 0;
	for (i = 0; i<33; i++)
	{
		setfillstyle(SOLID_FILL, BLUE);
		rectangle(248 + x, 294, 255 + x, 306);
		floodfill(249 + x, 295, BLUE);
		delay(150);
		x = x + 3;

	}
	clrscr();
	cleardevice();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                  Loading\n\n\n                             adjusting graphics....");
	setcolor(15);
	arc(250, 300, 90, 270, 7);
	arc(350, 300, 270, 90, 7);
	line(250, 292, 350, 292);
	line(250, 308, 350, 308);
	setcolor(BLUE);
	x = 0;
	for (i = 0; i<33; i++)
	{
		setfillstyle(SOLID_FILL, BLUE);
		rectangle(248 + x, 294, 255 + x, 306);
		floodfill(249 + x, 295, BLUE);
		delay(150);
		x = x + 3;

	}
	setcolor(WHITE);
	delay(500);
}
