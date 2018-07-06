#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PLID TicTacToe->Player   //Define PLID to meet the format of the code in H61CAE UNNC_1718 project_2017.pdf
#define A TicTacToe.PlayerScore[0]    //Define A to meet the format of the code in H61CAE UNNC_1718 project_2017.pdf
#define B TicTacToe.PlayerScore[1]    //Define B to meet the format of the code in H61CAE UNNC_1718 project_2017.pdf
#define StateMax 6//the maximum board size if 6*6
typedef struct TicTacToe//define a TicTacToe structure data type to store board type, state of board, current player, players' score, movement position and round counter.
{
    int BoardType;//an integer number to store board type
    char State[StateMax][StateMax];//two-dimensional array to store the states of every position
    int Player;//a flag of the current player, in this case, 1 and 2.
    int PlayerScore[2];//one-dimensional array to store the score of players. The first element is the first player and the second is the second player.
    int MovementPosition[2];//one-dimensional array to store the current input position. The first element is the row and the second is the column.
    int RoundCounter;//an integer number to store board type
} TicTacToe;
typedef enum bool {FALSE=0,TRUE} bool;//Define a bool data type. The FALSE element is zero and TURE element is one.
void ClearBuffer();//The function to clear the buffer of stdin to avoid the wrong input. No input. No return value.
void BoardDawing( TicTacToe *TicTacToe );//The function to draw the board. Input: a TicTacToe structure pointer. No return value
int ResultChecking( TicTacToe *TicTacToe );//The function to check whether the winning or tie condition occur. Input: a TicTacToe structure pointer. Return: if the winner occur return 0 to break the loop, else return 1.
bool ResultCheckingDiagonal(TicTacToe *TicTacToe);//The function to check whether diagonal direction occurs the winning condition. Input: a TicTacToe structure pointer. Return: if the winner occur return TRUE, else return FALSE.
bool ResultCheckingLine(TicTacToe *TicTacToe);//The function to check whether horizontal and vertical direction occurs the winning condition. Input: a TicTacToe structure pointer. Return: if the winner occur return TRUE, else return FALSE
bool ResultCheckingTie(TicTacToe *TicTacToe);//The function to check whether the tie condition occur. Input: a TicTacToe structure pointer. Return: if the tie condition occur return TRUE, else return FALSE.
void SelectTheBoardOptions(TicTacToe *TicTacToe);//Prompt the player to select the board options and get the board size information from the user. Keep prompting the player to enter the board size information until a valid board size is entered. Input: a TicTacToe structure pointer. No return value
void InitialBoard( TicTacToe *TicTacToe);//Create the initialize board for the game to start. Input: a TicTacToe structure pointer. No return value.
void MovementDestination(TicTacToe *TicTacToe);//Prompt the players to make a move and change the State array of TicTacToe structure according to input. Input: a TicTacToe structure pointer. No return value
int PlayAgainChoice();//Ask if the user wants to play again. No input. Return: If the user enters 'y' or 'Y', return 1, else return 0 to break the loop.
//function main beginning programming execution.
int main()
{
    TicTacToe TicTacToe={0,{{0}},1,{0},{0},0};//Define and initialize the TicTacToe structure.
    printf("Welcome to play the game!\n"); //Display the exact welcome message "Welcome to play the game!" at the beginning of the game.
    SelectTheBoardOptions(&TicTacToe);//Get the board size information from the user.
    do
    {
    InitialBoard(&TicTacToe);//Clear the screen and create the initial board for the game to start.
    BoardDawing( &TicTacToe );//Draw the board and the display needs to follow the given example.
        do
        {
        MovementDestination(&TicTacToe);//Decide movement destination beginning from player 1 and the 2 player take turns to enter movement destination.
        }while(ResultChecking(&TicTacToe));//Check if a winning or a tie situation can be determined.
    }while(PlayAgainChoice());//If a winning condition or tie condition can be determined,ask if the user wants to play again.
    printf("\nThe final score is %d - %d", A, B);//Display actual scores of player 1 and player 2.
    printf("\nThanks for playing this game!");//display the exact message “Thanks for playing this game!” and terminate the program.
    return 0;
}//end main
void ClearBuffer()//Clear the buffer of stdin
{
    char c;//declare a character to store the input
    while((c = getchar()) != '\n' && c != EOF);//get character until the input is '\n' or EOF
}
void BoardDawing( TicTacToe *TicTacToe )//The function to draw the board.
{
    int i,j;//declare counters
    system("cls");//clear the screen
    printf("\n\n     %dx%d Tic Tac Toe\n\n",TicTacToe->BoardType,TicTacToe->BoardType);//print title of the board.
    printf("Player 1 (O)  -  Player 2 (X)\n\n\n");//print the player information.
    for(i=0;i<TicTacToe->BoardType;i++)//the outer loop to count the row index.
    {
        for(j=0;j<TicTacToe->BoardType;j++)//The first inner loop to print the first line for every State array element in the TicTacToe structure.
        {
            if(j==TicTacToe->BoardType-1)
                {printf("     ");}//printed condition for the last element
            else
                {printf("     |");}//printed condition for the other elements
        }puts("");//print a new line for the second line.
        for(j=0;j<TicTacToe->BoardType;j++)//The second inner loop to print the second line for every State array element in the TicTacToe structure.
        {
            if((TicTacToe->State[i][j]!='X')&&(TicTacToe->State[i][j]!='O'))//
            {//the condition for the i th row j th column State element in TicTacToe structure is neither 'X' nor 'O'.
                if(j!=TicTacToe->BoardType-1)
                    {printf("  %-2d |",(int)(TicTacToe->State[i][j]));}//printed condition for the other elements
                else
                    {printf("  %-2d ",(int)(TicTacToe->State[i][j]));}//printed condition for the last element
            }
            else
            {//the condition for the i th row j th column State element in TicTacToe structure is 'X' or 'O'.
                if(j!=TicTacToe->BoardType-1)
                    {printf("  %c  |",(TicTacToe->State[i][j]));}//printed condition for the other elements
                else
                    {printf("  %c  ",(TicTacToe->State[i][j]));}//printed condition for the last element
            }
        }puts("");//print a new line for the third line.
        for(j=0;j<TicTacToe->BoardType;j++)//The third inner loop to print the third line for every State array element in the TicTacToe structure.
        {
            if(j==TicTacToe->BoardType-1)
            {//printed condition for the third line of the element of the last line
                if(i!=TicTacToe->BoardType-1)
                    {printf("_____");}//printed condition for the last element of the line except the last line
                else
                    {printf(" ");}//printed condition for the last element of last line
            }
            else
            {//printed condition for the third line of the element other than last line
                if(i==TicTacToe->BoardType-1)
                    {printf("     |");}//printed condition for the last line
                else
                    {printf("_____|");}//printed condition for the other element of the line
            }
        }puts("");//print a new line for the next loop.
    }puts("");//print a new line to meet the given format.
}
bool ResultCheckingDiagonal(TicTacToe *TicTacToe)//The function to check whether diagonal direction occurs the winning condition.
{
    int i=0;//counter
    int number=1;//initialize the number to 1 to count the 'O' or 'X' according to players in diagonally.
    //the first step : check and count the number of 'O' or 'X' according to players in downward diagonally to the right direction.
    for(i=1;((TicTacToe->MovementPosition[1]+i)<TicTacToe->BoardType)&&((TicTacToe->MovementPosition[0]+i)<TicTacToe->BoardType)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i++)
    {//check the element one by one in downward diagonally to the right direction until the element index is in outside of the board which means movement position must smaller than board type or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])+i][(TicTacToe->MovementPosition[1])+i]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in  downward diagonally to the right direction, the count number plus one.
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop.
    }
    //the second step : check and count the number of 'O' or 'X' according to players in direction of upward diagonally to the left.
    for(i=-1;((TicTacToe->MovementPosition[0]+i)>=0)&&((TicTacToe->MovementPosition[1]+i)>=0)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i--)
    {//check the element one by one in upward diagonally to the left direction until the element index is in outside of the board which means movement position must geater than 0 or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])+i][(TicTacToe->MovementPosition[1])+i]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in upward diagonally to the left direction, the count number plus one
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop
    }
    if(number>=((TicTacToe->BoardType==3)?3:4))
    {//The condition for winning is the counted number greater or equals to board type when the board type is less than 4 and the counted number greater or equals to 4 when the board type is greater than 4.
        return TRUE;
    }
    //the case for the last winning condition was unable to reach.
    number=1;//initialize the number to 1 again to count for the next step.
    //the third step : check and count the number of 'O' or 'X' according to players in upward diagonally to the right direction.
    for(i=1;(((TicTacToe->MovementPosition[0])-i)>=0)&&(((TicTacToe->MovementPosition[1])+i)<TicTacToe->BoardType)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i++)
    {//check the element one by one in upward diagonally to the right direction until the element index is in outside of the board which means the first movement position index must greater than 0 and the second movement position index must smaller than board type or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])-i][(TicTacToe->MovementPosition[1])+i]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in upward diagonally to the right direction, the count number plus one
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop
    }
    //the forth step : check and count the number of 'O' or 'X' according to players in downward diagonally to the left direction.
    for(i=-1;(((TicTacToe->MovementPosition[1])+i)>=0)&&(((TicTacToe->MovementPosition[0])-i)<TicTacToe->BoardType)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i--)
    {//check the element one by one in downward diagonally to the left direction until the element index is in outside of the board which means the first movement position index must greater than 0 and the second movement position index must smaller than board type or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])-i][(TicTacToe->MovementPosition[1])+i]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in downward diagonally to the left direction, the count number plus one
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop
    }
    if(number>=((TicTacToe->BoardType==3)?3:4))
    {
        return TRUE;//The condition for winning is the counted number greater or equals to board type when the board type is less than 4 and the counted number greater or equals to 4 when the board type is greater than 4.
    }else
    {
        return FALSE;//If the no winning condition occurred return FALSE
    }
}
bool ResultCheckingLine(TicTacToe *TicTacToe)//The function to check whether horizontal and vertical direction occurs the winning condition.
{
    int i=0;//counter
    int number=1;//initialize the number to 1 to count the 'O' or 'X' according to players in diagonally.
    for(i=1;(((TicTacToe->MovementPosition[1])+i)<TicTacToe->BoardType)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i++)
    {//check the element one by one in horizontally to the right direction until the element index is in outside of the board which means the second movement position index must smaller than board type or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])][(TicTacToe->MovementPosition[1])+i]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in horizontally to the right direction, the count number plus one
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop
    }
    for(i=-1;(((TicTacToe->MovementPosition[1])+i)>=0)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i--)
    {//check the element one by one in horizontally to the left direction until the element index is in outside of the board which means the second movement position index must smaller than board type or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])][(TicTacToe->MovementPosition[1])+i]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in horizontally to the left direction, the count number plus one
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop
    }
    if(number>=((TicTacToe->BoardType==3)?3:4))
    {
        return TRUE;//The condition for winning is the counted number greater or equals to board type when the board type is less than 4 and the counted number greater or equals to 4 when the board type is greater than 4.
    }
    number=1;//initialize the number to 1 again to count for the next step.
    for(i=1;(((TicTacToe->MovementPosition[0])+i)<TicTacToe->BoardType)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i++)
    {//check the element one by one in vertically to the upward direction until the element index is in outside of the board which means the first movement position index must smaller than board type or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])+i][(TicTacToe->MovementPosition[1])]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in vertically to the upward direction, the count number plus one.
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop
    }
    for(i=-1;(((TicTacToe->MovementPosition[0])+i)>=0)&&(!(number>=((TicTacToe->BoardType==3)?3:4)));i--)
    {//check the element one by one in vertically to the upward direction until the element index is in outside of the board which means the first movement position index must greater than 0 or the winning condition occurred.
        if(TicTacToe->State[(TicTacToe->MovementPosition[0])+i][(TicTacToe->MovementPosition[1])]==((TicTacToe->Player==2)?'O':'X'))
            {number++;}//if there are adjacent 'O' or 'X' in vertically to the upward direction, the count number plus one.
        else
            {break;}//if there are not adjacent 'O' or 'X', break the loop
    }
    if(number>=((TicTacToe->BoardType==3)?3:4))
    {
        return TRUE;//The condition for winning is the counted number greater or equals to board type when the board type is less than 4 and the counted number greater or equals to 4 when the board type is greater than 4.
    }
    else
    {
        return FALSE;//If the no winning condition occurred return FALSE
    }
}
bool ResultCheckingTie(TicTacToe *TicTacToe)//The function to check whether the tie condition occurs.
{
    if(TicTacToe->RoundCounter==(TicTacToe->BoardType)*(TicTacToe->BoardType)){return TRUE;}//If the round counter is equals to the total number of elements, the tie condition occurs and the function will return true.
    else {return FALSE;}//If the tie condition haven't occurred, return FALSE
}
int ResultChecking( TicTacToe *TicTacToe )//The function to check whether the winning or tie condition occur.
{
    if(ResultCheckingDiagonal(TicTacToe)==TRUE||ResultCheckingLine(TicTacToe)==TRUE)//For winning condition, the ResultCheckingDiagonal function or ResultCheckingLine function will return TRUE
    {
        TicTacToe->Player=(TicTacToe->Player==1)?2:1;//Change the player flag. Because the MovementDestination function will change the flag for each move.
        printf("\nPlayer %d wins!",PLID);//Print the winner information.
        TicTacToe->PlayerScore[TicTacToe->Player-1]+=1;//Add one score for winner.
        return 0;//return 0 to break the loop
    }else if(ResultCheckingTie(TicTacToe)==TRUE)//For tie condition, the ResultCheckingTie function will return TRUE.
    {
        printf("\nA tied game!");//Print the tie information.
        return 0;//return 0 to break the loop.
    }else
        {return 1;}////return 1 to continue the game.
}
void SelectTheBoardOptions(TicTacToe *TicTacToe)//The function to prompt the player to select the board options and get the board size information from the user.
{
    char input[3]={0};//declare the character array to store input and initialize to 0.
    do{
    printf("Please choose the board size from 3 to 6: ");//Prompt the player to select the board options
    scanf("%2s",input);//Get the board size information from the user.
    ClearBuffer();//Clear the buffer.
    }while('3'>input[0]||input[0]>'6'||input[1]!='\0');//If the input is not 3, 4, 5 or 6, keep prompting the player to enter the board size information until a valid board size is entered.
    TicTacToe->BoardType=input[0]-'0';//Converts input character to integer and give the integer to BoardType element of TicTacToe structure.
}
void InitialBoard(TicTacToe* TicTacToe)//Create the initialize board for the game to start.
{
    int i=0,row,col;//counter
    TicTacToe->Player=1;//Initialize the player
    TicTacToe->RoundCounter=0;//Initialize the round counter
    for(row=0;row<(TicTacToe->BoardType);row++)
    {
        for(col=0;col<(TicTacToe->BoardType);col++)
        {
            TicTacToe->State[row][col]=i;//initialize every element of the State array of TicTacToe structure from 0.
            i++;//counter plus one for the next element of array.
        }
    }
}
void MovementDestination(TicTacToe *TicTacToe)//Prompt the players to make a move and change the State array of TicTacToe structure according to input.
{//The input from user is first stored to an array and then converted to integer so that it will be easier to judge the decimals or other invalid input.
    int input=0,i;//Declare an integer to store input and declare a counter.
    char inputchar[3]={0};//Declare an array to store input
    printf("Player %d, enter a number: ",PLID);//Prompt the players to make a move.
    scanf("%3s",inputchar);//Get the input of the first two element to character array.
    ClearBuffer();//Clear buffer
    for(i=0;inputchar[i]!='\0';i++)
    {
        input=input*10+(inputchar[i]-'0');//Convert the input character to integer.
    }
    //Invalid input condition are the inputted position has already be inputted and the input is not a integer which means the the length of inputchar array is not less then 3, each input element not greater than '0' or less than '9' and the second character is not '\0' when only one character input.
    //Therefore, the code first judge the length and the whether the input is an integer and the it will judge whether the inputted position has already be inputted.
    while(((strlen(inputchar)<3)&&(((inputchar[1]=='\0')||((inputchar[1]<='9')&&(inputchar[1]>='0')))&&(inputchar[0]<='9')&&(inputchar[0]>='0')))? (TicTacToe->State[input/(TicTacToe->BoardType)][input%(TicTacToe->BoardType)])!=input:1 )
    {
        input=0;//Clear the input.
        printf("Invalid move! Player %d, enter a number: ", PLID);//Prompt the players to make a move, again.
        scanf("%3s",inputchar);//Get the input of the first two element to character array.
        ClearBuffer();//Clear the buffer
        for(i=0;inputchar[i]!='\0';i++)
        {
            input=input*10+(inputchar[i]-'0');//Convert the input character to integer.
        }
    }
    TicTacToe->MovementPosition[0]=input/(TicTacToe->BoardType);//Get the position value to MovementPosition of TicTacToe structure.
    TicTacToe->MovementPosition[1]=input%(TicTacToe->BoardType);//Get the position value to MovementPosition of TicTacToe structure.
    TicTacToe->State[TicTacToe->MovementPosition[0]][TicTacToe->MovementPosition[1]]=(TicTacToe->Player==1)?'O':'X';//Change the State array of TicTacToe structure according to input.
    TicTacToe->Player=(TicTacToe->Player==1)?2:1;//Change the player flag.
    TicTacToe->RoundCounter++;//The round number add one
    BoardDawing( TicTacToe );//Draw the board.
}
int PlayAgainChoice()//The function to ask if the user wants to play again.
{
    char PlayAgainChoice='N';//Declare a character variable and initialize it to 'N'
    printf("\nPlay again? ");//Ask if the user wants to play again.
    while((PlayAgainChoice=getchar())=='\n');//Get the input except '\n'.
    ClearBuffer();//Clear the buffer.
    return (PlayAgainChoice=='Y'||PlayAgainChoice=='y');//If the first input of the character except '\n' is 'y' or 'Y', return 1 to start a new game.
}
