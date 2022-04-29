#ifndef FLIGHTS_H
#define FLIGHTS_H

// System headers
#include <limits.h>
#include <stdio.h>

// My headers
#include <graph.h>
#include <mymem.h>

// Longest city name in the world is 85 characters
#define MAX_CITY_NAME_LEN 128

typedef struct flight_t {
    double leave;
    double duration;
    char *orig;
    char *dest;
} flight_t;

/// Free flight object
/// @param ptr pointer to flight
/// @return nothing
void free_flight(void *ptr);

/// Read flight data from file and store it in a graph
/// @param file input file
/// @return graph containing flight info
graph_t* read_flights(const char* file);

/// Returns the shortest flight from city c1 to city c2
/// if no such flight exists returns NULL
/// @param g graph of flights
/// @param c1 name of origin city
/// @param c2 name of destination city
/// @return pointer to shortest flight 
flight_t* get_shortest_flight(graph_t *g, const char *c1, const char *c2);

#endif /* FLIGHTS_H */