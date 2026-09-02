#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

// Cross-Platform Setup
#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#endif

// Clears screen without flickering (ANSI escape sequences)
#define clrscr() printf("\033[2J\033[H")
#define CYCLE 60

// Global flag for graceful Ctrl+C handling
volatile int keep_running = 1;

void sigint_handler(int sig)
{
    keep_running = 0;
}

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

// Helper to clear leftover newline characters from input buffer
void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

void show_menu()
{
    clrscr();
    printf("===============================================\n");
    printf("||        DIGITAL CLOCK & TIMER SUITE        ||\n");
    printf("===============================================\n");
    printf("||  1. Real-Time Clock                       ||\n");
    printf("||  2. Countdown Timer                       ||\n");
    printf("||  3. Stopwatch                             ||\n");
    printf("||  4. Set Alarm                             ||\n");
    printf("||  0. Exit                                  ||\n");
    printf("===============================================\n");
    printf("Select an option: ");
}

void real_time_clock()
{
    clrscr();
    printf("Real-Time Clock (Press Ctrl+C to return to menu)\n");
    printf("-------------------------------------------------\n");
    signal(SIGINT, sigint_handler);

    while (keep_running)
    {
        time_t raw_time;
        struct tm *time_info;
        time(&raw_time);
        time_info = localtime(&raw_time);

        clrscr();
        printf("-------------------------------------------------\n");
        printf("||                                           ||\n");
        printf("||           CURRENT TIME: %02d:%02d:%02d          ||\n",
               time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
        printf("||           DATE: %04d-%02d-%02d                ||\n",
               time_info->tm_year + 1900, time_info->tm_mon + 1, time_info->tm_mday);
        printf("||                                           ||\n");
        printf("-------------------------------------------------\n");
        printf("Real-Time Clock (Press Ctrl+C to return to menu)\n");

        sleep(1);
    }
    signal(SIGINT, SIG_DFL);
    keep_running = 1;
}

void countdown_timer()
{
    int hour, minute, second;
    clrscr();
    printf("===============================================\n");
    printf("||            COUNTDOWN TIMER                ||\n");
    printf("===============================================\n\n");
    printf("Set the countdown duration.\n");
    printf("(Example: type '0 5 30' for 5 mins and 30 secs)\n\n");
    printf("Your time (HH MM SS): ");

    if (scanf("%d %d %d", &hour, &minute, &second) != 3)
    {
        printf("\nInvalid input. Enter numbers only.\n");
        clear_buffer();
        sleep(2);
        return;
    }
    clear_buffer();

    if (hour < 0 || minute < 0 || minute >= CYCLE || second < 0 || second >= CYCLE)
    {
        printf("\nInvalid time. Minutes and seconds must be under 60.\n");
        sleep(2);
        return;
    }

    // Convert everything to total seconds for accurate countdown
    int total_seconds = hour * 3600 + minute * 60 + second;

    signal(SIGINT, sigint_handler);
    while (total_seconds >= 0 && keep_running)
    {
        int h = total_seconds / 3600;
        int m = (total_seconds % 3600) / 60;
        int s = total_seconds % 60;

        clrscr();
        printf("====================\n");
        printf("||                ||\n");
        printf("||    %02d:%02d:%02d    ||\n", h, m, s);
        printf("||                ||\n");
        printf("====================\n");
        printf(" (Press Ctrl+C to quit early)\n");

        if (total_seconds == 0)
        {
            break;
        }

        sleep(1);
        total_seconds--;
    }

    signal(SIGINT, SIG_DFL);
    keep_running = 1;

    if (total_seconds <= 0)
    {
        clrscr();
        printf("----------------------------------------\n");
        printf("|                TIME UP!              |\n");
        printf("----------------------------------------\n\n");
        printf("Your countdown has finished.\n");
        play_alert_sound();
        printf("\nPress Enter to continue...");
        getchar();
    }
}

void stopwatch()
{
    clrscr();
    printf("===============================================\n");
    printf("||               STOPWATCH                   ||\n");
    printf("===============================================\n\n");
    printf("Stopwatch started! (Press Ctrl+C to stop)\n");

    signal(SIGINT, sigint_handler);
    time_t start_time = time(NULL);

    while (keep_running)
    {
        time_t current_time = time(NULL);
        int elapsed = (int)difftime(current_time, start_time);

        int h = elapsed / 3600;
        int m = (elapsed % 3600) / 60;
        int s = elapsed % 60;

        clrscr();
        printf("===============================================\n");
        printf("||               STOPWATCH                   ||\n");
        printf("===============================================\n\n");
        printf("Stopwatch running... (Press Ctrl+C to stop)\n\n");
        printf("====================\n");
        printf("||                ||\n");
        printf("||    %02d:%02d:%02d    ||\n", h, m, s);
        printf("||                ||\n");
        printf("====================\n");

        sleep(1);
    }

    signal(SIGINT, SIG_DFL);
    keep_running = 1;

    time_t end_time = time(NULL);
    int elapsed = (int)difftime(end_time, start_time);
    int h = elapsed / 3600;
    int m = (elapsed % 3600) / 60;
    int s = elapsed % 60;

    clrscr();
    printf("===============================================\n");
    printf("||               STOPWATCH                   ||\n");
    printf("===============================================\n\n");
    printf("Stopped at: %02d:%02d:%02d\n", h, m, s);
    printf("\nPress Enter to continue...");
    getchar();
}

// set_alarm() — named this way because alarm() is already declared in <unistd.h>
void set_alarm()
{
    int alarm_h, alarm_m, alarm_s;
    clrscr();
    printf("===============================================\n");
    printf("||                 ALARM                     ||\n");
    printf("===============================================\n\n");
    printf("Set the alarm time (24-hour format).\n");
    printf("(Example: type '14 30 0' for 2:30 PM)\n\n");
    printf("Alarm time (HH MM SS): ");

    if (scanf("%d %d %d", &alarm_h, &alarm_m, &alarm_s) != 3)
    {
        printf("\nInvalid input. Enter numbers only.\n");
        clear_buffer();
        sleep(2);
        return;
    }
    clear_buffer();

    if (alarm_h < 0 || alarm_h >= 24 || alarm_m < 0 || alarm_m >= 60 || alarm_s < 0 || alarm_s >= 60)
    {
        printf("\nInvalid time. HH must be 0-23, MM and SS must be 0-59.\n");
        sleep(2);
        return;
    }

    clrscr();
    printf("Alarm set for %02d:%02d:%02d\n", alarm_h, alarm_m, alarm_s);
    printf("Waiting... (Press Ctrl+C to cancel)\n");

    signal(SIGINT, sigint_handler);

    while (keep_running)
    {
        time_t raw_time;
        struct tm *time_info;
        time(&raw_time);
        time_info = localtime(&raw_time);

        if (time_info->tm_hour == alarm_h && time_info->tm_min == alarm_m && time_info->tm_sec == alarm_s)
        {
            break;
        }

        clrscr();
        printf("Alarm set for: %02d:%02d:%02d\n", alarm_h, alarm_m, alarm_s);
        printf("Current time : %02d:%02d:%02d\n", time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
        printf("\nWaiting... (Press Ctrl+C to cancel)\n");

        sleep(1);
    }

    signal(SIGINT, SIG_DFL);
    keep_running = 1;

    if (!keep_running)
    {
        clrscr();
        printf("Alarm cancelled.\n");
        sleep(2);
        return;
    }

    clrscr();
    printf("===============================================\n");
    printf("||                ALARM RINGING!             ||\n");
    printf("===============================================\n\n");
    printf("It's %02d:%02d:%02d.\n", alarm_h, alarm_m, alarm_s);

    for (int i = 0; i < 5; i++)
    {
        play_alert_sound();
        sleep(1);
    }

    printf("\nPress Enter to stop and continue...");
    getchar();
}

int main()
{
    int choice;
    while (1)
    {
        show_menu();
        if (scanf("%d", &choice) != 1)
        {
            clear_buffer(); // Clear invalid input (e.g., letters)
            continue;
        }

        switch (choice)
        {
        case 1:
            real_time_clock();
            break;
        case 2:
            countdown_timer();
            break;
        case 3:
            stopwatch();
            break;
        case 4:
            set_alarm();
            break;
        case 0:
            clrscr();
            printf("Exiting Digital Clock & Timer Suite. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            sleep(1);
        }
    }
    return 0;
}
