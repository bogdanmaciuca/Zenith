# Zenith programming language

## 1. Introduction: Goals and philosophy
Zenith is a low-level, C-like programming language with QOL features added in for PERSONAL use.

### 1.1 Goals
- Very fast compile times
- Keeping the good parts of C/C++ and changing the bad parts

## 2. Lexical structure

### 2.1. Comments
```
// This is a comment
/*
This is a multi-line comment.
Multi-line comments cannot be nested
*/
```

### 2.2. Keywords
- `mut`
- `struct`
- `type`
- `alias`
- `if`
- `else`
- `while`
- `for`
- `in`
- `return`
- `break`
- `continue`
- `namespace`
- `trait`
- `using`
- `impl`

### 2.3. Identifiers
Must start with a letter or underscore, can also contain numbers

Regex: `[a-zA-Z_][a-zA-Z0-9_]*`

### 2.4. Literals

#### 2.4.1. Integers
Decimal: `123`, `1_234_567`

Hexadecimal: `0xDEAD`, `0xbeef`

Binary: `0b00100101`

Octal: `0o777`


#### 2.4.2. Floating point
`12.3`, `1.2e-5`

#### 2.4.3. Strings
`"This is a string"`

#### 2.4.4. Characters
`'A'`. `'\0'`

### 2.5. Operators

#### 2.5.1. Arithmetic operators
`+`, `-`, `*`, `/`, `%`, `**` 

#### 2.5.2. Logical operators
`&&`, `||`, `!`

#### 2.5.3. Comparison operators
`==`, `!=`, `<`, `>`, `<=`, `>=`

#### 2.5.4. Bitwise operators:
`&`, `|`, `^`, `~`, `<<`, `>>`

#### 2.5.4. Assignment operators:
`=`

#### 2.5.4. Pointer operators:
`&`, `*`

#### 2.5.4. Range operators:
`..<`, `..=`

#### 2.5.4. Scope operators:
`::`

#### 2.5.4. Other operators:
`.`

## 3. Grammar

### 3.1. Imports and namespaces
- Each file implicitly has its own namespace
- Importing: `import "path/to/file.zn"`
- Symbol access: `using math::Vector3` lets you use `Vector3` without the `math::` qualifier
- Aliasing a namespace: `using deep::nested::namespace = shorter;`

### 3.2. Declarations
All declarations are *immutable by default*.

#### 3.2.1. The `mut` keyword
`x := 10;` -> `x` is immutable

`mut x := 10;`: `y` is mutable

`p := &x;` -> `p` is an immutable pointer to immutable data (`a` is immutable)

`p := &y;` -> `p` is an immutable pointer to mutable data (because `y` is mutable)

`mut p := &y;` -> `p` is a mutable pointer to mutable data (`y` is mutable)

# 3.2.2. Compile-time constants
Compile-time constants do not have a type, each expression tries to convert to whatever type it needs (if possible).
`comptime_constant :: 69`

### 3.3 Type system

#### 3.3.1. Inference
The `:=` operator infers type from the right-hand side

`num := 420; // num will be of type i32`

It can be inferred whether a pointer points to mutable or immutable memory: `p := &a;`

If `a` is defined as mutable, then `*p` is allowed to be changed. Otherwise, `*p` is immutable. This can be overwritten by specifying `mut`: `p : *mut T = &a;`

#### 3.3.2. Primitives
`bool`, `string`, `i8`, `u8`, `i16`, `u16`, `i32`, `u32`, `i64`, `u64`, `f32`, `f64`

#### 3.3.3 Pointers

