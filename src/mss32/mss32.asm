; mss32.s - NASM syntax

global _AIL_3D_distance_factor
global _AIL_3D_doppler_factor
global _AIL_3D_orientation
global _AIL_3D_position
global _AIL_3D_provider_attribute
global _AIL_3D_rolloff_factor
global _AIL_3D_room_type
global _AIL_3D_sample_attribute
global _AIL_3D_sample_cone
global _AIL_3D_sample_distances
global _AIL_3D_sample_effects_level
global _AIL_3D_sample_exclusion
global _AIL_3D_sample_length
global _AIL_3D_sample_loop_count
global _AIL_3D_sample_obstruction
global _AIL_3D_sample_occlusion
global _AIL_3D_sample_offset
global _AIL_3D_sample_playback_rate
global _AIL_3D_sample_status
global _AIL_3D_sample_volume
global _AIL_3D_speaker_type
global _AIL_3D_user_data
global _AIL_3D_velocity
global _AIL_active_3D_sample_count
global _AIL_active_sample_count
global _AIL_active_sequence_count
global _AIL_allocate_3D_sample_handle
global _AIL_allocate_file_sample
global _AIL_allocate_sample_handle
global _AIL_allocate_sequence_handle
global _AIL_auto_service_stream
global _AIL_auto_update_3D_position
global _AIL_background
global _AIL_branch_index
global _AIL_close_3D_listener
global _AIL_close_3D_object
global _AIL_close_3D_provider
global _AIL_close_digital_driver
global _AIL_close_filter
global _AIL_close_input
global _AIL_close_stream
global _AIL_close_XMIDI_driver
global _AIL_compress_ADPCM
global _AIL_compress_ASI
global _AIL_compress_DLS
global _AIL_controller_value
global _AIL_create_wave_synthesizer
global _AIL_decompress_ADPCM
global _AIL_decompress_ASI
global _AIL_delay
global _AIL_destroy_wave_synthesizer
global _AIL_digital_configuration
global _AIL_digital_CPU_percent
global _AIL_digital_handle_reacquire
global _AIL_digital_handle_release
global _AIL_digital_latency
global _AIL_digital_master_reverb_levels
global _AIL_digital_master_reverb
global _AIL_digital_master_volume_level
global _AIL_DLS_close
global _AIL_DLS_compact
global _AIL_DLS_get_info
global _AIL_DLS_get_reverb_levels
global _AIL_DLS_load_file
global _AIL_DLS_load_memory
global _AIL_DLS_open
global _AIL_DLS_set_reverb_levels
global _AIL_DLS_unload
global _AIL_end_3D_sample
global _AIL_end_sample
global _AIL_end_sequence
global _AIL_enumerate_3D_provider_attributes
global _AIL_enumerate_3D_providers
global _AIL_enumerate_3D_sample_attributes
global _AIL_enumerate_filter_attributes
global _AIL_enumerate_filter_sample_attributes
global _AIL_enumerate_filters
global _AIL_extract_DLS
global _AIL_file_error
global _AIL_file_read
global _AIL_file_size
global _AIL_file_type
global _AIL_file_write
global _AIL_filter_attribute
global _AIL_filter_DLS_attribute
global _AIL_filter_DLS_with_XMI
global _AIL_filter_sample_attribute
global _AIL_filter_stream_attribute
global _AIL_find_DLS
global _AIL_get_DirectSound_info
global _AIL_get_input_info
global _AIL_get_preference
global _AIL_get_timer_highest_delay
global _AIL_HWND
global _AIL_channel_notes
global _AIL_init_sample
global _AIL_init_sequence
global _AIL_last_error
global _AIL_list_DLS
global _AIL_list_MIDI
global _AIL_load_sample_buffer
global _AIL_lock_channel
global _AIL_lock_mutex
global _AIL_lock
global _AIL_map_sequence_channel
global _AIL_mem_alloc_lock
global _AIL_mem_free_lock
global _AIL_mem_use_free
global _AIL_mem_use_malloc
global _AIL_merge_DLS_with_XMI
global _AIL_MIDI_handle_reacquire
global _AIL_MIDI_handle_release
global _AIL_MIDI_to_XMI
global _AIL_midiOutClose
global _AIL_midiOutOpen
global _AIL_minimum_sample_buffer_size
global _AIL_MMX_available
global _AIL_ms_count
global _AIL_open_3D_listener
global _AIL_open_3D_object
global _AIL_open_3D_provider
global _AIL_open_digital_driver
global _AIL_open_filter
global _AIL_open_input
global _AIL_open_stream
global _AIL_open_XMIDI_driver
global _AIL_pause_stream
global _AIL_primary_digital_driver
global _AIL_process_digital_audio
global _AIL_quick_copy
global _AIL_quick_halt
global _AIL_quick_handles
global _AIL_quick_load_and_play
global _AIL_quick_load_mem
global _AIL_quick_load
global _AIL_quick_ms_length
global _AIL_quick_ms_position
global _AIL_quick_play
global _AIL_quick_set_low_pass_cut_off
global _AIL_quick_set_ms_position
global _AIL_quick_set_reverb_levels
global _AIL_quick_set_speed
global _AIL_quick_set_volume
global _AIL_quick_shutdown
global _AIL_quick_startup
global _AIL_quick_status
global _AIL_quick_type
global _AIL_quick_unload
global _AIL_redbook_close
global _AIL_redbook_eject
global _AIL_redbook_id
global _AIL_redbook_open_drive
global _AIL_redbook_open
global _AIL_redbook_pause
global _AIL_redbook_play
global _AIL_redbook_position
global _AIL_redbook_resume
global _AIL_redbook_retract
global _AIL_redbook_set_volume_level
global _AIL_redbook_status
global _AIL_redbook_stop
global _AIL_redbook_track_info
global _AIL_redbook_track
global _AIL_redbook_tracks
global _AIL_redbook_volume_level
global _AIL_register_3D_EOS_callback
global _AIL_register_beat_callback
global _AIL_register_EOB_callback
global _AIL_register_EOF_callback
global _AIL_register_EOS_callback
global _AIL_register_event_callback
global _AIL_register_ICA_array
global _AIL_register_prefix_callback
global _AIL_register_sequence_callback
global _AIL_register_SOB_callback
global _AIL_register_stream_callback
global _AIL_register_timbre_callback
global _AIL_register_timer
global _AIL_register_trigger_callback
global _AIL_release_3D_sample_handle
global _AIL_release_all_timers
global _AIL_release_channel
global _AIL_release_sample_handle
global _AIL_release_sequence_handle
global _AIL_release_timer_handle
global _AIL_request_EOB_ASI_reset
global _AIL_resume_3D_sample
global _AIL_resume_sample
global _AIL_resume_sequence
global _AIL_sample_buffer_info
global _AIL_sample_buffer_ready
global _AIL_sample_granularity
global _AIL_sample_loop_count
global _AIL_sample_low_pass_cut_off
global _AIL_sample_ms_position
global _AIL_sample_playback_rate
global _AIL_sample_position
global _AIL_sample_reverb_levels
global _AIL_sample_status
global _AIL_sample_user_data
global _AIL_sample_volume_levels
global _AIL_sample_volume_pan
global _AIL_send_channel_voice_message
global _AIL_send_sysex_message
global _AIL_sequence_loop_count
global _AIL_sequence_ms_position
global _AIL_sequence_position
global _AIL_sequence_status
global _AIL_sequence_tempo
global _AIL_sequence_user_data
global _AIL_sequence_volume
global _AIL_serve
global _AIL_service_stream
global _AIL_set_3D_distance_factor
global _AIL_set_3D_doppler_factor
global _AIL_set_3D_orientation
global _AIL_set_3D_position
global _AIL_set_3D_provider_preference
global _AIL_set_3D_rolloff_factor
global _AIL_set_3D_room_type
global _AIL_set_3D_sample_cone
global _AIL_set_3D_sample_distances
global _AIL_set_3D_sample_effects_level
global _AIL_set_3D_sample_exclusion
global _AIL_set_3D_sample_file
global _AIL_set_3D_sample_info
global _AIL_set_3D_sample_loop_block
global _AIL_set_3D_sample_loop_count
global _AIL_set_3D_sample_obstruction
global _AIL_set_3D_sample_occlusion
global _AIL_set_3D_sample_offset
global _AIL_set_3D_sample_playback_rate
global _AIL_set_3D_sample_preference
global _AIL_set_3D_sample_volume
global _AIL_set_3D_speaker_type
global _AIL_set_3D_user_data
global _AIL_set_3D_velocity_vector
global _AIL_set_3D_velocity
global _AIL_set_digital_driver_processor
global _AIL_set_digital_master_reverb_levels
global _AIL_set_digital_master_reverb
global _AIL_set_digital_master_room_type
global _AIL_set_digital_master_volume_level
global _AIL_set_DirectSound_HWND
global _AIL_set_DLS_processor
global _AIL_set_error
global _AIL_set_file_async_callbacks
global _AIL_set_file_callbacks
global _AIL_set_filter_DLS_preference
global _AIL_set_filter_preference
global _AIL_set_filter_sample_preference
global _AIL_set_filter_stream_preference
global _AIL_set_input_state
global _AIL_set_named_sample_file
global _AIL_set_preference
global _AIL_set_redist_directory
global _AIL_set_sample_address
global _AIL_set_sample_adpcm_block_size
global _AIL_set_sample_file
global _AIL_set_sample_loop_block
global _AIL_set_sample_loop_count
global _AIL_set_sample_low_pass_cut_off
global _AIL_set_sample_ms_position
global _AIL_set_sample_playback_rate
global _AIL_set_sample_position
global _AIL_set_sample_processor
global _AIL_set_sample_reverb_levels
global _AIL_set_sample_type
global _AIL_set_sample_user_data
global _AIL_set_sample_volume_levels
global _AIL_set_sample_volume_pan
global _AIL_set_sequence_loop_count
global _AIL_set_sequence_ms_position
global _AIL_set_sequence_tempo
global _AIL_set_sequence_user_data
global _AIL_set_sequence_volume
global _AIL_set_stream_loop_block
global _AIL_set_stream_loop_count
global _AIL_set_stream_low_pass_cut_off
global _AIL_set_stream_ms_position
global _AIL_set_stream_playback_rate
global _AIL_set_stream_position
global _AIL_set_stream_processor
global _AIL_set_stream_reverb_levels
global _AIL_set_stream_user_data
global _AIL_set_stream_volume_levels
global _AIL_set_stream_volume_pan
global _AIL_set_timer_divisor
global _AIL_set_timer_frequency
global _AIL_set_timer_period
global _AIL_set_timer_user
global _AIL_set_XMIDI_master_volume
global _AIL_shutdown
global _AIL_size_processed_digital_audio
global _AIL_start_3D_sample
global _AIL_start_all_timers
global _AIL_start_sample
global _AIL_start_sequence
global _AIL_start_stream
global _AIL_start_timer
global _AIL_startup
global _AIL_stop_3D_sample
global _AIL_stop_all_timers
global _AIL_stop_sample
global _AIL_stop_sequence
global _AIL_stop_timer
global _AIL_stream_info
global _AIL_stream_loop_count
global _AIL_stream_low_pass_cut_off
global _AIL_stream_ms_position
global _AIL_stream_playback_rate
global _AIL_stream_position
global _AIL_stream_reverb_levels
global _AIL_stream_status
global _AIL_stream_user_data
global _AIL_stream_volume_levels
global _AIL_stream_volume_pan
global _AIL_true_sequence_channel
global _AIL_unlock_mutex
global _AIL_unlock
global _AIL_update_3D_position
global _AIL_us_count
global _AIL_WAV_file_write
global _AIL_WAV_info
global _AIL_waveOutClose
global _AIL_waveOutOpen
global _AIL_XMIDI_master_volume
global _DllMain
global _DLSMSSGetCPU
global _MIX_RIB_MAIN
global _RIB_enumerate_providers
global _RIB_find_file_dec_provider
global _RIB_find_files_provider
global _RIB_find_provider
global _RIB_load_application_providers
global _RIB_load_static_provider_library
global _RIB_provider_system_data
global _RIB_provider_user_data
global _RIB_set_provider_system_data
global _RIB_set_provider_user_data
global _AIL_debug_printf
global _AIL_sprintf
global _DLSClose
global _DLSCompactMemory
global _DLSGetInfo
global _DLSLoadFile
global _DLSLoadMemFile
global _DLSMSSOpen
global _DLSSetAttribute
global _DLSUnloadAll
global _DLSUnloadFile
global _RIB_alloc_provider_handle
global _RIB_enumerate_interface
global _RIB_error
global _RIB_find_file_provider
global _RIB_free_provider_handle
global _RIB_free_provider_library
global _RIB_load_provider_library
global _RIB_register_interface
global _RIB_request_interface
global _RIB_request_interface_entry
global _RIB_type_string
global _RIB_unregister_interface
global _stream_background




extern _pMSS32_original_functions

section .text




_AIL_3D_distance_factor:                          jmp dword [_pMSS32_original_functions + 0]               ; _AIL_3D_distance_factor@4
_AIL_3D_doppler_factor:                           jmp dword [_pMSS32_original_functions + 4]               ; _AIL_3D_doppler_factor@4
_AIL_3D_orientation:                              jmp dword [_pMSS32_original_functions + 8]               ; _AIL_3D_orientation@28
_AIL_3D_position:                                 jmp dword [_pMSS32_original_functions + 12]              ; _AIL_3D_position@16
_AIL_3D_provider_attribute:                       jmp dword [_pMSS32_original_functions + 16]              ; _AIL_3D_provider_attribute@12
_AIL_3D_rolloff_factor:                           jmp dword [_pMSS32_original_functions + 20]              ; _AIL_3D_rolloff_factor@4
_AIL_3D_room_type:                                jmp dword [_pMSS32_original_functions + 24]              ; _AIL_3D_room_type@4
_AIL_3D_sample_attribute:                         jmp dword [_pMSS32_original_functions + 28]              ; _AIL_3D_sample_attribute@12
_AIL_3D_sample_cone:                              jmp dword [_pMSS32_original_functions + 32]              ; _AIL_3D_sample_cone@16
_AIL_3D_sample_distances:                         jmp dword [_pMSS32_original_functions + 36]              ; _AIL_3D_sample_distances@12
_AIL_3D_sample_effects_level:                     jmp dword [_pMSS32_original_functions + 40]              ; _AIL_3D_sample_effects_level@4
_AIL_3D_sample_exclusion:                         jmp dword [_pMSS32_original_functions + 44]              ; _AIL_3D_sample_exclusion@4
_AIL_3D_sample_length:                            jmp dword [_pMSS32_original_functions + 48]              ; _AIL_3D_sample_length@4
_AIL_3D_sample_loop_count:                        jmp dword [_pMSS32_original_functions + 52]              ; _AIL_3D_sample_loop_count@4
_AIL_3D_sample_obstruction:                       jmp dword [_pMSS32_original_functions + 56]              ; _AIL_3D_sample_obstruction@4
_AIL_3D_sample_occlusion:                         jmp dword [_pMSS32_original_functions + 60]              ; _AIL_3D_sample_occlusion@4
_AIL_3D_sample_offset:                            jmp dword [_pMSS32_original_functions + 64]              ; _AIL_3D_sample_offset@4
_AIL_3D_sample_playback_rate:                     jmp dword [_pMSS32_original_functions + 68]              ; _AIL_3D_sample_playback_rate@4
_AIL_3D_sample_status:                            jmp dword [_pMSS32_original_functions + 72]              ; _AIL_3D_sample_status@4
_AIL_3D_sample_volume:                            jmp dword [_pMSS32_original_functions + 76]              ; _AIL_3D_sample_volume@4
_AIL_3D_speaker_type:                             jmp dword [_pMSS32_original_functions + 80]              ; _AIL_3D_speaker_type@4
_AIL_3D_user_data:                                jmp dword [_pMSS32_original_functions + 84]              ; _AIL_3D_user_data@8
_AIL_3D_velocity:                                 jmp dword [_pMSS32_original_functions + 88]              ; _AIL_3D_velocity@16
_AIL_active_3D_sample_count:                      jmp dword [_pMSS32_original_functions + 92]              ; _AIL_active_3D_sample_count@4
_AIL_active_sample_count:                         jmp dword [_pMSS32_original_functions + 96]              ; _AIL_active_sample_count@4
_AIL_active_sequence_count:                       jmp dword [_pMSS32_original_functions + 100]             ; _AIL_active_sequence_count@4
_AIL_allocate_3D_sample_handle:                   jmp dword [_pMSS32_original_functions + 104]             ; _AIL_allocate_3D_sample_handle@4
_AIL_allocate_file_sample:                        jmp dword [_pMSS32_original_functions + 108]             ; _AIL_allocate_file_sample@12
_AIL_allocate_sample_handle:                      jmp dword [_pMSS32_original_functions + 112]             ; _AIL_allocate_sample_handle@4
_AIL_allocate_sequence_handle:                    jmp dword [_pMSS32_original_functions + 116]             ; _AIL_allocate_sequence_handle@4
_AIL_auto_service_stream:                         jmp dword [_pMSS32_original_functions + 120]             ; _AIL_auto_service_stream@8
_AIL_auto_update_3D_position:                     jmp dword [_pMSS32_original_functions + 124]             ; _AIL_auto_update_3D_position@8
_AIL_background:                                  jmp dword [_pMSS32_original_functions + 128]             ; _AIL_background@0
_AIL_branch_index:                                jmp dword [_pMSS32_original_functions + 132]             ; _AIL_branch_index@8
_AIL_close_3D_listener:                           jmp dword [_pMSS32_original_functions + 136]             ; _AIL_close_3D_listener@4
_AIL_close_3D_object:                             jmp dword [_pMSS32_original_functions + 140]             ; _AIL_close_3D_object@4
_AIL_close_3D_provider:                           jmp dword [_pMSS32_original_functions + 144]             ; _AIL_close_3D_provider@4
_AIL_close_digital_driver:                        jmp dword [_pMSS32_original_functions + 148]             ; _AIL_close_digital_driver@4
_AIL_close_filter:                                jmp dword [_pMSS32_original_functions + 152]             ; _AIL_close_filter@4
_AIL_close_input:                                 jmp dword [_pMSS32_original_functions + 156]             ; _AIL_close_input@4
_AIL_close_stream:                                jmp dword [_pMSS32_original_functions + 160]             ; _AIL_close_stream@4
_AIL_close_XMIDI_driver:                          jmp dword [_pMSS32_original_functions + 164]             ; _AIL_close_XMIDI_driver@4
_AIL_compress_ADPCM:                              jmp dword [_pMSS32_original_functions + 168]             ; _AIL_compress_ADPCM@12
_AIL_compress_ASI:                                jmp dword [_pMSS32_original_functions + 172]             ; _AIL_compress_ASI@20
_AIL_compress_DLS:                                jmp dword [_pMSS32_original_functions + 176]             ; _AIL_compress_DLS@20
_AIL_controller_value:                            jmp dword [_pMSS32_original_functions + 180]             ; _AIL_controller_value@12
_AIL_create_wave_synthesizer:                     jmp dword [_pMSS32_original_functions + 184]             ; _AIL_create_wave_synthesizer@16
_AIL_decompress_ADPCM:                            jmp dword [_pMSS32_original_functions + 188]             ; _AIL_decompress_ADPCM@12
_AIL_decompress_ASI:                              jmp dword [_pMSS32_original_functions + 192]             ; _AIL_decompress_ASI@24
_AIL_delay:                                       jmp dword [_pMSS32_original_functions + 196]             ; _AIL_delay@4
_AIL_destroy_wave_synthesizer:                    jmp dword [_pMSS32_original_functions + 200]             ; _AIL_destroy_wave_synthesizer@4
_AIL_digital_configuration:                       jmp dword [_pMSS32_original_functions + 204]             ; _AIL_digital_configuration@16
_AIL_digital_CPU_percent:                         jmp dword [_pMSS32_original_functions + 208]             ; _AIL_digital_CPU_percent@4
_AIL_digital_handle_reacquire:                    jmp dword [_pMSS32_original_functions + 212]             ; _AIL_digital_handle_reacquire@4
_AIL_digital_handle_release:                      jmp dword [_pMSS32_original_functions + 216]             ; _AIL_digital_handle_release@4
_AIL_digital_latency:                             jmp dword [_pMSS32_original_functions + 220]             ; _AIL_digital_latency@4
_AIL_digital_master_reverb_levels:                jmp dword [_pMSS32_original_functions + 224]             ; _AIL_digital_master_reverb_levels@12
_AIL_digital_master_reverb:                       jmp dword [_pMSS32_original_functions + 228]             ; _AIL_digital_master_reverb@16
_AIL_digital_master_volume_level:                 jmp dword [_pMSS32_original_functions + 232]             ; _AIL_digital_master_volume_level@4
_AIL_DLS_close:                                   jmp dword [_pMSS32_original_functions + 236]             ; _AIL_DLS_close@8
_AIL_DLS_compact:                                 jmp dword [_pMSS32_original_functions + 240]             ; _AIL_DLS_compact@4
_AIL_DLS_get_info:                                jmp dword [_pMSS32_original_functions + 244]             ; _AIL_DLS_get_info@12
_AIL_DLS_get_reverb_levels:                       jmp dword [_pMSS32_original_functions + 248]             ; _AIL_DLS_get_reverb_levels@12
_AIL_DLS_load_file:                               jmp dword [_pMSS32_original_functions + 252]             ; _AIL_DLS_load_file@12
_AIL_DLS_load_memory:                             jmp dword [_pMSS32_original_functions + 256]             ; _AIL_DLS_load_memory@12
_AIL_DLS_open:                                    jmp dword [_pMSS32_original_functions + 260]             ; _AIL_DLS_open@28
_AIL_DLS_set_reverb_levels:                       jmp dword [_pMSS32_original_functions + 264]             ; _AIL_DLS_set_reverb_levels@12
_AIL_DLS_unload:                                  jmp dword [_pMSS32_original_functions + 268]             ; _AIL_DLS_unload@8
_AIL_end_3D_sample:                               jmp dword [_pMSS32_original_functions + 272]             ; _AIL_end_3D_sample@4
_AIL_end_sample:                                  jmp dword [_pMSS32_original_functions + 276]             ; _AIL_end_sample@4
_AIL_end_sequence:                                jmp dword [_pMSS32_original_functions + 280]             ; _AIL_end_sequence@4
_AIL_enumerate_3D_provider_attributes:            jmp dword [_pMSS32_original_functions + 284]             ; _AIL_enumerate_3D_provider_attributes@12
_AIL_enumerate_3D_providers:                      jmp dword [_pMSS32_original_functions + 288]             ; _AIL_enumerate_3D_providers@12
_AIL_enumerate_3D_sample_attributes:              jmp dword [_pMSS32_original_functions + 292]             ; _AIL_enumerate_3D_sample_attributes@12
_AIL_enumerate_filter_attributes:                 jmp dword [_pMSS32_original_functions + 296]             ; _AIL_enumerate_filter_attributes@12
_AIL_enumerate_filter_sample_attributes:          jmp dword [_pMSS32_original_functions + 300]             ; _AIL_enumerate_filter_sample_attributes@12
_AIL_enumerate_filters:                           jmp dword [_pMSS32_original_functions + 304]             ; _AIL_enumerate_filters@12
_AIL_extract_DLS:                                 jmp dword [_pMSS32_original_functions + 308]             ; _AIL_extract_DLS@28
_AIL_file_error:                                  jmp dword [_pMSS32_original_functions + 312]             ; _AIL_file_error@0
_AIL_file_read:                                   jmp dword [_pMSS32_original_functions + 316]             ; _AIL_file_read@8
_AIL_file_size:                                   jmp dword [_pMSS32_original_functions + 320]             ; _AIL_file_size@4
_AIL_file_type:                                   jmp dword [_pMSS32_original_functions + 324]             ; _AIL_file_type@8
_AIL_file_write:                                  jmp dword [_pMSS32_original_functions + 328]             ; _AIL_file_write@12
_AIL_filter_attribute:                            jmp dword [_pMSS32_original_functions + 332]             ; _AIL_filter_attribute@12
_AIL_filter_DLS_attribute:                        jmp dword [_pMSS32_original_functions + 336]             ; _AIL_filter_DLS_attribute@12
_AIL_filter_DLS_with_XMI:                         jmp dword [_pMSS32_original_functions + 340]             ; _AIL_filter_DLS_with_XMI@24
_AIL_filter_sample_attribute:                     jmp dword [_pMSS32_original_functions + 344]             ; _AIL_filter_sample_attribute@12
_AIL_filter_stream_attribute:                     jmp dword [_pMSS32_original_functions + 348]             ; _AIL_filter_stream_attribute@12
_AIL_find_DLS:                                    jmp dword [_pMSS32_original_functions + 352]             ; _AIL_find_DLS@24
_AIL_get_DirectSound_info:                        jmp dword [_pMSS32_original_functions + 356]             ; _AIL_get_DirectSound_info@12
_AIL_get_input_info:                              jmp dword [_pMSS32_original_functions + 360]             ; _AIL_get_input_info@4
_AIL_get_preference:                              jmp dword [_pMSS32_original_functions + 364]             ; _AIL_get_preference@4
_AIL_get_timer_highest_delay:                     jmp dword [_pMSS32_original_functions + 368]             ; _AIL_get_timer_highest_delay@0
_AIL_HWND:                                        jmp dword [_pMSS32_original_functions + 372]             ; _AIL_HWND@0
_AIL_channel_notes:                               jmp dword [_pMSS32_original_functions + 376]             ; _AIL_channel_notes@8
_AIL_init_sample:                                 jmp dword [_pMSS32_original_functions + 380]             ; _AIL_init_sample@4
_AIL_init_sequence:                               jmp dword [_pMSS32_original_functions + 384]             ; _AIL_init_sequence@12
_AIL_last_error:                                  jmp dword [_pMSS32_original_functions + 388]             ; _AIL_last_error@0
_AIL_list_DLS:                                    jmp dword [_pMSS32_original_functions + 392]             ; _AIL_list_DLS@20
_AIL_list_MIDI:                                   jmp dword [_pMSS32_original_functions + 396]             ; _AIL_list_MIDI@20
_AIL_load_sample_buffer:                          jmp dword [_pMSS32_original_functions + 400]             ; _AIL_load_sample_buffer@16
_AIL_lock_channel:                                jmp dword [_pMSS32_original_functions + 404]             ; _AIL_lock_channel@4
_AIL_lock_mutex:                                  jmp dword [_pMSS32_original_functions + 408]             ; _AIL_lock_mutex@0
_AIL_lock:                                        jmp dword [_pMSS32_original_functions + 412]             ; _AIL_lock@0
_AIL_map_sequence_channel:                        jmp dword [_pMSS32_original_functions + 416]             ; _AIL_map_sequence_channel@12
_AIL_mem_alloc_lock:                              jmp dword [_pMSS32_original_functions + 420]             ; _AIL_mem_alloc_lock@4
_AIL_mem_free_lock:                               jmp dword [_pMSS32_original_functions + 424]             ; _AIL_mem_free_lock@4
_AIL_mem_use_free:                                jmp dword [_pMSS32_original_functions + 428]             ; _AIL_mem_use_free@4
_AIL_mem_use_malloc:                              jmp dword [_pMSS32_original_functions + 432]             ; _AIL_mem_use_malloc@4
_AIL_merge_DLS_with_XMI:                          jmp dword [_pMSS32_original_functions + 436]             ; _AIL_merge_DLS_with_XMI@16
_AIL_MIDI_handle_reacquire:                       jmp dword [_pMSS32_original_functions + 440]             ; _AIL_MIDI_handle_reacquire@4
_AIL_MIDI_handle_release:                         jmp dword [_pMSS32_original_functions + 444]             ; _AIL_MIDI_handle_release@4
_AIL_MIDI_to_XMI:                                 jmp dword [_pMSS32_original_functions + 448]             ; _AIL_MIDI_to_XMI@20
_AIL_midiOutClose:                                jmp dword [_pMSS32_original_functions + 452]             ; _AIL_midiOutClose@4
_AIL_midiOutOpen:                                 jmp dword [_pMSS32_original_functions + 456]             ; _AIL_midiOutOpen@12
_AIL_minimum_sample_buffer_size:                  jmp dword [_pMSS32_original_functions + 460]             ; _AIL_minimum_sample_buffer_size@12
_AIL_MMX_available:                               jmp dword [_pMSS32_original_functions + 464]             ; _AIL_MMX_available@0
_AIL_ms_count:                                    jmp dword [_pMSS32_original_functions + 468]             ; _AIL_ms_count@0
_AIL_open_3D_listener:                            jmp dword [_pMSS32_original_functions + 472]             ; _AIL_open_3D_listener@4
_AIL_open_3D_object:                              jmp dword [_pMSS32_original_functions + 476]             ; _AIL_open_3D_object@4
_AIL_open_3D_provider:                            jmp dword [_pMSS32_original_functions + 480]             ; _AIL_open_3D_provider@4
_AIL_open_digital_driver:                         jmp dword [_pMSS32_original_functions + 484]             ; _AIL_open_digital_driver@16
_AIL_open_filter:                                 jmp dword [_pMSS32_original_functions + 488]             ; _AIL_open_filter@8
_AIL_open_input:                                  jmp dword [_pMSS32_original_functions + 492]             ; _AIL_open_input@4
_AIL_open_stream:                                 jmp dword [_pMSS32_original_functions + 496]             ; _AIL_open_stream@12
_AIL_open_XMIDI_driver:                           jmp dword [_pMSS32_original_functions + 500]             ; _AIL_open_XMIDI_driver@4
_AIL_pause_stream:                                jmp dword [_pMSS32_original_functions + 504]             ; _AIL_pause_stream@8
_AIL_primary_digital_driver:                      jmp dword [_pMSS32_original_functions + 508]             ; _AIL_primary_digital_driver@4
_AIL_process_digital_audio:                       jmp dword [_pMSS32_original_functions + 512]             ; _AIL_process_digital_audio@24
_AIL_quick_copy:                                  jmp dword [_pMSS32_original_functions + 516]             ; _AIL_quick_copy@4
_AIL_quick_halt:                                  jmp dword [_pMSS32_original_functions + 520]             ; _AIL_quick_halt@4
_AIL_quick_handles:                               jmp dword [_pMSS32_original_functions + 524]             ; _AIL_quick_handles@12
_AIL_quick_load_and_play:                         jmp dword [_pMSS32_original_functions + 528]             ; _AIL_quick_load_and_play@12
_AIL_quick_load_mem:                              jmp dword [_pMSS32_original_functions + 532]             ; _AIL_quick_load_mem@8
_AIL_quick_load:                                  jmp dword [_pMSS32_original_functions + 536]             ; _AIL_quick_load@4
_AIL_quick_ms_length:                             jmp dword [_pMSS32_original_functions + 540]             ; _AIL_quick_ms_length@4
_AIL_quick_ms_position:                           jmp dword [_pMSS32_original_functions + 544]             ; _AIL_quick_ms_position@4
_AIL_quick_play:                                  jmp dword [_pMSS32_original_functions + 548]             ; _AIL_quick_play@8
_AIL_quick_set_low_pass_cut_off:                  jmp dword [_pMSS32_original_functions + 552]             ; _AIL_quick_set_low_pass_cut_off@8
_AIL_quick_set_ms_position:                       jmp dword [_pMSS32_original_functions + 556]             ; _AIL_quick_set_ms_position@8
_AIL_quick_set_reverb_levels:                     jmp dword [_pMSS32_original_functions + 560]             ; _AIL_quick_set_reverb_levels@12
_AIL_quick_set_speed:                             jmp dword [_pMSS32_original_functions + 564]             ; _AIL_quick_set_speed@8
_AIL_quick_set_volume:                            jmp dword [_pMSS32_original_functions + 568]             ; _AIL_quick_set_volume@12
_AIL_quick_shutdown:                              jmp dword [_pMSS32_original_functions + 572]             ; _AIL_quick_shutdown@0
_AIL_quick_startup:                               jmp dword [_pMSS32_original_functions + 576]             ; _AIL_quick_startup@20
_AIL_quick_status:                                jmp dword [_pMSS32_original_functions + 580]             ; _AIL_quick_status@4
_AIL_quick_type:                                  jmp dword [_pMSS32_original_functions + 584]             ; _AIL_quick_type@4
_AIL_quick_unload:                                jmp dword [_pMSS32_original_functions + 588]             ; _AIL_quick_unload@4
_AIL_redbook_close:                               jmp dword [_pMSS32_original_functions + 592]             ; _AIL_redbook_close@4
_AIL_redbook_eject:                               jmp dword [_pMSS32_original_functions + 596]             ; _AIL_redbook_eject@4
_AIL_redbook_id:                                  jmp dword [_pMSS32_original_functions + 600]             ; _AIL_redbook_id@4
_AIL_redbook_open_drive:                          jmp dword [_pMSS32_original_functions + 604]             ; _AIL_redbook_open_drive@4
_AIL_redbook_open:                                jmp dword [_pMSS32_original_functions + 608]             ; _AIL_redbook_open@4
_AIL_redbook_pause:                               jmp dword [_pMSS32_original_functions + 612]             ; _AIL_redbook_pause@4
_AIL_redbook_play:                                jmp dword [_pMSS32_original_functions + 616]             ; _AIL_redbook_play@12
_AIL_redbook_position:                            jmp dword [_pMSS32_original_functions + 620]             ; _AIL_redbook_position@4
_AIL_redbook_resume:                              jmp dword [_pMSS32_original_functions + 624]             ; _AIL_redbook_resume@4
_AIL_redbook_retract:                             jmp dword [_pMSS32_original_functions + 628]             ; _AIL_redbook_retract@4
_AIL_redbook_set_volume_level:                    jmp dword [_pMSS32_original_functions + 632]             ; _AIL_redbook_set_volume_level@8
_AIL_redbook_status:                              jmp dword [_pMSS32_original_functions + 636]             ; _AIL_redbook_status@4
_AIL_redbook_stop:                                jmp dword [_pMSS32_original_functions + 640]             ; _AIL_redbook_stop@4
_AIL_redbook_track_info:                          jmp dword [_pMSS32_original_functions + 644]             ; _AIL_redbook_track_info@16
_AIL_redbook_track:                               jmp dword [_pMSS32_original_functions + 648]             ; _AIL_redbook_track@4
_AIL_redbook_tracks:                              jmp dword [_pMSS32_original_functions + 652]             ; _AIL_redbook_tracks@4
_AIL_redbook_volume_level:                        jmp dword [_pMSS32_original_functions + 656]             ; _AIL_redbook_volume_level@4
_AIL_register_3D_EOS_callback:                    jmp dword [_pMSS32_original_functions + 660]             ; _AIL_register_3D_EOS_callback@8
_AIL_register_beat_callback:                      jmp dword [_pMSS32_original_functions + 664]             ; _AIL_register_beat_callback@8
_AIL_register_EOB_callback:                       jmp dword [_pMSS32_original_functions + 668]             ; _AIL_register_EOB_callback@8
_AIL_register_EOF_callback:                       jmp dword [_pMSS32_original_functions + 672]             ; _AIL_register_EOF_callback@8
_AIL_register_EOS_callback:                       jmp dword [_pMSS32_original_functions + 676]             ; _AIL_register_EOS_callback@8
_AIL_register_event_callback:                     jmp dword [_pMSS32_original_functions + 680]             ; _AIL_register_event_callback@8
_AIL_register_ICA_array:                          jmp dword [_pMSS32_original_functions + 684]             ; _AIL_register_ICA_array@8
_AIL_register_prefix_callback:                    jmp dword [_pMSS32_original_functions + 688]             ; _AIL_register_prefix_callback@8
_AIL_register_sequence_callback:                  jmp dword [_pMSS32_original_functions + 692]             ; _AIL_register_sequence_callback@8
_AIL_register_SOB_callback:                       jmp dword [_pMSS32_original_functions + 696]             ; _AIL_register_SOB_callback@8
_AIL_register_stream_callback:                    jmp dword [_pMSS32_original_functions + 700]             ; _AIL_register_stream_callback@8
_AIL_register_timbre_callback:                    jmp dword [_pMSS32_original_functions + 704]             ; _AIL_register_timbre_callback@8
_AIL_register_timer:                              jmp dword [_pMSS32_original_functions + 708]             ; _AIL_register_timer@4
_AIL_register_trigger_callback:                   jmp dword [_pMSS32_original_functions + 712]             ; _AIL_register_trigger_callback@8
_AIL_release_3D_sample_handle:                    jmp dword [_pMSS32_original_functions + 716]             ; _AIL_release_3D_sample_handle@4
_AIL_release_all_timers:                          jmp dword [_pMSS32_original_functions + 720]             ; _AIL_release_all_timers@0
_AIL_release_channel:                             jmp dword [_pMSS32_original_functions + 724]             ; _AIL_release_channel@8
_AIL_release_sample_handle:                       jmp dword [_pMSS32_original_functions + 728]             ; _AIL_release_sample_handle@4
_AIL_release_sequence_handle:                     jmp dword [_pMSS32_original_functions + 732]             ; _AIL_release_sequence_handle@4
_AIL_release_timer_handle:                        jmp dword [_pMSS32_original_functions + 736]             ; _AIL_release_timer_handle@4
_AIL_request_EOB_ASI_reset:                       jmp dword [_pMSS32_original_functions + 740]             ; _AIL_request_EOB_ASI_reset@8
_AIL_resume_3D_sample:                            jmp dword [_pMSS32_original_functions + 744]             ; _AIL_resume_3D_sample@4
_AIL_resume_sample:                               jmp dword [_pMSS32_original_functions + 748]             ; _AIL_resume_sample@4
_AIL_resume_sequence:                             jmp dword [_pMSS32_original_functions + 752]             ; _AIL_resume_sequence@4
_AIL_sample_buffer_info:                          jmp dword [_pMSS32_original_functions + 756]             ; _AIL_sample_buffer_info@20
_AIL_sample_buffer_ready:                         jmp dword [_pMSS32_original_functions + 760]             ; _AIL_sample_buffer_ready@4
_AIL_sample_granularity:                          jmp dword [_pMSS32_original_functions + 764]             ; _AIL_sample_granularity@4
_AIL_sample_loop_count:                           jmp dword [_pMSS32_original_functions + 768]             ; _AIL_sample_loop_count@4
_AIL_sample_low_pass_cut_off:                     jmp dword [_pMSS32_original_functions + 772]             ; _AIL_sample_low_pass_cut_off@4
_AIL_sample_ms_position:                          jmp dword [_pMSS32_original_functions + 776]             ; _AIL_sample_ms_position@12
_AIL_sample_playback_rate:                        jmp dword [_pMSS32_original_functions + 780]             ; _AIL_sample_playback_rate@4
_AIL_sample_position:                             jmp dword [_pMSS32_original_functions + 784]             ; _AIL_sample_position@4
_AIL_sample_reverb_levels:                        jmp dword [_pMSS32_original_functions + 788]             ; _AIL_sample_reverb_levels@12
_AIL_sample_status:                               jmp dword [_pMSS32_original_functions + 792]             ; _AIL_sample_status@4
_AIL_sample_user_data:                            jmp dword [_pMSS32_original_functions + 796]             ; _AIL_sample_user_data@8
_AIL_sample_volume_levels:                        jmp dword [_pMSS32_original_functions + 800]             ; _AIL_sample_volume_levels@12
_AIL_sample_volume_pan:                           jmp dword [_pMSS32_original_functions + 804]             ; _AIL_sample_volume_pan@12
_AIL_send_channel_voice_message:                  jmp dword [_pMSS32_original_functions + 808]             ; _AIL_send_channel_voice_message@20
_AIL_send_sysex_message:                          jmp dword [_pMSS32_original_functions + 812]             ; _AIL_send_sysex_message@8
_AIL_sequence_loop_count:                         jmp dword [_pMSS32_original_functions + 816]             ; _AIL_sequence_loop_count@4
_AIL_sequence_ms_position:                        jmp dword [_pMSS32_original_functions + 820]             ; _AIL_sequence_ms_position@12
_AIL_sequence_position:                           jmp dword [_pMSS32_original_functions + 824]             ; _AIL_sequence_position@12
_AIL_sequence_status:                             jmp dword [_pMSS32_original_functions + 828]             ; _AIL_sequence_status@4
_AIL_sequence_tempo:                              jmp dword [_pMSS32_original_functions + 832]             ; _AIL_sequence_tempo@4
_AIL_sequence_user_data:                          jmp dword [_pMSS32_original_functions + 836]             ; _AIL_sequence_user_data@8
_AIL_sequence_volume:                             jmp dword [_pMSS32_original_functions + 840]             ; _AIL_sequence_volume@4
_AIL_serve:                                       jmp dword [_pMSS32_original_functions + 844]             ; _AIL_serve@0
_AIL_service_stream:                              jmp dword [_pMSS32_original_functions + 848]             ; _AIL_service_stream@8
_AIL_set_3D_distance_factor:                      jmp dword [_pMSS32_original_functions + 852]             ; _AIL_set_3D_distance_factor@8
_AIL_set_3D_doppler_factor:                       jmp dword [_pMSS32_original_functions + 856]             ; _AIL_set_3D_doppler_factor@8
_AIL_set_3D_orientation:                          jmp dword [_pMSS32_original_functions + 860]             ; _AIL_set_3D_orientation@28
_AIL_set_3D_position:                             jmp dword [_pMSS32_original_functions + 864]             ; _AIL_set_3D_position@16
_AIL_set_3D_provider_preference:                  jmp dword [_pMSS32_original_functions + 868]             ; _AIL_set_3D_provider_preference@12
_AIL_set_3D_rolloff_factor:                       jmp dword [_pMSS32_original_functions + 872]             ; _AIL_set_3D_rolloff_factor@8
_AIL_set_3D_room_type:                            jmp dword [_pMSS32_original_functions + 876]             ; _AIL_set_3D_room_type@8
_AIL_set_3D_sample_cone:                          jmp dword [_pMSS32_original_functions + 880]             ; _AIL_set_3D_sample_cone@16
_AIL_set_3D_sample_distances:                     jmp dword [_pMSS32_original_functions + 884]             ; _AIL_set_3D_sample_distances@12
_AIL_set_3D_sample_effects_level:                 jmp dword [_pMSS32_original_functions + 888]             ; _AIL_set_3D_sample_effects_level@8
_AIL_set_3D_sample_exclusion:                     jmp dword [_pMSS32_original_functions + 892]             ; _AIL_set_3D_sample_exclusion@8
_AIL_set_3D_sample_file:                          jmp dword [_pMSS32_original_functions + 896]             ; _AIL_set_3D_sample_file@8
_AIL_set_3D_sample_info:                          jmp dword [_pMSS32_original_functions + 900]             ; _AIL_set_3D_sample_info@8
_AIL_set_3D_sample_loop_block:                    jmp dword [_pMSS32_original_functions + 904]             ; _AIL_set_3D_sample_loop_block@12
_AIL_set_3D_sample_loop_count:                    jmp dword [_pMSS32_original_functions + 908]             ; _AIL_set_3D_sample_loop_count@8
_AIL_set_3D_sample_obstruction:                   jmp dword [_pMSS32_original_functions + 912]             ; _AIL_set_3D_sample_obstruction@8
_AIL_set_3D_sample_occlusion:                     jmp dword [_pMSS32_original_functions + 916]             ; _AIL_set_3D_sample_occlusion@8
_AIL_set_3D_sample_offset:                        jmp dword [_pMSS32_original_functions + 920]             ; _AIL_set_3D_sample_offset@8
_AIL_set_3D_sample_playback_rate:                 jmp dword [_pMSS32_original_functions + 924]             ; _AIL_set_3D_sample_playback_rate@8
_AIL_set_3D_sample_preference:                    jmp dword [_pMSS32_original_functions + 928]             ; _AIL_set_3D_sample_preference@12
_AIL_set_3D_sample_volume:                        jmp dword [_pMSS32_original_functions + 932]             ; _AIL_set_3D_sample_volume@8
_AIL_set_3D_speaker_type:                         jmp dword [_pMSS32_original_functions + 936]             ; _AIL_set_3D_speaker_type@8
_AIL_set_3D_user_data:                            jmp dword [_pMSS32_original_functions + 940]             ; _AIL_set_3D_user_data@12
_AIL_set_3D_velocity_vector:                      jmp dword [_pMSS32_original_functions + 944]             ; _AIL_set_3D_velocity_vector@16
_AIL_set_3D_velocity:                             jmp dword [_pMSS32_original_functions + 948]             ; _AIL_set_3D_velocity@20
_AIL_set_digital_driver_processor:                jmp dword [_pMSS32_original_functions + 952]             ; _AIL_set_digital_driver_processor@12
_AIL_set_digital_master_reverb_levels:            jmp dword [_pMSS32_original_functions + 956]             ; _AIL_set_digital_master_reverb_levels@12
_AIL_set_digital_master_reverb:                   jmp dword [_pMSS32_original_functions + 960]             ; _AIL_set_digital_master_reverb@16
_AIL_set_digital_master_room_type:                jmp dword [_pMSS32_original_functions + 964]             ; _AIL_set_digital_master_room_type@8
_AIL_set_digital_master_volume_level:             jmp dword [_pMSS32_original_functions + 968]             ; _AIL_set_digital_master_volume_level@8
_AIL_set_DirectSound_HWND:                        jmp dword [_pMSS32_original_functions + 972]             ; _AIL_set_DirectSound_HWND@8
_AIL_set_DLS_processor:                           jmp dword [_pMSS32_original_functions + 976]             ; _AIL_set_DLS_processor@12
_AIL_set_error:                                   jmp dword [_pMSS32_original_functions + 980]             ; _AIL_set_error@4
_AIL_set_file_async_callbacks:                    jmp dword [_pMSS32_original_functions + 984]             ; _AIL_set_file_async_callbacks@20
_AIL_set_file_callbacks:                          jmp dword [_pMSS32_original_functions + 988]             ; _AIL_set_file_callbacks@16
_AIL_set_filter_DLS_preference:                   jmp dword [_pMSS32_original_functions + 992]             ; _AIL_set_filter_DLS_preference@12
_AIL_set_filter_preference:                       jmp dword [_pMSS32_original_functions + 996]             ; _AIL_set_filter_preference@12
_AIL_set_filter_sample_preference:                jmp dword [_pMSS32_original_functions + 1000]            ; _AIL_set_filter_sample_preference@12
_AIL_set_filter_stream_preference:                jmp dword [_pMSS32_original_functions + 1004]            ; _AIL_set_filter_stream_preference@12
_AIL_set_input_state:                             jmp dword [_pMSS32_original_functions + 1008]            ; _AIL_set_input_state@8
_AIL_set_named_sample_file:                       jmp dword [_pMSS32_original_functions + 1012]            ; _AIL_set_named_sample_file@20
_AIL_set_preference:                              jmp dword [_pMSS32_original_functions + 1016]            ; _AIL_set_preference@8
_AIL_set_redist_directory:                        jmp dword [_pMSS32_original_functions + 1020]            ; _AIL_set_redist_directory@4
_AIL_set_sample_address:                          jmp dword [_pMSS32_original_functions + 1024]            ; _AIL_set_sample_address@12
_AIL_set_sample_adpcm_block_size:                 jmp dword [_pMSS32_original_functions + 1028]            ; _AIL_set_sample_adpcm_block_size@8
_AIL_set_sample_file:                             jmp dword [_pMSS32_original_functions + 1032]            ; _AIL_set_sample_file@12
_AIL_set_sample_loop_block:                       jmp dword [_pMSS32_original_functions + 1036]            ; _AIL_set_sample_loop_block@12
_AIL_set_sample_loop_count:                       jmp dword [_pMSS32_original_functions + 1040]            ; _AIL_set_sample_loop_count@8
_AIL_set_sample_low_pass_cut_off:                 jmp dword [_pMSS32_original_functions + 1044]            ; _AIL_set_sample_low_pass_cut_off@8
_AIL_set_sample_ms_position:                      jmp dword [_pMSS32_original_functions + 1048]            ; _AIL_set_sample_ms_position@8
_AIL_set_sample_playback_rate:                    jmp dword [_pMSS32_original_functions + 1052]            ; _AIL_set_sample_playback_rate@8
_AIL_set_sample_position:                         jmp dword [_pMSS32_original_functions + 1056]            ; _AIL_set_sample_position@8
_AIL_set_sample_processor:                        jmp dword [_pMSS32_original_functions + 1060]            ; _AIL_set_sample_processor@12
_AIL_set_sample_reverb_levels:                    jmp dword [_pMSS32_original_functions + 1064]            ; _AIL_set_sample_reverb_levels@12
_AIL_set_sample_type:                             jmp dword [_pMSS32_original_functions + 1068]            ; _AIL_set_sample_type@12
_AIL_set_sample_user_data:                        jmp dword [_pMSS32_original_functions + 1072]            ; _AIL_set_sample_user_data@12
_AIL_set_sample_volume_levels:                    jmp dword [_pMSS32_original_functions + 1076]            ; _AIL_set_sample_volume_levels@12
_AIL_set_sample_volume_pan:                       jmp dword [_pMSS32_original_functions + 1080]            ; _AIL_set_sample_volume_pan@12
_AIL_set_sequence_loop_count:                     jmp dword [_pMSS32_original_functions + 1084]            ; _AIL_set_sequence_loop_count@8
_AIL_set_sequence_ms_position:                    jmp dword [_pMSS32_original_functions + 1088]            ; _AIL_set_sequence_ms_position@8
_AIL_set_sequence_tempo:                          jmp dword [_pMSS32_original_functions + 1092]            ; _AIL_set_sequence_tempo@12
_AIL_set_sequence_user_data:                      jmp dword [_pMSS32_original_functions + 1096]            ; _AIL_set_sequence_user_data@12
_AIL_set_sequence_volume:                         jmp dword [_pMSS32_original_functions + 1100]            ; _AIL_set_sequence_volume@12
_AIL_set_stream_loop_block:                       jmp dword [_pMSS32_original_functions + 1104]            ; _AIL_set_stream_loop_block@12
_AIL_set_stream_loop_count:                       jmp dword [_pMSS32_original_functions + 1108]            ; _AIL_set_stream_loop_count@8
_AIL_set_stream_low_pass_cut_off:                 jmp dword [_pMSS32_original_functions + 1112]            ; _AIL_set_stream_low_pass_cut_off@8
_AIL_set_stream_ms_position:                      jmp dword [_pMSS32_original_functions + 1116]            ; _AIL_set_stream_ms_position@8
_AIL_set_stream_playback_rate:                    jmp dword [_pMSS32_original_functions + 1120]            ; _AIL_set_stream_playback_rate@8
_AIL_set_stream_position:                         jmp dword [_pMSS32_original_functions + 1124]            ; _AIL_set_stream_position@8
_AIL_set_stream_processor:                        jmp dword [_pMSS32_original_functions + 1128]            ; _AIL_set_stream_processor@12
_AIL_set_stream_reverb_levels:                    jmp dword [_pMSS32_original_functions + 1132]            ; _AIL_set_stream_reverb_levels@12
_AIL_set_stream_user_data:                        jmp dword [_pMSS32_original_functions + 1136]            ; _AIL_set_stream_user_data@12
_AIL_set_stream_volume_levels:                    jmp dword [_pMSS32_original_functions + 1140]            ; _AIL_set_stream_volume_levels@12
_AIL_set_stream_volume_pan:                       jmp dword [_pMSS32_original_functions + 1144]            ; _AIL_set_stream_volume_pan@12
_AIL_set_timer_divisor:                           jmp dword [_pMSS32_original_functions + 1148]            ; _AIL_set_timer_divisor@8
_AIL_set_timer_frequency:                         jmp dword [_pMSS32_original_functions + 1152]            ; _AIL_set_timer_frequency@8
_AIL_set_timer_period:                            jmp dword [_pMSS32_original_functions + 1156]            ; _AIL_set_timer_period@8
_AIL_set_timer_user:                              jmp dword [_pMSS32_original_functions + 1160]            ; _AIL_set_timer_user@8
_AIL_set_XMIDI_master_volume:                     jmp dword [_pMSS32_original_functions + 1164]            ; _AIL_set_XMIDI_master_volume@8
_AIL_shutdown:                                    jmp dword [_pMSS32_original_functions + 1168]            ; _AIL_shutdown@0
_AIL_size_processed_digital_audio:                jmp dword [_pMSS32_original_functions + 1172]            ; _AIL_size_processed_digital_audio@16
_AIL_start_3D_sample:                             jmp dword [_pMSS32_original_functions + 1176]            ; _AIL_start_3D_sample@4
_AIL_start_all_timers:                            jmp dword [_pMSS32_original_functions + 1180]            ; _AIL_start_all_timers@0
_AIL_start_sample:                                jmp dword [_pMSS32_original_functions + 1184]            ; _AIL_start_sample@4
_AIL_start_sequence:                              jmp dword [_pMSS32_original_functions + 1188]            ; _AIL_start_sequence@4
_AIL_start_stream:                                jmp dword [_pMSS32_original_functions + 1192]            ; _AIL_start_stream@4
_AIL_start_timer:                                 jmp dword [_pMSS32_original_functions + 1196]            ; _AIL_start_timer@4
_AIL_startup:                                     jmp dword [_pMSS32_original_functions + 1200]            ; _AIL_startup@0
_AIL_stop_3D_sample:                              jmp dword [_pMSS32_original_functions + 1204]            ; _AIL_stop_3D_sample@4
_AIL_stop_all_timers:                             jmp dword [_pMSS32_original_functions + 1208]            ; _AIL_stop_all_timers@0
_AIL_stop_sample:                                 jmp dword [_pMSS32_original_functions + 1212]            ; _AIL_stop_sample@4
_AIL_stop_sequence:                               jmp dword [_pMSS32_original_functions + 1216]            ; _AIL_stop_sequence@4
_AIL_stop_timer:                                  jmp dword [_pMSS32_original_functions + 1220]            ; _AIL_stop_timer@4
_AIL_stream_info:                                 jmp dword [_pMSS32_original_functions + 1224]            ; _AIL_stream_info@20
_AIL_stream_loop_count:                           jmp dword [_pMSS32_original_functions + 1228]            ; _AIL_stream_loop_count@4
_AIL_stream_low_pass_cut_off:                     jmp dword [_pMSS32_original_functions + 1232]            ; _AIL_stream_low_pass_cut_off@4
_AIL_stream_ms_position:                          jmp dword [_pMSS32_original_functions + 1236]            ; _AIL_stream_ms_position@12
_AIL_stream_playback_rate:                        jmp dword [_pMSS32_original_functions + 1240]            ; _AIL_stream_playback_rate@4
_AIL_stream_position:                             jmp dword [_pMSS32_original_functions + 1244]            ; _AIL_stream_position@4
_AIL_stream_reverb_levels:                        jmp dword [_pMSS32_original_functions + 1248]            ; _AIL_stream_reverb_levels@12
_AIL_stream_status:                               jmp dword [_pMSS32_original_functions + 1252]            ; _AIL_stream_status@4
_AIL_stream_user_data:                            jmp dword [_pMSS32_original_functions + 1256]            ; _AIL_stream_user_data@8
_AIL_stream_volume_levels:                        jmp dword [_pMSS32_original_functions + 1260]            ; _AIL_stream_volume_levels@12
_AIL_stream_volume_pan:                           jmp dword [_pMSS32_original_functions + 1264]            ; _AIL_stream_volume_pan@12
_AIL_true_sequence_channel:                       jmp dword [_pMSS32_original_functions + 1268]            ; _AIL_true_sequence_channel@8
_AIL_unlock_mutex:                                jmp dword [_pMSS32_original_functions + 1272]            ; _AIL_unlock_mutex@0
_AIL_unlock:                                      jmp dword [_pMSS32_original_functions + 1276]            ; _AIL_unlock@0
_AIL_update_3D_position:                          jmp dword [_pMSS32_original_functions + 1280]            ; _AIL_update_3D_position@8
_AIL_us_count:                                    jmp dword [_pMSS32_original_functions + 1284]            ; _AIL_us_count@0
_AIL_WAV_file_write:                              jmp dword [_pMSS32_original_functions + 1288]            ; _AIL_WAV_file_write@20
_AIL_WAV_info:                                    jmp dword [_pMSS32_original_functions + 1292]            ; _AIL_WAV_info@8
_AIL_waveOutClose:                                jmp dword [_pMSS32_original_functions + 1296]            ; _AIL_waveOutClose@4
_AIL_waveOutOpen:                                 jmp dword [_pMSS32_original_functions + 1300]            ; _AIL_waveOutOpen@16
_AIL_XMIDI_master_volume:                         jmp dword [_pMSS32_original_functions + 1304]            ; _AIL_XMIDI_master_volume@4
_DllMain:                                         jmp dword [_pMSS32_original_functions + 1308]            ; _DllMain@12
_DLSMSSGetCPU:                                    jmp dword [_pMSS32_original_functions + 1312]            ; _DLSMSSGetCPU@4
_MIX_RIB_MAIN:                                    jmp dword [_pMSS32_original_functions + 1316]            ; _MIX_RIB_MAIN@8
_RIB_enumerate_providers:                         jmp dword [_pMSS32_original_functions + 1320]            ; _RIB_enumerate_providers@12
_RIB_find_file_dec_provider:                      jmp dword [_pMSS32_original_functions + 1324]            ; _RIB_find_file_dec_provider@20
_RIB_find_files_provider:                         jmp dword [_pMSS32_original_functions + 1328]            ; _RIB_find_files_provider@20
_RIB_find_provider:                               jmp dword [_pMSS32_original_functions + 1332]            ; _RIB_find_provider@12
_RIB_load_application_providers:                  jmp dword [_pMSS32_original_functions + 1336]            ; _RIB_load_application_providers@4
_RIB_load_static_provider_library:                jmp dword [_pMSS32_original_functions + 1340]            ; _RIB_load_static_provider_library@8
_RIB_provider_system_data:                        jmp dword [_pMSS32_original_functions + 1344]            ; _RIB_provider_system_data@8
_RIB_provider_user_data:                          jmp dword [_pMSS32_original_functions + 1348]            ; _RIB_provider_user_data@8
_RIB_set_provider_system_data:                    jmp dword [_pMSS32_original_functions + 1352]            ; _RIB_set_provider_system_data@12
_RIB_set_provider_user_data:                      jmp dword [_pMSS32_original_functions + 1356]            ; _RIB_set_provider_user_data@12
_AIL_debug_printf:                                jmp dword [_pMSS32_original_functions + 1360]            ; AIL_debug_printf
_AIL_sprintf:                                     jmp dword [_pMSS32_original_functions + 1364]            ; AIL_sprintf
_DLSClose:                                        jmp dword [_pMSS32_original_functions + 1368]            ; DLSClose
_DLSCompactMemory:                                jmp dword [_pMSS32_original_functions + 1372]            ; DLSCompactMemory
_DLSGetInfo:                                      jmp dword [_pMSS32_original_functions + 1376]            ; DLSGetInfo
_DLSLoadFile:                                     jmp dword [_pMSS32_original_functions + 1380]            ; DLSLoadFile
_DLSLoadMemFile:                                  jmp dword [_pMSS32_original_functions + 1384]            ; DLSLoadMemFile
_DLSMSSOpen:                                      jmp dword [_pMSS32_original_functions + 1388]            ; DLSMSSOpen
_DLSSetAttribute:                                 jmp dword [_pMSS32_original_functions + 1392]            ; DLSSetAttribute
_DLSUnloadAll:                                    jmp dword [_pMSS32_original_functions + 1396]            ; DLSUnloadAll
_DLSUnloadFile:                                   jmp dword [_pMSS32_original_functions + 1400]            ; DLSUnloadFile
_RIB_alloc_provider_handle:                       jmp dword [_pMSS32_original_functions + 1404]            ; RIB_alloc_provider_handle
_RIB_enumerate_interface:                         jmp dword [_pMSS32_original_functions + 1408]            ; RIB_enumerate_interface
_RIB_error:                                       jmp dword [_pMSS32_original_functions + 1412]            ; RIB_error
_RIB_find_file_provider:                          jmp dword [_pMSS32_original_functions + 1416]            ; RIB_find_file_provider
_RIB_free_provider_handle:                        jmp dword [_pMSS32_original_functions + 1420]            ; RIB_free_provider_handle
_RIB_free_provider_library:                       jmp dword [_pMSS32_original_functions + 1424]            ; RIB_free_provider_library
_RIB_load_provider_library:                       jmp dword [_pMSS32_original_functions + 1428]            ; RIB_load_provider_library
_RIB_register_interface:                          jmp dword [_pMSS32_original_functions + 1432]            ; RIB_register_interface
_RIB_request_interface:                           jmp dword [_pMSS32_original_functions + 1436]            ; RIB_request_interface
_RIB_request_interface_entry:                     jmp dword [_pMSS32_original_functions + 1440]            ; RIB_request_interface_entry
_RIB_type_string:                                 jmp dword [_pMSS32_original_functions + 1444]            ; RIB_type_string
_RIB_unregister_interface:                        jmp dword [_pMSS32_original_functions + 1448]            ; RIB_unregister_interface
_stream_background:                               jmp dword [_pMSS32_original_functions + 1452]            ; stream_background
