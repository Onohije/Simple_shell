#ifndef _ASHELL_
#define _ASHELL_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Extern char that points to an array of pointers to str called the "env". */
extern char **environ;


/**
 * struct data - A struct that contains all relevant data on runtime
 * @av: argument vector
 * @inpt: command input by the user
 * @args: tokens of the command line
 * @sta: last status of the shell
 * @contn: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *inpt;
	char **args;
	int sta;
	int contn;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_store - A single linked list to store separators
 * @sep: ; | &
 * @next: next node
 */
typedef struct sep_store
{
	char sep;
	struct sep_store *next;
} store_sep;

/**
 * struct line_store - A single linked list to store command lines
 * @line: command line
 * @next: next node
 */
typedef struct line_store
{
	char *line;
	struct line_store *next;
} store_line;

/**
 * struct var_store - A single linked list to store variables
 * @lv: length of the var
 * @value: value of the var
 * @lvalue: length of the value
 * @next: next node
 */
typedef struct var_store
{
	int lv;
	char *value;
	int lvalue;
	struct var_store *next;
} var_list;

/**
 * struct bull_s - A Builtin struct for command args.
 * @nam: The name of the command builtin.
 * @fun: data type pointer function.
 */
typedef struct bull_s
{
	char *nam;
	int (*fun)(data_shell *datash);
} bull_com;

/* auxList.c */
store_sep *addSepNodeEnd(store_sep **head, char sept);
void freeSepList(store_sep **head);
store_line *addLineNodeEnd(store_line **head, char *line);
void freeLineList(store_line **head);

/* auxLists.c */
var_list *addVarNode(var_list **head, int lvar, char *var, int lval);
void freeVarList(var_list **head);

/* ashell_str functions */
char *strcat_(char *dest, const char *src);
char *strcpy_(char *dest, char *src);
int strcmp_(char *s, char *ss);
char *strchr_(char *s, char c);
int strspn_(char *s, char *acc);

/* auxMem.c */
void _memcpy(void *nptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize);
char **_reallocdp(char **ptr, unsigned int oldSize, unsigned int newSize);

/* ashell_strr.c */
char *strdup_(const char *s);
int strlen_(const char *s);
int cmpChars(char str[], const char *dim);
char *strtok_(char str[], const char *dim);
int isdigit_(const char *s);

/* ashell_strrr.c */
void rev_str(char *s);

/* checkSyntaxError.c */
int repeatedChar(char *input, int c);
int errorSepOp(char *input, int c, char ls);
int firstChar(char *input, int *c);
void printSyntaxError(data_shell *datash, char *input, int c, int bool);
int checkSyntaxError(data_shell *datash, char *input);

/* loop.c */
char *del_comment(char *in);
void shellLoop(data_shell *datash);

/* readLine.c */
char *readLine(int *i);

/* split.c */
char *swapChar(char *input, int bool);
void addNodes(store_sep **hd_s, store_line **hd_l, char *input);
void goNext(store_sep **lt_s, store_line **lt_l, data_shell *datash);
int splitCommands(data_shell *datash, char *input);
char **splitLine(char *input);

/* pv.c */
void checkEnv(var_list **hd, char *in, data_shell *data);
int checkVars(var_list **hd, char *in, char *st, data_shell *data);
char *replacedInput(var_list **hd, char *in, char *n_input, int n_len);
char *repVar(char *in, data_shell *datash);

/* getLine.c */
void line(char **lineptr, size_t *i, char *buf, size_t j);
ssize_t getLine(char **lineptr, size_t *i, FILE *stream);

/* execLine.c */
int execLine(data_shell *datash);

/* commandExec.c */
int c_dir(char *path, int *n);
char *is_which(char *cmd, char **_environ);
int executable_(data_shell *datash);
int checkErrorCmd(char *dir, data_shell *datash);
int commandExec(data_shell *datash);

/* ashell_env.c */
char *_getenv(const char *n, char **_environ);
int _env(data_shell *datash);

/* ashellEnv.c */
char *copyInfo(char *n, char *v);
void setEnv(char *n, char *v, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* change_dir.c */
void change_dir_dot(data_shell *datash);
void change_dir_to(data_shell *datash);
void change_dir_previous(data_shell *datash);
void change_dir_to_home(data_shell *datash);

/* change_dir_shell.c */
int change_dir_shell(data_shell *datash);

/* builtin.c */
int (*getBuiltin(char *cmd))(data_shell *datash);

/* exit_ashell.c */
int exit_ashell(data_shell *datash);

/* ashell_stdlib.c */
int getLen(int n);
char *auxItoa(int n);
int _atoi(char *s);

/* auxError.c */
char *strcatCd(data_shell *, char *, char *, char *);
char *errorGetCd(data_shell *datash);
char *errorNotFound(data_shell *datash);
char *errorExitShell(data_shell *datash);

/* auxErrorr.c */
char *errorGetAlias(char **args);
char *errorEnv(data_shell *datash);
char *errorSyntax(char **args);
char *errorPermission(char **args);
char *errorPath_126(data_shell *datash);


/* getError.c */
int getError(data_shell *datash, int e_v);

/* getSigint.c */
void getSigint(int s);

/* auxHelp.c */
void auxHelpEnv(void);
void auxHelpSetenv(void);
void auxHelpUnsetenv(void);
void auxHelpGeneral(void);
void auxHelpExit(void);

/* auxHep.c */
void auxHelp(void);
void auxHelp_alias(void);
void auxHelp_cd(void);

/* getHelp.c */
int getHelp(data_shell *datash);

#endif
