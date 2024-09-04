// Código base (inicial) para implementação do TP3 de CG
#include <GL/glut.h>
#include <map>
#include <iostream>

#define WINNERSCORE 1

enum Difficulty
{
    EASY,
    MEDIUM,
    HARD
};
Difficulty currentDifficulty = MEDIUM;

// Armazena o estado das teclas
std::map<unsigned char, bool> keyStates;
std::map<int, bool> specialKeyStates;

// Tamanho da janela
const int width = 800;
const int height = 600;

// Posições e dimensões das barras
float barWidth = 20.0f;
float barHeight = 100.0f;
float bar1Y = height / 2 - barHeight / 2;
float bar2Y = height / 2 - barHeight / 2;

// Posição e velocidade da bola
float ballX = width / 2;
float ballY = height / 2;
float ballSize = 20.0f;

// Velocidades
float barSpeed = 10.0f;
float ballXSpeed = 5.0f;
float ballYSpeed = 5.0f;

// Placar
int score1 = 0;
int score2 = 0;

void setDifficulty(Difficulty difficulty)
{
    switch (difficulty)
    {
    case EASY:
        ballXSpeed = 3.0f;
        ballYSpeed = 3.0f;
        barHeight = 150.0f;
        break;
    case MEDIUM:
        ballXSpeed = 5.0f;
        ballYSpeed = 5.0f;
        barHeight = 100.0f;
        break;
    case HARD:
        ballXSpeed = 8.0f;
        ballYSpeed = 8.0f;
        barHeight = 50.0f;
        break;

    default:
        break;
    }
}

void handleKeysDown(unsigned char key, int x, int y)
{
    keyStates[key] = true; // Marca a tecla como pressionada
}

void handleKeysUp(unsigned char key, int x, int y)
{
    keyStates[key] = false; // Marca a tecla como liberada
}

void handleKeysDownSpecial(int key, int x, int y)
{
    specialKeyStates[key] = true; // Marca a tecla especial como pressionada
}

void handleKeysUpSpecial(int key, int x, int y)
{
    specialKeyStates[key] = false; // Marca a tecla especial como liberada
}

void playerLeft()
{
    glBegin(GL_QUADS);
    glVertex2f(0, bar1Y);
    glVertex2f(0, bar1Y + barHeight);
    glVertex2f(barWidth, bar1Y + barHeight);
    glVertex2f(barWidth, bar1Y);
    glEnd();
}

void playerRight(int barHeight)
{
    glBegin(GL_QUADS);
    glVertex2f(width, bar2Y);
    glVertex2f(width, bar2Y + barHeight);
    glVertex2f(width - barWidth, bar2Y + barHeight);
    glVertex2f(width - barWidth, bar2Y);
    glEnd();
}

void ball()
{
    glBegin(GL_QUADS);
    glVertex2f(ballX - ballSize / 2, ballY - ballSize / 2);
    glVertex2f(ballX - ballSize / 2, ballY + ballSize / 2);
    glVertex2f(ballX + ballSize / 2, ballY + ballSize / 2);
    glVertex2f(ballX + ballSize / 2, ballY - ballSize / 2);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o placar
    glRasterPos2f(width / 2 - 50, height - 50);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + score1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ' ');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + score2);

    // Espaço para desenhar as barras e a bola
    // BOLA
    glPushMatrix();
    ball();
    glPopMatrix();

    // BARRA-LEFT
    glPushMatrix();
    playerLeft();
    glPopMatrix();

    // BARRA-RIGHT
    glPushMatrix();
    playerRight(barHeight);
    glPopMatrix();

    glutSwapBuffers();
}

void dislpayWinner()
{
    const char *winner = (score1 == WINNERSCORE) ? "Player left win!" : "Player right win!";

    // Definindo a posição onde a mensagem será exibida
    glRasterPos2f(width / 2 - 50, height - 100);
    for (const char *c = winner; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glutSwapBuffers();
}

void update(int value)
{
    // Lógica de atualização do jogo, incluindo movimentação das barras e bola
    ballX += ballXSpeed;
    ballY += ballYSpeed;

    if (score1 == WINNERSCORE)
    {
        dislpayWinner();
        return;
    }

    if (score2 == WINNERSCORE)
    {
        dislpayWinner();
        return;
    }

    // Espaço para a lógica de movimentação das barras
    if ((keyStates['w'] || keyStates['W']) && (bar1Y + barHeight < height))
    {
        bar1Y += 10;
        if (bar1Y + barHeight > height)
            bar1Y = height - barHeight;
    }
    if ((keyStates['s'] || keyStates['S']) && (bar1Y > 0))
    {
        bar1Y -= 10;
        if (bar1Y < 0)
            bar1Y = 0;
    }
    if (specialKeyStates[GLUT_KEY_UP] && bar2Y + barHeight < height)
    {
        bar2Y += 10;
        if (bar2Y + barHeight > height)
            bar2Y = height - barHeight;
    }
    if (specialKeyStates[GLUT_KEY_DOWN] && bar2Y > 0)
    {
        bar2Y -= 10;
        if (bar2Y < 0)
            bar2Y = 0;
    }

    // Espaço para a lógica de movimentação e colisão da bola
    int direction = rand();

    // COLISÃO COM PLAYER1
    if (ballX - ballSize / 2 <= 0 + barWidth)
    {
        if (ballY + ballSize / 2 >= bar1Y && ballY - ballSize / 2 <= bar1Y + barHeight)
        {
            ballXSpeed = -ballXSpeed;
        }
    }

    // COLISÃO COM PLAYER2
    if (ballX + ballSize / 2 >= width - barWidth)
    {
        if (ballY + ballSize / 2 >= bar2Y && ballY - ballSize / 2 <= bar2Y + barHeight)
        {
            ballXSpeed = -ballXSpeed;
        }
    }

    // COLISÃO BORDA SUPERIOR
    if (ballY + ballSize / 2 >= height)
    {
        ballYSpeed = -ballYSpeed;
    }

    // COLISÃO COM BORDA INFERIOR
    if (ballY - ballSize / 2 <= 0)
    {
        ballYSpeed = -ballYSpeed;
    }

    // Espaço para a lógica de contagem de pontos
    if (ballX + ballSize / 2 >= width)
    {
        score1 += 1;

        ballX = width / 2;
        ballY = height / 2;

        ballXSpeed = -ballXSpeed;

        if (direction % 2 == 0)
        {
            ballYSpeed = -ballYSpeed;
        }
        direction = -direction;
    }

    if (ballX - ballSize / 2 <= 0)
    {
        score2 += 1;

        ballX = width / 2;
        ballY = height / 2;

        ballXSpeed = -ballXSpeed;

        if (direction % 2 == 0)
        {
            ballYSpeed = -ballYSpeed;
        }
        direction = -direction;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Aproximadamente 60 FPS
}

// Função para evitar o redimensionamento da janela
void reshape(int w, int h)
{
    glutReshapeWindow(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // aqui a origem do sistema de coordenadas é colocada na parte inferior à esquerda
    gluOrtho2D(0.0, width, 0.0, height);
    glutPostRedisplay();
}

void Init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("TP3 - Jogo Pong");
}

int main(int argc, char **argv)
{
    Init(argc, argv);
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutKeyboardFunc(handleKeysDown);
    glutKeyboardUpFunc(handleKeysUp);
    glutSpecialFunc(handleKeysDownSpecial);
    glutSpecialUpFunc(handleKeysUpSpecial);
    glutReshapeFunc(reshape);
    setDifficulty(HARD);

    glutMainLoop();
    return 0;
}