NAME		= LeapGame

SRC		= source/main.cpp \

OBJ		= $(SRC:.cpp=.o)

CC		= g++

CPPFLAGS	= -I include

LDFLAGS		=

RM		= rm -rf

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(OBJ)

re: fclean all
