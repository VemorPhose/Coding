#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int canExecute(int process, int *working, int m, int n, int request[][n], int allocation[][n], int *finish)
{
    if (finish[process])
        return 0;
    for (int j = 0; j < n; j++)
        if (request[process][j] > working[j])
            return 0;
    return 1;
}

void findMinimumSet(int m, int n, int *finish, int allocation[][n],
                    int request[][n], int *resources)
{
    int minSet[m], minSize = m + 1;
    int currentSet[m], size = 0;

    for (int i = 0; i < m; i++)
    {
        if (!finish[i])
        {
            currentSet[size++] = i;

            int working[n];
            int testFinish[m];

            for (int j = 0; j < n; j++)
            {
                working[j] = resources[j];
                for (int k = 0; k < size; k++)
                    working[j] += allocation[currentSet[k]][j];
            }

            for (int j = 0; j < m; j++)
                testFinish[j] = finish[j] || (j == currentSet[size - 1]);
            int change;
            do
            {
                change = 0;
                for (int j = 0; j < m; j++)
                {
                    if (canExecute(j, working, m, n, request, allocation, testFinish))
                    {
                        testFinish[j] = 1;
                        for (int k = 0; k < n; k++)
                            working[k] += allocation[j][k];
                        change = 1;
                    }
                }
            } while (change);

            // Check if deadlock is resolved
            int resolved = 1;
            for (int j = 0; j < m; j++)
                if (!testFinish[j])
                {
                    resolved = 0;
                    break;
                }
            if (resolved && size < minSize)
            {
                minSize = size;
                for (int j = 0; j < size; j++)
                    minSet[j] = currentSet[j];
            }
        }
    }

    if (minSize <= m)
    {
        printf("\nMinimum processes to terminate: ");
        for (int i = 0; i < minSize; i++)
            printf("P%d ", minSet[i]);
        printf("\n");
    }
}

void main()
{
    printf("Number of distinct resources: ");
    int n;
    scanf("%d", &n);
    printf("Number of processes: ");
    int m;
    scanf("%d", &m);
    int resources[n];
    printf("Number of each resource: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &resources[i]);
    int allocation[m][n];
    printf("Allocation matrix: ");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &allocation[i][j]);
    int request[m][n];
    printf("Request matrix: ");
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &request[i][j]);

    int working[n];
    for (int i = 0; i < n; i++)
        working[i] = resources[i];

    int finish[m];
    for (int i = 0; i < m; i++)
        finish[i] = 0;

    // Detect deadlock
    int change = 0;
    do
    {
        change = 0;
        for (int i = 0; i < m; i++)
        {
            if (canExecute(i, working, m, n, request, allocation, finish))
            {
                finish[i] = 1;
                for (int j = 0; j < n; j++)
                    working[j] += allocation[i][j];
                change = 1;
            }
        }
    } while (change);

    // Check for detected deadlock
    int deadlock = 0;
    for (int i = 0; i < m; i++)
    {
        if (!finish[i])
        {
            deadlock = 1;
            break;
        }
    }

    if (!deadlock)
    {
        printf("\nNo deadlock exists.\n");
    }
    else
    {
        printf("\nDeadlock exists.\n");
        findMinimumSet(m, n, finish, allocation, request, resources);
    }
}