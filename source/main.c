#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "../include/manip_data.h"

int main(int argc, char *argv[])
{
    while (true) {
        switch (output_menu(0)) {
            case '1':
                loading();
                input_data();
                break;
            case '2':
                loading();
                output_data();
                break;
            case '3':
                loading();
                reset_data();
                break;
            case '4':
                return 0;
                break;
        }
    }

    return 0;
}