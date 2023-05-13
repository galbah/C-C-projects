#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// your code goes here
#define MAX_BIT 16
const int input_1 = 2;
const int input_2 = 5;
const int base = 10;

bool is_number (const char *number);
int run_tests ();
int arg_check1 (int len, const char *action);
int arg_check2 (const char *action, const char *k);
int file_coder (const char *action, const char *shift,
                const char *in, const char *out);

int main (int argc, char *argv[])
{

  if (arg_check1 (argc, argv[1]) != 0)
    {
      return EXIT_FAILURE;
    }
  if (argc == 2)
    {
      return run_tests ();
    }
  else
    {
      if (arg_check2 (argv[1], argv[2]) != 0)
        {
          return EXIT_FAILURE;
        }
      if (file_coder (argv[1], argv[2], argv[3], argv[4]) != 0)
        {
          return EXIT_FAILURE;
        }
    }
}

bool is_number (const char *number)
{
  int i = 0;

  //checking for negative numbers
  if (number[0] == '-')
    {
      i = 1;
    }
  for (; number[i] != 0; i++)
    {
      //if (number[i] > '9' || number[i] < '0')
      if (!isdigit (number[i]))
        {
          return false;
        }
    }
  return true;
}

int run_tests ()
{
  int x = 0;
  x += test_encode_non_cyclic_lower_case_positive_k ();
  x += test_encode_cyclic_lower_case_special_char_positive_k ();
  x += test_encode_non_cyclic_lower_case_special_char_negative_k ();
  x += test_encode_cyclic_lower_case_negative_k ();
  x += test_encode_cyclic_upper_case_positive_k ();
  x += test_decode_non_cyclic_lower_case_positive_k ();
  x += test_decode_cyclic_lower_case_special_char_positive_k ();
  x += test_decode_non_cyclic_lower_case_special_char_negative_k ();
  x += test_decode_cyclic_lower_case_negative_k ();
  x += test_decode_cyclic_upper_case_positive_k ();
  if (x == 0)
    {
      return EXIT_SUCCESS;
    }
  return EXIT_FAILURE;
}

int arg_check1 (int len, const char *action)
{
  if (len != input_1 && len != input_2)
    {
      fprintf (stderr, "The program receives 1 or 4 arguments only.\n");
      return EXIT_FAILURE;
    }
  if (len == 2 && strcmp (action, "test") != 0)
    {
      fprintf (stderr, "Usage: cipher test\n");
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

int arg_check2 (const char *action, const char *k)
{
  if (strcmp (action, "decode") != 0 && strcmp (action, "encode") != 0)
    {
      fprintf (stderr, "The given command is invalid.\n");
      return EXIT_FAILURE;
    }
  if (is_number (k) != 1)
    {
      fprintf (stderr, "The given shift value is invalid.\n");
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}

int file_coder (const char *action, const char *shift,
                const char *in, const char *out)
{
  long int k = strtol (shift, NULL, base);
  FILE *f_in = fopen (in, "r");
  if (f_in == NULL)
    {
      fprintf (stderr, "The given file is invalid.\n");
      return EXIT_FAILURE;
    }
  FILE *f_out = fopen (out, "w");
  char buffer[MAX_BIT];
  if (strcmp (action, "decode") == 0)
    {
      while (fgets (buffer, MAX_BIT, f_in))
        {
          decode (buffer, k);
          fprintf (f_out, buffer);
        }
    }
  else
    {
      while (fgets (buffer, MAX_BIT, f_in))
        {
          encode (buffer, k);
          fprintf (f_out, buffer);
        }
    }
  fclose (f_in);
  fclose (f_out);
  return EXIT_SUCCESS;
}