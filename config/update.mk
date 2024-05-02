U_DIR := env builtin prompt parser
OUT = ./out.mk

$(touch $(OUT))

list_files = $($(cat) $(dir))

update:
	@echo "#---auto gen---" > $(OUT)
	@((cd srcs/ && find -maxdepth 1 -name "*.c") | sed 's/^\./SRCS += /g' >> $(OUT))
	@for dir in $(U_DIR); do \
		echo "#---$$dir---" >> $(OUT); \
		((cd srcs/$$dir && find -name "*.c") | sed 's/^\./SRCS += '"$$dir"'/g' >> $(OUT)); \
	done

.PHONY: update