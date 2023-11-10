#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {

    struct termios ttyAttributes;

    // Make sure the FD is a TTY device
    if (!isatty(STDIN_FILENO)) {
        perror("FD is not a tty");
        _Exit(1);
    }

    if (argc == 1) {
        if (tcgetattr(STDIN_FILENO, &ttyAttributes) != 0) {
            perror("tcgetattr error");
        }

        // Print settings
        printf("speed %d baud; CLOCAL %d, PARODD %d\n", (int) (cfgetispeed(&ttyAttributes)), (int) (ttyAttributes.c_cflag &CLOCAL), (int) (ttyAttributes.c_cflag &PARODD));
        printf("VINTR %d, VERASE %d, VKILL %d, VSTART %d, VSTOP %d\n", (ttyAttributes.c_cc[VINTR]), (ttyAttributes.c_cc[VERASE]), (ttyAttributes.c_cc[VKILL]), (ttyAttributes.c_cc[VSTART]), (ttyAttributes.c_cc[VSTOP]));
        printf("BRKINT %d, INPCK %d, INLCR %d\n", (int) (ttyAttributes.c_iflag &BRKINT), (int) (ttyAttributes.c_iflag &INPCK), (int) (ttyAttributes.c_iflag &INLCR));
    
        // // For some reason the character equavalent doent print out
        // printf("speed %c baud; CLOCAL %c, PARODD %c\n", (cfgetispeed(&ttyAttributes)), (ttyAttributes.c_cflag &CLOCAL), (ttyAttributes.c_cflag &PARODD));
        // printf("VINTR %d, VERASE %d, VKILL %d, VSTART %d, VSTOP %d\n", (ttyAttributes.c_cc[VINTR]), (ttyAttributes.c_cc[VERASE]), (ttyAttributes.c_cc[VKILL]), (ttyAttributes.c_cc[VSTART]), (ttyAttributes.c_cc[VSTOP]));
        // printf("BRKINT %c, INPCK %c, INLCR %c\n", (ttyAttributes.c_iflag &BRKINT), (ttyAttributes.c_iflag &INPCK), (ttyAttributes.c_iflag &INLCR));
    }
    else {

        int i;
        for (i=1; i < argc; ++i) {

            if (strcmp(argv[i], "erase") == 0) {
                ++i;
                if (argv[i][0] == '^')
                    ttyAttributes.c_cc[VERASE] = argv[i][1];
                else
                    ttyAttributes.c_cc[VERASE] = argv[i][0];
                printf("VERASE set\n");
            }
            else if (strcmp(argv[i], "kill") == 0) {
                ++i;
                if (argv[i][0] == '^')
                    ttyAttributes.c_cc[VKILL] = argv[i][1];
                else
                    ttyAttributes.c_cc[VERASE] = argv[i][0];
                printf("VKILL set\n");
            }

            if (strcmp(argv[i], "icrnl") == 0 || strcmp(argv[i], "-icrnl") == 0) {
                if (argv[i][0] == '-')
                    ttyAttributes.c_iflag &= ~ICRNL;
                else
                    ttyAttributes.c_iflag |= ICRNL;
                printf("ICRNL set\n");
            }
            else if (strcmp(argv[i], "onlcr") == 0 || strcmp(argv[i], "-onlcr") == 0) {
                if (argv[i][0] == '-')
                    ttyAttributes.c_iflag &= ~ONLCR;
                else
                    ttyAttributes.c_iflag |= ONLCR;
                printf("ONLCR set\n");
            }
            else if (strcmp(argv[i], "echo") == 0 || strcmp(argv[i], "-echo") == 0) {/////////////////////
                if (argv[i][0] == '-')
                    ttyAttributes.c_iflag &= ~ECHO;
                else
                    ttyAttributes.c_iflag |= ECHO;
                printf("ECHO set\n");
            }
            else if (strcmp(argv[i], "echoe") == 0 || strcmp(argv[i], "-echoe") == 0) {
                if (argv[i][0] == '-')
                    ttyAttributes.c_iflag &= ~ECHOE;
                else
                    ttyAttributes.c_iflag |= ECHOE;
                printf("ECHOE set\n");
            }
            // else if (strcmp(argv[i], "olcuc") == 0 || strcmp(argv[i], "-olcuc") == 0) {
            //     if (argv[i][0] == '-')
            //         ttyAttributes.c_iflag &= ~OLCUC;
            //     else
            //         ttyAttributes.c_iflag |= OLCUC;
            //     printf("OLCUC set\n");
            // }
            // else if (strcmp(argv[i], "xtabs") == 0 || strcmp(argv[i], "-xtabs") == 0) {
            //     if (argv[i][0] == '-')
            //         ttyAttributes.c_iflag &= ~XTABS;
            //     else
            //         ttyAttributes.c_iflag |= XTABS;
            //     printf("XTABS set\n");
            // }
            else if (strcmp(argv[i], "icanon") == 0 || strcmp(argv[i], "-icanon") == 0) {
                if (argv[i][0] == '-')
                    ttyAttributes.c_iflag &= ~ICANON;
                else
                    ttyAttributes.c_iflag |= ICANON;
                printf("ICANON set\n");
            }
            else if (strcmp(argv[i], "isig") == 0 || strcmp(argv[i], "-isig") == 0) {
                if (argv[i][0] == '-')
                    ttyAttributes.c_iflag &= ~ISIG;
                else
                    ttyAttributes.c_iflag |= ISIG;
                printf("ISIG set\n");
            }
            else {
                printf("Unknown argument: %s\n", argv[i]);
            }


        }

        // Set attributes
        tcsetattr(STDIN_FILENO, TCSANOW, &ttyAttributes);

    }

}