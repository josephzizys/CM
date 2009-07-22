#>
#include "juce.h"
#include "CmSupport.h"
<#

(define ffi_quit (foreign-lambda void "cm_quit"))
(define ffi_print_error (foreign-lambda void "cm_print_error" c-string))
(define ffi_print_output (foreign-lambda void "cm_print_output" c-string bool))
(define ffi_print_values (foreign-lambda void "cm_print_values" c-string))
(define ffi_shell (foreign-lambda void "cm_shell" c-string))
(define ffi_play (foreign-lambda void "cm_play" c-string))
(define ffi_rescale (foreign-lambda double "cm_rescale" double double double double double double))
(define ffi_descrete (foreign-lambda int "cm_discrete" double double double int int double))
(define ffi_float_to_fixnum (foreign-lambda int "cm_float_to_fixnum" double))
(define ffi_quantize (foreign-lambda double "cm_quantize" double double))
(define ffi_rhythm_to_seconds (foreign-lambda double "cm_rhythm_to_seconds" double double double))
(define ffi_cents_to_scaler (foreign-lambda double "cm_cents_to_scaler" double))
(define ffi_scaler_to_cents (foreign-lambda double "cm_scaler_to_cents" double))
(define ffi_scaler_to_steps (foreign-lambda double "cm_scaler_to_steps" double))
(define ffi_explseg (foreign-lambda double "cm_explseg" int int double double))
(define ffi_geoseg (foreign-lambda double "cm_geoseg" int int double double))
(define ffi_keynum_to_hertz (foreign-lambda double "cm_keynum_to_hertz" double))
(define ffi_keynum_to_pc (foreign-lambda int "cm_keynum_to_pc" double))
(define ffi_hertz_to_keynum (foreign-lambda double "cm_hertz_to_keynum" double))
(define ffi_ranseed (foreign-lambda void "cm_ranseed" integer64))
(define ffi_ranint (foreign-lambda int "cm_ranint" int))
(define ffi_ranfloat (foreign-lambda double "cm_ranfloat" double))
(define ffi_ranint2 (foreign-lambda int "cm_ranint2" int int))
(define ffi_ranfloat2 (foreign-lambda double "cm_ranfloat2" double double))
(define ffi_ranlow (foreign-lambda double "cm_ranlow"))
(define ffi_ranhigh (foreign-lambda double "cm_ranhigh"))
(define ffi_ranmiddle (foreign-lambda double "cm_ranmiddle"))
(define ffi_rangauss (foreign-lambda double "cm_rangauss" double double))
(define ffi_ranexp (foreign-lambda double "cm_ranexp" double))
(define ffi_ranbeta (foreign-lambda double "cm_ranbeta" double double))
(define ffi_rangamma (foreign-lambda double "cm_rangamma" double))
(define ffi_rancauchy (foreign-lambda double "cm_rancauchy"))
(define ffi_ranpoisson (foreign-lambda int "cm_ranpoisson" double))
(define ffi_ranpink (foreign-lambda double "cm_ranpink"))
(define ffi_ranbrown (foreign-lambda double "cm_ranbrown"))
(define ffi_bes_jn (foreign-lambda double "cm_bes_jn" int double))
(define ffi_log_ten (foreign-lambda double "cm_log_ten" double))
(define ffi_log_two (foreign-lambda double "cm_log_two" double))
(define ffi_now (foreign-lambda double "cm_now"))
(define ffi_sched_sprout (foreign-lambda void "cm_sched_sprout" scheme-object double int))
(define ffi_sched_paused_p (foreign-lambda bool "cm_sched_paused_p"))
(define ffi_sched_pause (foreign-lambda void "cm_sched_pause"))
(define ffi_sched_continue (foreign-lambda void "cm_sched_continue"))
(define ffi_sched_stop (foreign-lambda void "cm_sched_stop" int))
(define ffi_sched_busy_p (foreign-lambda bool "cm_sched_busy_p"))
(define ffi_sched_score_mode_p (foreign-lambda bool "cm_sched_score_mode_p"))
(define ffi_sched_set_score_mode (foreign-lambda void "cm_sched_set_score_mode" int))
(define ffi_sched_score_time (foreign-lambda double "cm_sched_score_time"))
(define ffi_user_home_directory (foreign-lambda c-string "cm_user_home_directory"))
(define ffi_temp_directory (foreign-lambda c-string "cm_temp_directory"))
(define ffi_current_directory (foreign-lambda c-string "cm_current_directory"))
(define ffi_set_current_directory (foreign-lambda bool "cm_set_current_directory" c-string))
(define ffi_pathname_directory (foreign-lambda c-string "cm_pathname_directory" c-string))
(define ffi_pathname_name (foreign-lambda c-string "cm_pathname_name" c-string))
(define ffi_pathname_type (foreign-lambda c-string "cm_pathname_type" c-string))
(define ffi_full_pathname (foreign-lambda c-string "cm_full_pathname" c-string))
(define ffi_pathname_exists_p (foreign-lambda bool "cm_pathname_exists_p" c-string))
(define ffi_pathname_writable_p (foreign-lambda bool "cm_pathname_writable_p" c-string))
(define ffi_pathname_directory_p (foreign-lambda bool "cm_pathname_directory_p" c-string))
(define ffi_directory (foreign-lambda c-string "cm_directory" c-string bool))
(define ffi_sal_tokenize (foreign-lambda c-string "sal_tokenize" c-string))
(define ffi_port_info (foreign-lambda c-string "cm_port_info"))
(define ffi_mp_open_output (foreign-lambda bool "mp_open_output" int))
(define ffi_mp_open_input (foreign-lambda bool "mp_open_input" int))
(define ffi_mp_close_output (foreign-lambda void "mp_close_output" int))
(define ffi_mp_close_input (foreign-lambda void "mp_close_input" int))
(define ffi_mp_set_output_file (foreign-lambda void "mp_set_output_file" c-string))
(define ffi_mp_send_note (foreign-lambda void "mp_send_note" double double double double double))
(define ffi_mp_send_data (foreign-lambda void "mp_send_data" int double double double double))
(define ffi_mp_set_channel_mask (foreign-lambda void "mp_set_channel_mask" int))
(define ffi_mp_set_message_mask (foreign-lambda void "mp_set_message_mask" int))
(define ffi_mp_set_tuning (foreign-lambda void "mp_set_tuning" int))
(define ffi_mp_set_instruments (foreign-lambda void "mp_set_instruments" int int int int int int int int int int int int int int int int))
(define ffi_mp_play_seq (foreign-lambda void "mp_play_seq"))
(define ffi_mp_save_seq (foreign-lambda void "mp_save_seq"))
(define ffi_mp_copy_seq (foreign-lambda void "mp_copy_seq"))
(define ffi_mp_plot_seq (foreign-lambda void "mp_plot_seq"))
(define ffi_mp_clear_seq (foreign-lambda void "mp_clear_seq"))
(define ffi_mp_set_midi_input_hook (foreign-lambda void "mp_set_midi_input_hook" scheme-object))
(define ffi_mp_clear_midi_input_hook (foreign-lambda void "mp_clear_midi_input_hook"))
(define ffi_cs_init_score (foreign-lambda void "cs_init_score" c-string))
(define ffi_cs_send_score (foreign-lambda void "cs_send_score" int int double c-string))
(define ffi_fms_open_score (foreign-lambda void "fms_open_score" c-string c-string))
(define ffi_fms_close_score (foreign-lambda void "fms_close_score"))
(define ffi_fms_new (foreign-lambda void "fms_new" c-string))
(define ffi_fms_select (foreign-lambda void "fms_select" c-string))
(define ffi_fms_free (foreign-lambda void "fms_free"))
(define ffi_fms_clear (foreign-lambda void "fms_clear"))
(define ffi_fms_load (foreign-lambda void "fms_load" c-string))
(define ffi_fms_run (foreign-lambda void "fms_run"))
(define ffi_fms_xml (foreign-lambda void "fms_xml" c-string))
(define ffi_fms_save (foreign-lambda void "fms_save" c-string))
(define ffi_fms_isfiletype (foreign-lambda int "fms_isfiletype" c-string))
(define ffi_plot_xml (foreign-lambda void "plot_xml" c-string))
(define ffi_plot_data (foreign-lambda c-string "plot_data" c-string int))
