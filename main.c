#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void
main_menu();

void
oct_to_str();

void
str_to_oct();

int
main()
{
    char ch[4] = {0};
    unsigned char choise = 0;
    int tch;

    main_menu();
    fgets(ch, 3, stdin);
    ch[strcspn(ch, "\r\n")] = 0;
    tch = atoi(ch);
    if (tch > 3 || tch < 1){
	puts("Wrong choice!");
	exit(1);
    }
    else {
	choise = (unsigned char)tch;
    }
    switch (choise) {
        case 1:
            oct_to_str();
	    break;
        case 2:
            str_to_oct();
	    break;
        case 3:
            exit(0);
    }

    return 0;
}

void
main_menu()
{
    printf("1 - Convert octal permissions to string\n");
    printf("2 - Convert stirng permissions to octal\n");
    printf("3 - Exit\n");
}

void
oct_to_str()
{
    const char *s = "rwxrwxrwx";
    
    unsigned int mask = 511;
    unsigned int user_mask = 0;
    unsigned char user_perm[5] = {0};

    printf("Enter your octal permissions: ");
    fgets(user_perm, 4, stdin);
    user_perm[strcspn(user_perm, "\r\n")] = 0;

    for (int i = 0; i < 3; i++) {
        unsigned char ch = user_perm[i] - '0';
	if (ch > 7 || ch < 0) {
	    puts("Wrong permissions!");
	    exit(1);
	}
        user_mask = (user_mask << 3) | ch;
    }

    int iter = 0;
    for (int i = 8; i >= 0; i--) {
        if ((mask&1) & ((user_mask>>i)&1)) {
            printf("%c", s[iter]);
        } else {
            printf("%c", '-');
        }

        mask >>= 1;
        iter++;
    }

    printf("\n");
}

void
str_to_oct()
{
    char user_perm[11] = {0};
    unsigned int user_mask = 0;

    printf("Enter your string permissions: ");
    fgets(user_perm, 10, stdin);
    user_perm[strcspn(user_perm, "\r\n")] = 0;
    for (int i = 0; i < 9; i++){
	if (user_perm[i] != 'r' &&
	    user_perm[i] != 'w' &&
	    user_perm[i] != 'x' &&
	    user_perm[i] != '-'){
	    puts("Wrong permissions!");
	    exit(1);
	}
    }

    for (int i = 0; i < 9; i += 3) {
        if (user_perm[i] != '-') {
            user_mask |= 1;
        }
        user_mask <<= 1;

        if (user_perm[i + 1] != '-') {
            user_mask |= 1;
        }
        user_mask <<= 1;

        if (user_perm[i + 2] != '-') {
            user_mask |= 1;
        }

        printf("%o", user_mask);
        user_mask = 0;
    }
    printf("\n");
}
