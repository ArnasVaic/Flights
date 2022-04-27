# Flights

## What does it do
This application finds the fastest flight from city A to city B given the list of all flights.

## How to use it
```
$> ./flights.exe list_of_flights.txt city_A city_B
```

## How does the flight list look

Flight list file must contain the list of all flights.
Each flight has 4 pieces of data:
* origin city
* destination city
* leave time
* flight duration
  
Example flight:
```
Vilnius Warsaw 1100 0120
```

## How does it work

This application stores flight data as a graph using neighbour adjacency lists.