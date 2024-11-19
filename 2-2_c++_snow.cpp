//#include <iostream>
//#include <stdlib.h>
//#include <time.h>
//#include <windows.h>
//#include <conio.h>
//
//#define SNOW 3
//
//using namespace std;
//
//#define X 80
//#define Y 25
//
//
//class CLA {
//private :
// int map_size;
// int map[Y][X];
// int ch = 0;
// int rand_x[5];
//public:
// void manage();
// void screen(int x, int y);
// int snow_create();
//
//};
//
//void CLA::manage(){
// int toggle = 0;
// int y[10] = { 0 ,};
// int snow_quantity = 0;
//
// while (1) {
//
// //toggle = rand() % 3;
// if (toggle == 0) {
// snow_quantity = snow_create();
//
// }
// for (int i = 0; i < snow_quantity; i++) {
// map[0][rand_x[i]] = 1;
// /*screen(rand_x[i], 2);
// cout << "*";*/
// }
// for (int x = 0; x < X; x++) {
// for (int y = 0; y < Y - 1; y++) {
// if (map[y][x] == 1) {
// map[y + 1][x] = 1;
// map[y][x] = 0;
// }
// if (map[y+1][x] == 1) {
// //cout << "여기오기는 하냐";
// screen(x, y);
// cout << "*";
// }
//
// }
// Sleep(1000);
// system("cls");
//
// }
//
// }
//
//}
//void CLA::screen(int x, int y) {
// COORD Pos = { x,y };
// SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
// //cout << "여기오기는 하냐";
//}
//
//int CLA::snow_create() {
//
// int rand_quantity = rand() % 5;
//
//
// for (int i = 0; i < rand_quantity; i++) {
// rand_x[i] = rand() % X;
// }
// return rand_quantity;
//
//}
//
//int main() {
// srand(time(NULL));
// CLA nm;
//
// nm.manage();
// return 0;
//}

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <queue>
#include <queue>
using namespace std;

#define MAP_X 80
#define MAP_Y 20
#define SNOW_X 5 //X에 출력할 최대 눈의 개수
#define SNOW_MAX_Y 3 //쌓일 수 있는 최대 높이.

struct snow_XY {
  int x;
  int y;
  snow_XY(int x, int y) : x(x), y(y) {}
};

class CLA {
private:
  int snowX[SNOW_X];  //눈의 위치
  int map[MAP_Y][MAP_X] = { 0, }; // 눈이 쌓인 위치 관리
  queue<snow_XY> q;
public:
  void SCR_Manage();
  void ScreenXY(int x, int y);
  void snow_create();             //눈 생성
  void snow_print();             //블록 출력
  void snowY_down();             //블록 다운
  bool snow_collision_check(int x, int y);  //블록 체크 검사
  void snow_Installation();          //블록 설치
};



void CLA::SCR_Manage() {
  while (1) {
    snow_create();
    snow_print();
    snow_Installation();
    snowY_down();
    Sleep(100);
    system("cls");
  }


}

void CLA::snow_create() {
  int rand_probability = rand() % 1;
  int rand_snow = rand() % 6;
  if (rand_probability == 0) {
    for (int i = 0; i < rand_snow; i++) {
      snowX[i] = rand() % MAP_X;
      q.push(snow_XY(snowX[i], 0));
    }
  }

}

void CLA::snow_print() {  //출력
  queue<snow_XY> q_copy = q;
  while (!q_copy.empty()) {
    snow_XY snow = q_copy.front();
    ScreenXY(snow.x, snow.y);
    q_copy.pop();
  }

}

void CLA::snowY_down() {

  queue<snow_XY> q_copy;
  int count = 0;
  while (!q.empty()) {
    snow_XY snow = q.front();
     
    int x = snow.x;
    //int x = snow.x + rand()%2;
    //if (x > 77) { //대충 해놓은거임. 고쳐야함. //x이동시 고쳐야함.
    //  x = 79;
    //}
    int y = snow.y + 1;
    if (y != MAP_Y) {
      if (!snow_collision_check(x, y)) {  //x와 y의 위치에 블록이 있다면.1반환
        q_copy.push(snow_XY(x, y));
      }

    }
    if (y >= MAP_Y - SNOW_MAX_Y) {
      if (y == MAP_Y - 1) {  //초기 벽 생성
        map[y][x] = 1;
      }
      if (map[y + 1][x] == 1) {  //벽 쌓기
        map[y][x] = 1;
      }

    }
    //q.push(snow_XY(x, y));
    q.pop();
  }


  q = q_copy;
}




bool CLA::snow_collision_check(int x, int y) {
  if (map[y][x] == 1) {
    return 1;
  }
  return 0;
}

void CLA::ScreenXY(int x, int y) {
  COORD Pos = { (SHORT)x, (SHORT)y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
  cout << "*";
}

void CLA::snow_Installation() {
  for (int i = MAP_Y - SNOW_MAX_Y; i < MAP_Y; i++) {
    for (int j = 0; j < MAP_X; j++) {
      if (map[i][j] == 1) {
        ScreenXY(j, i);
      }
    }
  }
}


int main() {
  srand(time(NULL));
  CLA nm;
  nm.SCR_Manage();
  return 0;
}
