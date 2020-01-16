#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stddef.h>

using namespace std;

//This function initializes the GAME
void ClearMatrix(char M[][3]){
    for(int i = 0;i < 3; i++){
        for(int j = 0; j < 3; j++){
            M[i][j] = '_';
        }
    }
}

//This function is to print the progress of the game after each move
void PrintMatrix(char M[][3]){
    for(int i = 0; i<3 ; i++){
        for(int j = 0; j<3 ; j++){
            cout<<M[i][j]<<"\t";
        }
        cout<<"\n\n";
    }
}

/*RANDOM CORNER GENERATOR*/

/*
This generator will give you a position array whose first element will be the row and second element
will be the column of the empty random position.If random position is not available it will return the NULL value
*/
int *RandomCornerGenerator(char M[][3]){
    srand(time(NULL));//So that the random values do not start of from the same value
    static int posArray[2];//An array in which first element will be row number and second will be column number
    bool posFound = false;//Boolean value declared to break out of double for loop
    int i = rand()%3;//Random value between 0 and 2
    posArray[0] = (i==1)?(i+1):i;// 1 is discarded
    i = rand()%3;
    posArray[1] = (i==1)?(i+1):i;
    //check whether position is empty, if not, check iteratively for an empty position in all corners
    if(M[posArray[0]][posArray[1]] != '_'){
        for(int j = 0; j<3 ; j = j+2){
            for(int k = 0; k<3 ; k = k+2){
                if(M[j][k] == '_'){
                    posArray[0] = j;
                    posArray[1] = k;
                    posFound = true;
                    break;
                }
            }
            if(posFound == true)
                break;
        }
    }
    //if no empty corner is found return NULL
    if(M[posArray[0]][posArray[1]] != '_' && posFound == false){
        return NULL;
    }
    else{
        return posArray;//else return the posArray containing required corner
    }
}

/*
    When no move works this move will be called and its logic is empirical
*/

bool randomMove(char M[][3]){
    //boolean value to check whether move was done or not
    bool moveDone = false;
    //pointer to hold position of random corner
    int *randomCornerPosition;
    randomCornerPosition = RandomCornerGenerator(M);
    if(randomCornerPosition == NULL){
        //NULL indicates that no corner is empty hence we find the next empty position iteratively
        for(int i = 0; i<3 ;i++){
            for(int j = 0; j<3 ;j++){
                if(M[i][j] == '_'){
                    M[i][j] = 'X';
                    moveDone = true;
                    break;
                }
            }
            if(moveDone == true)
                break;
        }
    }
    else{
        //if a random corner was returned
        M[randomCornerPosition[0]][randomCornerPosition[1]] = 'X';
        moveDone = true;
    }
    //return the truth of whether the move was done or not
    return moveDone;
}

/*
    This function can be used for the following two purposes

        1. If 'X' is the character passed to the function and if there are two X's in a row, column or diagonal,
        it will insert an X in the third position if empty and reach the win condition

        2. If 'O' is the character passed to this function, and if there are two O's in a row, column or diagonal
        then it will oppose it by adding an 'X' in the empty position, if any and the GAME moves forward.
*/

bool OpposeAssist(char insertedMove, char M[][3]){
    //this variable keeps track of the number of insertedMove characters encountered.
    int check = 0;
    //this character flag keeps track of the empty position for a move
    char flag = '_';
    //This boolean variable will ensure whether insertedMove was entered or not
    bool moveDone = false;

    /*******
    FOR ROWS
    ********/

    //Check for rows: i changes the rows, j changes the columns
    for(int i = 0; i<3; i++){
        //before every row-check initialize check to 0
        check = 0;
        flag = '_';
        for(int j = 0; j<3 ;j++){
            if( M[i][j] == insertedMove && check == 0)
                check++;    //first insertedMove character encountered
            else if( M[i][j] == insertedMove && check == 1)
                check++;    //second insertedMove character encountered
            if( M[i][j] != insertedMove && M[i][j] != '_')
                flag = 'N';     //No empty space for opposition or assisting
        }
        //check whether insertedMove character should be entered
        if( check == 2 && flag != 'N'){
            for(int j = 0; j<3 ; j++){
                if(M[i][j] == '_'){
                    M[i][j] = 'X';
                    moveDone = true;
                    break;
                }
            }
        //if the move was done in one of the rows break through the row checking
        if( moveDone == true)
            break;
        }
    }
    //after checking is complete, if insertedMove has been entered return true
    if(moveDone == true)
        return moveDone;

    /**********
    FOR COLUMNS
    ***********/

    //reinitialize variables for use with columns
    check = 0;
    flag = '_';

    //Check for columns: i changes the rows, j changes the columns
    for(int j = 0; j<3; j++){
        //before every column-check initialize check to 0
        check = 0;
        flag = '_';
        for(int i = 0; i<3 ;i++){
            if( M[i][j] == insertedMove && check == 0)
                check++;    //first insertedMove character encountered
            else if( M[i][j] == insertedMove && check == 1)
                check++;    //second insertedMove character encountered
            if( M[i][j] != insertedMove && M[i][j] != '_')
                flag = 'N';     //No empty space for opposition or assisting
        }
        //check whether insertedMove character should be entered
        if( check == 2 && flag != 'N'){
            for(int i = 0; i<3 ; i++){
                if(M[i][j] == '_'){
                    M[i][j] = 'X';
                    moveDone = true;
                    break;
                }
            }
        //if the move was done in one of the columns break through the column checking
        if( moveDone == true)
            break;
        }
    }
    //after checking is complete, if insertedMove has been entered return true
    if(moveDone == true)
        return moveDone;

    /********************
    FOR DIAGONAL CHECKING
    *********************/

    /********************
    LEFT->RIGHT DIAGONAL
    *********************/

    //initialize checking variables to zero
    check = 0;
    flag = '_';
    //checking left->right diagonal
    for(int i = 0; i<3 ;i++){
        if( M[i][i] == insertedMove && check == 0)
            check++;    //first insertedMove character encountered
        else if( M[i][i] == insertedMove && check == 1)
            check++;    //second insertedMove character encountered
        if( M[i][i] != insertedMove && M[i][i] != '_')
            flag = '_';     //character cannot be inserted due to lack of empty space
    }
    //check whether character can be inserted
    if(check == 2 && flag != 'N'){
        for(int i = 0; i<3 ; i++){
            if(M[i][i] == '_'){
                M[i][i] = 'X';
                moveDone = true;
                break;
            }
        }
    }
    //If insertedMove character gets inserted then return true
    if(moveDone == true){
        return moveDone;
    }

    /************************
    FOR RIGHT->LEFT DIAGONAL
    *************************/

    //initialize variables
    check = 0;
    flag = '_';
    //check the right->left diagonal
    for(int i = 0; i < 3; i++ ){
        if(M[i][2-i] == insertedMove && check == 0)
            check++;    //insertedMove encountered for the first time
        else if (M[i][2-i] == insertedMove && check == 1)
            check++;    //insertedMove encountered for the second time
        if(M[i][2-i] != insertedMove && M[i][2-i] != '_')
            flag = 'N';     //No empty space to enter the inserted move
    }
    //check whether insertedMove can be entered
    if(check == 2 && flag == 'N'){
        for(int i = 0; i<3 ; i++){
            if(M[i][2-i] == '_'){
                M[i][2-i] = 'X';
                moveDone = true;
                break;
            }
        }
    }
    //if the insertedMove character has been entered then return true
    if(moveDone == true){
        return moveDone;
    }

    //Everything was checked but no opposition or assisting could be done then return false
    return moveDone;
}

    /***********************
    CHECK MATRIX FOR VICTORY
    ************************/
//This function returns true or false based on the character passed

bool victory(char M[][3],char victoryChar){
    int victoryCharCount = 0;
    bool victoryCharWins = false;
    //Check for three continuous victoryCharacters in the row. i: changes rows. j: changes columns
    for(int i = 0; i<3 ; i++){
        //zeroing out victoryCharCount before checking each row
        victoryCharCount = 0;
        for(int j = 0; j<3 ; j++){
            if(M[i][j] == victoryChar)
                victoryCharCount++;
        }
        if(victoryCharCount == 3){
            victoryCharWins = true;
            break;
        }
    }
    if(victoryCharWins == true){
        return true;
    }


    //Reinitialize variables for column-checking
    victoryCharCount = 0;
    //Check for three continuous victoryCharacters in the column. i: changes rows. j: changes columns
    for(int j = 0; j<3 ; j++){
        //zeroing out victoryCharCount before checking each column
        victoryCharCount = 0;
        for(int i = 0; i<3 ; i++){
            if(M[i][j] == victoryChar)
                victoryCharCount++;
        }
        if(victoryCharCount == 3){
            victoryCharWins = true;
            break;
        }
    }
    if(victoryCharWins == true){
        return true;
    }

    //reinitialize variables for checking left->right diagonal
    victoryCharCount = 0;
    //Check for three continuous victoryCharacters in the left->right diagonal
    for(int i = 0; i<3 ; i++){
        if(M[i][i] == victoryChar)
            victoryCharCount++;
    }
    if(victoryCharCount == 3){
        victoryCharWins = true;
        return true;
    }

    //reinitialize variables for checking right->left diagonal
    victoryCharCount = 0;
    //check for 3 continuous victory characters in the right->left diagonal
    for(int i = 0; i<3 ;i++){
        if(M[i][2-i] == victoryChar)
            victoryCharCount++;
    }
    if(victoryCharCount == 3){
        victoryCharWins = true;
        return true;
    }
    //If it reaches this point, it means that victoryChar hasn't won yet, hence,return false
    return false;
}

void UserMove(char M[][3]){
    int row,col;
    bool moveDone = false;
    while( moveDone != true ){
    cout<<"\nENTER THE ROW AND COLUMN OF PLAYER MOVE:";
    cout<<"\nRow: ";
    cin>>row;
    cout<<"\nColumn: ";
    cin>>col;
        if(M[row-1][col-1] == '_'){
            M[row-1][col-1] = 'O';
            moveDone = true;
        }
        else{
            cout<<"\nINVALID MOVE!"<<endl;

        }
    }
}

int main()
{
    //the Main matrix
    char TicTacToe[3][3];
    //variables to keep track of code and user moves
    int codeMoveNumber = 0;
    int userMoveNumber = 0;
    //victory variables for X and O
    bool victoryX,victoryO;
    victoryO = victoryX = false;
    //variable to hold the status of move done or not
    bool moveDone = false;
    cout<<"\nBEGIN THE GAME OF TIC-TAC-TOE"<<endl;
    //Empty the matrix and print it
    ClearMatrix(TicTacToe);
    PrintMatrix(TicTacToe);
    for(int i = 0; i<=5 ;i++){
        codeMoveNumber++;
        if(codeMoveNumber<3){
            //This is to fill a corner randomly
            moveDone = randomMove(TicTacToe);
        }
        else{
            //here codeMoveNumber is 3,4,or 5
            moveDone = OpposeAssist('X',TicTacToe);
            if(moveDone!=true){
                moveDone = OpposeAssist('O',TicTacToe);
                if(moveDone!=true){
                    moveDone = randomMove(TicTacToe);
                }
            }
        }
        //check victory of X
        victoryX = victory(TicTacToe,'X');
        if(moveDone == true){
            cout<<"\nCOMPUTER MOVE"<<endl;
            PrintMatrix(TicTacToe);
            if(victoryX == true){
                cout<<"\nTHE COMPUTER HAS WON!";
                break;
            }
        }
        else{
            cout<<"\nERROR IN CODE!";
        }
        if(codeMoveNumber==5 && victoryX == false){
            cout<<"\nTHE GAME WAS DRAWN!";
            break;
        }
        //User Move
        UserMove(TicTacToe);
        victoryO = victory(TicTacToe,'O');
        userMoveNumber++;
        cout<<"\nUSER MOVE:"<<endl;
        PrintMatrix(TicTacToe);
        if(victoryO == true){
            cout<<"\nTHE USER HAS WON!";
        }
    }
    return 0;
}
