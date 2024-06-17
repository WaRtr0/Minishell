NAME	=	libft.a

CC		=	cc
AR		=	ar -rcs
RMF		=	rm -f
RMD		=	rm -d

CFLAGS	:= -Wall -Werror -Wextra

DEPSFLAGS	=	-MMD -MP

HDIR	=	includes

SDIR	=	srcs
BDIR	=	build

LSTDIR		=	list
LSTFILES	=	ft_lstadd_back.c	\
				ft_lstadd_front.c	\
				ft_lstclear.c		\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstlast.c		\
				ft_lstmap.c			\
				ft_lstnew.c			\
				ft_lstsize.c		\
				ft_lstpop.c			\
				ft_lstpush.c		\
				ft_lstshift.c		\
				ft_lstunshift.c

CHARDIR		=	char
CHARFILES	=	ft_tolower.c		\
				ft_toupper.c		\
				ft_isalnum.c		\
				ft_isalpha.c		\
				ft_isascii.c		\
				ft_isdigit.c		\
				ft_isprint.c

STRDIR		=	str
STRFILES	=	ft_split.c			\
				ft_strsjoin.c		\
				ft_strchr.c			\
				ft_strdup.c			\
				ft_striteri.c		\
				ft_strjoin.c		\
				ft_strlcat.c		\
				ft_strcpy.c			\
				ft_strlen.c			\
				ft_strmapi.c		\
				ft_strncmp.c		\
				ft_strnstr.c		\
				ft_strrchr.c		\
				ft_strtrim.c		\
				ft_substr.c			\
				ft_itoa.c			\
				ft_strisnum.c

MEMDIR		=	mem
MEMFILES	=	ft_bzero.c			\
				ft_calloc.c			\
				ft_memchr.c			\
				ft_memcmp.c			\
				ft_memcpy.c			\
				ft_memmove.c		\
				ft_memset.c			\
				ft_nfree.c

PUTDIR		=	put
PUTFILES	=	ft_putchar_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_putstr_fd.c

GNLDIR		=	gnl
GNLFILES	=	get_next_line.c

FTPRINTFDIR		=	ft_printf
FTPRINTFFILES	=	ft_printchar.c	\
					ft_printf.c		\
					ft_printnbr.c	\
					ft_printptr.c	\
					ft_printstr.c	\
					ft_printxnbr.c

NUMDIR			=	num
NUMFILES		=	ft_atoi.c		\
					ft_atol.c		\
					ft_min_max.c		\
					ft_abs.c

ARRDIR			=	arr
ARRFILES		=	ft_arr_new.c		\
					ft_arr_resize.c		\
					ft_arr_clear.c		\
					ft_arr_free.c		\
					ft_arr_push.c		\
					ft_arr_shift.c		\
					ft_arr_unshift.c	\
					ft_arr_map.c		\
					ft_arr_pop.c		\
					ft_arr_append.c

VECDIR			=	vector
VECFILES		=	ft_vec_append.c		\
					ft_vec_clear.c		\
					ft_vec_destroy.c	\
					ft_vec_get.c		\
					ft_vec_init.c		\
					ft_vec_new.c		\
					ft_vec_resize.c


SFILES	=	${addprefix $(LSTDIR)/, $(LSTFILES)}		\
			${addprefix $(CHARDIR)/, $(CHARFILES)}		\
			${addprefix $(STRDIR)/, $(STRFILES)}		\
			${addprefix $(MEMDIR)/, $(MEMFILES)}		\
			${addprefix $(PUTDIR)/, $(PUTFILES)}		\
			${addprefix $(GNLDIR)/, $(GNLFILES)}		\
			${addprefix $(NUMDIR)/, $(NUMFILES)}		\
			${addprefix $(ARRDIR)/, $(ARRFILES)}		\
			${addprefix $(VECDIR)/, $(VECFILES)}		\
			${addprefix $(FTPRINTFDIR)/, $(FTPRINTFFILES)}

SRCS	=	$(SFILES:%=$(SDIR)/%)

OFILES	=	$(SFILES:%.c=%.o)
OBJS	=	$(OFILES:%=$(BDIR)/%)

DEPSDIR		= build
DEPS		= $(SFILES:%.c=$(DEPSDIR)/%.d)

.PHONY	:	all	fclean	clean	re	debug

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(AR) $(NAME) $?

-include $(DEPS)

$(BDIR)/%.o		:	$(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(DEPSFLAGS) -c $< -o $@ -I $(HDIR)/
	@echo "	$@"

fclean	:	clean
	$(RMF) $(NAME)

clean	:
	$(RMF) $(OBJS) $(DEPS)

re		:	fclean
	$(MAKE) all CFLAGS="$(CFLAGS)"

debug	:	CFLAGS += -g3
debug	:	re
