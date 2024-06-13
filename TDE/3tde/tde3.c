#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void dfs(int start_node, int curr_level, int *levels, int **graph, int nodes)
{
    levels[start_node] = curr_level;
    for (int i = 0; i < nodes; i++)
    {
        if (graph[start_node][i] == 1 && levels[i] == -1)
        {
            graph[start_node][i] = 2;
            graph[i][start_node] = 0;
            dfs(i, curr_level + 1, levels, graph, nodes);
        }
    }
}


int lowpoint(int start_node, int *lwpoints, int *levels, int **graph, int nodes)
{
    for (int from = 1; from < nodes; from++)
        for (int to = 1; to < nodes; to++)
            if (graph[from][to] == 1 && levels[from] < levels[to])
                graph[from][to] = 0;

    if (lwpoints[start_node] != -1)
        return lwpoints[start_node];

    lwpoints[start_node] = start_node;

    for (int i = 1; i <= nodes; i++)
    {
        if (graph[start_node][i] == 2 && levels[lowpoint(i, lwpoints, levels, graph, nodes)] < levels[lwpoints[start_node]])
            lwpoints[start_node] = lwpoints[i];
        else if (graph[start_node][i] == 1 && levels[i] < levels[lwpoints[start_node]])
            lwpoints[start_node] = i;
    }

    return lwpoints[start_node];
}

void print_graph(int **graph, int nodes)
{
    for(int i = 0; i < nodes; i++)
    {
        for(int j = 0; j < nodes; j++)
            printf("%d ", graph[i][j]);
        
        printf("\n");
    }
}

int **read_graph(FILE *file, int nodes, int edges)
{
    // Inicializa grafo limpo
    int **graph = (int **)calloc(sizeof(int *), nodes);
    if (graph == NULL)
    {
        printf("Error allocating graph.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < nodes; i++)
    {
        graph[i] = (int *)calloc(sizeof(int), nodes);
        if (graph[i] == NULL)
        {
            printf("Error allocating graph line %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Le as arestas do grafo
    for (int i = 0; i < edges; i++)
    {
        int from, to;
        fscanf(file, "%d %d", &from, &to);
        graph[from][to] = 1; graph[to][from] = 1;
    }

    return graph;
}

void destroy_graph(int **graph, int nodes)
{
    for (int i = 0; i < nodes; i++)
        free(graph[i]);

    free(graph);
}

void print_lowpoints(int *lwpoints, int nodes)
{
    printf("lowpoints: ");
    for (int i = 0; i < nodes; i++)
        printf("%d:%d ", i, lwpoints[i]);

    printf("\n");
}

void print_bridges(int **graph, int *lwpoints, int nodes)
{
    bool has_bridge = false;
    printf("bridges: ");

    for (int from = 1; from < nodes; from++)
        for (int to = 1; to < nodes; to++)
            if (graph[from][to] == 2 && lwpoints[to] == to)
            {
                has_bridge = true;
                printf("(%d,%d) ", from, to);
            }

    if (!has_bridge)
        printf("none");

    printf("\n");
}

void print_articulations(int *articulations, int nodes)
{
    bool has_articulation = false;
    printf("articulations: ");
    for (int i = 0; i < nodes; i++)
        if (articulations[i] != 0)
        {
            has_articulation = true;
            printf("%d ", articulations[i]);
        }

    if (!has_articulation)
        printf("none");

    printf("\n");
}

void print_markers(int *markers, int nodes)
{
    bool has_markers = false;
    printf("markers: ");
    for (int i = 0; i < nodes; i++)
        if (markers[i] != 0)
        {
            has_markers = true;
            printf("%d ", markers[i]);
        }

    if (!has_markers)
        printf("none");

    printf("\n");
}

void print_bicomponents(int **graph, int *markers, int *articulations, int root, int nodes)
{
    printf("bicomponents: ");

    int articulation;
    for (int i = nodes - 1; i > 0; i--)
        if ((articulation = articulations[i]) != 0)
        {
            printf(" {|%d", articulation);
            for (int from = articulation; from < nodes; from++)
                for (int to = 1; to < nodes; to++)

                    if (graph[from][to] == 2)
                    {
                        printf("|%d", to);
                        graph[from][to] = 0;
                    }

            printf("|}");
        }

    bool has_bicomponents = false;

    for (int i = 0; i < nodes; i++)
        if (markers[i] != 0)
            has_bicomponents = true;

    if (has_bicomponents)
    {
        printf(" {|%d", root);
        for (int from = 1; from < nodes; from++)
            for (int to = 1; to < nodes; to++)
                if (graph[from][to] == 2)
                    printf("|%d", to);

        printf("|}\n");
    }

    printf("\n");
}

int main(void)
{
    FILE *file;
    if ((file = fopen("input.txt", "r")) == NULL)
    {
        printf("Error opening file.\n");
        return EXIT_FAILURE;
    }

    int graph_count;
    fscanf(file, "%d", &graph_count);

    for (int i = 0; i < graph_count; i++)
    {
        int nodes, edges;
        fscanf(file, "%d %d", &nodes, &edges);
        nodes++;

        int **graph = read_graph(file, nodes, edges);

        int *levels = (int *)malloc(sizeof(int) * nodes);
        int *lwpoints = (int *)malloc(sizeof(int) * nodes);
        for(int i = 0; i < nodes; i++)
        {
            levels[i] = lwpoints[i] = -1;
        }

        dfs(1, 0, levels, graph, nodes);
        lowpoint(1, lwpoints, levels, graph, nodes);

        int *markers = (int *)calloc(sizeof(int), nodes);
        int *articulations = (int *)calloc(sizeof(int), nodes);

        int root = 1, children = 0;
        for (int to = 1; to < nodes; to++)
            if (graph[root][to] == 2)
            {
                children++;
                if (children > 2)
                    articulations[root] = root;
            }

        for (int from = 1; from < nodes; from++)
            for (int to = 1; to < nodes; to++)
                if (graph[from][to] == 2 && (lwpoints[to] == from || lwpoints[to] == to))
                {
                    markers[from] = to;
                    if (from != root)
                        articulations[from] = from;
                }

        print_lowpoints(lwpoints, nodes);
        print_bridges(graph, lwpoints, nodes);
        print_articulations(articulations, nodes);
        print_markers(markers, nodes);
        print_bicomponents(graph, markers, articulations, root, nodes);

        // Desaloca tudo
        destroy_graph(graph, nodes);
        free(levels);
        free(lwpoints);
        free(markers);
        free(articulations);
    }

    fclose(file);
    return EXIT_SUCCESS;
}
