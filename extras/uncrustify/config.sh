#!/bin/bash

# @file config.sh
# @author Manny Peterson <manny@heliosproj.org>
# @brief A shell script to build Uncrustify configuration file
# @version 0.4.0
# @date 2023-03-19
# 
# @copyright
# HeliOS Embedded Operating System Copyright (C) 2020-2023 HeliOS Project <license@heliosproj.org>
#  
#  SPDX-License-Identifier: GPL-2.0-or-later

CONFIG=$(cat <<- END
newlines:lf									# modified
input_tab_size:8
output_tab_size:8
string_escape_char:92
string_escape_char2:0
string_replace_tab_chars:false
tok_split_gte:false
disable_processing_nl_cont:false
disable_processing_cmt:\"*UNCRUSTIFY-OFF*\"	# modified
enable_processing_cmt:\"*UNCRUSTIFY-ON*\"	# modified
enable_digraphs:false
processing_cmt_as_regex:false
utf8_bom:remove								# modified
utf8_byte:false
utf8_force:true								# modified
sp_arith:force								# modified
sp_arith_additive:ignore
sp_assign:force								# modified
sp_cpp_lambda_assign:ignore
sp_cpp_lambda_square_paren:ignore
sp_cpp_lambda_square_brace:ignore
sp_cpp_lambda_argument_list:ignore
sp_cpp_lambda_paren_brace:ignore
sp_cpp_lambda_fparen:ignore
sp_assign_default:ignore
sp_before_assign:ignore
sp_after_assign:ignore
sp_enum_brace:force							# modified
sp_enum_paren:ignore
sp_enum_assign:force						# modified
sp_enum_before_assign:ignore
sp_enum_after_assign:ignore
sp_enum_colon:ignore
sp_pp_concat:add
sp_pp_stringify:ignore
sp_before_pp_stringify:ignore
sp_bool:force								# modified
sp_compare:force							# modified
sp_inside_paren:remove						# modified
sp_paren_paren:remove						# modified
sp_cparen_oparen:remove						# modified
sp_balance_nested_parens:false
sp_paren_brace:force						# modified
sp_brace_brace:remove						# modified
sp_before_ptr_star:force					# modified
sp_before_unnamed_ptr_star:ignore
sp_between_ptr_star:remove					# modified
sp_after_ptr_star:remove					# modified
sp_after_ptr_block_caret:ignore
sp_after_ptr_star_qualifier:ignore
sp_after_ptr_star_func:ignore
sp_after_ptr_star_trailing:ignore
sp_ptr_star_func_var:ignore
sp_ptr_star_func_type:ignore
sp_ptr_star_paren:remove					# modified
sp_before_ptr_star_func:force				# modified
sp_before_ptr_star_trailing:ignore
sp_before_byref:force						# modified
sp_before_unnamed_byref:ignore
sp_after_byref:remove						# modified
sp_after_byref_func:ignore
sp_before_byref_func:force					# modified
sp_byref_paren:force						# modified
sp_after_type:force
sp_after_decltype:ignore
sp_before_template_paren:ignore
sp_template_angle:ignore
sp_before_angle:ignore
sp_inside_angle:ignore
sp_inside_angle_empty:ignore
sp_angle_colon:ignore
sp_after_angle:ignore
sp_angle_paren:ignore
sp_angle_paren_empty:ignore
sp_angle_word:ignore
sp_angle_shift:add
sp_permit_cpp11_shift:false
sp_before_sparen:remove						# modified
sp_inside_sparen:remove						# modified
sp_inside_sparen_open:ignore
sp_inside_sparen_close:ignore
sp_inside_for:remove						# modified
sp_inside_for_open:ignore
sp_inside_for_close:ignore
sp_sparen_paren:remove						# modified
sp_after_sparen:force						# modified
sp_sparen_brace:force						# modified
sp_do_brace_open:force						# modified
sp_brace_close_while:force					# modified
sp_while_paren_open:force					# modified
sp_invariant_paren:ignore
sp_after_invariant_paren:ignore
sp_special_semi:ignore
sp_before_semi:remove
sp_before_semi_for:remove					# modified
sp_before_semi_for_empty:remove				# modified
sp_between_semi_for_empty:remove			# modified
sp_after_semi:force							# modified
sp_after_semi_for:force
sp_after_semi_for_empty:remove				# modified
sp_before_square:remove						# modified
sp_before_vardef_square:remove
sp_before_square_asm_block:ignore
sp_before_squares:remove					# modified
sp_cpp_before_struct_binding:ignore
sp_inside_square:remove						# modified
sp_inside_square_empty:remove				# modified
sp_inside_square_oc_array:ignore
sp_after_comma:force						# modified
sp_before_comma:remove
sp_after_mdatype_commas:ignore
sp_before_mdatype_commas:ignore
sp_between_mdatype_commas:ignore
sp_paren_comma:force
sp_type_colon:ignore
sp_after_ellipsis:ignore
sp_before_ellipsis:ignore
sp_type_ellipsis:ignore
sp_ptr_type_ellipsis:ignore
sp_paren_ellipsis:ignore
sp_byref_ellipsis:ignore
sp_paren_qualifier:force					# modified
sp_paren_noexcept:ignore
sp_after_class_colon:ignore
sp_before_class_colon:ignore
sp_after_constr_colon:add
sp_before_constr_colon:add
sp_before_case_colon:remove
sp_after_operator:ignore
sp_after_operator_sym:ignore
sp_after_operator_sym_empty:ignore
sp_after_cast:force							# modified
sp_inside_paren_cast:remove					# modified
sp_cpp_cast_paren:ignore
sp_sizeof_paren:remove						# modified
sp_sizeof_ellipsis:ignore
sp_sizeof_ellipsis_paren:ignore
sp_ellipsis_parameter_pack:ignore
sp_parameter_pack_ellipsis:ignore
sp_decltype_paren:ignore
sp_after_tag:ignore
sp_inside_braces_enum:remove				# modified
sp_inside_braces_struct:remove				# modified
sp_inside_braces_oc_dict:ignore
sp_after_type_brace_init_lst_open:ignore
sp_before_type_brace_init_lst_close:ignore
sp_inside_type_brace_init_lst:ignore
sp_inside_braces:remove						# modified
sp_inside_braces_empty:remove				# modified
sp_trailing_return:ignore
sp_type_func:remove							# modified
sp_type_brace_init_lst:ignore
sp_func_proto_paren:remove					# modified
sp_func_proto_paren_empty:remove			# modified
sp_func_type_paren:ignore
sp_func_def_paren:ignore
sp_func_def_paren_empty:remove				# modified
sp_inside_fparens:remove					# modified
sp_inside_fparen:remove						# modified
sp_inside_tparen:remove						# modified
sp_after_tparen_close:remove				# modified
sp_square_fparen:force						# modified
sp_fparen_brace:force						# modified
sp_fparen_brace_initializer:ignore
sp_fparen_dbrace:ignore
sp_func_call_paren:remove					# modified
sp_func_call_paren_empty:remove				# modified
sp_func_call_user_paren:ignore
sp_func_call_user_inside_fparen:ignore
sp_func_call_user_paren_paren:ignore
sp_func_class_paren:ignore
sp_func_class_paren_empty:ignore
sp_return:force
sp_return_paren:ignore
sp_return_brace:ignore
sp_attribute_paren:force					# modified
sp_defined_paren:remove						# modified
sp_throw_paren:ignore
sp_after_throw:ignore
sp_catch_paren:ignore
sp_oc_catch_paren:ignore
sp_before_oc_proto_list:ignore
sp_oc_classname_paren:ignore
sp_version_paren:ignore
sp_scope_paren:ignore
sp_super_paren:remove
sp_this_paren:remove
sp_macro:force								# modified
sp_macro_func:force							# modified
sp_else_brace:force							# modified
sp_brace_else:force							# modified
sp_brace_typedef:force						# modified
sp_catch_brace:ignore
sp_oc_catch_brace:ignore
sp_brace_catch:ignore
sp_oc_brace_catch:ignore
sp_finally_brace:ignore
sp_brace_finally:ignore
sp_try_brace:ignore
sp_getset_brace:ignore
sp_word_brace_init_lst:ignore
sp_word_brace_ns:add
sp_before_dc:ignore
sp_after_dc:ignore
sp_d_array_colon:ignore
sp_not:remove
sp_not_not:ignore
sp_inv:remove
sp_addr:remove
sp_member:remove
sp_deref:remove
sp_sign:remove
sp_incdec:remove
sp_before_nl_cont:add
sp_after_oc_scope:ignore
sp_after_oc_colon:ignore
sp_before_oc_colon:ignore
sp_after_oc_dict_colon:ignore
sp_before_oc_dict_colon:ignore
sp_after_send_oc_colon:ignore
sp_before_send_oc_colon:ignore
sp_after_oc_type:ignore
sp_after_oc_return_type:ignore
sp_after_oc_at_sel:ignore
sp_after_oc_at_sel_parens:ignore
sp_inside_oc_at_sel_parens:ignore
sp_before_oc_block_caret:ignore
sp_after_oc_block_caret:ignore
sp_after_oc_msg_receiver:ignore
sp_after_oc_property:ignore
sp_after_oc_synchronized:ignore
sp_cond_colon:force							# modified
sp_cond_colon_before:ignore
sp_cond_colon_after:ignore
sp_cond_question:force						# modified
sp_cond_question_before:ignore
sp_cond_question_after:ignore
sp_cond_ternary_short:ignore
sp_case_label:ignore
sp_range:ignore
sp_after_for_colon:ignore
sp_before_for_colon:ignore
sp_extern_paren:force						# modified
sp_cmt_cpp_start:ignore
sp_cmt_cpp_region:ignore
sp_cmt_cpp_doxygen:false
sp_cmt_cpp_qttr:false
sp_endif_cmt:ignore
sp_after_new:ignore
sp_between_new_paren:ignore
sp_after_newop_paren:ignore
sp_inside_newop_paren:ignore
sp_inside_newop_paren_open:ignore
sp_inside_newop_paren_close:ignore
sp_before_tr_cmt:force						# modified
sp_num_before_tr_cmt:1						# modified
sp_before_emb_cmt:force
sp_num_before_emb_cmt:1
sp_after_emb_cmt:force
sp_num_after_emb_cmt:1
sp_annotation_paren:ignore
sp_skip_vbrace_tokens:false
sp_after_noexcept:ignore
sp_vala_after_translation:ignore
force_tab_after_define:false
indent_columns:2							# modified
indent_ignore_first_continue:false
indent_continue:-2							# modified
indent_continue_class_head:0
indent_single_newlines:false
indent_param:0
indent_with_tabs:0							# modified
indent_cmt_with_tabs:false
indent_align_string:false
indent_xml_string:0
indent_brace:0
indent_braces:false
indent_braces_no_func:false
indent_braces_no_class:false
indent_braces_no_struct:false
indent_brace_parent:false
indent_paren_open_brace:false
indent_cs_delegate_brace:false
indent_cs_delegate_body:false
indent_namespace:false
indent_namespace_single_indent:false
indent_namespace_level:0
indent_namespace_limit:0
indent_namespace_inner_only:false
indent_extern:true							# modified
indent_class:false
indent_ignore_before_class_colon:false
indent_before_class_colon:0
indent_class_colon:false
indent_class_on_colon:false
indent_ignore_before_constr_colon:false
indent_constr_colon:false
indent_ctor_init_leading:2
indent_ctor_init_following:2
indent_ctor_init:0
indent_else_if:false
indent_var_def_blk:0
indent_var_def_cont:false
indent_shift:0
indent_func_def_force_col1:false
indent_func_call_param:false
indent_func_def_param:false
indent_func_def_param_paren_pos_threshold:0
indent_func_proto_param:false
indent_func_class_param:false
indent_func_ctor_var_param:false
indent_template_param:false
indent_func_param_double:false
indent_func_const:0
indent_func_throw:0
indent_macro_brace:true
indent_member:0
indent_member_single:false
indent_single_line_comments_before:0
indent_single_line_comments_after:0
indent_sparen_extra:0
indent_relative_single_line_comments:false
indent_switch_case:0
indent_switch_body:0
indent_ignore_case_brace:false
indent_case_brace:0
indent_switch_break_with_case:false
indent_switch_pp:true
indent_case_shift:0
indent_case_comment:true
indent_comment:true
indent_col1_comment:false
indent_col1_multi_string_literal:false
indent_comment_align_thresh:3
indent_ignore_label:false
indent_label:1
indent_access_spec:1
indent_access_spec_body:false
indent_paren_nl:false
indent_paren_close:0
indent_paren_after_func_def:false
indent_paren_after_func_decl:false
indent_paren_after_func_call:false
indent_comma_brace:0
indent_comma_paren:0
indent_bool_paren:0
indent_ignore_bool:false
indent_ignore_arith:false
indent_semicolon_for_paren:false
indent_ignore_semicolon:false
indent_first_bool_expr:false
indent_first_for_expr:false
indent_square_nl:false
indent_preserve_sql:false
indent_ignore_assign:false
indent_align_assign:true
indent_off_after_assign:false
indent_align_paren:true
indent_oc_inside_msg_sel:false
indent_oc_block:false
indent_oc_block_msg:0
indent_oc_msg_colon:0
indent_oc_msg_prioritize_first_colon:true
indent_oc_block_msg_xcode_style:false
indent_oc_block_msg_from_keyword:false
indent_oc_block_msg_from_colon:false
indent_oc_block_msg_from_caret:false
indent_oc_block_msg_from_brace:false
indent_min_vbrace_open:0
indent_vbrace_open_on_tabstop:false
indent_token_after_brace:true
indent_cpp_lambda_body:false
indent_compound_literal_return:true
indent_using_block:true
indent_ternary_operator:0
indent_inside_ternary_operator:false
indent_off_after_return:false
indent_off_after_return_new:false
indent_single_after_return:false
indent_ignore_asm_block:false
donot_indent_func_def_close_paren:false
nl_collapse_empty_body:false
nl_collapse_empty_body_functions:false
nl_assign_leave_one_liners:false
nl_class_leave_one_liners:false
nl_enum_leave_one_liners:false
nl_getset_leave_one_liners:false
nl_cs_property_leave_one_liners:false
nl_func_leave_one_liners:false
nl_cpp_lambda_leave_one_liners:false
nl_if_leave_one_liners:false
nl_while_leave_one_liners:false
nl_do_leave_one_liners:false
nl_for_leave_one_liners:false
nl_oc_msg_leave_one_liner:false
nl_oc_mdef_brace:ignore
nl_oc_block_brace:ignore
nl_oc_before_interface:ignore
nl_oc_before_implementation:ignore
nl_oc_before_end:ignore
nl_oc_interface_brace:ignore
nl_oc_implementation_brace:ignore
nl_start_of_file:remove						# modified
nl_start_of_file_min:0
nl_end_of_file:remove						# modified
nl_end_of_file_min:0
nl_assign_brace:ignore
nl_assign_square:ignore
nl_tsquare_brace:ignore
nl_after_square_assign:ignore
nl_fcall_brace:ignore
nl_enum_brace:remove						# modified
nl_enum_class:ignore
nl_enum_class_identifier:ignore
nl_enum_identifier_colon:ignore
nl_enum_colon_type:ignore
nl_struct_brace:remove						# modified
nl_union_brace:remove						# modified
nl_if_brace:remove							# modified
nl_brace_else:remove						# modified
nl_elseif_brace:remove						# modified
nl_else_brace:remove						# modified
nl_else_if:remove							# modified
nl_before_opening_brace_func_class_def:ignore
nl_before_if_closing_paren:remove			# modified
nl_brace_finally:ignore
nl_finally_brace:ignore
nl_try_brace:ignore
nl_getset_brace:ignore
nl_for_brace:remove							# modified
nl_catch_brace:ignore
nl_oc_catch_brace:ignore
nl_brace_catch:ignore
nl_oc_brace_catch:ignore
nl_brace_square:ignore
nl_brace_fparen:ignore
nl_while_brace:remove						# modified
nl_scope_brace:ignore
nl_unittest_brace:ignore
nl_version_brace:ignore
nl_using_brace:ignore
nl_brace_brace:ignore
nl_do_brace:remove							# modified
nl_brace_while:remove						# modified
nl_switch_brace:remove						# modified
nl_synchronized_brace:ignore
nl_multi_line_cond:false
nl_multi_line_sparen_open:ignore
nl_multi_line_sparen_close:ignore
nl_multi_line_define:false
nl_before_case:false
nl_after_case:false
nl_case_colon_brace:ignore
nl_before_throw:ignore
nl_namespace_brace:ignore
nl_template_class:ignore
nl_template_class_decl:ignore
nl_template_class_decl_special:ignore
nl_template_class_def:ignore
nl_template_class_def_special:ignore
nl_template_func:ignore
nl_template_func_decl:ignore
nl_template_func_decl_special:ignore
nl_template_func_def:ignore
nl_template_func_def_special:ignore
nl_template_var:ignore
nl_template_using:ignore
nl_class_brace:ignore
nl_class_init_args:ignore
nl_constr_init_args:ignore
nl_enum_own_lines:true						# modified
nl_func_type_name:ignore
nl_func_type_name_class:ignore
nl_func_class_scope:ignore
nl_func_scope_name:ignore
nl_func_proto_type_name:ignore
nl_func_paren:ignore
nl_func_paren_empty:ignore
nl_func_def_paren:ignore
nl_func_def_paren_empty:ignore
nl_func_call_paren:ignore
nl_func_call_paren_empty:ignore
nl_func_decl_start:ignore
nl_func_def_start:ignore
nl_func_decl_start_single:ignore
nl_func_def_start_single:ignore
nl_func_decl_start_multi_line:false
nl_func_def_start_multi_line:false
nl_func_decl_args:ignore
nl_func_def_args:ignore
nl_func_call_args:ignore
nl_func_decl_args_multi_line:false
nl_func_def_args_multi_line:false
nl_func_decl_end:ignore
nl_func_def_end:ignore
nl_func_decl_end_single:ignore
nl_func_def_end_single:ignore
nl_func_decl_end_multi_line:false
nl_func_def_end_multi_line:false
nl_func_decl_empty:ignore
nl_func_def_empty:ignore
nl_func_call_empty:ignore
nl_func_call_start:ignore
nl_func_call_end:ignore
nl_func_call_start_multi_line:false
nl_func_call_args_multi_line:false
nl_func_call_end_multi_line:false
nl_func_call_args_multi_line_ignore_closures:false
nl_template_start:false
nl_template_args:false
nl_template_end:false
nl_oc_msg_args:false
nl_oc_msg_args_min_params:0
nl_oc_msg_args_max_code_width:0
nl_fdef_brace:ignore
nl_fdef_brace_cond:ignore
nl_cpp_ldef_brace:ignore
nl_return_expr:ignore
nl_throw_expr:ignore
nl_after_semicolon:true						# modified
nl_paren_dbrace_open:ignore
nl_type_brace_init_lst:ignore
nl_type_brace_init_lst_open:ignore
nl_type_brace_init_lst_close:ignore
nl_before_brace_open:false
nl_after_brace_open:true					# modified
nl_after_brace_open_cmt:false
nl_after_vbrace_open:false
nl_after_vbrace_open_empty:false
nl_after_brace_close:false
nl_after_vbrace_close:false
nl_brace_struct_var:ignore
nl_define_macro:false
nl_squeeze_paren_close:false
nl_squeeze_ifdef:false
nl_squeeze_ifdef_top_level:false
nl_before_if:force							# modified
nl_after_if:force							# modified
nl_before_for:force							# modified
nl_after_for:force							# modified
nl_before_while:force						# modified
nl_after_while:force						# modified
nl_before_switch:force						# modified
nl_after_switch:force						# modified
nl_before_synchronized:ignore
nl_after_synchronized:ignore
nl_before_do:force							# modified
nl_after_do:force							# modified
nl_before_ignore_after_case:false
nl_before_return:true						# modified
nl_after_return:true						# modified
nl_before_member:true						# modified
nl_after_member:true						# modified
nl_ds_struct_enum_cmt:false
nl_ds_struct_enum_close_brace:false
nl_class_colon:ignore
nl_constr_colon:ignore
nl_namespace_two_to_one_liner:false
nl_create_if_one_liner:false
nl_create_for_one_liner:false
nl_create_while_one_liner:false
nl_create_func_def_one_liner:false
nl_create_list_one_liner:false
nl_split_if_one_liner:false
nl_split_for_one_liner:false
nl_split_while_one_liner:false
donot_add_nl_before_cpp_comment:false
nl_max:4									# modified
nl_max_blank_in_func:3						# modified
nl_inside_empty_func:3						# modified
nl_before_func_body_proto:1					# modified
nl_before_func_body_def:3					# modified
nl_before_func_class_proto:0
nl_before_func_class_def:0
nl_after_func_proto:1						# modified
nl_after_func_proto_group:0
nl_after_func_class_proto:0
nl_after_func_class_proto_group:0
nl_class_leave_one_liner_groups:false
nl_after_func_body:3						# modified
nl_after_func_body_class:0
nl_after_func_body_one_liner:0
nl_typedef_blk_start:0
nl_typedef_blk_end:0
nl_typedef_blk_in:0
nl_var_def_blk_end_func_top:3				# modified
nl_var_def_blk_start:3						# modified
nl_var_def_blk_end:3						# modified
nl_var_def_blk_in:0
nl_before_block_comment:3					# modified
nl_before_c_comment:3						# modified
nl_before_cpp_comment:0
nl_after_multiline_comment:false
nl_after_label_colon:false
nl_before_struct:0
nl_after_struct:0
nl_before_class:0
nl_after_class:0
nl_before_namespace:0
nl_inside_namespace:0
nl_after_namespace:0
nl_before_access_spec:0
nl_after_access_spec:0
nl_comment_func_def:1						# modified
nl_after_try_catch_finally:0
nl_around_cs_property:0
nl_between_get_set:0
nl_property_brace:ignore
eat_blanks_after_open_brace:false
eat_blanks_before_close_brace:false
nl_remove_extra_newlines:2					# modified
nl_after_annotation:ignore
nl_between_annotation:ignore
nl_before_whole_file_ifdef:0
nl_after_whole_file_ifdef:0
nl_before_whole_file_endif:0
nl_after_whole_file_endif:0
pos_arith:ignore
pos_assign:ignore
pos_bool:ignore
pos_compare:ignore
pos_conditional:ignore
pos_comma:ignore
pos_enum_comma:ignore
pos_class_comma:ignore
pos_constr_comma:ignore
pos_class_colon:ignore
pos_constr_colon:ignore
pos_shift:ignore
code_width:160								# modified
ls_for_split_full:false
ls_func_split_full:false
ls_code_width:true							# modified
align_keep_tabs:false
align_with_tabs:false
align_on_tabstop:false
align_number_right:false
align_keep_extra_space:false
align_func_params:false
align_func_params_span:0
align_func_params_thresh:0
align_func_params_gap:0
align_constr_value_span:0
align_constr_value_thresh:0
align_constr_value_gap:0
align_same_func_call_params:false
align_same_func_call_params_span:0
align_same_func_call_params_thresh:0
align_var_def_span:0
align_var_def_star_style:0
align_var_def_amp_style:0
align_var_def_thresh:0
align_var_def_gap:0
align_var_def_colon:false
align_var_def_colon_gap:0
align_var_def_attribute:false
align_var_def_inline:false
align_assign_span:0
align_assign_func_proto_span:0
align_assign_thresh:0
align_assign_on_multi_var_defs:false
align_braced_init_list_span:0
align_braced_init_list_thresh:0
align_assign_decl_func:0
align_enum_equ_span:0
align_enum_equ_thresh:0
align_var_class_span:0
align_var_class_thresh:0
align_var_class_gap:0
align_var_struct_span:0
align_var_struct_thresh:0
align_var_struct_gap:0
align_struct_init_span:0
align_typedef_span:0
align_typedef_gap:0
align_typedef_func:0
align_typedef_star_style:0
align_typedef_amp_style:0
align_right_cmt_span:0
align_right_cmt_gap:0
align_right_cmt_mix:false
align_right_cmt_same_level:false
align_right_cmt_at_col:0
align_func_proto_span:0
align_func_proto_star_style:0
align_func_proto_amp_style:0
align_func_proto_thresh:0
align_func_proto_gap:0
align_on_operator:false
align_mix_var_proto:false
align_single_line_func:false
align_single_line_brace:false
align_single_line_brace_gap:0
align_oc_msg_spec_span:0
align_nl_cont:false
align_pp_define_together:false
align_pp_define_span:0
align_pp_define_gap:0
align_left_shift:true
align_eigen_comma_init:false
align_asm_colon:false
align_oc_msg_colon_span:0
align_oc_msg_colon_first:false
align_oc_decl_colon:false
align_oc_msg_colon_xcode_like:false
cmt_width:80								# modified
cmt_reflow_mode:2							# modified
cmt_reflow_fold_regex_file:\"\"
cmt_reflow_indent_to_paragraph_start:false
cmt_convert_tab_to_spaces:true				# modified
cmt_indent_multi:true
cmt_align_doxygen_javadoc_tags:true			# modified
cmt_sp_before_doxygen_javadoc_tags:1
cmt_trailing_single_line_c_to_cpp:false
cmt_c_group:false
cmt_c_nl_start:false
cmt_c_nl_end:false
cmt_cpp_to_c:false
cmt_cpp_group:false
cmt_cpp_nl_start:false
cmt_cpp_nl_end:false
cmt_star_cont:true							# modified
cmt_sp_before_star_cont:0
cmt_sp_after_star_cont:1					# modified
cmt_multi_check_last:true
cmt_multi_first_len_minimum:4
cmt_insert_file_header:\"\"
cmt_insert_file_footer:\"\"
cmt_insert_func_header:\"\"
cmt_insert_class_header:\"\"
cmt_insert_oc_msg_header:\"\"
cmt_insert_before_preproc:false
cmt_insert_before_inlines:true
cmt_insert_before_ctor_dtor:false
mod_full_brace_do:force						# modified
mod_full_brace_for:force					# modified
mod_full_brace_function:force				# modified
mod_full_brace_if:force						# modified
mod_full_brace_if_chain:0
mod_full_brace_if_chain_only:false
mod_full_brace_while:force					# modified
mod_full_brace_using:force					# modified
mod_full_brace_nl:0
mod_full_brace_nl_block_rem_mlcond:false
mod_paren_on_return:force					# modified
mod_paren_on_throw:ignore
mod_pawn_semicolon:false
mod_full_paren_if_bool:true					# modified
mod_full_paren_assign_bool:false
mod_full_paren_return_bool:false
mod_remove_extra_semicolon:true				# modified
mod_remove_duplicate_include:false
mod_add_long_function_closebrace_comment:0
mod_add_long_namespace_closebrace_comment:0
mod_add_long_class_closebrace_comment:0
mod_add_long_switch_closebrace_comment:0
mod_add_long_ifdef_endif_comment:1			# modified
mod_add_long_ifdef_else_comment:1			# modified
mod_sort_case_sensitive:false
mod_sort_import:false
mod_sort_using:false
mod_sort_include:false
mod_sort_incl_import_prioritize_filename:false
mod_sort_incl_import_prioritize_extensionless:false
mod_sort_incl_import_prioritize_angle_over_quotes:false
mod_sort_incl_import_ignore_extension:false
mod_sort_incl_import_grouping_enabled:false
mod_move_case_break:false
mod_move_case_return:false
mod_case_brace:ignore
mod_remove_empty_return:false
mod_enum_last_comma:ignore
mod_infinite_loop:0
mod_int_short:ignore
mod_short_int:ignore
mod_int_long:ignore
mod_long_int:ignore
mod_int_signed:ignore
mod_signed_int:ignore
mod_int_unsigned:ignore
mod_unsigned_int:ignore
mod_int_prefer_int_on_left:false
mod_sort_oc_properties:false
mod_sort_oc_property_class_weight:0
mod_sort_oc_property_thread_safe_weight:0
mod_sort_oc_property_readwrite_weight:0
mod_sort_oc_property_reference_weight:0
mod_sort_oc_property_getter_weight:0
mod_sort_oc_property_setter_weight:0
mod_sort_oc_property_nullability_weight:0
pp_indent_with_tabs:0						# modified
pp_indent:force								# modified
pp_indent_at_level:false
pp_indent_at_level0:false
pp_indent_count:2							# modified
pp_space_after:ignore
pp_space_count:0
pp_indent_region:0
pp_region_indent_code:false
pp_indent_if:0
pp_if_indent_code:true						# modified
pp_indent_in_guard:false
pp_define_at_level:false
pp_include_at_level:false
pp_ignore_define_body:false
pp_multiline_define_body_indent:8
pp_indent_case:true
pp_indent_func_def:true
pp_indent_extern:true
pp_indent_brace:1
pp_warn_unbalanced_if:false
include_category_0:\"\"
include_category_1:\"\"
include_category_2:\"\"
use_indent_func_call_param:true
use_indent_continue_only_once:false
indent_cpp_lambda_only_once:false
use_sp_after_angle_always:false
use_options_overriding_for_qt_macros:true
use_form_feed_no_more_as_whitespace_character:false
warn_level_tabs_found_in_verbatim_string_literals:2
debug_max_number_of_loops:0
debug_line_number_to_protocol:0
debug_timeout:0
debug_truncate:0
debug_sort_the_tracks:true
debug_decode_the_flags:false
set_numbering_for_html_output:false
END
)
DEFFILE=defaults.cfg
OUTFILE=helios.cfg
rm $OUTFILE
cp $DEFFILE $OUTFILE
sed -i 's/#.*//' $OUTFILE
sed -i '/^$/d' $OUTFILE
sed -i 's/ //g' $OUTFILE
IFS=$'\n' command eval "LINES=($CONFIG)"
for LINE in "${LINES[@]}"
do
	KEY=$(echo $LINE | cut -f1 -d:)
	VALUE=$(echo $LINE | cut -f2 -d:)
	sed -i "/^$KEY=/s/=.*/ = $VALUE/" $OUTFILE
done