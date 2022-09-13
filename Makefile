#=======================================#
#[Containers] Fonctions partie principale#
#=======================================#

CONTAINERS_SRC = main.cpp

SRCS_SRC = 
				
SRCS_OBJ = ${addprefix ${OBJDIR}, ${SRCS_SRC:%.c=%.o}}

CONTAINERS_OBJ = ${addprefix ${OBJDIR}, ${CONTAINERS_SRC:%.c=%.o}} ${SRCS_OBJ}

#====#
#Tags#
#====#

OBJDIR = ./objs/
MAINDIR = ./main/
SRCSDIR = ./srcs/
INCLUDES = ./includes/
NAME = Containers
CFLAGS = -Wall -Wextra -Werror

#=========#
#Commandes#
#=========#					

${OBJDIR}%.o : ${MAINDIR}%.c
								@clang++ ${CFLAGS} -c $< -o $@ -I ${INCLUDES}
${OBJDIR}%.o : ${SRCSIR}%.c
								@clang++ ${CFLAGS} -c $< -o $@ -I ${INCLUDES}

${NAME}: 						${OBJDIR} ${CONTAINERS_OBJ} -o ${NAME}
								@printf "\e[32;3m$@ successfully build\e[0m\n"

${OBJDIR}:						
								@mkdir -p ${OBJDIR}

all:							${NAME}

clean:
								@rm -rf ${OBJDIR}
								@printf "\e[31;3mClean files\e[0m\n"

fclean:							clean
								@rm -f ${NAME}
								@printf "\e[31;3mClean exec\e[0m\n"

re:								fclean all

.PHONY:							all clean fclean re bonus