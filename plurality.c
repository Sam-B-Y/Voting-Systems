#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int l = 0;
    while (l < candidate_count)
    {
        if (strcmp(candidates[l].name, name) == 0)
        {
            candidates[l].votes++;
            l = candidate_count;
            return true;
        }
        l++;
        
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    string winner[MAX];
    int winnercount = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > winnercount)
        {
            memset(winner, 0, MAX * sizeof(string));
            winner[j] = candidates[j].name;
            winnercount = candidates[j].votes;
        }
        else if (candidates[j].votes == winnercount)
        {
            winner[j] = candidates[j].name;
        }
        
    }
    
    for (int k = 0; k < candidate_count; k++)
    {
        if (winner[k] != (void *)0)
        {
            printf("%s\n", winner[k]);
        }
    }
    
    // TODO
    return;
}

