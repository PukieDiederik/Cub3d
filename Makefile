## File stuff
SHELL		=/bin/zsh

FNAMES 		=	cub3d.c

SRCS		= 	$(addprefix $(SRCS_DIR)/,$(FNAMES))

OBJS		= 	$(addprefix $(OBJS_DIR)/,$(notdir $(FNAMES:.c=.o)))

INCLUDE_DIR	= include
SRCS_DIR	= src
OBJS_DIR	= obj
LIBFT		= libft/libft.a
MLX			= mlx/libmlx_Linux.a

## Compilation

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
INCLUDES	= -I $(INCLUDE_DIR) -I libft/include
LIBS		= -L libft -lft -L mlx -lmlx_Linux
## Other

NAME		= cub3d
RM			= rm -rf
MAKE		= make -s

ECHO		= echo -e


# Colors
BLACK		= \033[0;30m
RED			= \033[0;31m
GREEN		= \033[0;32m
ORANGE		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
GRAY		= \033[0;37m
WHITE		= \033[0;38m
RESET		= \033[0m


## Targets
all: $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(ECHO) "$(GREEN)>>>>> Compiling $(RESET)$(notdir $<)$(GREEN) -> $(RESET)$(notdir $@)$(RESET)"
	@gcc $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJS_DIR):
	@mkdir $(OBJS_DIR)
	@$(ECHO) "$(BLUE)Directory '$(CYAN)$(OBJS_DIR)/$(BLUE)' doesn't exist. Creating '$(CYAN)$(OBJS_DIR)/$(BLUE)'$(RESET)"

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(ECHO) "$(CYAN)>>> Creating MLX$(RESET)"
	@$(MAKE) -C mlx

# regular targets
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(ECHO) "$(GREEN)>>>>> Linking <<<<<$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

init:
	@$(ECHO) "$(PURPLE)>>>>> Initializing this repository <<<<<$(RESET)"
	@git submodule init
	@git submodule update

clean:
	@$(ECHO) "$(GREEN)>>>>> Cleaning <<<<<$(RESET)"
	$(RM) $(OBJS)
	@$(ECHO) "Cleaning libft"
	@$(MAKE) -C libft clean

fclean: clean
	@$(ECHO) "Applying full clean"
	@$(RM) $(OBJS_DIR) $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C mlx clean

re: fclean all

vars:
	@$(ECHO) "$(GREEN)CFLAGS: $(WHITE)$(CFLAGS)$(RESET)"
	@$(ECHO) "$(GREEN)CC: $(WHITE)$(CC)$(RESET)"
	@$(ECHO) "$(GREEN)FNAMES: $(WHITE)$(FNAMES)$(RESET)"
	@$(ECHO) "$(GREEN)SRCS: $(WHITE)$(SRCS)$(RESET)"
	@$(ECHO) "$(GREEN)OBJS: $(WHITE)$(OBJS)$(RESET)"

.PHONY: all clean fclean re init
