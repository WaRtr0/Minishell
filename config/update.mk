U_DIR := env \
			exec
OUT = ./out.mk

list_files = $($(cat) $(dir))

update:
	@echo "#---auto gen---" > $(OUT)
	@((cd srcs/ && find -maxdepth 1 -name "*.c") | sed 's/^\./SRCS += /g' >> $(OUT))
	@for dir in $(U_DIR); do \
		echo "#---$$dir---" >> $(OUT); \
		((cd srcs/$$dir && find -name "*.c") | sed 's/^\./SRCS += '"$$dir"'/g' >> $(OUT)); \
	done