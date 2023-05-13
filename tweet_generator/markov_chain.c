#include "markov_chain.h"
#include <stdlib.h>
#include <string.h>

//------------------------//

#define INIT_FREQ 1
#define MIN_NUMBER_OF_WORDS_IN_TWEET 2

//------------------------//


int get_random_number (int max_number)
{
  return rand () % max_number;
}

MarkovNode *get_first_random_node (MarkovChain *markov_chain)
{
  bool word_is_legal = false;
  char *word;
  Node *state;
  int rand_num, max_rand = markov_chain->database->size;
  while (!word_is_legal)
  {
    state = markov_chain->database->first;
    rand_num = get_random_number (max_rand);
    for (int i = 0; i < rand_num; i++)
    { state = state->next; }
    word = state->data->data;
    if (word[strlen (word) - 1] != '.')
    { word_is_legal = true; }
  }
  return state->data;
}

MarkovNode *get_next_random_node (MarkovNode *state_struct_ptr)
{
  int max_rand = state_struct_ptr->counter_list_sum;
  if (max_rand == 0)
  { return NULL; }
  int rand_num = get_random_number (max_rand);
  int i;
  for (i = 0; i < state_struct_ptr->counter_list_size; i++)
  {
    rand_num -= state_struct_ptr->counter_list[i].frequency;
    if (rand_num < 0)
    { break; }
  }
  return state_struct_ptr->counter_list[i].markov_node;
}

void generate_random_sequence (MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
  if (max_length < MIN_NUMBER_OF_WORDS_IN_TWEET)
  { return; }
  MarkovNode *cur_node;
  if (first_node != NULL)
  { cur_node = first_node; }
  else
  { cur_node = get_first_random_node (markov_chain); }
  printf ("%s ", cur_node->data);
  while (max_length > 1)
  {
    cur_node = get_next_random_node (cur_node);
    if (cur_node == NULL)
    { break; }
    if (cur_node->data[strlen (cur_node->data) - 1] != '.')
    {
      printf ("%s ", cur_node->data);
      max_length--;
    }
    else
    {
      printf ("%s\n", cur_node->data);
      break;
    }
  }
}

void free_markov_chain (MarkovChain **ptr_chain)
{
  Node *cur_node = (*ptr_chain)->database->first;
  Node *next_node = cur_node;
  while (next_node != NULL)
  {
    next_node = cur_node->next;
    free (cur_node->data->data);
    free (cur_node->data);
    free (cur_node);
    cur_node = next_node;
  }
}

bool add_node_to_counter_list (MarkovNode *first_node, MarkovNode *second_node)
{
  bool is_it_in = false;
  char *cur_word;
  (first_node->counter_list_sum) += 1;
  for (int i = 0; i < first_node->counter_list_size; i++)
  {
    cur_word = first_node->counter_list[i].markov_node->data;
    if (strcmp (cur_word, second_node->data) == 0)
    {
      is_it_in = true;
      first_node->counter_list[i].frequency++;
      break;
    }
  }
  if (!is_it_in)
  {
    first_node->counter_list_size++;
    NextNodeCounter *tmp;
    tmp = realloc (first_node->counter_list,
                   (first_node->counter_list_size) * sizeof (NextNodeCounter));
    if (tmp == NULL)
    { return false; }
    first_node->counter_list = tmp;
    first_node->counter_list[first_node->counter_list_size - 1]
        .markov_node = second_node;
    first_node->counter_list[first_node->counter_list_size - 1]
        .frequency = INIT_FREQ;
  }
  return true;
}

Node *get_node_from_database (MarkovChain *markov_chain, char *data_ptr)
{
  Node *cur_node = markov_chain->database->first;
  while (cur_node != NULL)
  {
    if (strcmp (cur_node->data->data, data_ptr) == 0)
    {
      return cur_node;
    }
    cur_node = cur_node->next;
  }
  return NULL;
}

Node *add_to_database (MarkovChain *markov_chain, char *data_ptr)
{
  if (data_ptr[strlen (data_ptr) - 1] == '\n')
  { data_ptr[strlen (data_ptr) - 1] = '\0'; }
  Node *node = get_node_from_database (markov_chain, data_ptr);
  if (node != NULL)
  { return node; }
  MarkovNode *ptr_markov_node = malloc (sizeof (MarkovNode));
  if (ptr_markov_node == NULL)
  {
    char allocation_error[] = "Allocation failure: did not "
                              "manage to add a markov_node";
    printf ("%s\n", allocation_error);
    return NULL;
  }
  *ptr_markov_node = (MarkovNode) {NULL, NULL, 0, 0};
  ptr_markov_node->data = malloc (strlen (data_ptr) + 1);
  if (ptr_markov_node->data == NULL)
  {
    free (ptr_markov_node);
    char allocation_error[] = "Allocation failure: did not "
                              "manage to add a word to node";
    printf ("%s\n", allocation_error);
    return NULL;
  }
  strcpy (ptr_markov_node->data, data_ptr);
  if (add (markov_chain->database, ptr_markov_node) == 1)
  {
    free (ptr_markov_node);
    char allocation_error[] = "Allocation failure: did not "
                              "manage to add node to linked list";
    printf ("%s\n", allocation_error);
    return NULL;
  }
  return markov_chain->database->last;
}