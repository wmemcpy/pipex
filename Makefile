EXEC		= pipex

# **************************************************************************** #

CC 		= cc
FLAGS	= -Wall -Wextra -Werror

ifeq ($(MAKECMDGOALS), debug)
	FLAGS += -g3 -ggdb3
endif

# **************************************************************************** #

CDIR	= ./src/
ODIR	= ./bin/
LDIR	= ./libft/

# **************************************************************************** #

CNAME	= exec.c \
main.c \
utils.c \

ONAME	= $(CNAME:.c=.o)
LNAME	= libft.a

# **************************************************************************** #

CFILES	= $(addprefix $(CDIR), $(CNAME))
OFILES	= $(addprefix $(ODIR), $(ONAME))
LFILES	= $(addprefix $(LDIR), $(LNAME))

# **************************************************************************** #

all: $(EXEC)

$(EXEC): $(OFILES)
	make -C $(RULES) $(LDIR)
	$(CC) $(FLAGS) -o $(EXEC) $(OFILES) $(LFILES)

$(ODIR):
	mkdir -p $(ODIR)

$(ODIR)%.o: $(CDIR)%.c | $(ODIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	make clean -C $(LDIR)
	rm -rf $(ODIR)

fclean: clean
	make fclean -C $(LDIR)
	rm -f $(EXEC)

re: fclean all

debug:
	$(MAKE) re FLAGS="$(FLAGS) -g3 -ggdb3"

norme:
	make norme -C $(LDIR)
	norminette $(CFILES) $(HFILES)

.PHONY: all clean fclean re debug norme
