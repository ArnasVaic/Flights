#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

// Maximum nodes per graph
#define MAX_CITIES 16
// Maximum edges per node
#define MAX_FLIGHTS MAX_CITIES - 1
// Longest city name is at most 85 characters long
//https://www.worldatlas.com/articles/the-10-longest-place-names-in-the-world.html
#define MAX_NAME_LEN 85 + 1

typedef struct flight_t {
    int dur, start;
    char from[MAX_NAME_LEN], to[MAX_NAME_LEN];
} flight_t;

typedef struct graph_t {
    char cities[MAX_CITIES][MAX_NAME_LEN];
    flight_t flights[MAX_CITIES][MAX_FLIGHTS];
    size_t city_cnt;
    size_t flight_cnt[MAX_CITIES];
} graph_t;

typedef struct path_t {
    char cities[MAX_NAME_LEN][MAX_FLIGHTS];
    size_t city_cnt;
    int total_time;
} path_t;

void print_graph(FILE *os, graph_t *graph) {
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        fprintf(os, "%s[%zu]:", graph->cities[i], graph->flight_cnt[i]);
        for(size_t j = 0; j < graph->flight_cnt[i]; ++j) {
            fprintf(os, "{%s, %d}", graph->flights[i][j].to, graph->flights[i][j].dur);
        }
        fputc('\n', os);
    }
}

flight_t read_flight(FILE *is) {
    flight_t flight;
    int read = fscanf(is, "%s %s %d %d", flight.from, flight.to, &flight.start, &flight.dur);
    assert(read == 4); // crashes if flight list is not proper
    return flight;
}

// Does not work 
void add_flight(graph_t *graph, flight_t flight) {
    // check if origin and destination is amongst cities
    bool contains_orig = false;
    bool contains_dest = false;
    for(size_t i = 0; i < MAX_CITIES; ++i) {
        if(!strcmp(graph->cities[i], flight.from)) {
            contains_orig = true;
            graph->flights[i][graph->flight_cnt[i]++] = flight;
        }
        if(!strcmp(graph->cities[i], flight.to)) {
            contains_dest = true;
        }
    }
    if(!contains_orig) {
        // add origin city if not already there
        size_t city_index = graph->city_cnt;
        strcpy(graph->cities[city_index], flight.from);
        graph->flights[city_index][graph->flight_cnt[city_index]++] = flight;
        graph->city_cnt++;
    }
    if(!contains_dest) {
        // add destination city if not already there
        strcpy(graph->cities[graph->city_cnt++], flight.to);
    }
}

void fill_graph(graph_t *graph, const char* filename) {
    FILE *is = fopen(filename, "rb");
    while(!feof(is)) {
        flight_t flight = read_flight(is);
        add_flight(graph, flight);
    }
    fclose(is);
}

void print_path(FILE *os, path_t *path) {
    if(path->city_cnt == 0) {
        fprintf(os, "Path does not exist\n");
        return;
    }
    fprintf(os, "Flight will take %d time units\n", path->total_time);
    for(size_t i = 0; i < path->city_cnt; ++i) {
        fprintf(os, "[%s]", path->cities[i]);
    }
}

int get_city_index(graph_t *graph, const char *city) {
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        if(!strcmp(city, graph->cities[i])) {
            return i;
        }  
    }
    return -1;
}

void print_mat(int mat[][MAX_CITIES], size_t city_cnt) {
    // print matrix
    for(size_t i = 0; i < city_cnt; ++i) {
        for(size_t j = 0; j < city_cnt; ++j) {
            if(mat[i][j] >= INT32_MAX >> 1) {
                printf("inf, ");
            } else {
                printf("%3d, ", mat[i][j]);
            }
        }
        putc('\n', stdout);
    }
}

void find_path(graph_t *graph, const char *from, const char *to, path_t *path) {

    int duration[MAX_CITIES][MAX_CITIES];
    int start[MAX_CITIES][MAX_CITIES];
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        for(size_t j = 0; j < graph->city_cnt; ++j) {
            duration[i][j] = INT32_MAX >> 1;
            start[i][j] = INT32_MAX >> 1;
        }
    }
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        int index = get_city_index(graph, graph->cities[i]);
        for(size_t j = 0; j < graph->city_cnt; ++j) {
            int to_index = get_city_index(graph, graph->flights[i][j].to);
            duration[i][to_index] = graph->flights[i][j].dur;
            start[i][to_index] = graph->flights[i][j].start;
        }
    }

    // https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm
    int dist[MAX_CITIES][MAX_CITIES];
    // initialize each dist to +inf except to themselves
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        for(size_t j = 0; j < graph->city_cnt; ++j) {
            dist[i][j] = INT32_MAX >> 1;
        }
    }
    
    int next[MAX_CITIES][MAX_CITIES];
    // initialize to invalid indices
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        for(size_t j = 0; j < graph->city_cnt; ++j) {
            next[i][j] = -1;
        }
    }
    
    // set weights of existing edges and indices of vertices
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        for(size_t j = 0; j < graph->flight_cnt[i]; ++j) {
            int to_index = get_city_index(graph, graph->flights[i][j].to);
            dist[i][to_index] = graph->flights[i][j].dur;
            next[i][to_index] = to_index;
        }
    }

    // set weights of existing edges and indices of vertices
    for(size_t i = 0; i < graph->city_cnt; ++i) {
        dist[i][i] = 0;
        next[i][i] = i;
    }

    for(size_t k = 0; k < graph->city_cnt; ++k) {
        for(size_t i = 0; i < graph->city_cnt; ++i) {
            for(size_t j = 0; j < graph->city_cnt; ++j) {

                bool shorter = dist[i][j] > dist[i][k] + dist[k][j];
                //bool ontime = duration[i][k] + start[i][k] <= start[k][j];
                if(shorter /*&& ontime*/) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // generate path
    int idx1 = get_city_index(graph, from);
    int idx2 = get_city_index(graph, to);
    path->total_time = dist[idx1][idx2];

    if(next[idx1][idx2] == -1) return;

    strcpy(path->cities[path->city_cnt++], graph->cities[idx1]);
    while(idx1 != idx2) {
        idx1 = next[idx1][idx2];
        strcpy(path->cities[path->city_cnt++], graph->cities[idx1]);
    }
}

int main(int argc, char **argv) {
    if(argc != 4) {
        printf("Usage: %s flight_list_file from to\n", argv[0]);
        return 0;
    }
    graph_t graph = {{0}, {0}, 0, {0}};
    fill_graph(&graph, argv[1]);
    path_t path = {{0}, 0, 0};
    find_path(&graph, argv[2], argv[3], &path);
    print_path(stdout, &path);
}