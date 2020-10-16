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
  'src/main.c',
  ]

executable('ubsh', src, include_directories: inc)
