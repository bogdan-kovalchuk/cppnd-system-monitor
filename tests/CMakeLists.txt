cmake_minimum_required(VERSION 3.16)
project(system_monitor_focused_tests LANGUAGES CXX)

enable_testing()

add_executable(linux_parser_test
  linux_parser_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(linux_parser_test PRIVATE ../include)
target_compile_features(linux_parser_test PRIVATE cxx_std_17)
target_compile_options(linux_parser_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME linux_parser_test COMMAND linux_parser_test)

add_executable(string_parser_test
  string_parser_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(string_parser_test PRIVATE ../include)
target_compile_features(string_parser_test PRIVATE cxx_std_17)
target_compile_options(string_parser_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME string_parser_test COMMAND string_parser_test)

add_executable(boundary_test
  boundary_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(boundary_test PRIVATE ../include)
target_compile_features(boundary_test PRIVATE cxx_std_17)
target_compile_options(boundary_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME boundary_test COMMAND boundary_test)

add_executable(format_test
  format_test.cpp
  ../src/format.cpp
)
target_include_directories(format_test PRIVATE ../include)
target_compile_features(format_test PRIVATE cxx_std_17)
target_compile_options(format_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME format_test COMMAND format_test)

add_executable(format_compare_test
  format_compare_test.cpp
  ../src/format.cpp
)
target_include_directories(format_compare_test PRIVATE ../include)
target_compile_features(format_compare_test PRIVATE cxx_std_17)
target_compile_options(format_compare_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME format_compare_test COMMAND format_compare_test)

add_executable(format_edge_test
  format_edge_test.cpp
  ../src/format.cpp
)
target_include_directories(format_edge_test PRIVATE ../include)
target_compile_features(format_edge_test PRIVATE cxx_std_17)
target_compile_options(format_edge_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME format_edge_test COMMAND format_edge_test)

add_executable(parse_long_test
  parse_long_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_long_test PRIVATE ../include)
target_compile_features(parse_long_test PRIVATE cxx_std_17)
target_compile_options(parse_long_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_long_test COMMAND parse_long_test)

add_executable(process_order_test
  process_order_test.cpp
  ../src/linux_parser.cpp
  ../src/process.cpp
)
target_include_directories(process_order_test PRIVATE ../include)
target_compile_features(process_order_test PRIVATE cxx_std_17)
target_compile_options(process_order_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME process_order_test COMMAND process_order_test)

add_executable(user_lookup_test
  user_lookup_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(user_lookup_test PRIVATE ../include)
target_compile_features(user_lookup_test PRIVATE cxx_std_17)
target_compile_options(user_lookup_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME user_lookup_test COMMAND user_lookup_test)

add_executable(format_div_test
  format_div_test.cpp
  ../src/format.cpp
)
target_include_directories(format_div_test PRIVATE ../include)
target_compile_features(format_div_test PRIVATE cxx_std_17)
target_compile_options(format_div_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME format_div_test COMMAND format_div_test)

add_executable(parse_cmdline_test
  parse_cmdline_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_cmdline_test PRIVATE ../include)
target_compile_features(parse_cmdline_test PRIVATE cxx_std_17)
target_compile_options(parse_cmdline_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_cmdline_test COMMAND parse_cmdline_test)

add_executable(parse_meminfo_test
  parse_meminfo_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_meminfo_test PRIVATE ../include)
target_compile_features(parse_meminfo_test PRIVATE cxx_std_17)
target_compile_options(parse_meminfo_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_meminfo_test COMMAND parse_meminfo_test)

add_executable(process_rank_test
  process_rank_test.cpp
  ../src/linux_parser.cpp
  ../src/process.cpp
)
target_include_directories(process_rank_test PRIVATE ../include)
target_compile_features(process_rank_test PRIVATE cxx_std_17)
target_compile_options(process_rank_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME process_rank_test COMMAND process_rank_test)

add_executable(parse_pid_test
  parse_pid_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_pid_test PRIVATE ../include)
target_compile_features(parse_pid_test PRIVATE cxx_std_17)
target_compile_options(parse_pid_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_pid_test COMMAND parse_pid_test)

add_executable(parse_status_test
  parse_status_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_status_test PRIVATE ../include)
target_compile_features(parse_status_test PRIVATE cxx_std_17)
target_compile_options(parse_status_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_status_test COMMAND parse_status_test)

add_executable(parse_ram_test
  parse_ram_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_ram_test PRIVATE ../include)
target_compile_features(parse_ram_test PRIVATE cxx_std_17)
target_compile_options(parse_ram_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_ram_test COMMAND parse_ram_test)

add_executable(compute_cpu_test
  compute_cpu_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(compute_cpu_test PRIVATE ../include)
target_compile_features(compute_cpu_test PRIVATE cxx_std_17)
target_compile_options(compute_cpu_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME compute_cpu_test COMMAND compute_cpu_test)

add_executable(parse_meminfo_prefix_test
  parse_meminfo_prefix_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_meminfo_prefix_test PRIVATE ../include)
target_compile_features(parse_meminfo_prefix_test PRIVATE cxx_std_17)
target_compile_options(parse_meminfo_prefix_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_meminfo_prefix_test COMMAND parse_meminfo_prefix_test)

add_executable(parse_long_strict_test
  parse_long_strict_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_long_strict_test PRIVATE ../include)
target_compile_features(parse_long_strict_test PRIVATE cxx_std_17)
target_compile_options(parse_long_strict_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_long_strict_test COMMAND parse_long_strict_test)

add_executable(parse_ram_negative_test
  parse_ram_negative_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_ram_negative_test PRIVATE ../include)
target_compile_features(parse_ram_negative_test PRIVATE cxx_std_17)
target_compile_options(parse_ram_negative_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_ram_negative_test COMMAND parse_ram_negative_test)

add_executable(compute_processor_test
  compute_processor_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(compute_processor_test PRIVATE ../include)
target_compile_features(compute_processor_test PRIVATE cxx_std_17)
target_compile_options(compute_processor_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME compute_processor_test COMMAND compute_processor_test)

add_executable(cpu_field_extract_test
  cpu_field_extract_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(cpu_field_extract_test PRIVATE ../include)
target_compile_features(cpu_field_extract_test PRIVATE cxx_std_17)
target_compile_options(cpu_field_extract_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME cpu_field_extract_test COMMAND cpu_field_extract_test)

add_executable(parse_uid_test
  parse_uid_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_uid_test PRIVATE ../include)
target_compile_features(parse_uid_test PRIVATE cxx_std_17)
target_compile_options(parse_uid_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_uid_test COMMAND parse_uid_test)

add_executable(parse_kernel_test
  parse_kernel_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_kernel_test PRIVATE ../include)
target_compile_features(parse_kernel_test PRIVATE cxx_std_17)
target_compile_options(parse_kernel_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_kernel_test COMMAND parse_kernel_test)

add_executable(parse_os_test
  parse_os_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_os_test PRIVATE ../include)
target_compile_features(parse_os_test PRIVATE cxx_std_17)
target_compile_options(parse_os_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_os_test COMMAND parse_os_test)

add_executable(parse_memutil_test
  parse_memutil_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_memutil_test PRIVATE ../include)
target_compile_features(parse_memutil_test PRIVATE cxx_std_17)
target_compile_options(parse_memutil_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_memutil_test COMMAND parse_memutil_test)

add_executable(parse_user_test
  parse_user_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_user_test PRIVATE ../include)
target_compile_features(parse_user_test PRIVATE cxx_std_17)
target_compile_options(parse_user_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_user_test COMMAND parse_user_test)

add_executable(parse_uptime_test
  parse_uptime_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_uptime_test PRIVATE ../include)
target_compile_features(parse_uptime_test PRIVATE cxx_std_17)
target_compile_options(parse_uptime_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_uptime_test COMMAND parse_uptime_test)

add_executable(parse_stat_processes_test
  parse_stat_processes_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_stat_processes_test PRIVATE ../include)
target_compile_features(parse_stat_processes_test PRIVATE cxx_std_17)
target_compile_options(parse_stat_processes_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_stat_processes_test COMMAND parse_stat_processes_test)

add_executable(parse_cmdline_integration_test
  parse_cmdline_integration_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_cmdline_integration_test PRIVATE ../include)
target_compile_features(parse_cmdline_integration_test PRIVATE cxx_std_17)
target_compile_options(parse_cmdline_integration_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_cmdline_integration_test COMMAND parse_cmdline_integration_test)

add_executable(pids_sort_test
  pids_sort_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(pids_sort_test PRIVATE ../include)
target_compile_features(pids_sort_test PRIVATE cxx_std_17)
target_compile_options(pids_sort_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME pids_sort_test COMMAND pids_sort_test)

add_executable(process_compare_test
  process_compare_test.cpp
  ../src/linux_parser.cpp
  ../src/process.cpp
)
target_include_directories(process_compare_test PRIVATE ../include)
target_compile_features(process_compare_test PRIVATE cxx_std_17)
target_compile_options(process_compare_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME process_compare_test COMMAND process_compare_test)

add_executable(ram_integration_test
  ram_integration_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(ram_integration_test PRIVATE ../include)
target_compile_features(ram_integration_test PRIVATE cxx_std_17)
target_compile_options(ram_integration_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME ram_integration_test COMMAND ram_integration_test)

add_executable(parse_directory_pid_test
  parse_directory_pid_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(parse_directory_pid_test PRIVATE ../include)
target_compile_features(parse_directory_pid_test PRIVATE cxx_std_17)
target_compile_options(parse_directory_pid_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME parse_directory_pid_test COMMAND parse_directory_pid_test)

