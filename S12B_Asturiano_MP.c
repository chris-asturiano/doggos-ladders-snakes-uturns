/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned.
I have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.

Christian Emmanuel S. Asturiano, DLSU ID# 12126780
******************************************************************/
/*
     This program is a 2-5 player game called Doggos, Ladders, Slides, and U-turns
     Programmed by: Christian Emmanuel S. Asturiano S12B
     Last modified: Feb 6, 2022
     Version: 1.0
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*   Rolls a dice array and returns a value based on diceNum
     Precondition: diceNum is an int from 0-4
     @param diceNum is the index of the dice array
     @return the element of the array at index diceNum
*/
int
rollDice(int diceNum)
{
        int diceArray[5];
        int diceVal;

        srand (time(NULL));

        for (int i = 0; i < 5; i++)
                diceArray[i] = rand()%10+1;

        diceVal = diceArray[diceNum];

        return diceVal;
}

/*   Calculates row based on tile
     Precondition: tile is an int from 1 - 100
     @param tile is the tile of the player
     @return the row of the tile
*/
int
calcRow (int tile)
{
        return (tile+9)/10;
}

/*   Calculates column based on tile
     Precondition: tile is an int from 1 - 100
     @param tile is the tile of the player
     @return the column of the tile
*/
int
calcCol (int tile)
{
        if (calcRow(tile)%2 == 1) {
                if (tile%10 == 0)
                        return 10;

                else
                        return tile%10;
        } else
                return ((calcRow(tile)*10)+1) - tile;
}

/*   Calculates tile number based on column and row
     Precondition: row and column are ints from 1 - 10
     @param row is the row of the tile
     @param column is the column of the tile
     @return the resulting tile based on the column and row
*/
int
calcTile (int row,
          int column)
{
        int tile;
        if (row%2 == 1) {
                tile = ((row - 1) * 10) + column;
                return tile;
        } else {
                tile = (row * 10) - (column - 1);
                return tile;
        }
}

/*   Brings player 3 rows above current tile when player rolls double three
     Precondition: tile is an int from 0-90 (Can't roll two dice in top most row)
     @param tile is the tile of the player
     @return the tile that is 3 rows above the player
*/
int
doubleThree (int tile)
{
        int column = calcCol(tile);
        int row = calcRow(tile);

        if (tile == 0)
                return tile;

        else {
                if (row >= 8) {
                        row = 10;
                        column = 2;
                } else
                        row += 3;
        }
        return calcTile(row, column);
}

/*   Ladder dice roll (makes sure that tile is always higher than current tile and row)
     Precondition: tile is not on top most row (91 -  100)
     @param tile is the tile of the player
     @return a tile that is greater than the player's tile and row
*/
int
ladderDice (int tile)
{
        srand(time(NULL));
        int row = calcRow(tile);
        int newRow = rand()%(10+1 - (row+1))+(row+1);
        int newColumn = rollDice(3);

        return calcTile(newRow, newColumn);
}

/*   Slide dice roll (makes sure that the tile is always lesser than current tile and row)
     Precondition: tile is not on bottom most row (1 - 10)
     @param tile is the tile of the player
     @return a tile that is lesser than the player's tile and row
*/
int
slideDice (int tile)
{
        srand(time(NULL));
        int row = calcRow(tile);
        int newRow = rand()%((row-1)+1 - 1) + 1;
        int newColumn = rollDice(3);

        return calcTile(newRow, newColumn);
}

/*   Returns and prints a random tile if player gets a doggo, and increases the doggo counter for that specific player
     Precondition: tile is an int from 0-99, doggoCtr[i] is an integer with an initial value of 0
     @param tile is the tile of the player
     @param doggoCtr[] is the array that stores the doggo counter for that specific player
     @param i is the player's index in the doggoCtr array
     @return a random tile on the board
*/
int
ifDoggo (int tile,
         int doggoCtr[],
         int i)
{
        int doggoTile = calcTile(rollDice(3), rollDice(4));
        printf("A doggo is on tile %d. ", tile);

        if (tile == doggoTile)
                printf("The doggo wants to stay with you on tile %d. \n\n", doggoTile);

        else if (doggoTile > tile)
                printf("The doggo wants to help you! Please proceed to tile %d.\n\n", doggoTile);

        else if (doggoTile < tile)
                printf("The doggo got scared! Sorry, please follow the doggo to tile %d.\n\n", doggoTile);

        doggoCtr[i]++;

        return doggoTile;
}

/*   Returns and prints a tile that is greater than player's current tile and row if player gets a ladder, and increases ladder counter for that specific player.
     Precondition: tile is not on top most row (91 - 100), ladderCtr[i] is an integer with an initial value of 0
     @param tile is the tile of the player
     @param ladderCtr[] is the array that stores the ladder counter for that specific player
     @param i is the player's index in the ladderCtr array
     @return a tile that is greater than the player's current tile and row.
*/
int
ifLadder (int tile,
          int ladderCtr[],
          int i)
{
        int ladderTile = ladderDice(tile);
        printf("A ladder is on tile %d. ", tile);
        printf("Nice! Climb the ladder to get to tile %d. \n\n", ladderTile);

        ladderCtr[i]++;

        return ladderTile;
}

/*   Returns and prints a tile that is lesser than player's current tile and row if player gets a slide, and increases slide counter for that specific player.
     Precondition: tile is not on bottom most row (1- 10), slideCtr[i] is an integer with an initial value of 0
     @param tile is the tile of the player
     @param slideCtr[] is the array that stores the slide counter for that specific player
     @param i is the player's index in the slideCtr array
     @return a tile that is lesser than the player's current tile and row.
*/
int
ifSlide (int tile,
         int slideCtr[],
         int i)
{
        int slideTile = slideDice(tile);

        printf("A slide is on tile %d. ", tile);
        printf("Sorry, but you have to slide down to tile %d. Dont worry, it'll be fun! \n\n", slideTile);

        slideCtr[i]++;

        return slideTile;
}

/*   Returns and prints the previous tile of the player
     Precondition: tile is an int from 1 - 99, prevTile is an int from 0 - 99, uturnCtr[i] is an integer with an initial value of 0
     @param tile is the tile of the player
     @param prevTile is the previous tile of the player to be returned
     @return the previous tile of the player
*/
int
ifUturn (int tile,
         int prevTile,
         int uturnCtr[],
         int i)
{
        printf("A U-turn is on tile %d. ", tile);
        printf("Sorry, please take this U-turn to tile %d. \n\n", prevTile);

        uturnCtr[i]++;

        return prevTile;
}

/*   Returns and prints the tile if player does not get an object
     Precondition: tile is an int from 1 - 99
     @param tile is the tile of the player
     @return the tile of the player
*/
int
ifNothing (int tile)
{
        printf("There is no object on tile %d. ", tile);
        printf("Please stay on tile %d. \n\n", tile);

        return tile;
}

/*   Determines the object on the tile, and returns the tile based on the object
     Precondition: diceVal is an int from 1 - 10. tile, prevTile are ints from 0 - 9. Counter arrays have initial values of 0, and i is the index of the player in the arrays.
     @param tile is the tile of the player
     @param prevTile is the previous tile of the player
     @param doggoCtr[] is the array that stores the doggo counter for each player
     @param ladderCtr[] is the array that stores the ladder counter for each player
     @param slideCtr[] is the array that stores the slide counter for each player
     @param uturnCtr[] is the array that stores the U-turn counter for each player
     @param i is the index of the player for each array
     @return the tile based on the object
*/
int
whatObject (int diceVal,
            int tile,
            int prevTile,
            int doggoCtr[],
            int ladderCtr[],
            int slideCtr[],
            int uturnCtr[],
            int i)
{
        switch (diceVal) {
        case 1: //Doggo
                return ifDoggo(tile, doggoCtr, i);
                break;

        case 2: //Ladder
                //If row is 10, you cant get a ladder
                if (calcRow(tile) == 10)
                        return ifNothing(tile);
                else
                        return ifLadder(tile, ladderCtr, i);
                break;

        case 3: //Slide
                //If row is 1, you cant get a silde
                if (calcRow(tile) == 1)
                        return ifNothing(tile);
                else
                        return ifSlide(tile, slideCtr, i);
                break;

        case 4: //U-turn
                return ifUturn(tile, prevTile, uturnCtr, i);
                break;

        default:
                return ifNothing(tile);
                break;
        }
}

/*   Shuffles the player sequence
     Precondition: the array players[] have a number of elements equal to playerCount, and playerCount is an int from 2-5
     @param players[] is an array that stores the players and their sequence
     @param playerCount is the number of players, and how many times the loop will iterate
*/
void
playerSequence (int players[],
                int playerCount)
{
        int random, temp;
        srand(time(NULL));

        for (int i = 0; i < playerCount; i++) {
                //Gets a random index for the array
                random = rand()% playerCount;
                //Temp variable
                temp = players[i];

                //Swap players[i] with a random element in the array
                players[i]= players[random];
                //Swap random element with players[i]
                players[random] = temp;
        }
}

/*   Displays the order of players
     Precondition: the array players[] have a number of elements equal to playerCount, and playerCount is an int from 2-5
     @param players[] is an array that stores the players and their sequence
     @param playerCount is the number of players to be evaluated in the function
*/
void
displayOrder (int players[],
              int playerCount)
{
        switch (playerCount) {
        case 2:
                printf("\n\nPlayer %d will go first, and Player %d will go second.\n\n",
                       players[0], players[1]);
                break;

        case 3:
                printf("\n\nPlayer %d will go first, followed by player %d and player %d.\n\n",
                       players[0], players[1], players[2]);
                break;

        case 4:
                printf("\n\nPlayer %d will go first, followed by player %d, player %d, and player %d.\n\n",
                       players[0], players[1], players[2], players[3]);
                break;

        case 5:
                printf("\n\nPlayer %d will go first, followed by player %d, player %d, player %d, and player %d.\n\n",
                       players[0], players[1], players[2], players[3], players[4]);
                break;
        }
}

/*   Transforms the players array into a single integer
     Precondition: the array players[] have a number of elements equal to playerCount, and playerCount is an int from 2-5
     @param players[] is an array that stores the players and their sequence
     @param playerCount is the number of players
     @return the sequence of players
*/
int
getSequence (int players[],
             int playerCount)
{
        int sequence = players[0];

        for (int i = 0; i < playerCount-1; i++)
                sequence = (sequence*10)+players[i+1];

        return sequence;
}

/*   Updates the integer sequence
     Precondition: sequence have unique digits that may range from 1-5 depending on the amount of players (playerCount)
     @param sequence is the sequence of players
     @param playerCount is the number of players
     @return the updated sequence
*/
int
updateSequence(int sequence,
               int playerCount)
{
        int e = 1;
        int firstdigit;

        for (int i = 1; i < playerCount; i++)
                e *= 10;

        firstdigit = sequence / e;

        return (sequence%e)*10 + firstdigit;
}

/*   Displays the board of the game
     Precondition: the array players[] have a number of elements equal to playerCount, and playerCount is an int from 2-5
                   playerTile[] is an array with elements ranging from 0 - 100
     @param players[] is an array that stores the players and their sequence
     @param playerTile[] is the array that stores the tiles of each player
     @param playerCount is the number of players
*/
void
displayBoard(int players[],
             int playerTile[],
             int playerCount)
{
        int tile, col = 10, rowcounter = 10, counter = 0;

        while (tile != 10) {
                //If row is even
                if (rowcounter % 2 == 0) {
                        //First tile in the row is row x 10
                        tile = rowcounter * 10;

                        for (int i = 0; i < col; i++) {
                                counter = 0;
                                for (int i = 0; i < playerCount; i++) {
                                        //Prints the player if playerTile is equal to tile
                                        if (playerTile[i] == tile && counter == 0) {
                                                printf("%4s%d", "P", players[i]);
                                                counter++;
                                        } //Prints the player if playerTile is equal to tile
                                        else if (playerTile[i] == tile && counter >= 1) {
                                                printf("%s%d", "P", players[i]);
                                                counter++;
                                        }
                                        //If there was only 1 player on the tile, print a space
                                        if (counter == 1 && i == playerCount-1)
                                                printf("  ");
                                }
                                //Prints the tile if playerTile is not equal to tile
                                if (counter == 0)
                                        printf("%5d  ", tile);

                                tile--;
                        }
                        printf("\n");
                        rowcounter--;
                }
                //If row is even
                else if (rowcounter % 2 == 1) {
                        //First tile in the row is (row-1)x10 + 1
                        tile = ((rowcounter-1)*10)+1;

                        for (int i = 0; i < col; i++) {
                                counter = 0;
                                for (int i = 0; i < playerCount; i++) {
                                        //Prints the player if playerTile is equal to tile
                                        if (playerTile[i] == tile && counter == 0) {
                                                printf("%4s%d", "P", players[i]);
                                                counter++;
                                        }//Prints the player if playerTile is equal to tile
                                        else if (playerTile[i] == tile && counter >= 1) {
                                                printf("%s%d", "P", players[i]);
                                                counter++;
                                        }
                                        //If there was only 1 player on the tile, print a space
                                        if (counter == 1 && i == playerCount-1)
                                                printf("  ");
                                }
                                //Prints the tile if playerTile is not equal to tile
                                if (counter == 0)
                                        printf("%5d  ", tile);

                                tile++;
                        }
                        printf ("\n");
                        rowcounter--;
                }
                tile--;
        }
}

/*   Displays the rankings of the players based on their positions on the board
     Precondition: the array players[] have a number of elements equal to playerCount, and playerCount is an int from 2-5
                   playerTile[] is an array with elements ranging from 0 - 100
     @param players[] is an array that stores the players and their sequence
     @param playerTile[] is the array that stores the tiles of each player
     @param playerCount is the number of players
*/
void
displayRanking(int players[],
               int playerTile[],
               int playerCount)
{
        int scores[playerCount];
        int rankings[playerCount];

        //Equates scores to playerTile, and rankings to players[]
        for (int i = 0; i < playerCount; i++)
                scores[i] = playerTile[i];

        for (int i = 0; i < playerCount; i++)
                rankings[i] = players[i];

        //Sort from highest to lowest
        for (int i = 0; i < playerCount; i++)
        {
                for (int j = i+1; j < playerCount; j++) {
                        if (scores[j] > scores [i]) {
                                //Scores
                                int swapper1 = scores[i];
                                scores[i] = scores[j];
                                scores [j] = swapper1;

                                //Do the same for the rankings
                                int swapper2 = rankings[i];
                                rankings[i] = rankings[j];
                                rankings[j] = swapper2;
                        }
                }
        }

        printf("Rank\tPlayer");
        for (int i = 0; i < playerCount; i++)
                printf("\n%d\t%s%d", i+1, "P", rankings[i]);

        printf("\n");
}

/*   Displays the object that caused the player to travel the farthest
     Precondition: farthest[i] is an int from 0 - 100
     @param farthest[] is the array that stores the object that caused the player to travel the farthest for each palyer.
     @param i is the index of the winning player in the array farthest[]
*/
void
displayFarthest (int farthest[],
                 int i)
{
        switch (farthest[i]) {
        case 1:
                printf("A doggo took you to the farthest tile.\n");
                break;

        case 2:
                printf("A ladder took you to the farthest tile.\n");
                break;

        case 3:
                printf("A slide took you to the farthest tile.\n");
                break;

        case 4:
                printf("A U-turn took you to the farthest tile.\n");
                break;

        default:
                printf("You did not encounter objects this game.\n");
                break;

        }
}

/*   Displays the winning move of the winner
     Precondition: all parameters are nonnegative
     @param prevTile is the previous tile of the player
     @param diceVal1 is the first dice roll (determines the row)
     @param diceVal2 is the second dice roll (determines the column)
     @param diceval3 is the third dice roll (determines the object)
*/
void
displayWinningMove (int prevTile,
                    int diceVal1,
                    int diceVal2,
                    int diceVal3)
{
        if (diceVal1 == 10 && diceVal2 == 1)
                printf("The winning move was when you rolled the dice (%d and %d).", diceVal1, diceVal2);

        else if ((prevTile >= 90 && prevTile <= 99) && ((prevTile + diceVal1) == 100) )
                printf("The winning move was when you rolled the dice (%d).", diceVal1);

        else {
                switch (diceVal3) {
                case 1:
                        printf("The winning move was when you followed the doggo.");
                        break;

                case 2:
                        printf("The winning move was when you climbed the ladder.");
                        break;
                }
        }
}

/*   Displays the game summary
     Precondition: all parameters are nonnegative
     @param winner is the player number of the winning player
     @param doggoCtr[] is the array that stores the doggo counter for each player
     @param ladderCtr[] is the array that stores the ladder counter for each player
     @param slideCtr[] is the array that stores the slide counter for each player
     @param uturnCtr[] is the array that stores the U-turn counter for each player
     @param farthest[] is the array that stores the object that caused the player to move the farthest for each player
     @param j is the index of the player for the arrays
     @param prevTile is the previous tile of the player
     @param winningD1 is the 1st dice roll of the last move
     @param winningD2 is the 2nd dice roll of the last move
     @param winningD3 is the 3rd dice roll of the last move (determines the object).
*/

void
displayGameSummary(int winner,
                   int doggoCtr[],
                   int ladderCtr[],
                   int slideCtr[],
                   int uturnCtr[],
                   int farthest[],
                   int j,
                   int prevTile,
                   int winningD1,
                   int winningD2,
                   int winningD3)
{
        printf("\nPlayer %d, you reached tile 100! YOU WIN!", winner);
        printf("\nDoggo appeared %d time(s).", doggoCtr[j]);
        printf("\nYou climbed ladders %d time(s).", ladderCtr[j]);
        printf("\nYou rode slides %d time(s).", slideCtr[j]);
        printf("\nYou took U-turns %d time(s).\n", uturnCtr[j]);
        displayFarthest(farthest, j);
        displayWinningMove(prevTile, winningD1, winningD2, winningD3);
        printf("\nCONGRATULATIONS!");
}

//MAIN
int main()
{
        char ans;
        do
        {
                //Declarations
                int playerCount;
                int diceVal1, diceVal2, diceVal3;
                int rnd = 0, prevTile = 0, sequence, winner = 0, j, distance = 0;
                int tileNoObject = 0;
                int winningD1, winningD2, winningD3;

                char roll, brdAns, rnkAns;

                printf("Welcome to Doggos, Ladders, Slides and U-turns!\n");
                printf("How many players will be playing? (2-5 players) ");
                scanf(" %d", &playerCount);

                while (playerCount < 2 || playerCount > 5) {
                        getchar();
                        printf("Invalid Number of Players!\n");
                        printf("How many players will be playing? (2-5 players)");
                        scanf(" %d", &playerCount);
                }

                printf ("\nGenerating Sequence... ");
                //Generates sequence of players in the players array
                int players[playerCount];
                for (int i = 0; i < playerCount; i++)
                        players[i]=i+1;

                //Shuffles the players array
                playerSequence(players, playerCount);
                sequence = getSequence(players, playerCount);


                //Prints sequence of players
                for (int i = 0; i < playerCount; i++)
                        printf(" %d", players[i]);

                displayOrder(players, playerCount);


                //Every player is initially positioned off the board (equate each element in playerTile[] to 0)
                int playerTile[playerCount];
                for (int i = 0; i < playerCount; i++)
                        playerTile[i] = 0;

                //Doggo Counter, Ladder Counter, Slide, and Farthest Distance Counters
                int doggoCtr[playerCount];
                int ladderCtr[playerCount];
                int slideCtr[playerCount];
                int uturnCtr[playerCount];
                int farthest[playerCount];
                int highesttravel[playerCount];

                for (int i = 0; i < playerCount; i++) {
                        //Equates all of them to 0
                        doggoCtr[i] = 0;
                        ladderCtr[i] = 0;
                        slideCtr[i] = 0;
                        uturnCtr[i] = 0;
                        farthest[i] = 0;
                        highesttravel[i] = 0;
                }

                //Game Start
                do
                {
                        for (int i = 0; i < playerCount; i++) {
                                printf("\n[%d] Player %d, please enter R to roll a pair of D10 dice: ", playerTile[i], players[i]);
                                scanf(" %c", &roll);

                                while (roll != 'r' && roll != 'R') {
                                        printf("Invalid Input!\n");
                                        printf("Player %d, please enter R to roll a pair of D10 dice: ", players[i]);
                                        scanf(" %c", &roll);
                                }

                                //Saves the previous tile for U-Turns
                                prevTile = playerTile[i];

                                //Pseudo dice rolls
                                diceVal1 = rollDice(0);
                                diceVal2 = rollDice(1);
                                diceVal3 = rollDice(2);

                                //If player is on highest row, roll only one dice
                                if (playerTile[i] >= 90 && playerTile[i]<=99) {
                                        playerTile[i] += diceVal1;
                                        diceVal2 = 0;
                                        printf("You rolled: %d. \n", diceVal1);

                                        if (playerTile[i] >= 100) {
                                                playerTile[i] = 200 - playerTile[i];
                                                printf("Please proceed to tile %d.\n\n", playerTile[i]);
                                        }

                                        else
                                                printf("Please proceed to tile %d.\n\n", playerTile[i]);
                                } else {
                                        //If player rolls a double three
                                        if (diceVal1 == 3 && diceVal2 == 3) {
                                                playerTile[i] = doubleThree(playerTile[i]);
                                                printf("You rolled a double-3. \n");
                                                printf("Please proceed to tile %d.\n\n", playerTile[i]);
                                        } //If player rolls a double five
                                        else if (diceVal1 == 5 && diceVal2 == 5) {
                                                printf("You rolled a double-5. ");
                                                printf("You miss a turn.\n");
                                                printf("Sorry! PLease stay on tile %d.\n", playerTile[i]);
                                        } else {
                                                playerTile[i] = calcTile(diceVal1, diceVal2);
                                                printf("You rolled: %d and %d. \n", diceVal1, diceVal2);
                                                printf("Please proceed to tile %d.\n\n", playerTile[i]);
                                        }
                                }

                                //Gets the tile before the object is rolled to determine distance traveled by object.
                                tileNoObject = playerTile[i];

                                //Player should not get an object if they get a double five, if they win, or if they are on tile 0.
                                if (((diceVal1 != 5) || (diceVal2 != 5)) && playerTile[i] != 100  && playerTile[i] != 0)
                                        playerTile[i] = whatObject(diceVal3, playerTile[i], prevTile,
                                                                   doggoCtr, ladderCtr, slideCtr, uturnCtr,
                                                                   i);

                                //Update the integer sequence once everything is done
                                sequence = updateSequence(sequence, playerCount);

                                //Calculates the distance the object traveled.
                                if ((playerTile[i] >= tileNoObject) && (diceVal3 >= 1 && diceVal3 <= 4))
                                        distance = playerTile[i] - tileNoObject;

                                else if((playerTile[i] <= tileNoObject) && (diceVal3 >= 1 && diceVal3 <= 4))
                                        distance = tileNoObject - playerTile[i];

                                //highesttravel updates if the distance is bigger.
                                //farthest[] stores the object that caused the player to move the farthest.
                                if ((distance >= highesttravel[i]) && (diceVal3 >= 1 && diceVal3 <= 4)) {
                                        highesttravel[i] = distance;
                                        farthest[i] = diceVal3;
                                }

                                j = i; //j is going to be used outside the loop later to display game summary.

                                if (playerTile[i] == 100) {
                                        winner = players[i];

                                        //equate i to playerCount to end the loop
                                        i = playerCount;

                                        //To determine winning move
                                        winningD1 = diceVal1;
                                        winningD2 = diceVal2;
                                        winningD3 = diceVal3;

                                }

                                //Display round end details
                                if (i+1 == playerCount) {
                                        rnd++;
                                        printf("\nRound %d has ended. \n", rnd);
                                        printf("Would you like to display the board (Y/N)? ");
                                        scanf(" %c", &brdAns);

                                        if (brdAns == 'Y' || brdAns == 'y')
                                                displayBoard(players, playerTile, playerCount);

                                        printf("\nWould you like to display the ranking (Y/N)? ");
                                        scanf(" %c", &rnkAns);

                                        if (rnkAns == 'Y' || rnkAns == 'y')
                                                displayRanking(players, playerTile, playerCount);
                                }
                        }
                } while (winner == 0);
                //When there is a winner, display game summary
                displayGameSummary(winner, doggoCtr, ladderCtr, slideCtr, uturnCtr,
                                   farthest, j, prevTile, winningD1, winningD2, winningD3);

                //Ask if user wants to play again
                printf("\n\nWould you like to play again (Y/N)? ");
                scanf(" %c", &ans);

        } while (ans == 'Y' || ans == 'y');

        printf("Hope you enjoyed Doggos, Ladders, Slides, and U-Turns! ");
        printf("Thank you for playing! :D");

        return 0;
}
