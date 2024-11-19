#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

using namespace std;
//int CLA::m_value = 0; // static 멤버 변수 정의 및 초기화


class CLA {
private:
int arr[2][1];
int x_value = 0;
int x = 0;
char ch = 0;
//static int m_value;
public:
void manage();
void left();
void right();
void print_value();

};

void CLA::manage() {
arr[0][0] = 1;
arr[0][1] = 1;

print_value();

while (ch != 27) {
ch = _getch();
switch (ch) {
case 75:
left();
break;
case 77:
right();
break;
}
system("cls");
arr[0][0] = 0;
if (x == 0) {
arr[0][0] = x_value;
}
arr[0][1] = x_value;
print_value();
}
}

void CLA::left() {
--x;
if (0 > x) {
x_value--;
if (x_value == 0) {
//x = -1;
x_value = -1;
}
}

}

void CLA::right() {
x++;
if (0 < x) {
x_value++;
if (x_value == 0) {
//x = 1; 
x_value = 1;
}
}

}

void CLA:: print_value() {
cout << arr[0][0] << endl << arr[0][1] << endl;
}

int main() {
srand(time(NULL));
CLA nm;
nm.manage();
return 0;

}
