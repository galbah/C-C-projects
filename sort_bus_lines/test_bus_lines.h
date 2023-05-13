#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
/**
 * returns 1 if given array is sorted by distance, 0 else.
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);
/**
 * returns 1 if given array is sorted by durations, 0 else.
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);
/**
 * returns 1 if all elements between start and end of the sorted
 * array are in the original array, 0 else.
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H
// and #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
