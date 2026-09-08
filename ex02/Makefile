COMPILER = c++
FLAGS    = -Wall -Wextra -Werror -std=c++98
NAME     = PmergeMe

SRC     = main.cpp PmergeMe.cpp
OBJ     = $(SRC:%.cpp=$(OBJ_dir)%.o)
OBJ_dir = objs/

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $^ -o $(NAME)

$(OBJ_dir)%.o: %.cpp | $(OBJ_dir)
	$(COMPILER) $(FLAGS) -c $< -o $@

$(OBJ_dir):
	mkdir -p $(OBJ_dir)

clean:
	rm -rf $(OBJ_dir)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
.SECONDARY: $(OBJ) $(OBJ_dir)
