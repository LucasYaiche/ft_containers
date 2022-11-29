# #=======================================#
# #[Containers] Fonctions partie principale#
# #=======================================#

# CONTAINERS_SRC = main.cpp

# CONTAINERS_OBJ = ${addprefix ${OBJDIR}, ${CONTAINERS_SRC:%.c=%.o}}

# #====#
# #Tags#
# #====#

# OBJDIR = ./objs/
# MAINDIR = ./main/
# INCLUDES = ./includes/
# NAME = Containers
# CFLAGS = -Wall -Wextra -Werror

# #=========#
# #Commandes#
# #=========#					

# ${OBJDIR}%.o : ${MAINDIR}%.c
# 								@clang++ ${CFLAGS} -c $< -o $@ -I ${INCLUDES}

# ${NAME}: 						${OBJDIR} ${CONTAINERS_OBJ} -o ${NAME}
# 								@printf "\e[32;3m$@ successfully build\e[0m\n"

# ${OBJDIR}:						
# 								@mkdir -p ${OBJDIR}

# all:							${NAME}

# clean:
# 								@rm -rf ${OBJDIR}
# 								@printf "\e[31;3mClean files\e[0m\n"

# fclean:							clean
# 								@rm -f ${NAME}
# 								@printf "\e[31;3mClean exec\e[0m\n"

# re:								fclean all

# .PHONY:							all clean fclean re


NAME =	ft_containers
SRCS =	./main/main.cpp

OBJ = $(SRCS:.cpp=.o)

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++
rm = rm -rf

all : $(NAME)

$(NAME):	$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re bonus clean fclean all