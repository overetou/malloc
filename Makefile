.PHONY : clean, fclean, all

ifeq ($(HOSTTYPE), )
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

objdir = obj

obj = $(addprefix $(objdir)/,malloc.o mapping.o smart_funcs.o mblocks.o mconts.o sub_blocks.o free.o debugging.o utils.o printing.o alignment.o)

VPATH = src

CC = gcc

CFLAGS = -Wextra -Werror -Wall -I header/

$(objdir)/%.o : %.c header/malloc.h
	@$(COMPILE.c) $(OUTPUT_OPTION) -fpic $<

all: $(NAME) libft_malloc.so

$(NAME): $(obj)
	@$(CC) $(CFLAGS) -shared -o $@ $^

libft_malloc.so:
	ln -s $(NAME) libft_malloc.so

$(obj): | $(objdir)

$(objdir):
	mkdir $(objdir)

clean:
	rm -f $(obj)

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean all

test: $(NAME)
	@$(CC) test_main.c -I header/ ./$(NAME)
	@./a.out
