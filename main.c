#include <GL/glut.h>
#define WIDTH 900
#define HEIGHT 900
#define CELL (WIDTH / 3)
#include <stdio.h>
#include <math.h>
#include <time.h>

char player = 'X';
char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char winner = ' ';


void changeplayer()
{
    if (player == 'X')
    {
        player = 'O';
    }
    else
    {
        player = 'X';
    }
}

void showboard()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1, 1, 1);
    glLineWidth(2.0);

    // Show Outer Lines
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(WIDTH, 0);
    glVertex2f(WIDTH, HEIGHT);
    glVertex2f(0, HEIGHT);
    glEnd();

    // Show Vertical Lines
    for (int i = 1; i < 3; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f(0, (CELL * i));
        glVertex2f(WIDTH, (CELL * i));

        glEnd();
    }

    // Show Horizontal Lines
    for (int i = 1; i < 3; ++i)
    {
        glBegin(GL_LINES);
        glVertex2f((CELL * i), 0);
        glVertex2f((CELL * i), HEIGHT);

        glEnd();
    }

    glFlush();
}

void drawX(int row, int col)
{
    glBegin(GL_LINES);
    glVertex2f(((col + 0.1) * CELL), ((row + 0.1) * CELL));
    glVertex2f(((col + 1) - 0.1) * CELL, ((row + 1) - 0.1) * CELL);
    glVertex2f((col + 0.1) * CELL, ((row + 1) - 0.1) * CELL);
    glVertex2f(((col + 1) - 0.1) * CELL, (row + 0.1) * CELL);
    glEnd();
    glFlush();
}

void drawO(int row, int col)
{
    int segments = 100;
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        angle = i * 2.0 * (22 / 7) / segments;
        float x = cos(angle) * CELL / 2 + (col + 0.5) * CELL;

        float y = sin(angle) * CELL / 2 + (row + 0.5) * CELL;
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

void drawwin(int row, int col, char dir)
{
    glColor3f(1, 0, 0);
    glLineWidth(10.0);

    switch (dir)
    {
    case ('v'):
        glBegin(GL_LINES);
        glVertex2f(((col + 0.5) * CELL), 20);
        glVertex2f(((col + 0.5) * CELL), HEIGHT - 20);
        glEnd();
        break;
    case ('h'):
        glBegin(GL_LINES);
        glVertex2f(20, ((row + 0.5) * CELL));
        glVertex2f((WIDTH - 20), ((row + 0.5) * CELL));
        glEnd();
        break;
    case ('r'):
        glBegin(GL_LINES);
        glVertex2f(WIDTH - 20, 20);
        glVertex2f(20, HEIGHT - 20);
        glEnd();

        break;
    case ('l'):
        glBegin(GL_LINES);
        glVertex2f(HEIGHT - 20, WIDTH - 20);

        glVertex2f(20, 20);
        glEnd();

    default:
        break;
    }

    glFlush();
}

void game(int row, int col, char player)
{

    if (winner == ' '){
    if (board[row][col] == ' ')
    {

        board[row][col] = player;
        if (player == 'X')
        {
            drawX(row, col);
        }
        else
        {
            drawO(row, col);
        }
    }

    for (int i = 0; i < 3; ++i)
    {

        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player))
        {
            winner = player;
            drawwin(row, col, 'h');

            printf("winner is %c\n", winner);
        }

        else if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            winner = player;
            drawwin(row, col, 'v');
            printf("winner is %c\n", winner);
        }
         else if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
    {
        winner = player;
        drawwin(row, col, 'l');

        printf("winner is %c\n", winner);
    }
    else if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
    {
        winner = player;

        printf("winner is %c\n", winner);
        drawwin(row, col, 'r');
    }

    }

   
    changeplayer();}
    else{
 showboard();    }

}
void mouseclick(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == 0)
    {
        int row = y / CELL;
        int col = x / CELL;
        //            printf("row: %d, col: %d\n", row, col);

        game(row, col, player);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tic Tac Toe");
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    glutMouseFunc(mouseclick);
    glutDisplayFunc(showboard);

    glutMainLoop();
    return 0;
}
