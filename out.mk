#---auto gen---
SRCS += /exit_status.c
SRCS += /ms_signal_handler.c
SRCS += /main.c
#---env---
SRCS += env/ms_env_collapse.c
SRCS += env/ms_env_gen.c
SRCS += env/ms_env_new.c
SRCS += env/ms_env_exist.c
SRCS += env/ms_env_to_strs.c
SRCS += env/ms_env_get.c
SRCS += env/ms_env_append.c
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
SRCS += prompt/ms_join_prompt.c
#---parser---
SRCS += parser/syntax/ms_syntax_rule.c
SRCS += parser/syntax/ms_update_status_operator.c
SRCS += parser/syntax/ms_update_status_text.c
SRCS += parser/syntax/ms_update_status_quote.c
SRCS += parser/syntax/ms_update_status_heredoc.c
SRCS += parser/syntax/ms_syntax_error.c
SRCS += parser/ms_join_parsers.c
SRCS += parser/heredoc/ms_heredoc.c
SRCS += parser/utils/ms_get_operator.c
SRCS += parser/utils/ms_get_type.c
SRCS += parser/utils/ms_inc_name.c
SRCS += parser/utils/ms_inc_word.c
SRCS += parser/utils/ms_is_semicolon.c
SRCS += parser/utils/ms_is_chevron.c
SRCS += parser/utils/ms_reset_quote.c
SRCS += parser/utils/ms_inc_blank.c
SRCS += parser/utils/ms_get_indent.c
SRCS += parser/utils/ms_get_metachar.c
SRCS += parser/ms_parser.c
#---exec---
SRCS += exec/builtin/ms_run_builtin.c
SRCS += exec/builtin/ms_exec_builtin.c
SRCS += exec/ms_exec.c
SRCS += exec/ms_exec_io_utils.c
SRCS += exec/binary/ms_exec_get_path.c
SRCS += exec/binary/ms_exec_bin.c
SRCS += exec/binary/ms_file_status.c
SRCS += exec/binary/ms_execbin.c
#---debug---
SRCS += debug/ms_debug_command_to_json.c
SRCS += debug/ms_debug_cmd_to_str.c
SRCS += debug/ms_debug_print_json.c
SRCS += debug/ms_debug.c
SRCS += debug/ms_debug_command_map.c
#---utils---
SRCS += utils/ft_include.c
SRCS += utils/ft_free.c
SRCS += utils/ft_select_str.c
SRCS += utils/ft_splitstr.c
SRCS += utils/ft_strjoin_seperator.c
#---lexer---
SRCS += lexer/ms_commit_command.c
SRCS += lexer/ms_add_fd.c
SRCS += lexer/ms_free_command.c
SRCS += lexer/ms_lexer.c
SRCS += lexer/ms_get_command_type.c
SRCS += lexer/ms_clear_command.c
SRCS += lexer/ms_get_cmd.c
SRCS += lexer/ms_add_str.c
SRCS += lexer/utils/ms_get_cursor_type.c
SRCS += lexer/utils/ms_is_join.c
SRCS += lexer/utils/ms_get_parent.c
SRCS += lexer/utils/ms_is_parenthesis.c
SRCS += lexer/utils/ms_add_pipeline.c
SRCS += lexer/utils/ms_is_pipeline.c
SRCS += lexer/utils/ms_exit_pipeline.c
SRCS += lexer/utils/ms_get_cursor.c
SRCS += lexer/utils/ms_append_quote.c
SRCS += lexer/utils/ms_add_join.c
SRCS += lexer/utils/ms_join_command.c
SRCS += lexer/utils/ms_get_children.c
SRCS += lexer/utils/ms_exit_join.c
SRCS += lexer/ms_add_array.c
SRCS += lexer/ms_new_command.c
SRCS += lexer/actions/ms_lexer_operator.c
SRCS += lexer/actions/ms_lexer_quote.c
SRCS += lexer/actions/ms_lexer_redir.c
SRCS += lexer/actions/ms_lexer_wildcard.c
SRCS += lexer/actions/ms_lexer_empty.c
SRCS += lexer/actions/ms_lexer_parenthesis.c
SRCS += lexer/actions/ms_lexer_name.c
SRCS += lexer/actions/ms_lexer_heredoc.c
SRCS += lexer/ms_add_type.c
#---handle---
SRCS += handle/expand/ms_get_fd.c
SRCS += handle/expand/ms_expand.c
SRCS += handle/ms_close_fd.c
SRCS += handle/ms_handle.c
SRCS += handle/ms_handle_join.c
SRCS += handle/ms_handle_pipe.c
#---wildcard---
SRCS += wildcard/pathexp_utils.c
SRCS += wildcard/ms_pathexp.c
SRCS += wildcard/pattern_match.c
