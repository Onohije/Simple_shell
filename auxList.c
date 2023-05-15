#include "ashell.h"

/**
 * addSepNodeEnd - To adds a separator found at the end
 * of a store_sep.
 * @head: Head of the linked list.
 * @sept: Separator found (; | &).
 * Return: The address of the head.
 */
store_sep *addSepNodeEnd(store_sep **head, char sept)
{
	store_sep *new, *temp;

	new = malloc(sizeof(store_sep));
	if (new == NULL)
		return (NULL);

	new->sep = sept;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * freeSepList - To frees a store_sep
 * @head: head of the linked list.
 * Return: no return.
 */
void freeSepList(store_sep **head)
{
	store_sep *temp;
	store_sep *c;

	if (head != NULL)
	{
		c = *head;
		while ((temp = c) != NULL)
		{
			c = c->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * addLineNodeEnd - To adds a command line at the end
 * of a store_line.
 * @head: Head of the linked list.
 * @line: Command line.
 * Return: Address of the head.
 */
store_line *addLineNodeEnd(store_line **head, char *line)
{
	store_line *new, *temp;

	new = malloc(sizeof(store_line));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * freeLineList - To frees a line_list
 * @head: Head of the linked list.
 * Return: no return.
 */
void freeLineList(store_line **head)
{
	store_line *temp;
	store_line *c;

	if (head != NULL)
	{
		c = *head;
		while ((temp = c) != NULL)
		{
			c = c->next;
			free(temp);
		}
		*head = NULL;
	}
}
