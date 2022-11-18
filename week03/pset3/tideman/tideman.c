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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergeSort(int arr[], int length);
int verifyCycle(int wanted, int pointing);

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
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) 
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i]) 
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int temp_arr[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        temp_arr[i] = preferences[pairs[i].winner][pairs[i].loser];
    }

    mergeSort(temp_arr, pair_count);

    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i, swap_winner, swap_loser; j < pair_count; j++)
        {
            if (temp_arr[i] == preferences[pairs[j].winner][pairs[j].loser])
            {
                swap_winner = pairs[i].winner;
                swap_loser = pairs[i].loser;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = swap_winner;
                pairs[j].loser = swap_loser;
                break;
            }
        }
    }

    return;
}

int verifyCycle(int wanted, int pointing)
{
    int n = 0;
    int pointings[candidate_count];
    //if stays -1 means that this pointing doesn't have anyone pointing it
    pointings[0] = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][pointing] == 1)
        {
            pointings[n] = i;           
            n++;
        }
    }

    //try without pointings
    if (pointing == wanted)
    {
        return 1;
    }
    else if (pointings[0] == -1)
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        int match = verifyCycle(wanted, pointings[i]);
        if (match == 1)
        {
            return 1;
        }
    }
    return 0;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = 0;
        }
    }

    for (int lock_count = 0, cycle; lock_count < pair_count; lock_count++)
    {
        cycle = verifyCycle(pairs[lock_count].loser, pairs[lock_count].winner);
        if (cycle == 0)
        {
            locked[pairs[lock_count].winner][pairs[lock_count].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int n;
    for (int i = 0; i < candidate_count; i++)
    {
        n = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == 1)
            {
                n++;
            }
        }
        if (n == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

void merge(int arr[], int l, int m, int r)
{
    int len_l = m - l + 1;
    int len_r = r - m; 

    int temp_l[len_l];
    int temp_r[len_r];

    for (int i = 0; i < len_l; i++)
    {
        temp_l[i] = arr[l + i];
    }

    for (int j = 0; j < len_r; j++)
    {
        temp_r[j] = arr[m + 1 + j];
    }

    for (int i = 0, j = 0, k = l; k <= r; k++)
    {
        if ((i < len_l) && (temp_l[i] >= temp_r[j] || j >= len_r))
        {
            arr[k] = temp_l[i];
            i++;
        }
        else
        {
            arr[k] = temp_r[j];
            j++;
        }
    }
}

void mergeRecursive(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeRecursive(arr, l, m);
        mergeRecursive(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(int arr[], int length)
{
    mergeRecursive(arr, 0, length - 1);
}