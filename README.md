# ECPP - a simple programing language for non nerds.

ECPP (EC++ / Easy C++) is a minimalistic programming language implemented in C++. It features basic programming constructs like functions, variables, and arithmetic operations.

## Version History

### v0.1.0-alpha
- Initial release
- Basic function support
- Variable declarations
- Print statements
- Basic arithmetic (+, -)

## Features

- Function declarations and calls
- Variable declarations and assignments
- Basic arithmetic operations (+, -)
- String literals
- Print statements
- Basic error handling

## Building

### Windows

`.\BUILD.bat`

### Linux/MacOS

`g++ -std=c++17 -I./src/core -I./src/ast src/main.cpp src/core/.cpp -o build/ecpp`

## Usage

```bash
./ecpp <filename.ec>
```

## Language Syntax

### Functions

```
func greet() {
print("Hello, World!")
}
main() {
greet()
}
```

### Variables and Arithmetic

```
main() {
var x = 10
var y = 20
print(x + y)
print(y - x)
}
```

### String Output

```
main() {
print("Hello, ECPP!")
}
```

## Contributing

Feel free to open issues or submit pull requests. All contributions are welcome! ❤️

## Future Improvements

- [ ]  Add multiplication and division operations
- [ ]  Implement if/else conditionals
- [ ]  Add while/for loops
- [ ]  Support for more complex expressions
- [ ]  Add type system
