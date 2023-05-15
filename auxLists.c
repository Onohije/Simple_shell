#include "ashell.h"

/**
 * addVarNode - To adds a variable at the end
 * of a var_list.
 * @head: Head of the linked list.
 * @lvar: Length of the variable.
 * @val: Value of the variable.
 * @lval: Vength of the value.
 * Return: Address of the head.
 */
var_list *addVarNode(var_list **head, int lvar, char *val, int lval)
{
	var_list *new, *temp;

	new = malloc(sizeof(var_list));
	if (new == NULL)
		return (NULL);

	new->lv = lvar;
	new->value = val;
	new->lvalue= lval;

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
 * freeVarList - To frees a var_list
 * @head: Head of the linked list.
 * Return: no return.
 */
void freeVarList(var_list **head)
{
	var_list *temp;
	var_list *c;

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
