NAME		= LeapGame

SRC		= main.cpp \
          core/kernel/SFMLKernel.cpp \
          core/controllers/Controller.cpp \
          core/controllers/Home/HomeController.cpp \
          core/controllers/Game/GameController.cpp \

OBJ		= $(SRC:.cpp=.o)

CC		= g++ -lsfml-graphics -lsfml-window -lsfml-system

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
