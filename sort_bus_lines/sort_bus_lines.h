#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
/**
 * TODO add documentation
 */
typedef struct BusLine {
    int line_number, distance, duration;
} BusLine;

/**
 * sorts the given array using bubble sort, sorts it by distance.
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * sorts the given array using quick sort, sorts it by duration.
 */
void quick_sort (BusLine *start, BusLine *end);

/**
 * a helper for quick sort, takes the last element as
 * pivot and put all lower value elements on the right of it
 * and higher value elements on the left of it
 */
BusLine *partition (BusLine *start, BusLine *end);
// write only between #define EX2_REPO_SORTBUSLINES_H
// and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
