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
let a = 122
```

This assigns the string "122" immutably to the variable `a`.

### Mutable variables

```rust
let mut a = 144
a = 145
```

Set a mutable variable to "144", then change its value to "145".

### Unsetting a variable

```
let a = ubsh
unlet a
```

This sets the variable `a` to "ubsh" then unsets it.

### Variable expansion

To assign the value of a variable to another, use [string expansion](#string-expansion)

```rust
let a = $"{b}"
```

This assigns the value of the variable `b` to `a`.

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

### Displaying curly brackets

You can escape characters when doing string expansion

```rust
let a = 12
echo $"\{a\}"
```

will display "{a}" without expanding anything

```rust
let a = 12
echo $"\{{a}\}"
```

will display "{12}", expanding the value of the `a` variable
