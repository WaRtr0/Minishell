#---auto gen---
SRCS += /main.c
#---env---
SRCS += env/ms_env_complete.c
SRCS += env/ms_env_add.c
SRCS += env/ms_env_print.c
SRCS += env/ms_env_append.c
SRCS += env/ms_env_remove.c
SRCS += env/ms_env_exist.c
SRCS += env/ms_env_to_strs.c
SRCS += env/ms_env_new.c
SRCS += env/ms_env_collapse.c
SRCS += env/ms_env_init.c
SRCS += env/ms_env_gen.c
SRCS += env/ms_env_get.c
#---builtin---
SRCS += builtin/pwd.c
SRCS += builtin/cd.c
SRCS += builtin/unset.c
SRCS += builtin/echo.c
SRCS += builtin/export.c
SRCS += builtin/exit.c
SRCS += builtin/env.c
#---prompt---
SRCS += prompt/ms_prompt.c
#---parser---
SRCS += parser/heredoc/ms_heredoc.c
SRCS += parser/syntax/ms_syntax_rule.c
SRCS += parser/syntax/ms_syntax_error.c
#---exec---
SRCS += exec/builtin/ms_run_builtin.c
SRCS += exec/builtin/ms_exec_builtin.c
SRCS += exec/binary/ms_file_status.c
SRCS += exec/binary/ms_exec_bin.c
SRCS += exec/binary/ms_exec_get_path.c
SRCS += exec/binary/ms_execbin.c
SRCS += exec/ms_exec.c
SRCS += exec/ms_exec_io_utils.c
SRCS += exec/ms_exec_free.c
