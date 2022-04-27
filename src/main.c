#include <flights.h>
#include <print_utils.h>
#include <mem.h>

// start 10:30 - 14:00
// start 9:10 - 11:15
int main(int argc, char **argv) {

    assert(argc == 4);

    graph_t *g = read_flights(argv[1]);
    print_graph(stdout, g);

    flight_t *f = get_shortest_flight(g, argv[2], argv[3]);

    if(f == NULL) {
        printf("Such flight does not exist\n");
    } else {
        printf("Fastest flight leaves at: %lf and will take %lf\n", f->leave, f->duration);
    }

    free_graph(g, __free, free_flight);

    printf("malloc cnt: %zu\n", malloc_cnt);
    printf("calloc cnt: %zu\n", calloc_cnt);
    printf("realloc cnt: %zu\n", realloc_cnt);
    printf("free cnt: %zu\n", free_cnt);
}