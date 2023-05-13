#include <stdbool.h>
#include "sort_bus_lines.h"
#include "test_bus_lines.h"

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  BusLine *tmp = start;
  while (tmp < end)
    {
      if (tmp->distance > (tmp + 1)->distance)
        {
          return 0;
        }
      tmp++;
    }
  return 1;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  BusLine *tmp = start;
  while (tmp < end)
    {
      if (tmp->duration > (tmp + 1)->duration)
        {
          return 0;
        }
      tmp++;
    }
  return 1;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  BusLine *tmp1 = start_original;
  while (tmp1 <= end_original)
    {
      bool match = false;
      BusLine *tmp2 = start_sorted;
      while (tmp2 <= end_sorted)
        {
          if ((tmp1->duration == tmp2->duration) && (tmp1->distance ==
          tmp2->distance) && (tmp1->line_number == tmp2->line_number))
            {
              match = true;
              break;
            }
          tmp2++;
        }
      if(match == false)
        {
          return 0;
        }
      tmp1++;
    }
  return 1;
}