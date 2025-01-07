/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:16 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/07 17:26:02 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

extern int g_status;

typedef struct s_envp
{
	char			*name;
	char			*content;
	int				ind;
	struct s_envp	*next;
}	t_envp;

typedef struct s_paser
{
	int		filein;
	int		fileout;
	char	**all_cmd;
	char	*route;
}	t_parser;

typedef struct s_data
{
	char		*prompt;
	t_envp		*envp;
	char		**path;
	char		**cmd;
	int			i;
	int			j;
	char		*aux;
	char		*fileout;
	char		*filein;
	t_parser	*node;
	int			flag_hered;
	int			flag_token;
	int			flag_add;
	int			size;
	int			a;
	t_list		*nodes;
	int			flag_pipe;
	char		quote;
	char		*str;
	int			b;
	int			d;
	int			flag;
	int			dup_stdin;
	t_envp		*tmp_envp;
	int			flag_path;
	char		*error_cd;
	int			fd[2];
	char		**cnt;
}	t_data;

//UTILS
void		draw(void);
void		export_content(t_data *data, char *str, char **aux, t_envp *tmp);

//EXPORT
void		set_envp_index(t_data *data);
int			exp_cmp(const char *s1, const char *s2);
int			size_envp(t_envp *lst);
void		ex_export(t_data *d, char **str, int i, int fd);
//SIGNALS
void		signals(int sig);
void		sig_ctrlc(int sig);
void		sig_ctrlslash(int sig);
//free
void		free_split(char **tmp);
void		free_cd(t_data *data);
void		free_node(t_list **lst);
void		free_all(t_data *data);
void		free_t_parser(t_parser *node);
//splits
int			get_path(t_data *d);
int			get_cmds(t_data *d);
char		**get_words(t_data *data, char const *str, char c, int i);
int			count_words(t_data *data, char const *str, char c, int j);
int			size_words(t_data *data, char const *str, char c, int *d);
void		split_words(t_data *data, char const *str, char c);
char		**splits_cmd(char const *str, char c);
//lexer
int			lexer(char	*str);
int			check_builts(t_parser *node);
void		check_path(t_data *data);
int			check_node(t_data *data, char **str);
void		check_cargs(t_parser *node);
//expander
void		expand(t_data *d);
//parsing
int			parsing(t_data *data, int i, int j);
int			get_token_filein(t_data *data, t_parser **node, int *i, int *j);
int			get_token_fileout(t_data *data, t_parser **node, int *i, int *j);
void		ft_heredoc(t_data *data, t_parser **node, char *str);
//route
int			process_route(t_data *data, int i);
//exec
int			execute(t_data *data, t_parser *node, char **envp, t_list *aux);
void		ex_routepipes(t_data *data, t_parser *n, char **envp, t_list *tmp);
void		error_msg_pipe(char *error);
void		error_msg(char *error);
void		ex_route(t_data *data, t_parser *node, char **envp);
int			ex_builts(t_data *data, t_parser *n);
//builts
void		ex_cd(t_data *data, char **str, int flag);
void		ex_echo(char **str, int flag, int fd);
void		get_envp(t_data *data, char **envp, int i);
int			ex_exit(t_data *data, t_parser *node, int i, int fd);
void		ex_pwd(int fd);
void		ex_unset(t_data *data, char *str);
void		ex_envp(t_data *data, int fd);
#endif