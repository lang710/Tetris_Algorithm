#include <iostream>
#include <random>
#include <thread>
using namespace std;

struct point{
    int x,y;
};

void run(int graph[10][10],point shapes[7][4]){
    srandom((unsigned)time(nullptr));
    int choose,cx,cy,fi,fj;
    int i,j,k,l;
    int full,fill,t_full,t_fill,t_count;
    bool togo=true;
    bool jump;
    int visitX[10],visitY[10];
    int row,col;
    int score=0;
    while(togo) {
        choose = random() % 7;
        full = fill = 0;
        fi = fj = -1;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                jump = false;
                for (k = 0; k < 4; k++) {
                    cx = shapes[choose][k].x + i;
                    cy = shapes[choose][k].y + j;
                    if (!(cx < 10 && cy < 10 && graph[cx][cy] == 0)) {
                        jump = true;
                        break;
                    }
                }
                if (!jump) {
                    t_full = t_fill = 0;
                    memset(visitX, 0, sizeof(visitX));
                    memset(visitY, 0, sizeof(visitY));
                    for (k = 0; k < 4; k++) {
                        cx = shapes[choose][k].x + i;
                        cy = shapes[choose][k].y + j;
                        if (visitX[cx] == 0) {
                            t_count = 0;
                            visitX[cx] = 1;
                            for (l = 0; l < 10; l++) {
                                t_count += graph[cx][l];
                                t_fill += graph[cx][l];
                            }
                            if (t_count == 10)
                                t_full++;
                        }
                        if (visitY[cy] == 0) {
                            t_count = 0;
                            visitY[cy] = 1;
                            for (l = 0; l < 10; l++) {
                                t_count += graph[l][cy];
                                t_fill += graph[l][cy];
                            }
                            if (t_count == 10)
                                t_full++;
                        }
                    }
                    if (t_full > full || (t_full == full && t_fill > fill)) {
                        full = t_full, fill = t_fill;
                        fi = i, fj = j;
                    }
                }
            }
        }

        if (fi >= 0 && fj >= 0) {
            for (k = 0; k < 4; k++) {
                cx = shapes[choose][k].x + fi;
                cy = shapes[choose][k].y + fj;
                graph[cx][cy] = 1;
            }

            memset(visitX, 0, sizeof(visitX));
            memset(visitY, 0, sizeof(visitY));
            for (i = 0; i < 10; i++) {
                row = col = 0;
                for (j = 0; j < 10; j++)
                    row += graph[i][j], col += graph[j][i];
                if (row == 10)
                    visitX[i] = 1;
                if (col == 10)
                    visitY[i] = 1;
            }
            for (i = 0; i < 10; i++) {
                if (visitX[i] == 1) {
                    for (j = 0; j < 10; j++)
                        graph[i][j] = 0;
                    score++;
                }
                if (visitY[i] == 1) {
                    for (j = 0; j < 10; j++)
                        graph[j][i] = 0;
                    score++;
                }
            }

            for (i = 0; i < 10; i++) {
                for (j = 0; j < 10; j++)
                    cout << graph[i][j] << ' ';
                cout << endl;
            }
            cout << endl;
            cout << score << endl;

            chrono::milliseconds dura(1000);
            this_thread::sleep_for(dura);
        }
    }
}

int main(){
    int graph[10][10];
    memset(graph,0,sizeof(graph));

    point shapes[7][4]={{{0,1},{1,0},{1,1},{1,2}},
                        {{0,0},{0,1},{0,2},{0,3}},
                        {{0,0},{0,1},{1,0},{1,1}},
                        {{0,0},{0,1},{1,1},{1,2}},
                        {{0,1},{0,2},{1,0},{1,1}},
                        {{0,0},{1,0},{2,0},{2,1}},
                        {{0,1},{1,1},{2,0},{2,1}}};

    srandom((unsigned)time(nullptr));
    int choose=random()%7;
    int cx,cy;
    for(int i=0;i<4;i++){
        cx=shapes[choose][i].x;
        cy=shapes[choose][i].y;
        graph[cx][cy]=1;
    }
    for(int i=0;i<10;i++) {
        for (int j = 0; j < 10; j++)
            cout<<graph[i][j]<<' ';
        cout<<endl;
    }

    chrono::milliseconds dura(1000);
    this_thread::sleep_for(dura);

    cout<<"go on!"<<endl;
    run(graph,shapes);

    return 0;
}

/*

point shape1[4]={{0,1},{1,0},{1,1},{1,2}};
point shape2[4]={{0,0},{0,1},{0,2},{0,3}};
point shape3[4]={{0,0},{0,1},{1,0},{1,1}};
point shape4[4]={{0,0},{0,1},{1,1},{1,2}};
point shape5[4]={{0,1},{0,2},{1,0},{1,1}};
point shape6[4]={{0,0},{1,0},{2,0},{2,1}};
point shape7[4]={{0,1},{1,1},{2,0},{2,1}};
 */

/*
 * shape1:
 *    .
 *  . . .
 *
 * shape2:
 *  . . . .
 *
 * shape3:
 *  . .
 *  . .
 *
 *  shape4:
 *  . .
 *    . .
 *
 *  shape5:
 *    . .
 *  . .
 *
 *  shape6:
 *  .
 *  .
 *  . .
 *
 *  shape7:
 *    .
 *    .
 *  . .
 *
 *
 */

