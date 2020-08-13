#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
    Hi, this program is a simple algorithm
    for creating 'Sudoku' game maps.
    It is perfectly useful for creating this game.
    I basically used very simple functions and libraries
    so this program can be recreated by anyone.
    I hope this will help you, enjoy :))
*/

// This is one part of the nine part of the map
// containing 9 house of a 3x3 table.
struct nine_houses
{
    int data[9];
};

// This function will return the number of the nine part
// based on the map x and y coordinates.
int find_class(int locX, int locY)
{
    return 3 * ( locY / 3 ) + ( locX / 3 );
}

// This function is for putting the numbers in the map
void fill(int index, int map[index][index], int y, int x)
{
    int k;
    for(k = 1; k < 10; k++, x++)
    {
        if(x >= index)
            x = 0;
        map[y][x] = k;
    }
}

// This function will update the array of structs based of the map houses
void update(struct nine_houses class_test[], int index, int map[index][index])
{
    int i, j;
    for (i = 0; i < index; i++)
    {
        for (j = 0; j < index; j++)
        {
            class_test[find_class(j, i)].data[(j % 3) * 3 + (i % 3)] = map[i][j];
        }
    }
}

// This function creates the houses based on the places we give
void create(struct nine_houses class_test[], int index, int map[index][index])
{
    fill(9, map, 0, 0); // We create base on what houses we need
    fill(9, map, 1, 3);
    fill(9, map, 2, 6);
    fill(9, map, 3, 1);
    fill(9, map, 4, 4);
    fill(9, map, 5, 7);
    fill(9, map, 6, 2);
    fill(9, map, 7, 5);
    fill(9, map, 8, 8);
    update(class_test, index, map);
}

// This function does the update function in opposite
void de_update(struct nine_houses class_test[], int index, int map[index][index])
{
    int i, j;
    for (i = 0; i < index; i++)
    {
        for (j = 0; j < index; j++)
        {
            int x = (i % 3) * 3 + j / 3; // Finding the houses
            int y = (i / 3) * 3 + j % 3;
            map[y][x] = class_test[i].data[j];
        }
    }
}

// This function will change two numbers places in the map
void change(struct nine_houses class_test[], int index, int first, int second)
{
    int i, j, first_index, second_index;
    for (i = 0; i < index; i++)
    {
        for (j = 0; j < index; j++)
        {
            if (class_test[i].data[j] == first)
                first_index = j;
            if (class_test[i].data[j] == second)
                second_index = j;
        }
        int holder = class_test[i].data[first_index]; // Changing the places
        class_test[i].data[first_index] = class_test[i].data[second_index];
        class_test[i].data[second_index] = holder;
    }
}

// This function will modify the map
void modify(struct nine_houses class_test[], int index, int map[index][index])
{
    change(class_test, 9, rand() % 9 + 1, rand() % 9 + 1);
    de_update(class_test, 9 , map);
}

// A function for showing the output
void print(int index, int map[index][index])
{
    int i, j;
    for (i = 0; i < index; i++)
    {
        for (j = 0; j < index; j++)
        {
            printf(" %d ", map[i][j]);
            if ((j + 1) % 3 == 0 && j < 8)
                printf(" | ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0 && i < 8)
            printf("---------   ---------   ---------\n");
    }
}

// This function will assert house of the map to 0
void reset_map(int index, int map[index][index])
{
    int i, j;
    for (i = 0; i < index; i++)
        for (j = 0; j < index; j++)
            map[i][j] = 0;
}

// This function will assert the data in 3x3 tables to 0
void reset_struct(struct nine_houses class_test[], int index)
{
    int i, j;
    for (i = 0; i < index; i++)
        for (j = 0; j < index; j++)
            class_test[i].data[j] = 0;
}

// Program starts
int main()
{
    srand(time(0));

    int map[9][9];
    struct nine_houses nine_class[9];

    reset_map(9, map);
    reset_struct(nine_class, 9);

    create(nine_class, 9, map);

    int number = rand() % 10 + 1;
    int i;
    for (i = 0; i < number; i++)
    {
        modify(nine_class, 9, map);
    }

    print(9, map);
    return 0;
}
