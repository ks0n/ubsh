project('ubsh', 'c',
  default_options: [
    'warning_level=3',
    'debug=true',
    'b_sanitize=address',
    'c_std=c99',
    ])

inc = include_directories([ 'include', 'lib' ])

src = [
  'src/prompt.c',
  'src/charstream.c',
  'src/wordvec.c',
  'src/token.c',
  'src/lexer.c',
  ]

main = [
  'src/main.c',
  ]

readline = dependency('readline')

executable('ubsh', src, main, dependencies: [readline], include_directories: inc)

unit_tests_src = [
  'tests/charstream.c'
  ]
criterion = dependency('criterion')

unit_tests = executable('unit_tests', src, unit_tests_src, dependencies: [criterion], include_directories: inc)

test('Unit tests', unit_tests)
