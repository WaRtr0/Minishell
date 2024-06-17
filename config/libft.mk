
LIBFTDIR = libft-1.2
LIBFTNAME = ft
LIBFTAR = libft.a
LIBFTPATH = $(LIBFTDIR)/$(LIBFTAR)
LIBFTINCLUDES =  -I $(LIBFTDIR)/includes/
LIBFTFLAGS = -L $(LIBFTDIR)/ -l $(LIBFTNAME) $(LIBFTINCLUDES)

LIB_PATH += $(LIBFTPATH)
LIB_INCLUDE += $(LIBFTINCLUDES)
LIB_FLAGS += $(LIBFTFLAGS)
LIB_DIR += $(LIBFTDIR)

fclean ::
	@echo "clean libft";
	@$(MAKE) fclean -s -C $(LIBFTDIR);


$(LIBFTPATH) : force
	@echo "compiling libft";
	@$(MAKE) -C $(LIBFTDIR);
	@echo "libft compilation done";
