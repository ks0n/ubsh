project('ubsh', 'c',
  default_options: [
    'warning_level=3',
    'debug=true',
    'b_sanitize=address',
    'c_std=c99',
    'b_coverage=true',
    ])

add_project_arguments('-D_POSIX_C_SOURCE=200809L', language: 'c')

inc = include_directories(['include'])

src = [
  'src/prompt.c',
  'src/token_recognition.c',
  'src/charstream.c',
  'src/wordvec.c',
  'src/token.c',
  'src/lexer.c',
  'src/queue.c',
  ]

main = [
  'src/main.c',
  ]

readline = dependency('readline')
executable('ubsh', src, main, dependencies: [readline], include_directories: inc)

unit_tests_src = [
  'tests/charstream.c',
  'tests/wordvec.c',
  'tests/lexer.c',
  'tests/queue.c',
  ]

if get_option('enable_tests')
  criterion = dependency('criterion', required: false)
  unit_tests = executable('unit_tests', src, unit_tests_src, dependencies: [criterion], include_directories: inc, override_options: ['b_coverage=true'])
  test('Unit tests', unit_tests)
else
  warning('Tests are disabled. Run ``meson -Denable_tests=true``')
endif
