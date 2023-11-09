#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <stdio.h>

#define BSIZE 1024
#define TOK_SIZE 128
#define TOK_SEP " \t\r\n\a"

/** MACROS **/
extern char **environ;

/**
 * struct info - a struct that contains runtime data for the shell program
 * @argv: argument vector
 * @cdline: the command line input written by user
 * @arg_tok: array of tokens from the command line
 * @position: the exit position of the most recent shell command
 * @ln_index: line index counter
 * @envarias: the environment variables
 * @pid: the process identifier of the shell
 */
typedef struct info
{
	char **argv;
	char *cdline;
	char **arg_tok;
	int position;
	int ln_index;
	char **envarias;
	char *pid;
} datashell;

/**
 * struct div_node_lst - struct contains linked list to store separators
 * @divider: the separator characters (;, |, &)
 * @subsqt: pointer to the next node in the list
 */
typedef struct div_node_lst
{
	char divider;
	struct div_node_lst *subsqt;
} divd_t;

/**
 * struct cdline_node_lst - a struct contains linked list to store command line
 * @ln: commandline
 * @subsqt: a pointer to the next node
 */
typedef struct cdline_node_lst
{
	char *ln;
	struct cdline_node_lst *subsqt;
} cdline_t;

/**
 * struct vrs_node_lst - it contains linked list to keep variables
 * @vrlen: variable length
 * @val: vrs value
 * @vlen: val length
 * @subsqt: pointer to the next node in the list
 */
typedef struct vrs_node_lst
{
	int vrlen;
	char *val;
	int vlen;
	struct vrs_node_lst *subsqt;
} vrs_t;

/**
 * struct inbuilt_cmd - struct containing built-in commands
 * @id: the name of the builtin commands (cd, ls)
 * @f: a pointer to the associated func
 */
typedef struct inbuilt_cmd
{
	char *id;
	int (*f)(datashell *tam);
} inbuilt_t;

/** **/
void memory_cp(void *dest, const void *frm, unsigned int dimen);
void *_re_alloc(void *b, unsigned int prv_dimen, unsigned int nw_dimen);
char **_re_alloc_ptr(char **b, unsigned int prv_dimen, unsigned int nw_dimen);

/** **/
int _lenstr(const char *ser);
char *str_concat(char *dest, const char *frm);
int cmp_string(char *ser1, char *ser2);
char *cpy_string(char *dest, char *frm);
char *chr_string(char *ser, char ltr);
char *dup_string(const char *ser);
void rev_string(char *ser);
int sspn_string(char *ser, char *ltr);
char *tok_string(char ser[], const char *div);
int _number(const char *ser);
int cmp_chars(char ser[], const char *div);
int chars_count(char *ser, int indx);
int indx_chars(char *ser, int *indx);

divd_t *append_div(divd_t **start, char div);
void clear_div(divd_t **start);
cdline_t *append_cdline(cdline_t **start, char *line);
void clear_cdline(cdline_t **start);
vrs_t *append_vrs(vrs_t **start, int varlen, char *valu, int valength);
void clear_vrs(vrs_t **start);
void append_nodes_list(divd_t **div_start, cdline_t **cdline_start, char *ser);

int count_num(int count);
char *string_fmt(int count);
int str_atoi(char *ser);

int handle_error(char *ser, int indx, char lchars);
void _printerror(datashell *tam, char *ser, int indx, int errctr);
int verify_error(datashell *tam, char *ser);
char *unify_error(datashell *tam, char *emsg, char *err, char *cd_ctrl);
char *path_error(datashell *tam);
char *cmd_invalid(datashell *tam);
char *exit_shell_error(datashell *tam);
char *settings_emsg(datashell *tam);
char *path126_emsg(datashell *tam);

int find_err(datashell *tam, int errval);
int (*find_inbuilt(char *cmnd))(datashell *);
void find_signal(int signal);
int handles_help(datashell *tam);

char *exam_user_data(int *its_eof);
char *letter_swap(char *ser, int sub);
int delim_cdline(datashell *tam, char *ser);
char **data_parse(char *ser);
char *remove_coms(char *stat);

void opens_sh(datashell *tam);
void _subsqt_lst(divd_t **div_lst, cdline_t **cdline_lst, datashell *tam);
int exm_currdir(char *way, int *indx);
int exm_execc(datashell *tam);
int exm_perm(char *path, datashell *tam);

void exm_envarias(vrs_t **start, char *ser, datashell *tam);
int handle_uniq_vrs(vrs_t **start, char *ser, char *last, datashell *tam);
char *string_sub_vrs(vrs_t **start, char *ser, char *nser, int nlong);
char *vrs_string_swap(char *ser, datashell *tam);
char *execute_path(char *cmnd, char **envarias);

void output_lines(char **ptr, size_t *lndimen, char *buffs, size_t buff_size);
ssize_t _getline_(char **ptr, size_t *lndimen, FILE *curr);

int display_enviros(datashell *tam);
int envarias_comp(const char *envid, const char *id);
char *getenV_(const char *id, char **envarias);
char *dup_env_stat(char *id, char *sig);
void set_enV_(char *id, char *sig, datashell *tam);
int _setenV_(datashell *tam);
int unsets_Env(datashell *tam);

void goto_parent_dir(datashell *tam);
void goto_prev(datashell *tam);
void goto_home(datashell *tam);
void goto_path(datashell *tam);
int goto_shell(datashell *tam);

int closeshell(datashell *tam);
int handles_cdline(datashell *tam);
int handles_cmnd(datashell *tam);

void enVsupport_data(void);
void setEnv_support_data(void);
void unsetsEnv_support(void);
void general_help_data(void);
void close_guide_data(void);
void support_data(void);
void supportalias_data(void);
void chdir_guide_info(void);

#endif
