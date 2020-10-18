project('ubsh', 'c',
  default_options: [
    'warning_level=3',
    'debug=true',
    'b_sanitize=address',
    ])

inc = include_directories([ 'include', 'lib' ])

src = [
  'lib/linenoise/linenoise.c',
  'src/prompt.c',
  'src/charstream.c',
  ]

main = [
  'src/main.c',
  ]


executable('ubsh', src, main, include_directories: inc)

unit_tests_src = [
  'tests/charstream.c'
  ]
criterion = dependency('criterion')

unit_tests = executable('unit_tests', src, unit_tests_src, dependencies: [criterion], include_directories: inc)

test('Unit tests', unit_tests)
