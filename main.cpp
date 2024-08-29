// Código base (inicial) para implementação do TP3 de CG
#include <GL/glut.h>

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

// Especial
int specialPlayer1 = 0;
int specialPlayer2 = 0;

void playerLeft()
{
    glBegin(GL_QUADS);
    glVertex2f(0, bar1Y);
    glVertex2f(0, bar1Y + barHeight);
    glVertex2f(barWidth, bar1Y + barHeight);
    glVertex2f(barWidth, bar1Y);
    glEnd();
}

void playerRigth(int barHeight)
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

    // EspecialPlayer1
    glRasterPos2f(50, height - 50);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + specialPlayer1);

    // EspecialPlayer1
    glRasterPos2f(width - 50, height - 50);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0' + specialPlayer2);

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
    playerRigth(barHeight);
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)
{
    // Lógica de atualização do jogo, incluindo movimentação das barras e bola
    ballX += ballXSpeed;
    ballY += ballYSpeed;

    // Espaço para a lógica de movimentação das barras
    if (bar1Y + barHeight > height)
    {
        bar1Y -= 10;
    }
    if (bar1Y < 0)
    {
        bar1Y += 10;
    }

    if (bar2Y + barHeight > height)
    {
        bar2Y -= 10;
    }
    if (bar2Y < 0)
    {
        bar2Y += 10;
    }

    // Espaço para a lógica de movimentação e colisão da bola
    int direction = rand();

    // COLISÃO COM PLAYER1
    if (ballX - ballSize / 2 <= 0 + barWidth)
    {
        if (ballY + ballSize / 2 >= bar1Y && ballY - ballSize / 2 <= bar1Y + barHeight)
        {
            specialPlayer1++;

            if (specialPlayer1 == 3)
            {
                ballXSpeed = 1.5 * ballXSpeed;
                ballYSpeed = 1.5 * ballYSpeed;
                specialPlayer1 = 0;
            }

            ballXSpeed = -ballXSpeed;
        }
    }

    // COLISÃO COM PLAYER2
    if (ballX + ballSize / 2 >= width - barWidth)
    {
        if (ballY + ballSize / 2 >= bar2Y && ballY - ballSize / 2 <= bar2Y + barHeight)
        {
            specialPlayer2++;
            if (specialPlayer2 == 3)
            {
                ballXSpeed = 1.5 * ballXSpeed;
                ballYSpeed = 1.5 * ballYSpeed;
                specialPlayer2 = 0;
            }
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

        specialPlayer1 = 0;
        specialPlayer2 = 0;

        ballX = width / 2;
        ballY = height / 2;
        ballXSpeed = 5.0f;
        ballYSpeed = 5.0f;

        ballXSpeed = -ballXSpeed;

        if (direction % 2 == 0)
        {
            ballYSpeed = -ballYSpeed;
            direction = -direction;
        }
        else
        {
            direction = -direction;
        }
    }

    if (ballX - ballSize / 2 <= 0)
    {
        score2 += 1;

        specialPlayer1 = 0;
        specialPlayer2 = 0;

        ballX = width / 2;
        ballY = height / 2;
        ballXSpeed = -5.0f;
        ballYSpeed = -5.0f;

        ballXSpeed = -ballXSpeed;

        if (direction % 2 == 0)
        {
            ballYSpeed = -ballYSpeed;
            direction = -direction;
        }
        else
        {
            direction = -direction;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Aproximadamente 60 FPS
}

void handleKeysDown(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
    case 'S':
        bar1Y -= 10;
        break;

    case 'w':
    case 'W':
        bar1Y += 10;
        break;

    default:
        break;
    }
}

void handleKeysDownSpecial(int key, int x, int y)
{
    // Espaço para configurar o estado das teclas ao pressionar
    switch (key)
    {
    case GLUT_KEY_DOWN:
        bar2Y -= 10;
        break;

    case GLUT_KEY_UP:
        bar2Y += 10;
        break;

    default:
        break;
    }
}

void handleKeysUp(unsigned char key, int x, int y)
{
    // Espaço para configurar o estado das teclas ao soltar
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
    glutSpecialFunc(handleKeysDownSpecial);
    glutKeyboardUpFunc(handleKeysUp);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}