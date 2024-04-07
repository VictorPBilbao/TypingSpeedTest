#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <locale.h>

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void set_cursor_position(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}

void print_text(char *original_text, char *user_text)
{
    printf("\033[0;32m%s\033[0m", user_text);
    printf("\033[0;33m%s\033[0m \n", original_text + strlen(user_text));
}

void print_speed(int press_count, int err_count, time_t start_time)
{
    printf("Total of keypresses: %d\n", press_count);
    printf("Total of errors: %d\n", err_count);
    if (press_count > 0)
    {
        printf("Accuracy: %.2f%%\n", (1 - (err_count / (float)press_count)) * 100);
    }
    else
    {
        printf("Accuracy: 100%%\n");
    }
    printf("Elapsed time: %.4f seconds\n", difftime(time(NULL), start_time));
}

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
    printf("2. Custom\n");
    printf("3. Leaderboard\n");
    printf("4. Exit\n");
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
    if (choice = 1)
    {
        system("cls");
    }
    else if (choice = 2)
    {
        system("cls");
    }
    else if (choice = 3)
    {
        system("cls");
    }
    else if (choice = 4)
    {
        exit(0);
    }
}

int main()
{
    system("cls");

    char original_text[] = "A Hare was making fun of the Tortoise one day for being so slow. 'Do you ever get anywhere?' he asked with a mocking laugh. 'Yes,' replied the Tortoise, 'and I get there sooner than you think. I'll run you a race and prove it.' The Hare was much amused at the idea of running a race with the Tortoise, but for the fun of the thing he agreed. So the Fox, who had consented to act as judge, marked the distance and started the runners off. The Hare was soon far out of sight, and to make the Tortoise feel very deeply how ridiculous it was for him to try a race with a Hare, he lay down beside the course to take a nap until the Tortoise should catch up. The Tortoise meanwhile kept going slowly but steadily, and, after a time, passed the place where the Hare was sleeping. But the Hare slept on very peacefully; and when at last he did wake up, the Tortoise was near the goal. The Hare now ran his swiftest, but he could not overtake the Tortoise in time.";
    char user_text[100] = "";
    int keypress;
    char next_letter[2];
    int index_position = 0;
    int err_count = 0;
    int press_count = 0;

    int x = 0, y = 0; // Set these to the position where you want to start drawing

    hidecursor();

    time_t start_time, end_time, current_time;
    double elapsed_time;
    start_time = time(NULL); // get the start time

    print_main_menu();
    get_menu_selection();

    print_text(original_text, user_text);

    while (1)
    {
        set_cursor_position(x, y);
        if (kbhit())
        {
            keypress = getch(); // capture a keypress
            press_count++;      // count the number of keypresses
            next_letter[0] = keypress;
            next_letter[1] = '\0'; // convert int to string
            if (next_letter[0] == original_text[index_position])
            {
                strcat(user_text, next_letter);
                index_position++;
            }
            else
            {
                err_count++;
            }
        }
        if (strcmp(original_text, user_text) == 0)
        {
            break;
        }
        print_text(original_text, user_text);
        print_speed(press_count, err_count, start_time);
    }

    system("cls");

    end_time = time(NULL); // get the end time

    elapsed_time = difftime(end_time, start_time); // calculate elapsed time in seconds

    double words_per_minute = (strlen(user_text) / 5.0) / (elapsed_time / 60.0); // calculate words per minute

    printf("Congratulations! You have typed the text correctly!: \033[0;33m%s\033[0m \n", user_text);

    print_speed(press_count, err_count, start_time);
    printf("Words per minute: %.2f\n", words_per_minute);

    return 0;
}