#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("WRONG ARGUMENTS\n");
        return 1;
    }
    const char* fileName = argv[1];
    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("FOPEN PROBLEM, ELP!\n");
        return 1;
    }
    
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);    
    WINDOW* win = newwin(LINES - 1, COLS, 1, 0);
    keypad(win, TRUE);
    scrollok (win, FALSE);
    int height = getmaxy(win);
    char** fileContent = NULL;
    char* line = NULL;
    size_t* fileLenght = NULL;
    size_t buffer;
    int lineNumber = 0;
    while (getline(&line, &buffer, file) != -1) {
        fileContent = (char**)realloc(fileContent, (lineNumber + 1) * sizeof(char*));
        if (!fileContent) {
            perror("SO BAD\n");
            exit(1);
        }
        fileLenght = (size_t*)realloc(fileLenght, (lineNumber + 1) * sizeof(size_t));
        if (!fileLenght) {
            perror("SO BAD\n");
            exit(1);
        }
        fileContent[lineNumber] = line;
        fileLenght[lineNumber] = strlen(line);
        lineNumber++;
        line = NULL;
    }
    move(0, 0);
    printw("File: %s", fileName);
    refresh();

    line = NULL;
    int flag = 1;
    int row = 0;
    int column = 0;
    while (flag) {
        wclear(win);
        wmove(win, 1, 0);
        for (int i = 0; i < height - 2 && row + i < lineNumber; i++) {
            char* LineCurrent = NULL;
            if (column < fileLenght[row + i]) {
                LineCurrent = fileContent[row + i] + column;
            } else {
                LineCurrent = "\n";
            }
            mvwprintw(win, i + 1, 0, "%4d: ", row + i);
            waddstr(win, LineCurrent);
        }
        box(win, 0, 0);
        wrefresh(win);
        int input = getch();
        switch (input) {
        case ' ':
        case KEY_DOWN:
            if (row + 1 < lineNumber) { 
                row++;
            }
            break;
        case KEY_UP:
            if (row > 0) {
                row--;
            }
            break;
        case KEY_LEFT:
            if (column > 0) {
                column--;
            }
            break;
        case KEY_RIGHT:
            column++;
            break;
        case 27:
            flag = 0;
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < lineNumber; i++) {
        free(fileContent[i]);
    }
    free(fileContent);
    endwin();
    fclose(file);
    return 0;
}
