# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edal--ce <edal--ce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 17:54:38 by edal--ce          #+#    #+#              #
#    Updated: 2020/01/22 11:53:14 by edal--ce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = game.o

SRCS = 	src/draw.c \
		src/fonctions.c \
		src/map.c \
		src/keys.c \
		src/dda.c

OBJS = $(SRCS:.c=.o)

INCL = header/

HEADER = $(INCL)header.h

CC = gcc

LIBFT = libft/libft.a

CFLAGS = 

FRMWORKS = -framework AppKit -framework OpenGL

LIBLINK = -L ./minilibx_opengl_20191021/ -lmlx $(FRMWORKS)

LIB = libft/

GNL = GetNextLine/

OBJLIB = $(LIB)/src/*.o

libft :
	@$(MAKE) -C libft

all : libft
	gcc -I ./minilibx_opengl_20191021/ $(LIBFT)  main.c src/* $(LIBLINK)

$(OBJS) : %.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -I $(INCL) -c $< -o $@

cleanlibft :
	$(MAKE) -C libft clean

fcleanlibft :
	$(MAKE) -C libft fclean

clean : cleanlibft
	$(RM) $(OBJS)

fclean : clean fcleanlibft
	$(RM) $(NAME)
	rm -rf a.out a.out.dSYM

re : fclean all

.PHONY : all clean fclean re libft cleanlibft fcleanlibft