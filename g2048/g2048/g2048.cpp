#include <iostream>
#include <conio.h>
#include <cstdlib> 
#include <ctime>
#include <math.h>
#include <iomanip>

using namespace std;

void randomAssignment(int arr[4][4], int);
int randomValue();
void showCells(int arr[4][4]);
char getInput();
bool updateCells(int arr[4][4], char);
void removeSpace(int arr[4]);
void toReverse(int arr[4]);
void rotate(int arr[4][4], int line[4], int index);
void rotateReverse(int arr[4][4], int line[4], int index);
bool summation(int arr[4]);
bool checkFullness(int arr[4][4]);
bool checkLosing(int arr[4][4]);
bool checkWinning(int arr[4][4]);

int main()
{
    const int fist_nums_count = 2;

    int cells[4][4] = {};

    char player_input = '\0';

    bool is_lost = false;
    bool is_win = false;

    srand(static_cast<unsigned int>(time(0)));

    randomAssignment(cells, fist_nums_count);

    system("color 70");
    showCells(cells);

    while (!is_lost && !is_win)
    {
        player_input = getInput();

        if (player_input != '\0') {
            system("color 70");

            if (updateCells(cells, player_input))
                randomAssignment(cells, 1);

            if (checkWinning(cells)) {
                is_win = true;
            }
            else if (checkFullness(cells))
            {
                is_lost = checkLosing(cells);
            }

            system("cls");
            showCells(cells);
        }
        else
        {
            system("color C0");
            system("cls");
            showCells(cells);
            cout << "Wrong Key!\nTry again.\n\n";
        }
    }

    if (is_lost)
    {
        system("color 40");
        cout << "You are a LOSER!\ndon't try it again.\n\n";
    }
    else if (is_win)
    {
        system("color 30");
        cout << "You won the game!\nbut you lost your time.\n\n";
    }
}

void randomAssignment(int cells[4][4], int cell_quantity)
{
    int num = 0;
    while (cell_quantity > 0) {
        num = (rand() % 16);
        if (cells[num / 4][num % 4] == 0) {
            cells[num / 4][num % 4] = randomValue();
            cell_quantity--;
        }
    }
    return;
}


int randomValue() 
{
    const int max_num_ss = 5;
    const int max_num = static_cast<int>(pow(2, max_num_ss));
    int num = ((rand() % max_num) + 1);
    if (num - 1 % 2 == 0)
    {
        return 2 * ((rand() % 2) + 1);
    }
    else
    {
        for (int i = 1;i <= max_num_ss;i++)
        {
            if (pow(2, i) >= num)
            {
                return static_cast<int>(pow(2, max_num_ss - i + 1));
            }
        }
    }
    return 2;
}


void showCells(int cells[4][4])
{
    for (int i = 0;i < 4;i++)
    {
        cout << " ---- ---- ---- ---- " << endl;

        for (int j = 0;j < 4;j++)
        {
            if (cells[i][j]) {
                cout << "|" << left << setw(4) << cells[i][j];
            }
            else {
                cout << "|    ";
            }
        }
        cout << "|" << endl;
    }
    cout << " ---- ---- ---- ---- " << endl;
    return;
}

char getInput()
{
    int inp = _getch();
    if (inp == 224)
    {
        inp = _getch();
        switch (inp)
        {
        case 72:
            inp = 'U';
            break;
        case 80:
            inp = 'D';
            break;
        case 75:
            inp = 'L';
            break;
        case 77:
            inp = 'R';
            break;
        default:
            inp = '\0';
            break;
        }
    }
    else
    {
        inp = '\0';
    }
    return inp;
}

bool updateCells(int cells[4][4], char inp)
{
    bool is_updated = false;
    int last_cells[4][4] = {};
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++)
            last_cells[i][j] = cells[i][j];

    if (inp == 'U' || inp == 'D')
    {
        int line[4] = {};

        for (int i = 0;i < 4;i++)
        {
            rotate(cells, line, i);
            if (inp == 'D')
                toReverse(line);

            removeSpace(line);
            if (summation(line))
                removeSpace(line);
            if (inp == 'D')
                toReverse(line);
            rotateReverse(cells, line, i);
        }
    }
    else if (inp == 'R' || inp == 'L')
    {
        for (int i = 0; i < 4;i++)
        {
            if (inp == 'R')
                toReverse(cells[i]);
            removeSpace(cells[i]);
            if (summation(cells[i]))
                removeSpace(cells[i]);
            if (inp == 'R')
                toReverse(cells[i]);
        }
    }
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++)
            if (last_cells[i][j] != cells[i][j])
            {
                is_updated = true;
                return is_updated;
            }

    return is_updated;
}

void removeSpace(int line[4])
{
    int index = 0;
    bool is_removed = false;

    while (!is_removed)
    {
        is_removed = true;
        for (int i = index;i < 4;i++)
        {
            if (line[i] != 0)
            {
                is_removed = false;
                break;
            }
        }
        if (is_removed)
        {
            break;
        }
        if (line[index] == 0)
        {
            for (int j = index;j < 3;j++)
            {
                line[j] = line[j + 1];
            }
            line[3] = 0;
            is_removed = false;
            index--;
        }
        index++;
    }
    return;
}

void toReverse(int arr[4])
{
    int temp = 0;
    for (int i = 0;i < 2;i++)
    {
        temp = arr[i];
        arr[i] = arr[3 - i];
        arr[3 - i] = temp;
    }
    return;
}

void rotate(int cells[4][4], int line[4], int index)
{
    for (int i = 0;i < 4;i++)
    {
        line[i] = cells[i][index];
    }
    return;
}

void rotateReverse(int cells[4][4], int line[4], int index)
{
    for (int i = 0;i < 4;i++)
    {
        cells[i][index] = line[i];
    }
    return;
}

bool summation(int line[4])
{
    bool is_summation_done = false;
    for (int i = 0;i < 3;i++)
    {
        if (line[i] == line[i + 1])
        {
            line[i] *= 2;
            line[i + 1] = 0;
            is_summation_done = true;
        }
    }
    return is_summation_done;
}

bool checkFullness(int cells[4][4])
{
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++)
            if (cells[i][j] == 0)
                return false;
    return true;
}

bool checkLosing(int cells[4][4])
{
    for (int i = 0;i < 4;i += 2)
        for (int j = 0; j < 4;j += 2)
        {
            if ((i != 3 && cells[i][j] == cells[i + 1][j]) || (j != 3 && cells[i][j] == cells[i][j + 1]))
                return false;
            if ((j != 3 && cells[j][i] == cells[j + 1][i]) || (i != 3 && cells[j][i] == cells[j][i + 1]))
                return false;
        }
    return true;
}

bool checkWinning(int cells[4][4])
{
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++)
            if (cells[i][j] == 2048)
                return true;

    return false;
}
