#include <stdio.h>
#define SIZE 10

void display_grid(char grid[][SIZE], int row, int col){
    for(int i = 0; i<row; i++){
        for(int c = 0; c<col; c++){
            printf("%c", grid[i][c]);
        }
        printf("\n");
    }
}
void flood_fill_rec(char grid[][SIZE], int y, int x, char new_ch, char old_ch){
    if(x >= SIZE || y >= SIZE || x < 0 || y < 0){
        return;
    }
    // if(grid[y][x] == '*' || grid[y][x] == new_ch)
    //     return;
    if(grid[y][x] != old_ch)
        return;
    grid[y][x] = new_ch;

    flood_fill_rec(grid, y+1, x, new_ch, old_ch); // down
    flood_fill_rec(grid, y-1, x, new_ch, old_ch); // up
    flood_fill_rec(grid, y, x-1, new_ch, old_ch); // left
    flood_fill_rec(grid, y, x+1, new_ch, old_ch); // right
}

void flood_fill(char grid[][SIZE], int x, int y, char ch)
{
    char old_char = grid[x][y];//take the old char from x,y
    flood_fill_rec(grid, x, y, ch, old_char);
}

int main(){
    // int n = 5;
    // toh(n, 'A', 'C', 'B');
    char grid[SIZE][SIZE] = {{'*','*','*','*','*','*','*','*','*','*'},
                             {'*',' ','*',' ',' ','*',' ',' ',' ','*'},
                             {'*',' ','*',' ',' ','*',' ',' ',' ','*'},
                             {'*',' ','*',' ',' ','*',' ',' ',' ','*'},
                             {'*',' ','*',' ',' ','*',' ',' ',' ','*'},
                             {'*',' ','*',' ',' ',' ',' ',' ',' ','*'},
                             {'*',' ','*',' ',' ','*',' ',' ',' ','*'},
                             {'*',' ','*',' ',' ','*',' ',' ',' ','*'},
                             {'*',' ','*',' ',' ','*',' ',' ',' ','*'},
                             {'*','*','*','*','*','*','*','*','*','*'}};
    display_grid(grid, SIZE, SIZE);
    printf("\n\n");

    flood_fill(grid, 3, 3, '~');
    display_grid(grid, SIZE, SIZE);

    return 0;
}