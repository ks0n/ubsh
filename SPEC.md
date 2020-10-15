# ubsh Specification reference

This document aims to provide a comprehensive dive into ubsh's syntax. It should also
enable you to develop a complete and valid implementation of ubsh.

## Variables

```rust
let [ mut ] <var> = <value>
```

- A var is attributed a value
- A value can ONLY be a string
- Variables are immutable by default, unless initialized with `mut`.

### Setting a variable

```rust
let fig = 122
```

This assigns the string "122" immutably to the variable `fig`.

### Mutable variables

```rust
let mut tangerine = 144
tangerine = 145
```

Set a mutable variable to "144", then changes its value to "145".

### Unsetting a variable

```
let pear = ubsh
unlet pear
```

This sets the variable `pear` to "ubsh" then unsets it.

### Variable expansion

To assign the value of a variable to another, use [string expansion](#string-expansion)

```rust
let melon = $"{cantaloupe}"
```

This assigns the value of the variable `cantaloupe` to `melon`.

## String expansion

String expansion can be achieved through the following syntax:

```rust
$ " { <var_to_expand> } "
```

String expansion follows the classic rules of string formatting. To display the value of
the variables `a` and `b` separated by an hyphen and the number 3, do the following

```rust
echo $"{a}-{b}"
```

Thus, the following code

```rust
let peach_color = pink
let apple_color = yellow
echo $"A peach is {peach_color}, while an apple is {apple_color}!"
```

will evaluate to "A peach is pink, while an apple is yellow!"

### Displaying curly brackets

You can escape characters when doing string expansion

```rust
let lemon = 12
echo $"\{lemon\}"
```

will display "{lemon}" without expanding anything

```rust
let lemon = 12
echo $"\{{lemon}\}"
```

will display "{12}", expanding the value of the `a` variable

## Functions

In ubsh, functions are actually scripts stored on your file system. They contain the code
to execute when calling the function with `call`

```rust
func <function_name> = <path>
call <function_name>
```
