#include "raylib.h"
#include <string.h>
#include <stdio.h>
#define LARGURA 1200
#define ALTURA 600
#define LINHA 30
#define COLUNA 60
//esse arquivo é baguncado e ta mal organizado, entao a versao final ficará no \game.c


int shoot(int proj[4][3], int direction, int arma[2]){


            if(proj[0][0] != 1){
                proj[0][0] = 1;
                proj[3][0] = direction;
                proj[1][0] = arma[0];
                proj[2][0] = arma[1];
                //se o projetil 1 nao existe, ele vai ser criado e colocado na matriz
            } else if(proj[0][1] != 1){
                proj[0][1] = 1;
                proj[3][1] = direction;
                proj[1][1] = arma[0];
                proj[2][1] = arma[1];
                //o mesmo para o projetil 2
            } else if(proj[0][2] != 1){
                proj[0][2] = 1;
                proj[3][2] = direction;
                proj[1][2] = arma[0];
                proj[2][2] = arma[1];
                //o mesmo para o projetil 3
            }

}


int main(void){
    int x, y, direction, projX, projY, numProj, i, j, k;
    int posInitX, posInitY, posX, posY, a, b;
    char armaH[50] = "-"; //H para horizontal
    char armaV[50] = "|"; //V para vertical
    int proj[4][3];
    int matriz[30][60];
    int player[2];
    int arma[2];
    char ponto;

    //pega o mapa, logo mais vai ter mudanca na escolha de mapa
    FILE *mapa;
    mapa = fopen("mapa1.txt", "r");


    //quando for usar matrizes, a primeira coordenada eh Y e a segunda eh X
    for (j = 0; j<30; j++){
        for (k = 0; k<60; k++){
            fscanf(mapa,"%c", &ponto);
            matriz[j][k] = ponto;
        }

    }


// [1 0 0] 1 = projetil existe, 0 = projetil nao existe
// [x x x] x = coordenada x de cada projetil i
// [y y y] y = coordenada y de cada projetil i
// [d d d] d = direcao q o projetil foi lancado





    direction = 0;
    //0 - direita; 1 - baixo; 2 - esquerda; 3 - cima

    numProj = 0;
    //numero de projeteis para mudar

    InitWindow(LARGURA, ALTURA, "Teclas");
    SetTargetFPS(30);
        for (i = 0; i<30; i++){
            for (j=0; j<60; j++){
                switch(matriz[i][j]){
                    case 'W':
                        //DrawRectangle(i*20, j*20, 20, 20, RED);
                        break;
                    case 'j':
                        player[0] = j;
                        player[1] = i;
                        a = j;
                        b = i;
                        break;

                }
            }
        }

    arma[0] = player[0] + 1;
    arma[1] = player[1];

    while (!WindowShouldClose()) {





        if (IsKeyDown(KEY_D)){
            if(matriz[b][a+1] != 'W'){
                matriz[b][a+1] = 'j';
                matriz[b][a] = ' ';
                a = a+1;
                arma[0] = arma[0]+1;
                player[0] = player[0] +1;
            }
        }
        if (IsKeyDown(KEY_S)){
            if(matriz[b+1][a] != 'W'){
                matriz[b+1][a] = 'j';
                matriz[b][a] = ' ';
                b=b+1;
                arma[1] = arma[1]+1;
                player[1] = player[1] +1;
            }
        }
        if (IsKeyDown(KEY_A)){
            if(matriz[b][a-1] != 'W'){
                matriz[b][a-1] = 'j';
                matriz[b][a] = ' ';
                a=a-1;
                arma[0] = arma[0]-1;
                player[0] = player[0] -1;
            }
        }
        if (IsKeyDown(KEY_W)){
            if(matriz[b-1][a] != 'W'){
                matriz[b-1][a] = 'j';
                matriz[b][a] = ' ';
                b=b-1;
                arma[1] = arma[1]-1;
                player[1] = player[1] -1;
            }
        }

        x = player[0] *20;
        y = player[1]*20;


        if (IsKeyPressed(KEY_RIGHT)){
            arma[0] = player[0]+1;
            arma[1] = player[1];
            direction = 0;
            shoot(proj, direction, arma);
        }
        if (IsKeyPressed(KEY_DOWN)){
            arma[0] = player[0];
            arma[1] = player[1]+1;
            direction = 1;
            shoot(proj, direction, arma);

        }
        if (IsKeyPressed(KEY_LEFT)){
            arma[0] = player[0]-1;
            arma[1] = player[1];
            direction = 2;
            shoot(proj, direction, arma);

        }
        if (IsKeyPressed(KEY_UP)){
            arma[0] = player[0];
            arma[1] = player[1]-1;
            direction = 3;
            shoot(proj, direction, arma);


        }


        BeginDrawing();
        ClearBackground(RAYWHITE);


        for (i = 0; i<30; i++){
            for (j=0; j<60; j++){
                //lembrar de trocar as coordenadas
                switch(matriz[i][j]){
                    case 'j':
                        DrawRectangle(a*20, b*20, 20, 20, ORANGE);
                        DrawRectangle(arma[0]*20, arma[1]*20, 20, 20, DARKBLUE);
                        break;
                    case 'W':
                        DrawRectangle(j*20, i*20, 20, 20, DARKGRAY);
                        break;
                    case 'e':
                        DrawRectangle(j*20, i*20, 20, 20, GREEN);
                        break;
                }
            }
        }

        if(x < 0 || x >= LARGURA || y < 0 || y >= ALTURA){
            CloseWindow();
        }



        //PROJETEIS
        for(i = 0; i<3; i++){
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

            if (proj[1][i] < COLUNA || proj[1][i] >=0 || proj[2][i] <LINHA || proj[2][i] >=0){
                DrawRectangle(proj[1][i]*20, proj[2][i]*20, 20, 20, RED);
            }
            if (proj[1][i] >= COLUNA || proj[1][i] <0 || proj[2][i] >=LINHA || proj[2][i] <0){
                proj[0][i] = 0;
                proj[1][i] = 0;
                proj[2][i] = 0;
                proj[3][i] = 0;
            }
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
