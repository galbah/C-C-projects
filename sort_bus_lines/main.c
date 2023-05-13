#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define MAX_INPUT 60
#define MAX_LINE_NUM 999
#define MIN_LINE_NUM 1
#define MIN_DISTANCE 0
#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MAX_DURATION 100

// functions declaration
int get_lines (BusLine **lines, int *num_of_lines);
void get_line_info (int *line_num, int *distance, int *duration);
void print_lines (BusLine *lines, BusLine *end);
int run_tests (BusLine *start, BusLine *end);

int main (int argc, char *argv[])
{
  if(argc != 2)
  {
    return EXIT_FAILURE;
  }
  BusLine *lines, *start, *end;
  int num_of_lines = 0;
  if (get_lines (&lines, &num_of_lines) == 1)
    {
      return EXIT_FAILURE;
    }
  start = lines;
  end = (lines + num_of_lines - 1);
  if (strcmp (argv[1], "bubble") == 0)
    {
      bubble_sort (start, end);
      print_lines (start, end);
    }
  else if (strcmp (argv[1], "quick") == 0)
    {
      quick_sort (start, end);
      print_lines (start, end);
    }
  else if (strcmp (argv[1], "test") == 0)
    {
      if(run_tests (start, end) == 1)
      {
        return EXIT_FAILURE;
      }
    }
  else
    {
      printf ("USAGE: command is not legal");
      return EXIT_FAILURE;
    }
  free (lines);
  return EXIT_SUCCESS;
}

int get_lines (BusLine **lines, int *num_of_lines)
{
  int line_num = 0, distance = 0, duration = 0;
  char num_of_lines_input[MAX_INPUT];
  bool ok = false;
  while (!ok)
    {
      printf ("Enter number of lines. Then enter\n");
      fgets (num_of_lines_input, MAX_INPUT, stdin);
      if (sscanf (num_of_lines_input, "%d", num_of_lines)
      != 1 || *num_of_lines < 1)
        {
          printf ("ERROR: number of lines should be positive integer\n");
          continue;
        }
      ok = true;
    }
  *lines = malloc (sizeof (BusLine) * (*num_of_lines));
  if (*lines == NULL)
    {
      return EXIT_FAILURE;
    }
  for (int i = 0; i < *num_of_lines; i++)
    {
      BusLine bl;
      get_line_info (&line_num, &distance, &duration);
      bl.line_number = line_num;
      bl.distance = distance;
      bl.duration = duration;
      *(*lines + i) = bl;
    }
  return EXIT_SUCCESS;
}

void get_line_info (int *line_num, int *distance, int *duration)
{
  bool ok = false;
  char line_info[MAX_INPUT];
  while (!ok)
    {
      printf ("Enter line info. Then enter\n");
      fgets (line_info, MAX_INPUT, stdin);
      if (sscanf (line_info, "%d,%d,%d", line_num, distance, duration) != 3)
        {
          printf ("ERROR: all 3 arguments should be integers\n");
          continue;
        }
      if (*line_num < MIN_LINE_NUM || *line_num > MAX_LINE_NUM)
        {
          printf ("ERROR: Line number should be an integer"
                  " between 1 and 999 (includes).\n");
          continue;
        }
      if (*distance < MIN_DISTANCE || *distance > MAX_DISTANCE)
        {
          printf ("ERROR: Distance should be an"
                  " integer between 0 and 1000 (includes).\n");
          continue;
        }
      if (*duration < MIN_DURATION || *duration > MAX_DURATION)
        {
          printf ("ERROR: Duration should be an"
                  " integer between 10 and 100 (includes).\n");
          continue;
        }
      ok = true;
    }
}

int run_tests (BusLine *start, BusLine *end)
{
  BusLine *orig_start = NULL, *orig_end = NULL;
  orig_start = malloc ((end - start + 1) * sizeof (BusLine));
  if (orig_start == NULL)
  {
    return EXIT_FAILURE;
  }
  memcpy (orig_start, start, (end - start + 1) * sizeof (BusLine));
  orig_end = orig_start + (end - start);
  bubble_sort (start, end);
  if (is_sorted_by_distance (start, end) == 1)
    {
      printf ("TEST 1 PASSED: good job\n");
    }
  else
    {
      printf ("TEST 1 FAILED: the array was not sorted by distance\n");
    }
  if (is_equal (start, end, orig_start, orig_end) == 1)
    {
      printf ("TEST 2 PASSED: good job\n");
    }
  else
    {
      printf ("TEST 2 FAILED: the array after"
              " the sort was not legally changed\n");
    }
  quick_sort (start, end);
  if (is_sorted_by_duration (start, end) == 1)
    {
      printf ("TEST 3 PASSED: good job\n");
    }
  else
    {
      printf ("TEST 3 FAILED: the array was not sorted by duration\n");
    }
  if (is_equal (start, end, orig_start, orig_end) == 1)
    {
      printf ("TEST 4 PASSED: good job\n");
    }
  else
    {
      printf ("TEST 4 FAILED: the array after"
              " the sort was not legally changed\n");
    }
  free (orig_start);
  return EXIT_SUCCESS;
}

void print_lines (BusLine *lines, BusLine *end)
{
  while (lines <= end)
    {
      printf ("%d,%d,%d\n",
              lines->line_number, lines->distance, lines->duration);
      lines++;
    }
}