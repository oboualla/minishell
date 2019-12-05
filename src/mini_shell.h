/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboualla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:57:50 by oboualla          #+#    #+#             */
/*   Updated: 2019/09/18 19:12:20 by oboualla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include "../libft/libft.h"
# include <sys/ioctl.h>
# define CMD_NOT_FOUND 	2
# define DIRECTORY_ERR	4
# define SETENV			8
# define UNSETENV		16
# define ERR_BF			2
# define ERR_AF			4

typedef struct s_env			t_env;
typedef struct s_sepcmd			t_sepcmd;
typedef struct s_rmpcmd			t_rmpcmd;
typedef struct s_mat			t_mat;

struct		s_mat
{
	char		*line;
	t_rmpcmd	*rmpcmd;
	t_env		*lst[2];
	t_sepcmd	*sepcmd;
};

struct		s_rmpcmd
{
	char		*origine;
	char		*rem;
	t_rmpcmd	*next;
};

struct		s_env
{
	char	*var;
	char	*path;
	t_env	*next;
};

struct		s_sepcmd
{
	char		**av;
	t_sepcmd	*next;
};

t_mat		*g_mat;

void		sig1(int sig);
void		sig2(int sig);
t_env		*newenv(char *var, char *path);
t_env		*ft_setenv(t_env *ptr, char **av, int ac);
t_env		*ft_unsetenv(t_env **alst, char **av, int ac);
t_env		*get_ptr(t_env *env, char *find);
t_env		*delthis(t_env **lst, t_env **del);
t_env		*lstenv(char **env, t_env **alst);
size_t		ft_lstlen(t_env *lst);
void		ft_delelem(t_env *ptr);
t_rmpcmd	*remplace_cmd(char **av, char **path, t_rmpcmd **alst);
char		**make_params(const char *params);
t_sepcmd	*read_cmd(char **line);
void		exec_cmd(char **av, char **path, char **env);
int			modifier_argument(char **line);
char		**switch_lstenv(t_env *lst);
char		**my_path(t_env *lst);
void		changer_directory(char **av, int ac);
void		aff_prompt(void);
int			mode_execmd(char **av, int ac);
int			modifier_argument(char **line);
int			modifier_path(char **path);
int			modifier_val(char **path);
void		me_echo(char **av);
void		auto_completion(char **join, char **path);
int			print_file(char *str, char *comp, char **join);
int			get_cmd(char **line, char **path);
int			confirme_alias(char *argument, char **path);
void		free_lstmateriel(int flag);
void		freedouble(char **tab);
void		define_error(char *err, int error);
void		error(char *path, char *message, int mode);
void		modifier_cmd(char **cmd, char **path);
#endif
