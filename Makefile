# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/12 14:02:57 by ppaquet           #+#    #+#              #
#    Updated: 2023/07/26 14:34:29 by ppaquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==================================================================================================|
#---< PIPEX >--------------------------------------------------------------------------------------|
#                                  VARIABLES                                                       |
#==================================================================================================|

# ---------------------------------------------------------------------------------< EXECUTABLE >---
NAME := pipex
NAME_MAJ := PIPEX

# ------------------------------------------------------------------------------------< LIBRARY >---
# ----------------------------------------------------------------------------------< COMPILING >---
CC := gcc 
CFLAGS := -g -Wall -Werror -Wextra

# --------------------------------------------------------------------------------------< OTHER >---
RM := rm -rf
MK := make
MK_C := make -C
DIR := mkdir

# -------------------------------------------------------------------------------------< COLORS >---
WTH := \033[0m#         WHITE
GRN := \033[0;32m#      RESET + GREEN
RED := \033[0;31m#      RESET + RED
YEL := \033[0;33m#      RESET + YELLOW
BLU := \033[0;34m#      RESET + PURPLE/BLUE
BLD := \033[1m#         BOLD
MGT := \033[1;35m#      BOLD + MAGENTA
CYA := \033[1;36m#      BOLD + CYAN

ERASE		=\033[2K
RST		=\033[0m

UP			="\033[A"#cursor up
CUT			="\033[K"#cut line

# -----------------------------------------------------------------------------------< INCLUDES >---
INCL_PATH := include/

LIBFT := libft.a
LIBFT_PATH := lib/LIBFT/

LIBS := ./$(LIBFT_PATH)$(LIBFT)

# -------------------------------------------------------------------------------------< HEADER >---
PIPEX_HEADER := -I ./$(INCL_PATH)
LIBFT_HEADER := -I ./$(LIBFT_PATH)$(INCL_PATH)

# ------------------------------------------------------------------------------------< SOURCES >---
SRCS_PATH := srcs/
SRCS_FILES := \
	main.c \
	pipex.c \
	pipex_checks.c \
	pipex_parsing.c \
	pipex_processes.c \
	pipex_errors.c \
	pipex_process_utils.c \

SRCS := $(addprefix $(SRCS_PATH), $(SRCS_FILES))

# ------------------------------------------------------------------------------------< OBJECTS >---
OBJS_PATH := objs/
OBJS := $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

#==================================================================================================|
#---< PIPEX >--------------------------------------------------------------------------------------|
#                                    RULES                                                         |
#==================================================================================================|

all: $(LIBFT) $(NAME)
	@echo "$(GRN)$(BLD)\nPIPEX ------------------------------------------------ ppaquet\n$(WTH)"


$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(CFLAGS) -o $@ $(PIPEX_HEADER) $(LIBFT_HEADER) -c $<
	@echo "Compiling $(notdir $<)"
	@sleep 0.08 && printf $(UP)$(CUT)

$(NAME): $(OBJS_PATH) $(OBJS)
	@echo "\t\t$(WTH)./pipex executable _________________ $(GRN)$(BLD)[CREATED]"
	@$(CC) $(CFLAGS) $(OBJS) $(PIPEX_HEADER) $(LIBFT_HEADER) $(LIBS) -o $@
	@sleep 1
	
$(LIBFT): 
	@$(MK_C) ./$(LIBFT_PATH) all

$(OBJS_PATH):
	@$(DIR) $(OBJS_PATH)

clean: 
	@$(MK_C) ./$(LIBFT_PATH) clean
	@$(RM) $(OBJS_PATH)

fclean: clean
	@$(MK_C) ./$(LIBFT_PATH) fclean
	@$(RM) $(NAME)
	@echo "\t\t$(WTH)./pipex executable _________________ $(RED)$(BLD)[DELETED]"

re: fclean all

# --------------------------------------------------------------------------------------< UTILS >---
backup:
	clear
	@echo "\n$(BLD)[BACKING UP $(NAME_MAJ)]\n"
	@tar -czvf $(NAME)_BACKUP_$(shell date +%Y%m%d_%H%M%S).tar.gz ./* > /dev/null 2>&1
	@mv $(NAME)_BACKUP_$(shell date +%Y%m%d_%H%M%S).tar.gz ~/Desktop/
	@sleep 2 && clear
	@echo "\n$(GRN)$(BLD)[$(NAME_MAJ) BACKUP NOW LOCATED ON DESKTOP]\n"

norm:
	clear
	@echo "$(GRN)$(BLD)[NORMINETTE - LIBFT SOURCE FILES]$(WTH)"
	@norminette -R CheckForbiddenSourceHeader lib/LIBFT/srcs | awk '{ printf("%65s\n", $$0) }'
	@echo "\n$(GRN)$(BLD)[NORMINETTE - $(NAME_MAJ) SOURCE FILES]$(WTH)"
	@norminette -R CheckForbiddenSourceHeader $(SRCS_PATH) | awk '{ printf("%65s\n", $$0) }'
	@echo "\n$(GRN)$(BLD)[NORMINETTE - INCLUDES]$(WTH)"
	@norminette -R CheckDefine lib/LIBFT/$(INCL_PATH) | awk '{ printf("%65s\n", $$0) }'
	@norminette -R CheckDefine $(INCL_PATH) | awk '{ printf("%65s\n", $$0) }'

help:
	@grep -E '^[a-zA-Z0-9_-]+:.*' Makefile | awk -F ':' '{print $$1}' | awk '{ printf("%65s\n", $$0) }'

.PHONY: all clean fclean re
