#include <stdio.h>

// --- Cross-Platform Setup ---
#ifdef _WIN32
#include <windows.h>

// Added a space in #define and wrapped x in parentheses
#define sleep(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#endif

// Clears screen without flickering
#define clrscr() printf("\033[2J\033[H")
#define CYCLE 60

// Cross-Platform Alert Sound
void play_alert_sound()
{
#ifdef _WIN32
    Beep(800, 300);
    Sleep(100);
    Beep(1000, 500);
#else
    printf("\a\a\a");
    fflush(stdout);
#endif
}

int main()
{
    int hour, minute, second;

    clrscr();
    printf("===============================================\n");
    printf("||               SIMPLE TIMER                ||\n");
    printf("===============================================\n\n");

    printf("Hey there! Let's set a timer.\n");
    printf("Please enter the hours, minutes, and seconds.\n");
    printf("(Example: type '0 5 30' for 5 mins and 30 secs)\n\n");

    printf("Your time (HH MM SS): ");

    if (scanf("%d %d %d", &hour, &minute, &second) != 3)
    {
        printf("\nOops! Please enter valid numbers only.\n");
        return 1;
    }

    if (hour < 0 || minute < 0 || minute >= CYCLE || second < 0 || second >= CYCLE)
    {
        printf("\nHmm, that's not a valid time. Keep mins/secs under 60!\n");
        return 1;
    }

    clrscr();

    int h = 0, m = 0, s = 0;

    // --- Main Timer Loop ---
    while (1)
    {

        printf("====================\n");
        printf("||                ||\n");
        printf("||                ||\n");
        printf("||    %02d:%02d:%02d    ||\n", h, m, s);
        printf("||                ||\n");
        printf("||                ||\n");
        printf("====================\n");
        printf(" (Press Ctrl+C to quit early)\n");

        if (h == hour && m == minute && s == second)
        {
            break;
        }

        sleep(1);
        clrscr();

        s++;
        if (s == CYCLE)
        {
            m++;
            s = 0;
        }
        if (m == CYCLE)
        {
            h++;
            m = 0;
        }
    }

    clrscr();
    printf("----------------------------------------\n");
    printf("|                TIME UP!              |\n");
    printf("----------------------------------------\n\n");

    printf("Your timer for %02d:%02d:%02d has finished.\n", hour, minute, second);

    // Play the alert sound
    play_alert_sound();

    return 0;
}
