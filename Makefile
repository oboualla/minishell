# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboualla <oboualla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/06 23:38:47 by oboualla          #+#    #+#              #
#    Updated: 2019/12/05 10:55:51 by oboualla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	minishell

SRC 	=	src/make_params.c src/mode_execmd.c src/get_cmd.c src/auto_completion.c src/print_file.c src/free_lstmateriel.c  src/read_cmd.c \
			src/mini_shell.c src/modifier_path_val.c src/confirme_alias.c  src/set_unset_env.c src/modifier_argument.c src/exec_cmd.c\
			src/me_echo.c src/lstenv.c src/changer_directory.c src/complet_cmd.c src/remplace_cmd.c src/fonc_lstenv.c src/objet.c

OBJ		=	$(SRC:.c=.o)

LIBMS	= mini_shell.a

FLAGS   = gcc -Wall -Wextra -Werror

all : $(NAME)


$(NAME) : $(OBJ)
	make -C libft/
	ar rc $(LIBMS) $(OBJ)
	ranlib $(LIBMS)
	$(FLAGS) $(LIBMS) libft/libft.a -o $(NAME)

clean :
	make clean -C libft/
	rm $(OBJ)

fclean : clean
	make fclean -C libft/
	rm $(NAME) $(LIBMS)

re : fclean all

%.o : %.c
	$(FLAGS) -c $< -o $@
