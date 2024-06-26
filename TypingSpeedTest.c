#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>

char original_text[] = "A Hare was making fun of the Tortoise one day for being so slow. 'Do you ever get anywhere?' he asked with a mocking laugh. 'Yes,' replied the Tortoise, 'and I get there sooner than you think. I'll run you a race and prove it.' The Hare was much amused at the idea of running a race with the Tortoise, but for the fun of the thing he agreed. So the Fox, who had consented to act as judge, marked the distance and started the runners off. The Hare was soon far out of sight, and to make the Tortoise feel very deeply how ridiculous it was for him to try a race with a Hare, he lay down beside the course to take a nap until the Tortoise should catch up. The Tortoise meanwhile kept going slowly but steadily, and, after a time, passed the place where the Hare was sleeping. But the Hare slept on very peacefully; and when at last he did wake up, the Tortoise was near the goal. The Hare now ran his swiftest, but he could not overtake the Tortoise in time.";
// char original_text[] = "The quick brown fox jumps over the lazy dog.";
char user_text[sizeof(original_text)] = "";
char error_text[sizeof(original_text)] = "";
char restOfString[sizeof(original_text)] = "";

int TIME_LIMIT = 60;

void print_main_menu()
{
    int choice;

    printf(" _____  _  _  _ __  _        __ _        ___  _ __               _        _____           _         \n");
    printf("|_   _|| || || '_ \\(_) _ _  / _` |      / __|| '_ \\ ___  ___  __| |      |_   _| ___  ___| |_     \n");
    printf("  | |   \\_. || .__/| || ' \\ \\__. |      \\__ \\| .__// -_)/ -_)/ _` |        | |  / -_)(_-/|  _| \n");
    printf("  |_|   |__/ |_|   |_||_||_||___/       |___/|_|   \\___|\\___|\\__/_|        |_|  \\___|/__/ \\__| \n");
    printf("\n");
    printf("Welcome to the Typing Speed Test!\n");
    printf("1. Play\n");
    printf("2. Exit\n");
}

void get_menu_selection()
{
    int choice;
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    while (choice < 1 || choice > 4)
    {
        system("cls");
        print_main_menu();
        printf("Invalid choice! Please enter a valid choice: ");
        scanf("%d", &choice);
    }
    // TODO: Implement the menu options later
    if (choice == 1)
    {
        system("cls");
    }
    else if (choice == 2)
    {
        exit(0);
    }
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void set_cursor_position(int *x, int *y)
{
    COORD coord;
    coord.X = *x;
    coord.Y = *y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}

void print_text()
{
    printf("\033[0;32m%s\033[0m", user_text);
    printf("\033[0;31m%s\033[0m", error_text);
    // printf("%s \n", original_text + strlen(user_text) + strlen(error_text));
    strncpy(restOfString, original_text + strlen(user_text) + strlen(error_text), 100);
    printf("%s", restOfString);
}

float calculate_accuracy(int *press_count, int *err_count)
{
    if (*err_count == *press_count || *press_count == 0)
    {
        return 0;
    }
    else
    {
        return (1 - (*err_count / (float)*press_count)) * 100;
    }
}

float calculate_words_per_minute(int *press_count, int *err_count, time_t *elapsed_time)
{
    return (strlen(user_text) / 5.0) / (*elapsed_time / 60.0);
}

void print_speed(int *press_count, int *err_count, time_t elapsed_time)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int y_position;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    y_position = csbi.srWindow.Bottom / 2; // This will get the middle of the screen

    int x_position = 0;
    y_position = (int)(y_position / 2);
    set_cursor_position(&x_position, &y_position);

    printf("Total of keypresses: %d\n", *press_count);
    printf("Total of errors: %d\n", *err_count);
    printf("Accuracy: %.2f%%\n", calculate_accuracy(press_count, err_count));
    printf("Time Left: %.2f seconds\n", TIME_LIMIT - (float)elapsed_time);
}

void show_statistics(int press_count, int err_count, time_t elapsed_time)
{
    system("cls");

    printf("\033[0;33mCongratulations! You have finished the test!\n\033[0m");

    printf("\nHere are your results:\n");

    printf("+---------------------------+-----------------+\n");
    printf("| %-25s | %-15s |\n", "Metric (Measure)", "Value");
    printf("+---------------------------+-----------------+\n");
    printf("| %-25s | %-15.2f |\n", "Time Elapsed (s)", (float)elapsed_time);
    printf("| %-25s | %-15.2f |\n", "Percentage Completed (%)", (strlen(user_text) / (float)strlen(original_text)) * 100);
    printf("| %-25s | %-15d |\n", "Total Keypresses", press_count);
    printf("| %-25s | %-15d |\n", "Total Errors", err_count);
    printf("| %-25s | %-15.2f |\n", "Accuracy (%)", calculate_accuracy(&press_count, &err_count));
    printf("| %-25s | %-15.2f |\n", "WPM", calculate_words_per_minute(&press_count, &err_count, &elapsed_time));
    printf("+---------------------------+-----------------+\n");

    Sleep(10000);
    system("pause");
}

void initialize_variables(int *keypress, char *next_letter, int *index_position, int *err_count, int *press_count, int *x, int *y, time_t *start_time, double *elapsed_time, bool *timer_started)
{
    *keypress = 0;
    *next_letter = '\0';
    *index_position = 0;
    *err_count = 0;
    *press_count = 0;
    *x = 0;
    *y = 0;
    *start_time = 0;
    *elapsed_time = 0.0;
    *timer_started = false;
}

void handle_keypress(int *keypress, int *press_count, char *next_letter, int *index_position, int *err_count, time_t *start_time, bool *timer_started)
{
    if (*start_time == 0) // if start_time is 0, set it to the current time
    {
        *start_time = time(NULL);
    }
    *keypress = getch(); // capture a keypress
    (*press_count)++;    // count the number of keypresses
    next_letter[0] = *keypress;
    next_letter[1] = '\0'; // convert int to string
    if (next_letter[0] == original_text[*index_position])
    {
        if (strlen(error_text) == 0)
        {
            strcat(user_text, next_letter);
            (*index_position)++;
        }
        else
        {
            strcat(error_text, next_letter);
            (*err_count)++;
        }
    }
    else if (*keypress == 8)
    {
        if (strlen(error_text) > 0)
        {
            error_text[strlen(error_text) - 1] = '\0';
        }
    }
    else
    {
        strcat(error_text, next_letter);
        (*err_count)++;
        Beep(350, 150);
    }
}

int main()
{
    while (1)
    {
        system("cls");
        int keypress;
        char next_letter[2];
        int index_position;
        int err_count;
        int press_count;
        int x, y; // Set these to the position where you want to start drawing
        time_t start_time;
        double elapsed_time;
        bool timer_started;

        initialize_variables(&keypress, next_letter, &index_position, &err_count, &press_count, &x, &y, &start_time, &elapsed_time, &timer_started);

        hidecursor();
        print_main_menu();
        get_menu_selection();
        print_text();

        while (1)
        {
            if (start_time != 0) // only calculate elapsed_time if start_time is not 0
            {
                elapsed_time = difftime(time(NULL), start_time);
            }
            set_cursor_position(&x, &y);
            if (kbhit())
            {
                handle_keypress(&keypress, &press_count, next_letter, &index_position, &err_count, &start_time, &timer_started);
            }
            if ((strcmp(original_text, user_text) == 0 && strlen(error_text) == 0) || (start_time != 0 && elapsed_time >= TIME_LIMIT)) // if the user has typed the entire text or 60 seconds have passed
            {
                break;
            }
            print_text();
            print_speed(&press_count, &err_count, elapsed_time);
        }
        show_statistics(press_count, err_count, elapsed_time);
    }
    return 0;
}