#include "sort_bus_lines.h"

void swap (BusLine *a, BusLine *b);

void bubble_sort (BusLine *start, BusLine *end)
{
  int total = end - start + 1;
  for (int i = 0; i < total - 1; i++)
    {
      BusLine *tmp = start;
      while (tmp < end - i)
        {
          if (tmp->distance > (tmp + 1)->distance)
            {
              swap (tmp, tmp + 1);
            }
          tmp++;
        }
    }
}

void quick_sort (BusLine *start, BusLine *end)
{
  if (start < end)
    {
      BusLine *mid = partition (start, end);
      quick_sort (start, mid-1);
      quick_sort (mid+1, end);
    }
}

BusLine *partition (BusLine *start, BusLine *end)
{
  int i = -1;
  BusLine *pivot = end;
  for (int j = 0; j < end - start + 1; j++)
    {
      if ((start + j)->duration < pivot->duration)
        {
          i++;
          swap (start + j, start + i);
        }
    }
  swap (start + i + 1, pivot);
  return pivot;
}

void swap (BusLine *a, BusLine *b)
{
  BusLine temp = *a;
  *a = *b;
  *b = temp;
}