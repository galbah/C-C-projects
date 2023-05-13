#include "cipher.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

const int letters = 26;

// See full documentation in header file
void encode (char s[], int k)
{
  int i = 0;
  if (k < 0)
    {
      k = letters + (k % letters);
    }
  while (s[i] != '\0')
    {
      if ('A' <= s[i] && s[i] <= 'Z')
        {
          s[i] = (s[i] - 'A' + k) % letters + 'A';
        }
      if ('a' <= s[i] && s[i] <= 'z')
        {
          s[i] = (s[i] - 'a' + k) % letters + 'a';
        }
      i++;
    }
}

// See full documentation in header file
void decode (char s[], int k)
{
  int i = 0;
  k = -k;
  if (k < 0)
    {
      k = letters + (k % letters);
    }
  while (s[i] != '\0')
    {
      if ('A' <= s[i] && s[i] <= 'Z')
        {
          s[i] = (s[i] - 'A' + k) % letters + 'A';
        }
      if ('a' <= s[i] && s[i] <= 'z')
        {
          s[i] = (s[i] - 'a' + k) % letters + 'a';
        }
      i++;
    }
}
