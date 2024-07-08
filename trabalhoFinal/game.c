#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#define LARGURA 1200
#define ALTURA 600
#define LINHA 30
#define COLUNA 60


int move(int movimentoDoJogador, int matriz[30][60], int x, int y, int player[2]){ //funcao da movimentacao do jogador

    switch(movimentoDoJogador){
    case 0:
        matriz[y][x+1] = 'j';
        matriz[y][x] = ' ';
        player[0] = player[0]+1;
        break;
    case 1:
        matriz[y+1][x] = 'j';
        matriz[y][x] = ' ';
        player[1] = player[1]+1;
        break;
    case 2:
        matriz[y][x-1] = 'j';
        matriz[y][x] = ' ';
        player[0] = player[0]-1;
        break;
    case 3:
        matriz[y-1][x] = 'j';
        matriz[y][x] = ' ';
        player[1] = player[1]-1;
        break;
    }

}

int shoot(int proj[4][3], int direction, int player[2]){ //funcao do tiro do projetil
            if(proj[0][0] != 1){
                proj[0][0] = 1;
                proj[3][0] = direction;
                proj[1][0] = player[0];
                proj[2][0] = player[1];
                //se o projetil 1 nao existe, ele vai ser criado e colocado na matriz
            } else if(proj[0][1] != 1){
                proj[0][1] = 1;
                proj[3][1] = direction;
                proj[1][1] = player[0];
                proj[2][1] = player[1];
                //o mesmo para o projetil 2
            } else if(proj[0][2] != 1){
                proj[0][2] = 1;
                proj[3][2] = direction;
                proj[1][2] = player[0];
                proj[2][2] = player[1];
                //o mesmo para o projetil 3
            }
}

int moveEnemyToBase(int enemy[3][10], int base[3], int j, int b, int matriz[30][60]){ //funcao que move o inimigo em direcao a base

    if(enemy[1][j] - base[1] >= 0 && b % 32 == 0 && matriz[enemy[2][j]][enemy[1][j]-1] != 'W' && matriz[enemy[2][j]][enemy[1][j]-1] != 'm'){ //se o inimigo está a direita da base
        matriz[enemy[2][j]][enemy[1][j]-1] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[1][j] = enemy[1][j] - 1; //vai pra esquerda
    }
    if(enemy[1][j] - base[1] < 0 && b % 32 == 0 && matriz[enemy[2][j]][enemy[1][j]+1] != 'W' && matriz[enemy[2][j]][enemy[1][j]+1] != 'm'){ //se o inimigo está a esquerda da base
        matriz[enemy[2][j]][enemy[1][j]+1] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[1][j] = enemy[1][j] + 1; //vai pra direita
    }
    if(enemy[2][j] - base[2] >= 0 && b % 32 !=0 && matriz[enemy[2][j]-1][enemy[1][j]] != 'W' && matriz[enemy[2][j]-1][enemy[1][j]] != 'm'){ //se o inimigo está acima da base
        matriz[enemy[2][j]-1][enemy[1][j]] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[2][j] = enemy[2][j] - 1; //vai pra cima
    }
    if(enemy[2][j] - base[2] < 0 && b % 32 !=0 && matriz[enemy[2][j]+1][enemy[1][j]] != 'W' && matriz[enemy[2][j]+1][enemy[1][j]] != 'm'){ //se o inimigo está abaixo da base
        matriz[enemy[2][j]+1][enemy[1][j]] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[2][j] = enemy[2][j] + 1; //vai pra baixo
    }//os ticks foram setados para que a cada 32 ticks, em 16 o inimigo vai para a base pelo caminho horizontal, e depois pelo caminho vertical, intercalando
}

int moveEnemyRandomly(int enemy[3][10], int base[3], int j, int a, int matriz[30][60]){ //funcao que move o inimigo em direcoes aleatorias
    switch(a){
    case 0:
        if (matriz[enemy[2][j]][enemy[1][j]+1] != 'W' && matriz[enemy[2][j]][enemy[1][j]+1] != 'm'){ //se o ponto a direita do inimigo for uma parede, ele nao faz o movimento
        matriz[enemy[2][j]][enemy[1][j]+1] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[1][j] = enemy[1][j] + 1;} //vai pra direita
        break;
    case 1:
        if (matriz[enemy[2][j]+1][enemy[1][j]] != 'W' && matriz[enemy[2][j]+1][enemy[1][j]] != 'm'){ //se o ponto acima do inimigo for uma parede, ele nao faz o movimento
        matriz[enemy[2][j]+1][enemy[1][j]] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[2][j] = enemy[2][j] + 1;} //vai pra baixo
        break;
    case 2:
        if (matriz[enemy[2][j]][enemy[1][j]-1] != 'W' && matriz[enemy[2][j]][enemy[1][j]-1] != 'm'){ //se o ponto a esquerda do inimigo for uma parede, ele nao faz o movimento
        matriz[enemy[2][j]][enemy[1][j]-1] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[1][j] = enemy[1][j] - 1;} //vai pra esquerda
        break;
    case 3:
        if (matriz[enemy[2][j]-1][enemy[1][j]] != 'W' && matriz[enemy[2][j]-1][enemy[1][j]] != 'm'){ //se o ponto abaixo do inimigo for uma parede, ele nao faz o movimento
        matriz[enemy[2][j]-1][enemy[1][j]] = 'm';
        matriz[enemy[2][j]][enemy[1][j]] = ' ';
        enemy[2][j] = enemy[2][j] - 1;} //vai pra cima
        break;
    }
}

int clearShot(int proj[4][3], int i){ //funcao que limpa o tiro do mapa
    proj[0][i] = 0;
    proj[1][i] = -1;
    proj[2][i] = -1;
    proj[3][i] = 0;
}

int clearEnemy(int enemy[3][10], int j, int matriz[30][60]){ //funcao que limpa o inimigo do mapa quando ele morre
    enemy[0][j] = 0;
    matriz[enemy[2][j]][enemy[1][j]] = ' ';
    enemy[1][j] = -1;
    enemy[2][j] = -1;
}

int enemyBase(int enemy[3][10], int j, int matriz[30][60]){ //funcao que limpa o inimigo do mapa quando ele toca a base
    enemy[0][j] = 0;
    matriz[enemy[2][j]][enemy[1][j]] = 's';
    enemy[1][j] = -1;
    enemy[2][j] = -1;
}

int main(void){

    int x, y, direction, i, j, posInitX, posInitY, posX, posY, numEnemy, a, b, d;
    int proj[4][3]; //matriz posicao dos projeteis
    int matriz[30][60]; //matriz mapa
    int player[2]; // posicao do jogador
    int enemy[3][10]; //matriz posicao dos inimigos
    int base[3];
    char c; //char usado para armazenar a info do mapa no ponto (x,y) no mapa e inserir na matriz[b][a]
    srand(time(NULL));

    b = 0;        //ticks
    d = 0;        //variavel para auxiliar na contagem de inimigos

    FILE *mapa;
    mapa = fopen("mapa1.txt", "r");

    proj[0][0] = proj[0][1] = proj[0][2] = 0;

    //quando for usar matrizes, a primeira coordenada eh Y e a segunda eh X
    for (i = 0; i<30; i++){
        for (j = 0; j<60; j++){
            fscanf(mapa,"%c", &c);
            matriz[i][j] = c;
        }
    }
    //listando os elementos do mapa e alocando eles
    for (i = 0; i<30; i++){
    for (j=0; j<60; j++){
        switch(matriz[i][j]){
        case 'j':
            player[0] = j; //coordenada X do jogador
            player[1] = i; //coordenada Y do jogador
            x = j; //ponteiros para X e Y
            y = i;
            break;
        case 'm':
            enemy[0][d] = 1;
            enemy[1][d] = j; //coordenada x do inimigo
            enemy[2][d] = i; //coordenada y do inimigo
            d = d+1;
            break;
        case 's':
            base[0] = 100; //vida
            base[1] = j; //coordenada x da base
            base[2] = i; //coordenada y da base
            }
        }
    }

    for(j = 0; j<10; j++){
    }

    direction = 0;

    InitWindow(LARGURA, ALTURA, "Game");
    SetTargetFPS(30);



    while (!WindowShouldClose()){

        //checagem inicial para a vida da base
        switch(base[0]){
        case 0:
            CloseWindow();
            break;
        case 50:
            DrawRectangle(base[1]*20, base[2]*20, 20, 20, ORANGE);
            break;
        case 100:
            DrawRectangle(base[1]*20, base[2]*20, 20, 20, GREEN);
            break;
        }

        numEnemy = 0; //numero de inimigos vivos
        b= b+1;
        for(j=0; j<10; j++){ //esse for é o comportamento do inimigo, como movimento e quando se encontra com um elemento
            a = rand() % 4;
            if(enemy[0][j] != 1){enemy[0][j] = 0;} //se o inimigo nao estiver vivo, ele vai estar morto (antes nao tinha sido declarado)

            numEnemy = numEnemy + enemy[0][j]; //numero de inimigo aumenta quando o codigo ler q tem um inimigo vivo

            if(enemy[0][j] == 1 && b %8 == 0 && b %16 != 0){
                moveEnemyRandomly(enemy, base, j, a, matriz);
            }
            if(enemy[0][j] == 1 && b %16 == 0){
                moveEnemyToBase(enemy, base, j, b, matriz);
            }
            if(enemy[1][j] == base[1] && enemy[2][j] == base[2]){
                enemyBase(enemy, j, matriz); //quando o inimigo chega na base, o inimigo morre, mas a base perde 50 de vida
                base[0] = base[0] - 50;
            }
            if(enemy[1][j] == player[0] && enemy[2][j] == player[1]){ //se o inimigo toca o jogador, o jogador morre e o jogo acaba
                CloseWindow();
            }
        }

        if (numEnemy <= 0){
            printf("Voce passou de fase!\n");
            //CloseWindow();
        }

        //movimentacao do jogador
        if (IsKeyDown(KEY_D)){
            if(matriz[y][x+1] != 'W'){
                move(0, matriz, x, y, player);
                x = x+1;
            }
        }
        if (IsKeyDown(KEY_S)){
            if(matriz[y+1][x] != 'W'){
                move(1, matriz, x, y, player);
                y = y+1;
            }
        }
        if (IsKeyDown(KEY_A)){
            if(matriz[y][x-1] != 'W'){
                move(2, matriz, x, y, player);
                x=x-1;
            }
        }
        if (IsKeyDown(KEY_W)){
            if(matriz[y-1][x] != 'W'){
                move(3, matriz, x, y, player);
                y=y-1;
            }
        }

        //movimento dos projeteis
        if (IsKeyPressed(KEY_RIGHT)){
            direction = 0;
            shoot(proj, direction, player);
        }
        if (IsKeyPressed(KEY_DOWN)){
            direction = 1;
            shoot(proj, direction, player);
        }
        if (IsKeyPressed(KEY_LEFT)){
            direction = 2;
            shoot(proj, direction, player);
        }
        if (IsKeyPressed(KEY_UP)){
            direction = 3;
            shoot(proj, direction, player);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for(i = 0; i<30; i++){ //desenho do jogador e das paredes
            for(j=0; j<60; j++){
                switch(matriz[i][j]){ //as coordenadas tem q sempre multiplicar por 20, porque sao em pixel
                    case 'j':
                        DrawRectangle(player[0]*20, player[1]*20, 20, 20, SKYBLUE);
                        break;
                    case 'W':
                        DrawRectangle(j*20, i*20, 20, 20, DARKGRAY);
                        break;
                    //case 's':
                    //    DrawRectangle(j*20, i*20, 20, 20, GREEN);
                    //    break;
                    //case 'm':
                    //    DrawRectangle(j*20, i*20, 20, 20, RED);
                    //    break;
                }
            }
        }

        if(player[0] < 0 || player[0]>= COLUNA || player[1]<0 || player[1]>=LINHA){ //se o jogador sair do mapa, o jogo fecha
            CloseWindow();
        }

        for(i = 0; i<3; i++){ //mapeamento dos projeteis e 'hitboxes' com inimigos
            if(proj[0][i] == 1){
                switch(proj[3][i]){
                    case 0:
                        proj[1][i] = proj[1][i] + 1;
                        break;
                    case 1:
                        proj[2][i] = proj[2][i] + 1;
                        break;
                    case 2:
                        proj[1][i] = proj[1][i] - 1;
                        break;
                    case 3:
                        proj[2][i] = proj[2][i] - 1;
                        break;
                }

            if (matriz[proj[2][i]][proj[1][i]] == 'W' || proj[1][i] >= COLUNA || proj[1][i] <0 || proj[2][i] >=LINHA || proj[2][i] <0){ //se o projetil acertar a parede ou ficar fora do mapa, ele vai sumir
                clearShot(proj, i);
            }

            for(j=0; j<10; j++){ //comportamento de cada projetil em contato com inimigo
                if(proj[1][i] == enemy[1][j] && proj[2][i] == enemy[2][j]){ //se o projetil acertar o inimigo, o projetil e o inimigo somem
                    clearShot(proj, i);
                    clearEnemy(enemy, j, matriz);
                }
            }


            if (proj[0][i] == 1 && proj[1][i] < COLUNA && proj[1][i] >=0 && proj[2][i] <LINHA && proj[2][i] >=0){ //se o projetil existe e está dentro dos limites do jogo, ele devera ser desenhado
                DrawRectangle(proj[1][i]*20, proj[2][i]*20, 20, 20, DARKBLUE);
            }

            }
        }

        for(i=0; i<10; i++) { //mapeamento dos inimigos
            if(enemy[0][i] == 1){
                DrawRectangle(enemy[1][i]*20, enemy[2][i]*20, 20, 20, RED);
            }
        }

        EndDrawing();

    }

    CloseWindow();
    return 0;
}
