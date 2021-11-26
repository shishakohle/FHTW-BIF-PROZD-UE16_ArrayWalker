#include <stdlib.h>
#include <stdio.h>

struct Robot
{
	char map[10][10];
	int currentPosLine;
	int currentPosColumn;
};

void printMap(struct Robot* robot)
{
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			printf("%c", robot->map[i][j]);
		}
		
		printf("\n");
	}
}

struct Robot* initRobot(void)
{
	struct Robot* newRobot = (struct Robot*) malloc( sizeof(struct Robot) );
	
	// init map
	for (int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			newRobot->map[i][j] = '.';
		}
	}
	
	// init position of robot at [0][0] with character A
	newRobot->currentPosLine   = 0;
	newRobot->currentPosColumn = 0;
	newRobot->map[0][0] = 'A';
	
	// print initial state of the map
	printMap(newRobot);
	
	return newRobot;
}

void terminateRobot(struct Robot* robot)
{
	free(robot);
}

int isWithinMapBoundary(int posLine, int posColumn)
{
	return posLine>= 0 && posLine<10 && posColumn>= 0 && posColumn<10;
}

void moveRobot(struct Robot* robot, char direction)
{
	int movePossible = 0;
	
	int targetPosLine   = robot->currentPosLine;
	int targetPosColumn = robot->currentPosColumn;
	
	switch(direction)
	{
		case 'n': targetPosLine  --; break;
		case 'e': targetPosColumn++; break;
		case 's': targetPosLine  ++; break;
		case 'w': targetPosColumn--; break;
	}
	
	if ( isWithinMapBoundary(targetPosLine, targetPosColumn) )
	{
		if( robot->map[targetPosLine][targetPosColumn] == '.' )
		{
			// all safe, perform the move!
			movePossible = 1;
			
			// write character to target's position on the map
			char currentCharacter =
				robot->map[robot->currentPosLine][robot->currentPosColumn];
			char targetCharacter  = currentCharacter+1;
			robot->map[targetPosLine][targetPosColumn] =
				targetCharacter > 'Z' ? 'A' : targetCharacter;
			
			// make target the new position of robot
			robot->currentPosLine   = targetPosLine;
			robot->currentPosColumn = targetPosColumn;
		}
	}
	
	if(movePossible)
		// print the new state of the map
		printMap(robot);
	else
		printf("not possible\n");
}

char getUserinput(void)
{
	char input;
	
	do
	{
		printf("walk to: ");
		scanf(" %c", &input);
	}
	while( input!='n' && input!='e' && input!='s' && input!='w' && input!='x' );
	
	return input;
}

int main(void)
{
	struct Robot* myRobot = initRobot();
	
	char userinput;
	
	do
	{
		userinput = getUserinput();
		
		if (userinput != 'x')
			moveRobot(myRobot, userinput);
	}
	while(userinput != 'x');
	
	terminateRobot(myRobot);
	
	return 0;
}
