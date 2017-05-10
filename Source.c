/* Name: Harpriya Bagri
 * Date: December 3rd, 2016
 * Lab #: 8 - SIMON GAME
 * Lab Section: L1F
 * Email: harpriya@alumni.ubc.ca
 */



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <DAQlib.h>

// defined values:
#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0

#define GREEN_LED 0
#define RED_LED 1
#define YELLOW_LED 2
#define BLUE_LED 3

#define BUTTON_0 0
#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_3 3

#define CONTINUE 5
#define WINNER 1
#define LOSER 0
#define MIN_VAL 0
#define MAX_VAL 3
#define MAX_TRIAL 4
#define FLASH_NUM 3
#define DELAY_TIME 800

// function protypes:
int randInt (int lower, int upper);
void generateSequence (int length, int data[]);
void runSimon( void );
void flash_sequence( int index, int data[]);
int compare_input( int index, int trial, int sequence[] );
int user_input( void );
void loser_sequence( void);
void winner_sequence( void);


int main (void){

	int setupNum;
	
	

	srand( (unsigned) time( NULL ) ) ;

	printf( "Hello! Welcome to the Simon Game!\n\n\n" );
	printf( "Instuctions: \n");
	printf( "1. Pay attention to which LED lights up\n" );
	printf( "2. Press corresponding button\n ");
	printf( "3. For every round, another LED will light up in sequence\n" );
	printf( "4. To quit, press the 'QUIT' button or exit the screen at any time.\n\n" );
	printf( "GOOD LUCK!\n\n" );
	
	printf( "Please enter an initialization number( 6 for simulator ): ");
	scanf( "%d", &setupNum);

	if( setupDAQ(setupNum) == TRUE ){
		runSimon();
	}
	else
		printf( "Error: Unable to initialize DAQ. " );

	system( "PAUSE" );
	return 0;
}

// 'runSimon' compiles the game using functions in a sequence together. 
// Function increments the round if the user pushes correct buttons matching the sequence displayed.
// Function also determines the trial # accordingly, and makes a call to the 'generateSequence' function if user pushes incorrect button or wins the simon game.
void runSimon( void) {
	int trial = 0;
	int nTrial = 0;
	int sequence[5] = {0};
	int indexA;
	int indexB;
	
	generateSequence( MAX_TRIAL, sequence);
	while( continueSuperLoop() == TRUE){
	
		while( trial <= MAX_TRIAL ){
			for( indexA = 0; indexA <= trial; indexA++ ){
				flash_sequence( indexA, sequence );
			}

			for( indexB = 0; indexB <= trial; indexB++ ){
				nTrial = compare_input( indexB, trial, sequence);
				if( nTrial == LOSER)
					break;
		}

			if(nTrial == CONTINUE)
				trial++;
			else if( nTrial == LOSER ){
				loser_sequence();
				trial = 0;
				Sleep( DELAY_TIME);
				generateSequence( MAX_TRIAL, sequence );
			}
			else if( nTrial == WINNER ){
				winner_sequence();
				trial = 0;
				Sleep( DELAY_TIME);
				generateSequence( MAX_TRIAL, sequence );
		}
	}
	}
}


	

// 'randInt' generates a random number between 0 and 3 and returns it.
int randInt (int lower, int upper) {
	int randomNum;
	randomNum = rand() % 4;
	return randomNum;
}


// 'generateSequence' generates a sequence and stores in the array 'sequence'.
void generateSequence (int length, int sequence[]) {
	int index;
	for (index = 0; index < length; index++) {
		sequence[index] = randInt (MIN_VAL, MAX_VAL);
	}
}



// 'flash_sequence' flashes sequence based on trial number.
void flash_sequence( int index, int sequence[]) {

	digitalWrite( sequence[index], ON);
	Sleep( DELAY_TIME);
	digitalWrite( sequence[index], OFF);
}
	

// 'user_input' lights up LEDs according to what button user has pushed.
int user_input( void ){
	int check = -1; 

	if( digitalRead( BUTTON_0) == ON){
		check = GREEN_LED;
		do{
			digitalWrite( GREEN_LED, ON);
		} while(digitalRead( BUTTON_0) == ON);
		digitalWrite( GREEN_LED, OFF);
	}

	else if( digitalRead( BUTTON_1) == ON) {
		check = RED_LED;
		do{
			digitalWrite( RED_LED, ON);
		} while(digitalRead( BUTTON_1) == ON);
		digitalWrite( RED_LED, OFF);
	}
			
	else if( digitalRead( BUTTON_2) == ON) {
		check = YELLOW_LED;
		do{
			digitalWrite( YELLOW_LED, ON);
		} while(digitalRead( BUTTON_2) == ON);
		digitalWrite( YELLOW_LED, OFF);
	}
			
	else if( digitalRead ( BUTTON_3) == ON) {
		check = BLUE_LED;
		do{
			digitalWrite( BLUE_LED, ON);
		} while(digitalRead( BUTTON_3) == ON);
		digitalWrite( BLUE_LED, OFF);
	
	}
		
	return check;
}

// 'compare_input' compares user input to the generated sequence
int compare_input( int index, int trial, int sequence[] ) {
	int check;

		do{
			check = user_input();
		} while( check < 0);

		if( check == sequence[index] ){

				if( index == trial && trial != MAX_TRIAL )
					return CONTINUE;
					
				else if( trial = MAX_TRIAL )
					return WINNER;

			}
			else
				return LOSER;


}

// 'loser_sequence' flashes red led 3 times when called.
void loser_sequence( void) {
	int index;
		for( index = 0; index < FLASH_NUM; index++ ){
			digitalWrite( RED_LED, ON);
			Sleep( DELAY_TIME /6 );
			digitalWrite( RED_LED, OFF);
			Sleep( DELAY_TIME /6);
		}
	}

// 'winner_sequence' flashes green led 3 times when called.
void winner_sequence( void) {
	int index;
		for( index = 0; index < FLASH_NUM; index++ ){
			digitalWrite( GREEN_LED, ON);
			Sleep( DELAY_TIME /5);
			digitalWrite( GREEN_LED, OFF);
			Sleep( DELAY_TIME/5);
		}
	}

		
	

