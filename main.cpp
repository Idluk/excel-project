#include <iostream>
#include <windows.h>
#include <string>
#include <chrono>
using namespace std;

void SetCursor(int x = 0, int y = 0) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, pos);
}

int main() {
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");
    srand(time(NULL));

    int cur_coord = 0;
    const int N = 10;

    int* arr = new int[N*N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i*N+j] = 0;
        }
    }
    bool enterPressed = false;
    while (true) {
        SetCursor();

        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (enterPressed) {

                int cellX = (cur_coord % N) * 8 + 8;
                int cellY = cur_coord / N + 2;
                SetCursor(cellX, cellY);
                cout << "     ";
                SetCursor(cellX, cellY);

                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

                string input;
                getline(cin, input);

                if (!input.empty()) {
                    try {
                        arr[cur_coord] = stoi(input);
                    } catch (...) {
                    }
                }

                system("cls");
                Sleep(200);
            }
        } else {
            enterPressed = true;
        }

        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (cur_coord % N == N-1) {
            }
            else cur_coord += 1;
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (cur_coord % N == 0) {
            }
            else cur_coord -= 1;
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if (cur_coord < N*(N-1)) {
                cur_coord += N;
            }
        }
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if (cur_coord >= N) {
                cur_coord -= N;
            }
        }

        if (cur_coord > N*N) cur_coord = N*N-1;
        if (cur_coord < 0) cur_coord = 0;
        
        cout << '\n';
        for (int i = -1; i < N; i++) {
            if (i != -1) {
                printf("%-6d", i);
            }
            for (int j = -1; j < N; j++) {
                if (i == -1) {
                    if (j == -1) {
                        printf("%6s","      ");
                    }
                    else {
                        printf("%6d ", j);
                        cout << "|";
                    }
                }
                else {
                    if (j == -1) continue;
                    if (i*N+j == cur_coord) {
                        printf("%1s%5d ", ">", arr[i*N+j]);
                        cout << "|";
                    }
                    else {
                        printf("%6d ", arr[i*N+j]);
                        cout << "|";
                    }
                }
            }
            cout << '\n';
        }
        Sleep(100);
       
        cout << '\n';
    }

    delete[] arr;
    return 0;
}
