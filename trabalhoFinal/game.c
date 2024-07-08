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

int moveEnemyToBase(int enemy[3][10], int base[3], int j, int b){ //funcao que move o inimigo em direcao a base

    if(enemy[1][j] - base[1] >= 0 && b % 32 == 0){ //se o inimigo est� a direita da base
        enemy[1][j] = enemy[1][j] - 1;
    }
    if(enemy[1][j] - base[1] < 0 && b % 32 == 0){ //se o inimigo est� a esquerda da base
        enemy[1][j] = enemy[1][j] + 1;
    }
    if(enemy[2][j] - base[2] >= 0 && b % 32 !=0){ //se o inimigo est� acima da base
        enemy[2][j] = enemy[2][j] - 1;
    }
    if(enemy[2][j] - base[2] < 0 && b % 32 !=0){ //se o inimigo est� abaixo da base
        enemy[2][j] = enemy[2][j] + 1;
    }//os ticks foram setados para que a cada 32 ticks, em 16 o inimigo vai para a base pelo caminho horizontal, e depois pelo caminho vertical, intercalando
}

int moveEnemyRandomly(int enemy[3][10], int base[3], int j, int a){ //funcao que move o inimigo em direcoes aleatorias
    switch(a){
    case 0:
        enemy[1][j] = enemy[1][j] + 1;
        break;
    case 1:
        enemy[2][j] = enemy[2][j] + 1;
        break;
    case 2:
        enemy[1][j] = enemy[1][j] - 1;
        break;
    case 3:
        enemy[2][j] = enemy[2][j] - 1;
        break;
    }
}

int clearShot(int proj[4][3], int i){ //funcao que limpa o tiro do mapa
    proj[0][i] = 0;
    proj[1][i] = -1;
    proj[2][i] = -1;
    proj[3][i] = 0;
}

int clearEnemy(int enemy[3][10], int j){ //funcao que limpa o inimigo do mapa
    enemy[0][j] = 0;
    enemy[1][j] = -1;
    enemy[2][j] = -1;
}

int main(void){

    int x, y, direction, i, j, posInitX, posInitY, posX, posY, numEnemy, a, b;
    int proj[4][3]; //matriz posicao dos projeteis
    int matriz[30][60]; //matriz mapa
    int player[2]; // posicao do jogador
    int enemy[3][10]; //matriz posicao dos inimigos
    int base[3];
    char c; //char usado para armazenar a info do mapa no ponto (x,y) no mapa e inserir na matriz[b][a]
    srand(time(NULL));

    numEnemy = 0;
    b = 0;

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

    direction = 0;

    InitWindow(LARGURA, ALTURA, "Game");
    SetTargetFPS(30);

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
                enemy[0][numEnemy] = 1;
                enemy[1][numEnemy] = j; //coordenada x do inimigo
                enemy[2][numEnemy] = i; //coordenada y do inimigo
                numEnemy = numEnemy+1;
                break;
            case 's':
                base[0] = 100; //vida
                base[1] = j; //coordenada x da base
                base[2] = i; //coordenada y da base
            }
        }
    }

    while (!WindowShouldClose()){

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
        ClearBackground(RAYWHITE);

        b= b+1; //a variavel B funciona como especie de 'tick' do jogo. a cada n ticks, alguma coisa acontece
        for(j=0; j<10; j++){ //base[1] base[2]
            a = rand() % 4;
            if(enemy[0][j] == 1 && b %8 == 0){
                moveEnemyRandomly(enemy, base, j, a);
            }
            if(enemy[0][j] == 1 && b %16 == 0){
                moveEnemyToBase(enemy, base, j, b);
            }
        }

        for(i = 0; i<30; i++){
            for(j=0; j<60; j++){
                switch(matriz[i][j]){ //as coordenadas tem q sempre multiplicar por 20, porque sao em pixel
                    case 'j':
                        DrawRectangle(player[0]*20, player[1]*20, 20, 20, ORANGE);
                        break;
                    case 'W':
                        DrawRectangle(j*20, i*20, 20, 20, DARKGRAY);
                        break;
                    case 's':
                        DrawRectangle(j*20, i*20, 20, 20, GREEN);
                        break;
                    //case 'm':
                    //    DrawRectangle(j*20, i*20, 20, 20, RED);
                    //    break;
                }
            }
        }

        if(player[0] < 0 || player[0]>= COLUNA || player[1]<0 || player[1]>=LINHA){
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

            for(j=0; j<10; j++){ //base[1] base[2]
                if(proj[1][i] == enemy[1][j] && proj[2][i] == enemy[2][j]){ //se o projetil acertar o inimigo, o projetil e o inimigo somem
                    clearShot(proj, i);
                    clearEnemy(enemy, j);
                }
            }


            if (proj[0][i] == 1 && proj[1][i] < COLUNA && proj[1][i] >=0 && proj[2][i] <LINHA && proj[2][i] >=0){ //se o projetil existe e est� dentro dos limites do jogo, ele devera ser desenhado
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
