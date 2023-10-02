#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define NUM_PLAYERS 2

typedef struct Square
{
    struct Square *prev;
    struct Square *next;
    struct Square *skip;
    int pos;
} Square;

Square *gen_square(int pos, Square *prev)
{
    Square *sq = (Square *)malloc(sizeof(Square));
    sq->prev = prev;
    sq->next = NULL;
    sq->skip = NULL;
    sq->pos = pos;
    return sq;
}

Square *append(Square *tail)
{
    tail->next = gen_square(tail->pos + 1, tail);
    return tail->next;
}

void create_board(int num_squares, Square **head, Square **tail)
{
    *tail = gen_square(1, NULL);
    *head = *tail;
    for (int i = 1; i < num_squares; i++) {
        *tail = append(*tail);
    }
}

Square *get_square(Square *head, int index)
{
    Square *cur = head;
    for (int i = 0; i < index; i++)
    {
        cur = cur->next;
    }
}

void create_skip(Square *head, int start_num, int end_num)
{
    start_num -= 1;
    end_num -= 1;
    Square *start = get_square(head, start_num);
    Square *end = get_square(head, end_num);
    start->skip = end;
}

int get_roll()
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
    }
    return rand() % 11;
}

int handle_roll()
{
    char buf[4096];
    while (true)
    {
        printf("Press Enter to Roll: ");
        fgets(buf, 4096, stdin);
        int roll = get_roll();
        printf("Your roll was: %d\n", roll);
        switch (roll)
        {
            case 0:
                printf("You got 0, rolling again!");
                continue;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                printf("Moving %d spaces forward.", roll);
                return roll; 
                break;
            case 7:
            case 8:
            case 9:
            case 10:
                printf("Moving %d spaces backward.", 6 - roll);
                return 6 - roll;
                break;
        }
    }
}

void destroy_board(Square *head)
{
    Square *cur = head, *prev = NULL;
    while (cur != NULL)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
}

int main()
{
    printf("Enter the number of squares in the board: ");
    char buf[4096];
    int num_squares;
    fgets(buf, 4096, stdin);
    sscanf(buf, "%d", &num_squares);
    Square *head, *tail;
    create_board(num_squares, &head, &tail);
    bool inLoop = true;
    while(inLoop) {
        printf("Enter 1 to create a skip, 2 to quit: ");
        int op;
        fgets(buf, 4096, stdin);
        sscanf(buf, "%d", &op);
        switch (op) {
            case 1:
                printf("Enter the starting and ending points: ");
                int start_num, end_num;
                fgets(buf, 4096, stdin);
                sscanf(buf, "%d %d", &start_num, &end_num);
                create_skip(head, start_num, end_num);
                break;
            default:
                inLoop = false;
                break;
        }
    }

    Square *player_pos[NUM_PLAYERS];
    for(int i = 0; i < NUM_PLAYERS; i++) {
        player_pos[i] = head;
    }

    int playerIndex = 1;
    while(true) {
        printf("Player %d is on square %d\n", playerIndex+1, player_pos[playerIndex]->pos);
        int change = handle_roll();
        if(change > 0) {
            for(int i = 0; i < change && player_pos[playerIndex]->pos != 100; i++) {
                player_pos[playerIndex] = player_pos[playerIndex]->next;
            }
        } else {
            for(int i = 0; i < -change && player_pos[playerIndex]->pos != 1; i++) {
                player_pos[playerIndex] = player_pos[playerIndex]->prev;
            }
        }
        int cur_pos = player_pos[playerIndex]->pos;
        printf("Player %d is now on square %d\n", playerIndex+1, cur_pos);
        Square *skip_square = player_pos[playerIndex]->skip;
        if(skip_square != NULL) {
            player_pos[playerIndex] = skip_square;
            if (skip_square->pos > cur_pos) {
                printf("This Square is a SLIDE, player %d is now at square %d", playerIndex+1, skip_square->pos);
            } else {
                printf("This Square is a SNAKE, player %d is now at square %d", playerIndex+1, skip_square->pos);
            }
        }
        if(player_pos[playerIndex]->pos == 100) {
            printf("Congrats, player %d, You've WON!", playerIndex+1);
            break;
        }
        playerIndex += 1;
        playerIndex %= NUM_PLAYERS;
    }
    destroy_board(head);
    return 0;
}