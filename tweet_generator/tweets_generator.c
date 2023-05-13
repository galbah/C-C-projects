#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "markov_chain.h"

//------------------------//

#define PARAMS1 4
#define PARAMS2 5
#define MAX_CHARS_OF_TWEET 1000
#define MAX_WORDS_IN_TWEET 20
#define DECIMAL 10

//------------------------//

/**
* reads words from file and fills the markov chain with them.
* @param fp the file of words to read.
* @param words_to_read the amount of words the function should read.
* @param markov_chain pointer to the database that should be filled.
*/
void fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain);
/**
* generates a number of tweets according to input.
* @param markov_chain_ptr pointer to database used to get tweet words.
* @param num_of_tweets the amount of tweets the function should make.
*/
void generate_tweets (MarkovChain *markov_chain_ptr, int num_of_tweets);

//------------------------//

void fill_database (FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  char file_content[MAX_CHARS_OF_TWEET];
  int words_read = 1;
  Node *first_node = NULL, *second_node = NULL;
  while (fgets (file_content, MAX_CHARS_OF_TWEET, fp))
  {
    char *token = strtok (file_content, " ");
    while (token != NULL)
    {
      second_node = add_to_database (markov_chain, token);
      if (first_node != NULL)
      {
        if (!add_node_to_counter_list (first_node->data,
                                       second_node->data))
        {
          char allocation_error[] = "Allocation failure: did not "
                                    "manage to add node to counter list";
          printf ("%s\n", allocation_error);
          return;
        }
      }
      if (words_read == words_to_read)
      { break; }
      token = strtok (NULL, " ");
      words_read++;
      first_node = second_node;
    }
    first_node = NULL;
    if (words_read == words_to_read && words_to_read != 0)
    { break; }
  }
}

int main (int argc, char *argv[])
{
  unsigned int seed = 0;
  int num_of_tweets = 0, num_words_to_read = 0;
  char *path, *tmp;
  if (argc == PARAMS1 || argc == PARAMS2)
  {
    seed = strtol (argv[1], &tmp, DECIMAL);
    num_of_tweets = strtol (argv[2], &tmp, DECIMAL);
    path = argv[3];
    srand (seed);
  }
  else
  {
    char usage_error[] = "Usage: num of parameters is not legal.";
    printf ("%s", usage_error);
    return EXIT_FAILURE;
  }
  if (argc == PARAMS2)
  {
    num_words_to_read = strtol (argv[4], &tmp, DECIMAL);
  }
  FILE *fp = fopen (path, "r");
  if (fp == NULL)
  {
    char file_error[] = "Error: file path is not valid";
    printf ("%s", file_error);
    return EXIT_FAILURE;
  }
  LinkedList l_list = {NULL, NULL, 0};
  MarkovChain markov_chain = {&l_list};
  MarkovChain *markov_chain_ptr = &markov_chain;
  fill_database (fp, num_words_to_read, markov_chain_ptr);
  fclose (fp);
  generate_tweets (markov_chain_ptr, num_of_tweets);
  free_markov_chain (&markov_chain_ptr);
}

void generate_tweets (MarkovChain *markov_chain_ptr, int num_of_tweets)
{
  MarkovNode *first_node = NULL;
  for (int i = 1; i <= num_of_tweets; i++)
  {
    first_node = get_first_random_node (markov_chain_ptr);
    printf ("Tweet %d: ", i);
    generate_random_sequence (markov_chain_ptr, first_node, MAX_WORDS_IN_TWEET);
  }
}