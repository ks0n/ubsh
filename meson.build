project('ubsh', 'c',
  default_options: [
    'warning_level=3',
    'debug=true',
    'b_sanitize=address',
    'std=c89',
    ])

inc = include_directories([ 'include', 'lib' ])

src = [
  'lib/linenoise/linenoise.c',
  'src/prompt.c',
  'src/main.c',
  'src/charstream.c',
  'src/wordvec.c',
  'src/token.c',
  'src/lexer.c',
  ]

executable('ubsh', src, include_directories: inc)
