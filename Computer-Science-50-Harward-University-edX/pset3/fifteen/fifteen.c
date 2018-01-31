/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // setting biggest value in board
    int max_value = d * d - 1;

    // // creating empty board
    // int board[d][d];

    // filling board decreasingly
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = max_value;
            max_value--;
        }
    }

    // if d is even:
    if (d % 2 == 0)
    {
        // secont-to-last and third-to-last board numbers are swaped
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }

}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // for every line
    for (int i = 0; i < d; i++)
    {

        // prints row separatos ---- ----
        for (int k = 0; k < d; k++)
        {
            printf(" ----");
        }
        printf("\n");

        // for every value in row
        for (int j = 0; j < d; j++)
        {
            // if value != 0, prints value, otherwise prints _
            if (board[i][j] != 0)
            {
                printf("| %2i ", board[i][j]);
            }

            else
            {
                printf("| __ ");
            }

        }
        printf("|\n");

    }

    // prints row separators ---- for last line
    for (int k = 0; k < d; k++)
    {
        printf(" ----");
    }
    printf("\n");

}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    if (tile < 0 || tile > d * d - 1)
    {
        return false;
    }

    // variables for location tracking
    int tile_row, tile_col, zero_row, zero_col;

    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // finding location of input value
            if (board[i][j] == tile){
                tile_row = i;
                tile_col = j;
            }

            // finding location of 0 value
            if (board[i][j] == 0){
                zero_row = i;
                zero_col = j;
            }
        }
    }

    // squared differences between tile location and 0 location
    int diff_row = (zero_row - tile_row) * (zero_row - tile_row);
    int diff_col = (zero_col - tile_col) * (zero_col - tile_col);

    // if swap is possible, tile and 0 are swaped
    if (diff_row + diff_col == 1)
    {
        board[zero_row][zero_col] = tile;
        board[tile_row][tile_col] = 0;
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // counter for sequence evaluation
    int counter = 1;

    // checks if all tiles are sorted increasingly
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // counter reset to 0 for last tile in board
            if (counter == d * d)
            {
                counter = 0;
            }

            if (board[i][j] != counter)
            {
                return false;
            }
            counter++;
        }
    }
    return true;
}
