/*
 * rluon003_finalproject.c
 *
 * Created: 8/28/2018 10:34:38 AM
 * Author : RichardPC
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "io.h"
#include "timer.h"

enum M_state {start, wait, ai, twoP, gameover3, reset} menu;
enum p1_state {start1, wait1, up1, down1, inter1, inter2} paddle1;
enum p2_state {start2, wait2, up2, down2, inter3, inter4} paddle2;
enum ai_state {start5, init2, gameplay, gameover2, reset2} aig;
enum b_state {start3, init, left, ur, lr, ul, ll, right, point} ball;
enum game_state{start4 ,inmenu, inplay, gameover, reset1} game;
enum d_state {init1, p1_, p2_, balls} display;
enum print_state {skrt, wait4, peep, grrr,itm ,itm1}print;


unsigned int count = 0;
unsigned char twoPFlag = 0;
unsigned char back_2_menu = 0;
unsigned char gamestart = 0;
unsigned char p1index = 3;
unsigned char p2index = 3;
unsigned char x_pos = 4;
unsigned char y_pos = 3;
unsigned char scored = 0;
unsigned char reset5 = 0;

unsigned char direction = 0;



unsigned char score1 = 0;
unsigned char score2 = 0;

unsigned char button = 0x00;

unsigned char button1 = 0x00;
unsigned char button2 = 0x00;

unsigned char button3 = 0x00;
unsigned char button4 = 0x00;

unsigned char printed = 0x00;

		unsigned int ran = 0;
		unsigned int move = 0;
/*
MENU- One player/ Two player
DISPLAY- LED DISPLAY
BALL PHYSICS
GAME STATE = In play/ gameover/ reset/ back to menu

button = reset;
button1 = P1 UP
button2 = P1 Down
button3 = P2 UP
button4 = P2 Down

*/
// left paddle
void set_colum1()
{
	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
}
// reset matrix
void clearmatrix()
{
	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x01;
	PORTD = 0x05;

	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x01;
	PORTD = 0x05;
	
	PORTD = 0x00;
	PORTD = 0x04;

	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;

	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;												
}
// paddle 2
void set_colum2()
{
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x00;
	PORTD = 0x04;
	
	PORTD = 0x01;
	PORTD = 0x05;
	
}
// set the matrix, 3 Leds for each matrix
void set_matrix(unsigned int index, unsigned char paddle)
{
	unsigned int amt = 3;
	unsigned int i = 0;
	unsigned int k = amt;
	
	while ( i < 8)
	{
		if( i == index)
		{
			while (amt > 0)
			{
				PORTD = 0x00;
				PORTD = 0x04;
				amt--;
			}
			
			i = i + k;
		}
		else
		{
			PORTD = 0x01;
			PORTD = 0x05;
			i++;
		}
		
		
	}
	
	if(!paddle)
	{
		set_colum1();
	}
	else
	{
		set_colum2();
	}
	
	PORTD = 0x02;
}
// updates the position of the ball
void ballposition(unsigned char x, unsigned char y)
{
	
	unsigned int i = 0;
	unsigned int j = 0;
	
	for ( i = 0; i < 8; i++)
	{
		if(i == x)
		{
			PORTD = 0x00;
			PORTD = 0x04;
		}
		else
		{
			PORTD = 0x01;
			PORTD = 0x05;
		}
	}
	
	for ( j = 0; j < 8; j++)
	{
		if(j == y)
		{
			PORTD = 0x01;
			PORTD = 0x05;
			
		}
		else
		{
			PORTD = 0x00;
			PORTD = 0x04;
		}
	}
	
	PORTD = 0x02;
}
//controls for the left paddle
void p1()
{
	button1 = ~PINB & 0x02;
	button2 = ~PINB & 0x04;
	
	switch(paddle1)
	{
		case start1:
		paddle1 = wait1;
		break;
		
		case wait1:
		if(button2 && !button1)
		{
			paddle1 = up1;
		}
		else if (button1 && !button2)
		{
			paddle1 = down1;
			
		}
		else
		{
			paddle1 = wait1;
		}
		break;
		
		case up1:
		if(button2)
		{
			paddle1 = inter1;
		}
		else
		{
			paddle1 = wait1;
		}
		break;
		
		case down1:
		if(button1)
		{
			paddle1 = inter2;
		}
		else
		{
			paddle1 = wait1;
		}
		break;
		
		case inter1:
		if(!button2)
		{
			paddle1 = wait1;
		}
		else
		{
			paddle1 = inter1;
		}
		break;
		
		case inter2:
		if(!button1)
		{
			paddle1 = wait1;
		}
		else
		{
			paddle1 = inter2;
		}
		break;
	}
	
	switch(paddle1)
	{
		case start1:
		

		break;
		
		case wait1:
	
		break;

		case up1:
		if( p1index == 0)
		{
			break;
		}
		else
		{
		p1index--;
		}
		break;
		
		
		case down1:
		if( p1index == 5)
		{
			break;
		}
		else
		{
			p1index++;
		}
		break;
		
		default:
		break;
	}

}
// right paddle controls
void p2()
{
	button3 = ~PINB & 0x08;
	button4 = ~PINB & 0x10;
	
	switch(paddle2)
	{
		case start2:
		paddle2 = wait2;
		break;
		
		case wait2:
		if(button4 && !button3)
		{
			paddle2 = up2;
		}
		else if (button3 && !button4)
		{
			paddle2 = down2;
			
		}
		else
		{
			paddle2 = wait2;
		}
		break;
		
		case up2:
		if(button4)
		{
			paddle2 = inter3;
		}
		else
		{
			paddle2 = wait2;
		}
		break;
		
		case down2:
		if(button3)
		{
			paddle2 = inter4;
		}
		else
		{
			paddle2 = wait2;
		}
		break;
		
		case inter3:
		if(!button4)
		{
			paddle2 = wait2;
		}
		else
		{
			paddle2 = inter3;
		}
		break;
		
		case inter4:
		if(!button3)
		{
			paddle2 = wait2;
		}
		else
		{
			paddle2 = inter4;
		}
		break;
	}
	
	switch(paddle2)
	{
		case start2:

		break;
		
		case wait2:
		
		break;

		case up2:
		if( p2index == 0)
		{
			break;
		}
		else
		{
			p2index--;
		}
		break;
		
		
		case down2:
		if( p2index == 5)
		{
			break;
		}
		else
		{
			p2index++;
		}
		break;
		
		default:
		break;
		
	}

}


//// Credit to Jerry for this state machine. The led for my ball was flickering before this state machine
// updates the paddles and balls positions states
void dis()
{
	switch(display)
	{
		case init1:
		display = p1_;
		break;
		
		case p1_:
		display = p2_;
		break;
		
		case p2_:
		display = balls;
		break;
		
		case balls:
		display = p1_; 
		break;
		
		default:
		display = init1;
		break;
	}
	
	switch (display)
	{
		case p1_:
		set_matrix(p1index,1);
		break;

		case p2_:
		set_matrix(p2index,0);
		break;
		
		case balls:
		ballposition(x_pos,y_pos);
		break;
		
		default:
		break;
	}
	
}
// reset the game to its initial state
void resetvalues()
{
	 count = 0;
	twoPFlag = 0;
	back_2_menu = 0;
	gamestart = 0;
	p1index = 3;
	p2index = 3;
	x_pos = 4;
	y_pos = 3;
	scored = 0;
	reset5 = 0;
	score1 = 0;
	score2 = 0;
	direction = 0;
}
//two player game mode rules
void twoplayer()
{
	button = ~PINB & 0x01;
	switch(game)
	{
		case start4:
		
		game = inplay;
		break;
		
		case inmenu:
		if(gamestart)
		{
			game = inplay;
		}
		break;
		
		case inplay:
		if(score1 == 5 || score2 == 5)
		{
			gamestart = 0;
			game = gameover;
		}
		else
		{
			game = inplay;
		}
		break;
	
		case gameover:
		if(button)
		{
			game = reset1;
		}
		else
		{
			game = gameover;
		}
		break;
		
		case reset1:
		game = start4;
		break;
		
		default:
		game = start4;
		break;
	}
	
	switch(game)
	{
		case inplay:
	
		break;
		
		case reset1:
		score1 = 0;
		score2 = 0;
		back_2_menu = 1;
		gamestart = 0;
		break;
		
		default:
		break;
		
	}
	
}
// ai game mode rules, ai chooses a random index to move to
void aigame()
{
	switch(aig)
	{
		case start5:
	
			aig = init2;
		break;
		
		case init2:
		if(gamestart)
		{
			aig = gameplay;
		}
		break;
		
		case gameplay:
		if(score1 == 5 || score2 == 5)
		{
			gamestart = 0;
			aig = gameover2;
		}
		else
		{
			aig = gameplay;
		}
		break;
		
		case gameover2:
		if(button)
		{
			aig = reset2;
		}
		else
		{
			aig = gameover2;
		}
		break;
		
		case reset2:
		aig = start5;
		break;
		
		default:
		aig = start5;
		break;
		
	}
	
	switch (aig)
	{
		case gameplay:
			ran = rand();
			move = ran % 3;
			
			if(move == 0)
			{
				if(p2index == 5)
				{
					
					
				}
				else
				{
					p2index++;

				}
			}
			else if ( move == 1)
			{
				if(p2index == 0)
				{
					
					
				}
				else
				{
					p2index--;

				}

			}
			else if (move == 2)
			{
				p2index = p2index;
			}
			
		break;
		
		case gameover2:
		gamestart = 0;
		break;
		
		case reset2:
		score1 = 0;
		score2 = 0;
		back_2_menu = 1;
		break;
		
		default:
		break;
		
	}
	
}
// game logic
void baller()
{
	switch(ball)
	{
		case start3:
		ball = init;
		break;
		// start of the game
		case init:
		if(gamestart && !direction)
		{
			ball = left;
		}
		else if (gamestart && direction)
		{
		ball = right;	
		}
		else
		{
			ball = init;
		}
		break;
		//direction of the ball = left
		case left:
		direction = 0;
		if(y_pos == 6){
		
		if(x_pos == p1index)
		{
				ball = lr;
		}
		else if(x_pos == (p1index + 1))
		{
			ball = right;
		}
		else if( x_pos == (p1index + 2))
		{
			ball = ur;
		}
		else
		{
			ball = point;
		}
			
	}
	else
	{
		ball = left;
	}
		
		
		break;
		//direction of the ball = right
		case right:
		direction = 1;

		if( y_pos == 1)
		{
			if( x_pos == (p2index))
			{
				ball = ll;
			}
			else if ( x_pos == (p2index + 1))
			{
				ball = left;
			}
			else if ( x_pos == (p2index + 2))
			{
				ball = ul;
			}
			else
			{
				ball = point;
			}
		}
		
		else
		{
			ball = right;
		}
			break;
		//direction of the ball = up and right
		case ur:
		direction = 1;
		if(x_pos == 7 && y_pos == 1 && ( (x_pos - 1) == p2index + 1))
		{
			ball = ll;
		}
		else if(x_pos == 7 && y_pos == 1 && ( (x_pos - 1) == p2index + 2))
		{
			ball = ll;
		}
		else if (x_pos == 7 && y_pos == 1)
		{
			ball = point;
		}
		else if(x_pos == 7)
		{
			ball = lr;
		}
		else if( y_pos == 1)
			{
				if( x_pos == (p2index))
				{
					ball = ul;
				}
				else if( (x_pos + 1) == p2index)
				{
					ball = ll;
				}
				else if ( x_pos == (p2index + 1))
				{
					ball = ul;
				}
				else if ( x_pos == (p2index + 2))
				{
					ball = ul;
				}
				else
				{
					ball = point;
				}
			}
		else
		{
			ball = ur;
		}
		
		break;
		//direction of the ball = down and right
		case lr:
		direction = 1;
			
		if(x_pos == 0 && y_pos == 1 && ((x_pos + 1) == p2index + 1))
		{
			ball = ul;	
		}
		else if(x_pos == 0 && y_pos == 1 && ((x_pos + 1) == p2index ))
		{
			ball = ul;
		}
		else if(x_pos == 0 && y_pos == 1)
		{
			ball = point;
		}
		else if(x_pos == 0)
		{
			ball = ur;
		}
		else if( y_pos == 1)
		{
			if( x_pos == (p2index))
			{
				ball = ll;
			}
			else if ( x_pos == (p2index + 1))
			{
				ball = ll;
			}
			else if ( x_pos  == (p2index + 2))
			{
				ball = ll;
			}
			else if ( (x_pos - 1) == p2index + 2)
			{
				ball = ul;
			}
			else
			{
				ball = point;
			}
		}
		else
		{
			ball = lr;
		}
		break;
		//direction of the ball = down and left
		case ll:
		direction = 0;
		
		if( x_pos == 0 && y_pos == 6 && ((x_pos + 1) == p1index + 1))
		{
			ball = ur;
		}
		else if( x_pos == 0 && y_pos == 6 && ((x_pos + 1) == p1index))
		{
			ball = ur;
		}
		else if( x_pos == 0 && y_pos == 6)
		{
			ball = point;
		}
		else if (x_pos == 0)
		{
			ball = ul;
		}
		else if(y_pos == 6){
			
			if(x_pos == p1index)
			{
				ball = lr;
			}
			else if(x_pos == (p1index + 1))
			{
				ball = lr;
			}
			else if( x_pos == (p1index + 2))
			{
				ball = lr;
			}
			else if ((x_pos - 1) == p1index + 2)
			{
				ball = ur;
			}
			else
			{
				ball = point;
			}
		}
		else if ( x_pos == 0)
		{
			ball = ul;
		}
		else 
		{
			ball = ll;
		}
		break;
		//direction of the ball = up and left
		case ul:
		direction = 0;
		
		if(x_pos == 7 && y_pos == 6 && (x_pos - 1) == p1index + 1)
		{
			ball = lr;
		}
		else if(x_pos == 7 && y_pos == 6 && (x_pos - 1) == p1index + 2)
		{
			ball = lr;
		}
		else if (x_pos == 7 && y_pos == 6)
		{
			ball = point;
		}
		
		else if(x_pos == 7)
		{
			ball = ll;
		}
		else if(y_pos == 6){
			
			if(x_pos == p1index)
			{
				ball = ur;
			}
			else if ( (x_pos + 1) == p1index)
			{
				ball = lr;
			}
			else if(x_pos == (p1index + 1))
			{
				ball = ur;
			}
			else if( x_pos == (p1index + 2))
			{
				ball = ur;
			}
			
			else
			{
				ball = point;
			}	
		}
			else
			{
				ball = ul;
			}
			break;
			// a player scores state
			case point:
			ball = init;
			break;
			
		default:
		ball = start3;
		break;
	}
	
	switch (ball)
	{
		case init:
		ballposition(x_pos, y_pos);
		break;
		
		case left:
	
		y_pos++;
		ballposition(x_pos, y_pos);
		break;
		
		case right:
		y_pos--;
		ballposition(x_pos, y_pos);
		break;
		
		case ll:
	
		x_pos--;
		y_pos++;
		ballposition(x_pos, y_pos);
		break;

		case ur:
		x_pos++;
		y_pos--;
		ballposition(x_pos, y_pos);
		break;
		
		case ul:
	
		y_pos++;
		x_pos++;
		ballposition(x_pos, y_pos);

		break;
		
		case lr:
		x_pos--;
		y_pos--;
		ballposition(x_pos, y_pos);
		break;
		
		case point:
		if(!direction)
		{
			scored = 1;
			score2++;
		}
		else
		{
			scored = 1;
			score1++;
		}
		
		x_pos = 4;
		y_pos = 4;
		break;
		
		default:
		break;
	}
}
// menu to choose between 2 player mode or player vs the AI on the LCD Screen
void flagcheck()
{
	button = ~PINB & 0x04;
	button1 = ~PINB & 0x08;
	twoPFlag = 0;
	switch(print)
	{
		case skrt:
		print = wait4;
		break;
		
		case wait4:
		if(button)
		{
		print = itm;	
		}
		else if (button1)
		{
			print = itm1;
		}
		else
		{
			print = wait4;
		}
		break;
		
		case itm:
		if(!button)
		{
			print = peep;
		}
		break;
		
		case itm1:
		if(!button1)
		{
			print = grrr;
		}
		break;
		case peep:
		print = peep;
		break;
		
		case grrr:
		print = grrr;
		break;
		
		default:
		print = skrt;
		break;
		
	}
	
	switch(print)
	{		
		
		case skrt:
			clearmatrix();
		break;
		
		case wait4:
		reset5 = 0;
			if(!printed)
			{
				LCD_ClearScreen();
				LCD_DisplayString(1, "SinglePlayer: B1Multiplayer: B2");
			}
			printed = 1;
			break;
		
		case peep:
		twoPFlag = 2;
		break;
		
		case grrr:
		twoPFlag = 1;
		break;
		
		default:
		break;
	}
	
}

// updates the scoreboard
void tick_menu()
{
	button = ~PINB & 0x01;
	button1 = ~PINB & 0x02;
	switch (menu)
	{
		case start:
		clearmatrix();
		menu = wait;
		break;
		
		case wait:
		if(twoPFlag == 1)
		{
			gamestart = 1;
			printed = 0;
			menu = twoP;
		}
		else if (twoPFlag == 2)
		{
			gamestart = 1;
			printed = 0;
			menu = ai;
		}
		else
		{
			menu = wait;
		}
		break;
		
		case ai:
		if(!gamestart)
		{
			printed = 0;
			menu = gameover3;
		}
		else
		{
			menu = ai;
		}
		break;
		
		case twoP:
		if(!gamestart)
		{
			printed = 0;
			menu = gameover3;
		}
		else
		{
			menu = twoP;
		}
		break;
		
		case gameover3:
		if(button)
		{
			menu = reset;
		}
		else
		{
			menu = gameover3;
		}
		break;
		
		case reset:
		
		break;
		
		default:
		menu = start;
		break;
		
	}
	
	switch(menu)
	{
		case wait:
		back_2_menu = 0;
	
		break;
		
		case ai:
		if(scored || !printed)
		{
			
		
		LCD_DisplayString(1, "Player 1:        Player 2:");
		LCD_Cursor(10);
		LCD_WriteData(score1 + '0');
		LCD_Cursor(27);
		LCD_WriteData(score2 + '0');
		scored = 0;
		}
		printed = 1;

		break;
		
		case twoP:
		if(scored || !printed)
		{
		LCD_DisplayString(1, "Player 1:       Player 2:");
		LCD_Cursor(10);
		LCD_WriteData(score1 + '0');
		LCD_Cursor(27);
		LCD_WriteData(score2 + '0');
		scored = 0;
		
		}
		printed = 1;

		break;
		
		
		case gameover3:
		
		if(!printed)
		{
		
		if(score1 > score2)
		{
		LCD_DisplayString(1, "Game Over! Player1 Wins!");
			printed = 1;
			break;
		}
		else
		{
			LCD_DisplayString(1, "Game Over! Player2 Wins!");
			printed = 1;
			break;
		}
	}
		break;
		
		case reset:
		twoPFlag = 0;
		printed = 0;
		reset5 = 1;
		LCD_ClearScreen();
		clearmatrix();
		break;
		
		default:
		break;
		
	}
	
} 

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	RESET:  resetvalues();

	
	unsigned int count1 = 0;
	LCD_init();

	TimerSet(10);
	TimerOn();
	// initialize states
	paddle1 = start1;
	paddle2 = start2;
	menu = start;
	ball = start3;
	aig = start5;
	display = init1;
	game = start4;
	print = skrt;
	//set the LCD to select game mode menu
	while(twoPFlag == 0)
	{
		flagcheck();

	}
	
	   /* Replace with your application code */
    while (1) 
    {
		if(reset5)
		{
			// resets game
			goto RESET;
		}
				// two player mode
				if(twoPFlag == 1){
				
				if(reset5)
				{
					goto RESET;
				}
				
				tick_menu();
				
				if(reset5)
				{
					goto RESET;
				}
				p1();
				p2();
				twoplayer();
				
				if(count++ >= 12000)
				{
					baller();
					count = 0;
				}
				
				dis();
				}
				//ai game mode
				else if ( twoPFlag == 2)
				{
				
				if(reset5)
				{
					goto RESET;
				}
				
				tick_menu();
				if(reset5)
				{
					goto RESET;
				}
				p1();
				
				
				if(count++ >= 10000)
				{
					baller();
					count = 0;
				}
				
				
				if(count1++ >= 10000)
				{
						aigame();
						count1 = 0;

				}
				
				
			
				dis();
		
				}

    }
}

