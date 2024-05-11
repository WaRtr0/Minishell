#---auto gen---
SRCS += /main.c
#---env---
SRCS += env/ms_env_collapse.c
SRCS += env/ms_env_gen.c
SRCS += env/ms_env_new.c
SRCS += env/ms_env_exist.c
SRCS += env/ms_env_to_strs.c
SRCS += env/ms_env_get.c
SRCS += env/ms_env_append.c
SRCS += env/ms_env_print.c
SRCS += env/ms_env_complete.c
SRCS += env/ms_env_init.c
SRCS += env/ms_env_remove.c
SRCS += env/ms_env_add.c
#---builtin---
SRCS += builtin/pwd.c
SRCS += builtin/cd.c
SRCS += builtin/export.c
SRCS += builtin/exit.c
SRCS += builtin/echo.c
SRCS += builtin/env.c
SRCS += builtin/unset.c
#---prompt---
SRCS += prompt/ms_prompt.c
SRCS += prompt/heredoc/ms_heredoc.c
#---parser---
SRCS += parser/handle/ms_handle.c
SRCS += parser/handle/ms_handle_join.c
SRCS += parser/handle/ms_handle_pipe.c
#---exec---
SRCS += exec/builtin/ms_run_builtin.c
SRCS += exec/builtin/ms_exec_builtin.c
SRCS += exec/ms_exec.c
SRCS += exec/ms_exec_io_utils.c
SRCS += exec/ms_exec_free.c
SRCS += exec/binary/ms_exec_get_path.c
SRCS += exec/binary/ms_exec_bin.c
SRCS += exec/binary/ms_file_status.c
SRCS += exec/binary/ms_execbin.c
