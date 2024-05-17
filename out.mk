#---auto gen---
SRCS += /main.c
#---env---
SRCS += env/ms_env_append.c
SRCS += env/ms_env_exist.c
SRCS += env/ms_env_gen.c
SRCS += env/ms_env_get.c
SRCS += env/ms_env_init.c
SRCS += env/ms_env_new.c
SRCS += env/ms_env_print.c
SRCS += env/ms_env_remove.c
SRCS += env/ms_env_to_strs.c
SRCS += env/ms_env_add.c
SRCS += env/ms_env_collapse.c
SRCS += env/ms_env_complete.c
#---builtin---
SRCS += builtin/cd.c
SRCS += builtin/echo.c
SRCS += builtin/env.c
SRCS += builtin/exit.c
SRCS += builtin/export.c
SRCS += builtin/pwd.c
SRCS += builtin/unset.c
#---prompt---
SRCS += prompt/ms_prompt.c
#---parser---
SRCS += parser/heredoc/ms_heredoc.c
SRCS += parser/syntax/ms_syntax_error.c
SRCS += parser/syntax/ms_syntax_rule.c
SRCS += parser/utils/ms_reset_quote.c
#---exec---
SRCS += exec/binary/ms_exec_bin.c
SRCS += exec/binary/ms_exec_get_path.c
SRCS += exec/binary/ms_execbin.c
SRCS += exec/binary/ms_file_status.c
SRCS += exec/builtin/ms_exec_builtin.c
SRCS += exec/builtin/ms_run_builtin.c
SRCS += exec/ms_exec.c
SRCS += exec/ms_exec_free.c
SRCS += exec/ms_exec_io_utils.c
#---debug---
SRCS += debug/ms_debug.c
#---utils---
SRCS += utils/ft_include.c
SRCS += utils/ft_splitstr.c
SRCS += utils/ft_select_str.c
SRCS += utils/ft_strjoin_seperator.c
#---lexer---
SRCS += lexer/utils/ms_is_pipeline.c
SRCS += lexer/utils/ms_is_join.c
SRCS += lexer/utils/ms_get_children.c
SRCS += lexer/utils/ms_get_parent.c
SRCS += lexer/utils/ms_get_cursor.c
SRCS += lexer/utils/ms_add_pipeline.c
SRCS += lexer/utils/ms_exit_pipeline.c
SRCS += lexer/utils/ms_add_join.c
SRCS += lexer/utils/ms_exit_join.c
SRCS += lexer/utils/ms_append_quote.c
SRCS += lexer/ms_lexer.c
#---handle---
SRCS += handle/ms_handle.c
SRCS += handle/ms_handle_join.c
SRCS += handle/ms_handle_pipe.c
SRCS += handle/expand/ms_get_fd.c
