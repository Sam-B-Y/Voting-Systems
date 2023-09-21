#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int tolocs[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool noloop(int x, int y);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// This program converts each candidate into a number: first candidate being 0, second one being 1 and so on.
bool vote(int rank, string name, int ranks[])
{
    // TODO
    int l = 0;
    while (l < candidate_count)
    {
        if (strcmp(candidates[l], name) == 0)
        {
            ranks[rank] = l;
            return true;
        }
        l++;

    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int x = 0;

    while (x < candidate_count)
    {

        int y = candidate_count - 1;

        while (y > x)
        {
            preferences[ranks[x]][ranks[y]]++;
            y--;
        }

        x++;
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int x = 0;
    while (x < candidate_count)
    {
        int y = 1;
        while (y < candidate_count)
        {
            if (preferences[x][y] > preferences[y][x])
            {
                pairs[pair_count].winner = x;
                pairs[pair_count].loser = y;
                pair_count++;
            }
            y++;
        }

        x++;
    }
    return;

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //using bubble sort algortihm
    int switches = 1;
    while (switches != 0)
    {
        int x = 0;
        switches = 0;
        while (x < pair_count)
        {
            int y = x + 1;
            if (preferences[pairs[x].winner][pairs[x].loser] < preferences[pairs[y].winner][pairs[y].loser])
            {
                pair cache = pairs[x];
                pairs[x] = pairs[y];
                pairs[y] = cache;
                switches++;
            }
            x++;
        }
    }
    return;
}




// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int x = 0; x < pair_count; x++)
    {
        if (noloop(pairs[x].winner, pairs[x].loser) && !locked[pairs[x].loser][pairs[x].winner])
        {
            tolocs[pairs[x].loser]++;
            locked[pairs[x].winner][pairs[x].loser] = true;
        }
        
    }
    return;
}

bool noloop(int winner, int loser)
{
    if (winner == loser)
    {
        return true;
    }
    for (int z = 0; z < candidate_count; z++)
    {
        if (locked[loser][z])
        {
            if (noloop(z, winner))
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    string winner;
    int x = 0;
    while (x < candidate_count)
    {
        if (tolocs[x] == 0)
        {
            {
                printf("%s\n", candidates[x]);
            }
        }
        x++;
    }

    return;
}