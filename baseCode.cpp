#include<bits/stdc++.h>
using namespace std;

char playersign, aisign;
int playerturn;
char player, opponent;
int BOARD_SIZE = 3;
char EMPTY_CELL = '_';

 vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, EMPTY_CELL));
void playermove(){
    cout << endl;
    cout << endl;
    cout << "your turn! enter row and column number (1 base indexing) \n";
    int row,col;
    while(1)
    {
        cin >> row >> col;
        if(row<0 || row>3 || col<0 || col>3) 
        cout << "wrong row or column number, enter again!\n";
        
        
         else if(board[row-1][col-1]!='_')
         cout << "wrong cell choosen, enter again\n";
         
         else break;
        
    }
    
    board[row-1][col-1] = playersign;
    for(int i=0;i<3;i++){
       for(int j=0;j<3;j++){
           cout << board[i][j] << " ";
       }
       cout << endl;
      
   }
    playerturn = 2;
}



 struct Move
{
    int row;
    int col;
};

bool checkWin(const vector<vector<char>>& board, char player)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

bool isBoardFull(const vector<vector<char>>& board)
{
    for (const auto& row : board)
    {
        for (char cell : row)
        {
            if (cell == EMPTY_CELL)
                return false;
        }
    }
    return true;
}

int minimax(vector<vector<char>>& board, int depth, bool isMaximizing)
{
    char PLAYER_X = aisign;
    char PLAYER_O = playersign;
    if (checkWin(board, PLAYER_X))
        return 10 - depth;
    if (checkWin(board, PLAYER_O))
        return depth - 10;
    if (isBoardFull(board))
        return 0;

    int bestScore = isMaximizing ? INT32_MIN : INT32_MAX;
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (board[i][j] == EMPTY_CELL)
            {
                board[i][j] = isMaximizing ? PLAYER_X : PLAYER_O;
                int score = minimax(board, depth + 1, !isMaximizing);
                board[i][j] = EMPTY_CELL;
                bestScore = isMaximizing ? max(bestScore, score) : min(bestScore, score);
            }
        }
    }
    return bestScore;
}
Move findBestMove()
{
    vector<vector<char>> tempBoard = board;
    int bestScore = INT32_MIN;
    Move bestMove{-1, -1};

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j)
        {
            if (tempBoard[i][j] == EMPTY_CELL)
            {
                tempBoard[i][j] = aisign;
                int score = minimax(tempBoard, 0, false);
                tempBoard[i][j] = EMPTY_CELL;
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}


void aimove(){
      cout << endl << endl;
      cout << "wait, AI's turn now: \n";
      Move bestMove = findBestMove();
     // cout << bestMove.row << " " << bestMove.col << endl;
      board[bestMove.row][bestMove.col] = aisign;
      
     
       
       for(int i=0;i<3;i++){
       for(int j=0;j<3;j++){
           cout << board[i][j] << " ";
       }
       cout << endl;
   }
    cout << endl;
      
    playerturn = 1;
}
void playgame()
{
    if(playerturn ==1) playermove();
    else aimove();
}
bool gameresult(const vector<vector<char>>& board, char player)
{
    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}

void setup()
{
    for(int i=0;i<3;i++){
       for(int j=0;j<3;j++){
           board[i][j]='_';
       }
      
   }
    
    
   cout << "We are playing tic-tac-toe" << endl << endl;
   
   cout << "Initial board:\n";
   for(int i=0;i<3;i++){
       for(int j=0;j<3;j++){
           cout << board[i][j] << " ";
       }
       cout << endl;
   }
   cout << endl;
   
  
   cout << "Choose your sign, either O (Capital O) or  X (Capital X)" << endl;
  
   while(1){
       cin >> playersign;
   if(playersign !='O' && playersign !='X'){
       cout << "wrong sign choosen, choose again!\n";
   }
   else break;
   }
   cout << "you choose " << playersign;
  
   if(playersign =='O') aisign = 'X';
   else aisign = 'O';
   cout << " so AI has choosen " << aisign << endl << endl;
   
   player = playersign;
   opponent = aisign;
   
   cout << "Enter 1 to play first, enter 2 to play second\n";
   
   while(1)
   {
       cin >> playerturn;
       if(playerturn!=1 && playerturn !=2) {
           cout << "wrong command, enter again!\n";
       }
       else break;
   }
   
   while(1)
   {
       playgame();
       
       
       
       bool f = gameresult(board, aisign);
       if(f){
           cout << "AI has won!\n";
           break;
       }
       f = gameresult(board, playersign);
        if(f){
           cout << "you have won the game!\n";
           break;
       }
       f = isBoardFull(board);
       if(f){
           cout << "no winner is found, game is drown!";
           break;
       }
       
   
   }
   
   cout << "\n game finished!";
}


int main()
{
    setup();
    
   
}