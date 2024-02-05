#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct 
{
    int x;
    int y;
} vector2d;

int hash() {
    return rand() % 5;
}

vector2d output(vector2d input) {
    input.x = hash();
    input.y = hash();
    return input;
}

int main() {
    WINDOW *win = initscr();
    keypad(win, true);
    nodelay(win, true);
    cbreak();
    noecho();
    curs_set(0);  // Hide the cursor
  
    int ch;
    int score = 0;

    vector2d food = {2, 4};
    vector2d dir = {0, 0};
    vector2d pos = {1, 1};
    vector2d tail[100];

    int len = 1;

    while (true) {
        int pressed = wgetch(win);
        switch (pressed) {
            case KEY_RIGHT:
                dir.x = 1;
                dir.y = 0;
                break;
            case KEY_LEFT:
                dir.x = -1;
                dir.y = 0;
                break;
            case KEY_UP:
                dir.y = -1;
                dir.x = 0;
                break;
            case KEY_DOWN:
                dir.y = 1;
                dir.x = 0;
                break;
        }

        pos.x += dir.x;
        pos.y += dir.y;

        erase();

        // Draw the tail if the snake has a length greater than 1
        if (len > 1) {
            // Draw the tail of the snake (optional)
            for (int i = 0; i < len; i++)
            {
                int tailX = pos.x - dir.x;
                int tailY = pos.y - dir.y;
                mvaddch(tailY, tailX, '*');    
            }
            
            
        }

        mvaddch(pos.y, pos.x, '*');
        mvaddch(food.y, food.x, '0');

        if (pos.x == food.x && pos.y == food.y) {
            score++;
            food = output(food);
            len++;  // Increase the length of the snake
            curs_set(0);  // Hide the cursor each time food appears
        }

        mvprintw(0, 0, "Score: %d", score);
        refresh();
        usleep(100000);
    }

    endwin();
    return 0;
}
