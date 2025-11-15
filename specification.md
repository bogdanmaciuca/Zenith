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
- `const`
- `struct`
- `alias`
- `type`
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
- `Self`

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
`+`, `-`, `*`, `/`, `%`, `**`, `++`, `--`

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
`.`, `,`


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

`mut p : *const i32 = &y;` -> `p` is a mutable pointer to immutable data


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
```
a := 256;

ptr := &a; // Cannot modify ptr or a. Mutability of a is inferred
mut ptr := &a; // Can modify ptr, cannot modify a
ptr : *mut i32 = a; // Can modify a, cannot modify ptr
mut ptr : *mut i32 = a; // Can modify both a and ptr
```
Pointer **can** be null.

#### 3.3.4. References
Reference can only be used in function arguments, to specify a **non-null** pointer which can also accept a temporary variable.
```
fn Add(obj1: &T, obj2: &T) {
    // obj1 and obj2 cannot be modified.
}
```

#### 3.3.5. Arrays
```
my_array : T[10]; // Size must be known at compile time
your_array : T[10] = { 1, 4, 3, 5 };
his_array : T[] = { 1, 2, 3, 4, 5 }; // Size is 5

our_array := {...}; // Type and size will be inferred

my_array_size := my_array.size;
```

Arrays of up to 4 elements will support access by component names:
```
position : f32[3];
color := { 3.23, 4.35, 0.23 };

// position.x <-> position[0]
// color.r <-> color[0]
```

There will be support for matrix multiplication

#### 3.3.6. Type aliases and distinct types
Type aliases: `alias Number = i32;`. Now `Number` can be used interchangeably with `i32` and no cast is needed between the two.

Distinct types: `type ID = i32;`. Now `ID` is a new, distinct type which requires an explicit cast to `i32`.

#### 3.3.7. Casting


### 3.4. Slices
Python-like slices.

Slices do not own the data, they just point to it.

### 3.5. Structs and methods
```
struct Point {
    // --- Fields (Layout) ---
    x: i32 = 0; // Fields may or may not be given default values
    y: i32 = 0; // If not given a default value, they are 0-intialized

    // Method
    fn Norm2(self: *Self) -> i32 {
        return self.x * self.x + self.y * self.y;
    }
    // Static method (no self argument)
    fn New(x : i32, y : i32) -> Self {
        return Self{ x = x, y = y };
    }
}
```
The fields must always come before the methods.

Methods with the self argument passed as pointer cannot be called from immutable structs, as they are assumed to modify the state if the struct. Methods with the self argument passed as referenced can be called from immutable, as self will not be modified.

`Self` is an alias for the type of the struct.

### 3.6. Functions
- Syntax: `fn FunctionName(arg1: type, arg2: type) -> return_type { ... }`
- Void return: `fn MyFunction(...) { ... }`

#### 3.6.1. Passing arguments as pointers
In the case of function arguments, the data the pointers point to is mutable by default.
```
fn Modify(obj: *T) {
    // the data at obj can be changed
    *obj = ...
}
```

#### 3.6.2. Passing arguments as references
If we want to pass an object by address (because it is a big struct/type) but also want to accept temporaries, we can pass the object by reference.
```
fn Add(obj1: &T, obj2: &T) {
    // obj1 and obj2 cannot be modified.
}
```

### 3.7. Control flow
Paranthesis are mandatory.

#### 3.7.1. If/else
*If-then-else* is an expression.
`x := if a > b then a else b;`
```
mut x : i32;
if a > b {
    x = a;
}
else if b > a {
    x = b;
}
else {
    x = -1;
}
```

#### 3.7.2. While and for loops
```
while condition {
    // Do stuff...
}

for i in 1..<10 {
    // 1, 2, ..., 9
}
```

While and for loops can be named, so break and continue can reference the correct loop easily.

```
main_loop: while True {
    for ... {
        if condition {
            break main_loop;
        }
    }
}
```


## 4. Semantics and memory

### 4.1. Type checking
Static, strong typing.

Integer inference: `x := 10;` infers `i32` by default;
Float inference: `x := 10.0;` infers `f32` by default

operations between an integer and float need explicit casting of one of the operands.

### 4.2. Error handling (TODO)
`Result<T, E>` will be a generic struct that holds either the result or the error. A macro UNWRAP() will be used to propagate the error through the call stack if it cannot be handled when it is encountered

### 4.3. Memory model and RAII

#### 4.3.1. Allocators
There will be a global, thread_local allocator `g_global_allocator`, which will be used by default by all standard library functions (another allocator can be specified for every function). There will be an utility struct which uses RAII to change the global allocator for the current scope.

```
{
    allocator := ContextAllocator::New(my_allocator);
}
```

#### 4.3.2. RAII
Each struct will have a `New()` function which can be used for initializing (the constructor) and a `Delete()` function which will be automatically be called at the end of the scope and can also be called at the user.


## 5. Generics and traits

### 5.1. Trait definition
```
trait Addable {
    // self: *Self has to always be the first argument of the
    // functions/operators required by the trait
    fn add(self: &Self, other: &Self) -> Self;
    
    operator +(self: &Self, other: &Self) -> Self;
}
```

#### 5.1.1. Marker traits
```
trait IsNumber {}
```
Used to label types.


### 5.2. Trait implementation
```
impl Point: Add {
    fn add(self: &Self, other: &Self) -> Point {
        // ...
    }
    
    operator +(self: &Self, other: &Self) -> Self {
        // ...
    }
}
```
Implementations can be defined in any file.

`Self` is an alias to the type in question (in this example, `Point`).

### 5.3. Generic usage
```
fn max<T: Comparable>(a: &T, b: &T) -> T { /* ... */ }

struct Pair<K: Hashable, V> {
    first : K;
    second : V;
}
```

## 6. Standard library
### Goals:
- Support for Windows and Linux
- Console IO
- Result/Error structs for error handling
- Containers (dynamic arrays, hashmap)
- Allocators
- Math (operators between arrays of numbers)
- Marker traits for all primitive types
- Traits for all containers

