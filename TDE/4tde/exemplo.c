
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_index(char c)
{
    return c - 'a';
}

void print_matrix(int matrix[26][26])
{
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

int main(void)
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.");
        return EXIT_FAILURE;
    }

    int matrix[26][26] = {0};
    int durations[26] = {0};
    int start[26] = {0};
    int finish[26] = {0};
    int room[26] = {0};
    int start_limit[26] = {0};
    int finish_limit[26] = {0};

    int duration;
    char task, curr_dep;
    while (fscanf(file, "%c,%d", &task, &duration) != EOF)
    {
        while ((curr_dep = getc(file)) != '\n')
        {
            if (curr_dep == EOF)
                break;

            if (isalpha(curr_dep))
                matrix[get_index(task)][get_index(curr_dep)] = 1;
        }
        durations[get_index(task)] = duration;
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
            if (matrix[i][j] && finish[j] > start[i])
                start[i] = finish[j];

        finish[i] = start[i] + durations[i];
    }

    int total_time = 0;

    for (int i = 0; i < 26; i++)
        if (finish[i] > total_time)
            total_time = finish[i];

    for (int i = 0; i < 26; i++)
        finish_limit[i] = total_time;

    for (int i = 25; i >= 0; i--)
    {
        start_limit[i] = finish_limit[i] - durations[i];
        for (int j = 0; j < 26; j++)
            if (matrix[i][j] == 1)
                if (finish_limit[j] > start_limit[i])
                {
                    finish_limit[j] = start_limit[i];
                    start_limit[j] = finish_limit[j] - durations[j];
                }
    }

    for (int i = 0; i < 26; i++)
        room[i] = start_limit[i] - start[i];

    printf("Minimum project timespan: %d\n", total_time);
    printf("Critical activities: ");
    for (int i = 0; i < 26; i++)
        if (room[i] == 0)
            printf("%c, ", i + 'a');

    printf("\n");

    return EXIT_SUCCESS;
}
