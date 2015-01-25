OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Linux)
  ifeq ($(ARCH), x86_64)
    LEAP_LIBRARY := ./lib/x64/libLeap.so -Wl,-rpath,./lib/x64
  else
    LEAP_LIBRARY := ./lib/x86/libLeap.so -Wl,-rpath,./lib/x86
  endif
else
  # OS X
  LEAP_LIBRARY := ./lib/libLeap.dylib
endif


NAME		= LeapGame

SRC		= main.cpp \
          core/kernel/SFMLKernel.cpp \
		  core/controllers/IController.cpp \
		  core/controllers/Game/GameController.cpp \
		  core/controllers/Home/HomeController.cpp \
		  core/controllers/Game/ContactListener.cpp \
		  core/controllers/Game/ResultsController.cpp \
		  leap/leap.cpp \

OBJ		= $(SRC:.cpp=.o)

CC		= g++ 

CPPFLAGS	= -I include -g -std=c++11

LDFLAGS		= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lliquidfun -lz

RM		= rm -rf

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LEAP_LIBRARY) $(CPPFLAGS) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
