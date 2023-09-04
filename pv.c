#include "ashell.h"

/**
 * checkEnv - To check if the typed variable is an env variable
 *
 * @hd: The head of linked list
 * @in: Input string
 * @data: Data structure.
 * Return: No return value.
 */
void checkEnv(var_list **hd, char *in, data_shell *data)
{
	int rw, c, i, lv;
	char **_envr;

	_envr = data->_environ;
	for (rw = 0; _envr[rw]; rw++)
	{
		for (i = 1, c = 0; _envr[rw][c]; c++)
		{
			if (_envr[rw][c] == '=')
			{
				lv = strlen_(_envr[rw] + c + 1);
				addVarNode(hd, i, _envr[rw] + c + 1, lv);
				return;
			}

			if (in[i] == _envr[rw][c])
				i++;
			else
				break;
		}
	}

	for (i = 0; in[i]; i++)
	{
		if (in[i] == ' ' || in[i] == '\t' || in[i] == ';' || in[i] == '\n')
			break;
	}

	addVarNode(hd, i, NULL, 0);
}

/**
 * checkVars - To check if the typed variable is $$ or $?
 *
 * @hd: Head of the linked list
 * @in: Input string
 * @st: Last status of the Shell
 * @data: Data structure
 * Return: no return value.
 */
int checkVars(var_list **hd, char *in, char *st, data_shell *data)
{
	int i, l_st, l_pd;

	l_st = strlen_(st);
	l_pd = strlen_(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				addVarNode(hd, 2, st, l_st), i++;
			else if (in[i + 1] == '$')
				addVarNode(hd, 2, data->pid, l_pd), i++;
			else if (in[i + 1] == '\n')
				addVarNode(hd, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				addVarNode(hd, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				addVarNode(hd, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				addVarNode(hd, 0, NULL, 0);
			else if (in[i + 1] == ';')
				addVarNode(hd, 0, NULL, 0);
			else
				checkEnv(hd, in + i, data);
		}
	}

	return (i);
}

/**
 * replacedInput - Replaces str into variables
 *
 * @hd: head of the linked list
 * @input: Input str
 * @n_input: new input string (replaced)
 * @n_len: new length
 * Return: Replaced string.
 */
char *replacedInput(var_list **hd, char *input, char *n_input, int n_len)
{
	var_list *in;
	int i, j, k;

	in = *hd;
	for (j = i = 0; i < n_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(in->lv) && !(in->lvalue))
			{
				n_input[i] = input[j];
				j++;
			}
			else if (in->lv && !(in->lvalue))
			{
				for (k = 0; k < in->lv; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < in->lvalue; k++)
				{
					n_input[i] = in->value[k];
					i++;
				}
				j += (in->lv);
				i--;
			}
			in = in->next;
		}
		else
		{
			n_input[i] = input[j];
			j++;
		}
	}

	return (n_input);
}

/**
 * repVar - To call functions to replace string into vars
 *
 * @input: Input string
 * @datash: Data structure
 * Return: Replaced string.
 */
char *repVar(char *input, data_shell *datash)
{
	var_list *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = auxItoa(datash->sta);
	head = NULL;

	olen = checkVars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->lvalue - indx->lv);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replacedInput(&head, input, new_input, nlen);

	free(input);
	free(status);
	freeVarList(&head);

	return (new_input);
}
