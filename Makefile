## File stuff
SHELL		=/bin/zsh

FNAMES 		=	cub3d.c parsing.c tex_info.c map.c is_map_enclosed.c utils.c map_utils.c read_map.c\
				convert_color.c convert_tex.c raycasting.c vector_funcs.c

SRCS		= 	$(addprefix $(SRCS_DIR)/,$(FNAMES))
OBJS		= 	$(addprefix $(OBJS_DIR)/,$(notdir $(FNAMES:.c=.o)))

DEPS		=	$(addprefix $(OBJS_DIR)/,$(notdir $(FNAMES:.c=.d)))

INCLUDE_DIR	= include
SRCS_DIR	= src
OBJS_DIR	= obj
LIBFT		= libft/libft.a
MLX			= mlx/libmlx_Linux.a

## Compilation

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g -fsanitize=address
INCLUDES	= -I $(INCLUDE_DIR) -I libft/include -I mlx
LIBS		= -L libft -lft -L mlx -lmlx_Linux -lXext -lX11 -lm -lz
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

ERR_TEST_FILES = $(wildcard maps/err_*)

## Targets
all: $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(ECHO) "$(GREEN)>>>>> Compiling $(RESET)$(notdir $<)$(GREEN) -> $(RESET)$(notdir $@)$(RESET)"
	@gcc $(CFLAGS) -MMD -MP -c $(INCLUDES) $< -o $@

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
	$(RM) $(OBJS) $(DEPS)
	@$(ECHO) "Cleaning libft"
	@$(MAKE) -C libft clean

fclean: clean
	@$(ECHO) "Applying full clean"
	@$(RM) $(OBJS_DIR) $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C mlx clean

re: fclean all

err_tests: $(NAME)
	@$(foreach cmd,$(ERR_TEST_FILES),echo -n "$(GREEN)$(notdir $(cmd))$(RESET) | ";./$(NAME) $(cmd);)

vars:
	@$(ECHO) "$(GREEN)CFLAGS: $(WHITE)$(CFLAGS)$(RESET)"
	@$(ECHO) "$(GREEN)CC: $(WHITE)$(CC)$(RESET)"
	@$(ECHO) "$(GREEN)FNAMES: $(WHITE)$(FNAMES)$(RESET)"
	@$(ECHO) "$(GREEN)SRCS: $(WHITE)$(SRCS)$(RESET)"
	@$(ECHO) "$(GREEN)OBJS: $(WHITE)$(OBJS)$(RESET)"
	@$(ECHO) "$(GREEN)DEPS: $(WHITE)$(DEPS)$(RESET)"

norm:
	@-norminette src include libft | sed /OK!/s//`printf "\033[32mOK!\033[0m"`/ \
		| sed /^Error/s//`printf "\033[33mError\033[0m"`/  | sed /Error!/s//`printf "\033[31mError!\033[0m"`/

.PHONY: all clean fclean re vars err_tests

-include $(DEPS)