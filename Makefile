#=======================================#
#[Containers] Fonctions partie principale#
#=======================================#

CONTAINERS_SRC = main.cpp

CONTAINERS_OBJ_STD = ${addprefix ${OBJDIR}, ${CONTAINERS_SRC:%.cpp=%.o}}

CONTAINERS_OBJ_FT = ${addprefix ${OBJDIR}, ${CONTAINERS_SRC:%.cpp=%.k}}

#====#
#Tags#
#====#

OBJDIR = ./objs/
MAINDIR = ./main/
INCLUDES = ./containers/
NAME = ft_containers_std
NAME_FT = ft_containers_ft
CFLAGS = -Wall -Wextra -Werror 

#=========#
#Commandes#
#=========#					

${OBJDIR}%.o : ${MAINDIR}%.cpp
								@c++ ${CFLAGS} -c $< -o $@ -I ${INCLUDES} -D TESTED_NAMESPACE=std

${OBJDIR}%.k : ${MAINDIR}%.cpp
								@c++ ${CFLAGS} -c $< -o $@ -I ${INCLUDES} -D TESTED_NAMESPACE=ft

${NAME}: 						${OBJDIR} ${CONTAINERS_OBJ_STD} ${NAME_FT}
								@c++ ${CFLAGS} ${CONTAINERS_OBJ_STD} -o ${NAME}
								@printf "\e[32;3m$@ successfully build\e[0m\n"

${NAME_FT}:						${OBJDIR} ${CONTAINERS_OBJ_FT}
								@c++ ${CFLAGS} ${CONTAINERS_OBJ_FT} -o ${NAME_FT}
								@printf "\e[32;3m$@ successfully build\e[0m\n"

${OBJDIR}:						
								@mkdir -p ${OBJDIR}

all:							${NAME}												

clean:
								@rm -rf ${OBJDIR}
								@printf "\e[31;3mClean files\e[0m\n"

fclean:							clean
								@rm -f ${NAME}
								@rm -f ${NAME_FT}
								@printf "\e[31;3mClean exec\e[0m\n"

re:								fclean all

.PHONY:							all clean fclean re
