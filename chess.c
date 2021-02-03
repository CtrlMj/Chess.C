////////////////////////////////////////////////////////////
//////////////////// CHESS PROJECT /////////////////////////
//////////////////// Written By : //////////////////////////
/////////////////// Kiarash Abbasi /////////////////////////
///////////////////////// & ////////////////////////////////
////////////////// Majid Alikhani //////////////////////////
///////// Any Copy Will Lead To Prosecution ! //////////////
////////////////////////////////////////////////////////////

/////////////////////
//System Libraries
/////////////////////

#include <stdio.h>
#include <math.h>

/////////////////
// Defines
/////////////////

#define MAKE_PIECE(T,X,Y) (T.color=X,T.kind=Y)
#define BOARD_SIZE 8

/////////////////
// Structure 
/////////////////

typedef struct
{
    int hasMoved; // For Controlling Castle - King Move .
    int enpassent; // For Controlling Enpassent .
    int threated; //0 For Threated, !0 Not Threated.
	char color; //W,B 'O' For Nothing .
	char kind; //r -> Rook ,k->Knight(lowercase) ,b-> Bishop ,q-> Queen ,K-> King(uppercase) ,p-> Pawn; 'O' For Nothing .
}piece;

/////////////////////////////
// Function Prototypes
////////////////////////////

void startingBoard();
void showBoard();
int gameIsFinished(int);
int isValidPiece(int x,int y,int player);
void markThreatedLocations(int,int);
void unmarkThreatedLocations();
void makeMove(int,int,int,int);

int charToLocation(char);
int isValidLocation(int);

//////////////////////
//Global Variables
//////////////////////

piece board[BOARD_SIZE][BOARD_SIZE];
piece emptyCell;
int isCastleMove;


int main()
{
    int player=0;
    startingBoard();
    char temp;
    while (!gameIsFinished(player))
    {
        unmarkThreatedLocations();
        showBoard();
        int x1=-1,y1=-1,x2=-1,y2=-1;
        do
        {
            printf("Enter Your Beginning Coordinate : Player -> %c \n",(player==0) ? 'W' : 'B');
            char a,b;
            scanf("%c%c%c",&a,&b,&temp);
            x1=charToLocation(a);
            y1=charToLocation(b);
        }while(!isValidLocation(x1) || !isValidLocation(y1) || !isValidPiece(x1,y1,player));
        
        int canceled=0;
        isCastleMove=0;
        markThreatedLocations(x1,y1);
        int t=0;
        int i , j ;
        for ( i=0;i<BOARD_SIZE;++i)
            for (j=0;j<BOARD_SIZE;++j)
            {
                if (board[i][j].threated==1)
                    t++;
            }
        if (t==0)
            continue;
        
        showBoard();
        
        do
        {
            printf("Enter Your Final Coordinate Or Enter \"cancel \" \n");
            char c,d;
            scanf("%c%c%c",&c,&d,&temp);
            
            if (c=='c' && d=='a')
            {
                canceled=1;
                unmarkThreatedLocations();
                do {
                    scanf("%c",&temp);
                } while (temp!='\n');
                break;
            }
            
            else
            {
                x2=charToLocation(c);
                y2=charToLocation(d);
            }
            
        } while (!isValidLocation(x2) || !isValidLocation(y2) || !board[x2][y2].threated);
        
        if (canceled==0)
        {
            makeMove(x1,y1,x2,y2);
            player=!player;
        }
    }
    
    printf("Winner  : %c" , (player==0 ) ? 'B':'W');
    printf("%d",temp);
    
}


void startingBoard()
{
    
	MAKE_PIECE(board[0][0],'B','r');
	MAKE_PIECE(board[7][0],'B','r');
	MAKE_PIECE(board[1][0],'B','k');
	MAKE_PIECE(board[6][0],'B','k');
	MAKE_PIECE(board[2][0],'B','b');
	MAKE_PIECE(board[5][0],'B','b');
	MAKE_PIECE(board[3][0],'B','q');
	MAKE_PIECE(board[4][0],'B','K');
	
	MAKE_PIECE(board[0][7],'W','r');
	MAKE_PIECE(board[7][7],'W','r');
	MAKE_PIECE(board[1][7],'W','k');
	MAKE_PIECE(board[6][7],'W','k');
	MAKE_PIECE(board[2][7],'W','b');
	MAKE_PIECE(board[5][7],'W','b');
	MAKE_PIECE(board[3][7],'W','q');
	MAKE_PIECE(board[4][7],'W','K');
    
	int i, j;
    
	for (i=0;i<8;++i)
		MAKE_PIECE(board[i][1],'B','p');
    
	for (i=0;i<8;++i)
		MAKE_PIECE(board[i][6],'W','p');
	
	for (j=2;j<6;++j)
		for (i=0;i<8;++i)
			MAKE_PIECE(board[i][j],'O','O');
    
    for(i=0; i<BOARD_SIZE; i++)
        for(j=0; j<BOARD_SIZE; j++)
        {
            board[i][j].hasMoved=0;
            board[i][j].enpassent=0;
            board[i][j].threated=0;
        }
    
    
    emptyCell.color='O';
    emptyCell.kind='O';
    emptyCell.threated=0;
    emptyCell.hasMoved=0;
    emptyCell.enpassent=0;
    
	return;
}


void showBoard()
{
    printf("  ");
    int j ;
    for ( j=0;j<BOARD_SIZE;++j)
    {
        printf("__%c__",(char)('a'+j));
    }
    printf("\n");
    for (j=0;j<BOARD_SIZE;++j)
    {
        printf("%d ",8-j);
        int i ;
        for ( i=0; i<BOARD_SIZE; ++i)
        {
            if (board[i][j].threated)
            {
                if (board[i][j].color!='O')
                    printf("|*%c%c*",board[i][j].color,board[i][j].kind);
                else
                    printf("|*  *");
                
            }
            
            else if (board[i][j].color !='O')
                printf("| %c%c ",board[i][j].color,board[i][j].kind);
            else
                printf("|    ");
        }
        printf("|\n  ");
        int j ;
        for (j=0;j<BOARD_SIZE;++j)
        {
            printf("_____");
        }
        
        printf("\n");
    }
}


int charToLocation(char c)
{
    if (c>='1' && c<='8')
        return 8-(c-'0');
    return c-'a';
}


int isValidLocation(int t)
{
    return (t>=0 && t<BOARD_SIZE) ? 1 : 0;
}


int isValidPiece(int x,int y,int player)
{
    if (board[x][y].color == 'W' && player==0)
        return 1;
    if (board[x][y].color == 'B' && player!=0)
        return 1;
    return 0;
}


int isKingChecked(int x, int y)
{
    char otherPlayer = (board[x][y].color=='W') ? 'B' : 'W';
    int ret = 0;
    int i , j ;
    for(i=0; i<BOARD_SIZE; i++)
        for(j=0; j<BOARD_SIZE; j++)
        {
            if(board[i][j].color == otherPlayer && board[i][j].kind != 'K')
            {
                markThreatedLocations(i, j);
                if(board[x][y].threated == 1)
                    ret = 1;
            }
            
            if (board[i][j].color==otherPlayer && board[i][j].kind=='K')
            {
                int direction[8][2]={ {-1,-1} , {-1,1} , {1,-1} , {1,1} ,{-1,0} , {1,0} , {0,-1} , {0,1} };
                for (i=0;i<8;++i)
                {
                    int x1=x+direction[i][0];
                    int y1=y+direction[i][1];
                    if (!isValidLocation(x1) || !isValidLocation(y1))
                        continue;
                    board[i][j].threated=1;
                }
            }
            
        }
    return ret;
}


void markThreatedLocationsKing(int x,int y)
{
	int i , j ;
    int isChecked = isKingChecked(x, y);
    int direction[8][2]={ {-1,-1} , {-1,1} , {1,-1} , {1,1} ,{-1,0} , {1,0} , {0,-1} , {0,1} };
    
    int threatedTemp[BOARD_SIZE][BOARD_SIZE];
    for ( i=0;i<BOARD_SIZE;++i)
        for ( j=0;j<BOARD_SIZE;++j)
            threatedTemp[i][j]=0;
  
    int availableMoves=0;
    for ( i=0;i<8;++i)
    {
        int x1=x+direction[i][0];
        int y1=y+direction[i][1];
        if (!isValidLocation(x1) || !isValidLocation(y1))
            continue;
        
        if (!board[x1][y1].threated  && board[x1][y1].color!=board[x][y].color)
        {
            threatedTemp[x1][y1]=1;
            availableMoves++;
        }
    }
    
    if (isChecked && availableMoves==0)
    {
        for ( i=0;i<8;++i)
        {
            int x1=x+direction[i][0];
            int y1=y+direction[i][1];
            if (!isValidLocation(x1) || !isValidLocation(y1))
                continue;
            if (board[x1][y1].threated==0 && board[x1][y1].color==board[x][y].color)
                threatedTemp[x1][y1]=1;
            
        }
    }
    
    if (!board[x][y].hasMoved && !board[x+3][y].hasMoved && board[x+1][y].color=='O' && board[x+2][y].color=='O' && board[x+1][y].threated==0 && board[x+2][y].threated==0)
    {
        isCastleMove=1;
        threatedTemp[x+2][y]=1;
    }
    
    unmarkThreatedLocations();
    
    for ( i=0;i<BOARD_SIZE;++i)
        for ( j=0;j<BOARD_SIZE;++j)
            board[i][j].threated=threatedTemp[i][j];
}


void markThreatedLocationsRook(int x,int y)
{
	int i , j ;
    int direction[4][2]={{1,0},{-1,0} , {0,-1} ,{0,1}};
    for ( i=0;i<4;++i)
    {
        int x1=x;
        int y1=y;
        do
        {
            x1+=direction[i][0];
            y1+=direction[i][1];
            if (!isValidLocation(x1) || !isValidLocation(y1))
                break;
            if (board[x1][y1].color!=board[x][y].color)
                board[x1][y1].threated=1;
            
        }while(board[x1][y1].color=='O');
    }
}


void markThreatedLocationsKnight(int x,int y)
{
	int i , j ;
    int direction[8][2]={{2,1},{-2,1} , {2,-1} , {-2,-1} , {1,2} , {1,-2} , {-1,2} , {-1,-2} };
    for ( i=0;i<8;++i)
    {
        int x1=x+direction[i][0];
        x1+=8;
        x1%=8;
        
        int y1=y+direction[i][1];
        if (!isValidLocation(y1))
        {
            y1+=8;
            y1%=8;
            if (board[x1][y1].color=='O')
                board[x1][y1].threated=1;
        }
        else if (board[x1][y1].color!=board[x][y].color)
            board[x1][y1].threated=1;
    }
}


void markThreatedLocationsBishop(int x,int y)
{
	int i , j ;
    int direction[4][2]={ {-1,-1} , {-1,1} , {1,-1} , {1,1} };
    
    for (i=0;i<4;++i)
    {
        int x1=x;
        int y1=y;
        do
        {
            x1+=direction[i][0];
            y1+=direction[i][1];
            if (!isValidLocation(x1) || !isValidLocation(y1))
                break;
            if (board[x1][y1].color!=board[x][y].color)
                board[x1][y1].threated=1;
            
        }while(board[x1][y1].color=='O');
    }
    
    // Occupation By Bishop :
    int direction2[4][2]={{2,0},{-2,0} , {0,2} , {0, -2} };
    
    for ( i=0;i<4;++i)
    {
        int x1=x + direction2[i][0];
        int y1=y + direction2[i][1];
        if (!isValidLocation(x1) || !isValidLocation(y1))
            continue;
        piece t1=board[x][y];
        piece t2=board[x1][y1];
        if ((t1.color=='W' && t2.color=='B') || (t1.color=='B' && t2.color=='W'))
            board[x1][y1].threated=1;
    }
}


void markThreatedLocationsQueen(int x,int y)
{
	int i , j ;
    int direction[8][2]={{-1,-1} , {-1,1} , {1,-1} , {1,1} ,{-1,0} , {1,0} , {0,-1} , {0,1}};
    
    for ( i=0;i<8;++i)
    {
        int x1=x;
        int y1=y;
        do
        {
            x1+=direction[i][0];
            y1+=direction[i][1];
            if (!isValidLocation(x1) || !isValidLocation(y1))
                break;
            if (board[x1][y1].color!=board[x][y].color)
                board[x1][y1].threated=1;
            
        }while(board[x1][y1].color=='O');
    }
}


void markThreatedLocationsPawn(int x,int y)
{
	int  i , j ;
    int straightDirection=(board[x][y].color=='W')? -1:1;
    char otherPlayer=(board[x][y].color=='W') ? 'B': 'W';
    
    int yp=y+straightDirection;
    if (isValidLocation(yp) && board[x][yp].color=='O')
        board[x][yp].threated=1;
    if (isValidLocation(yp) && isValidLocation(x+1) && board[x+1][yp].color==otherPlayer)
        board[x+1][yp].threated=1;
    if (isValidLocation(yp) && isValidLocation(x-1) && board[x-1][yp].color==otherPlayer)
        board[x-1][yp].threated=1;
    
    if (!board[x][y].hasMoved && board[x][y+2*straightDirection].color=='O')
        board[x][y+2*straightDirection].threated=1;
    
    // Enpassent :
    int direction[2][2]={{1,0},{-1,0}};
    for ( i=0;i<2;++i)
    {
        int x1=x+direction[i][0];
        int y1=y+direction[i][1];
        if (!isValidLocation(x1) || !isValidLocation(y1))
            continue;
        
        if (board[x1][y1].enpassent==1)
            board[x1][y1].threated=1;
    }
}


int gameIsFinished(int player)
{
	int  i , j ;
    char p1=(player==0)? 'W' : 'B';
    char p2=(player==0)? 'B' : 'W';
    int xk1,yk1;
    int xk2,yk2;
    
    for ( i=0;i<BOARD_SIZE;++i)
        for ( j=0;j<BOARD_SIZE;++j)
        {
            if (board[i][j].color==p1 && board[i][j].kind=='K')
                xk1=i,yk1=j;
            if (board[i][j].color==p2 && board[i][j].kind=='K')
                xk2=i,yk2=j;
        }
    
    if (isKingChecked(xk1,yk1))
    {
        unmarkThreatedLocations();
        markThreatedLocations(xk1, yk1);
        int t=isKingChecked(xk2, yk2);
        t=0;
        
        for ( i=0;i<BOARD_SIZE;++i)
            for ( j=0;j<BOARD_SIZE;++j)
                if (board[i][j].threated==1)
                    t++;
        if (t==0)
            return 1;
    }
    
    return 0;
}


void markThreatedLocations(int x, int y)
{
    unmarkThreatedLocations();
    piece p=board[x][y];
    if (p.kind=='r')
        markThreatedLocationsRook(x,y);
    else if (p.kind=='k')
        markThreatedLocationsKnight(x,y);
    else if (p.kind=='b')
        markThreatedLocationsBishop(x, y);
    else if (p.kind=='q')
        markThreatedLocationsQueen(x, y);
    else if (p.kind=='K')
        markThreatedLocationsKing(x, y);
    else if (p.kind=='p')
        markThreatedLocationsPawn(x, y);
    
}


void unmarkThreatedLocations()
{
	int i , j ;
    for ( i=0;i<BOARD_SIZE;++i)
        for( j=0;j<BOARD_SIZE;++j)
                board[i][j].threated=0;
}


void makeMove(int x1,int y1,int x2,int y2)
{
    board[x2][y2]=board[x1][y1];
    board[x2][y2].hasMoved=1;
    board[x2][y2].enpassent=0;
    board[x1][y1]=emptyCell;
    
    piece p=board[x2][y2];
    
    if (isCastleMove && board[x1+3][y1].kind=='r')
    {
        isCastleMove=0;
        int xr1=x1+3,yr1=y1;
        int xr2=x2-1,yr2=y2;
        makeMove(xr1, yr1, xr2, yr2);
        
        int straighDirection=(board[x2][y2].color=='W')? -1:1;
        
        int yp=y2+straighDirection;
        int xp1=x2;
        int xp2=x2+1;
        
        if (!board[xp1][yp].hasMoved && !board[xp2][yp].hasMoved)
        {
            printf(" Which Pawn You Wish To Move ? 'g' Or 'h' ");
            char c,temp;
            do
            {
                scanf("%c%c",&c,&temp);
                
            } while (c!='g' && c!='h');
            
            if (c=='h')
            {
                if (board[xp2][yp+straighDirection].color=='O')
                    makeMove(xp2, yp, xp2, yp+straighDirection);
                else if (board[xp1][yp+straighDirection].color=='O')
                    makeMove(xp1, yp, xp1, yp+straighDirection);
            }
            
            
            if (c=='g')
            {
                if (board[xp1][yp+straighDirection].color=='O')
                    makeMove(xp1, yp, xp1, yp+straighDirection);
                else if (board[xp2][yp+straighDirection].color=='O')
                    makeMove(xp2, yp, xp2, yp+straighDirection);
            }
        }
        
        if (!board[xp1][yp].hasMoved || !board[xp2][yp].hasMoved)
        {
    
            if (board[xp2][yp].kind=='p')
                makeMove(xp2, yp, xp2, yp+straighDirection);
            else
                makeMove(xp1, yp, xp1, yp+straighDirection);
        }

    }
    
    if (p.kind=='p' && (y2==0|| y2==7) )
    {
        printf("This Pawn Can Be Promoted To : (1)queen , (2)knight , (3)bishop , (4)rook . \n");
        int t;
        do
        {
            printf("Enter A number From 1 To 4 .\n");
            scanf("%d",&t);
        } while (t<1 || t>4);
        
        char kind;
        switch (t)
        {
            case 1:
                kind='q';
                break;
            case 2:
                kind='k';
            case 3:
                kind='b';
            case 4:
                kind='r';
        }
        
        board[x2][y2].kind=kind;
    }
    
    if (p.kind=='p' && abs(y1-y2)==2 )
        board[x2][y2].enpassent=1;
        
}
