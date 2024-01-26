# Simple Arithmetic Expression Evaluator

## Author
Ryan Hecht

## Date
2024-01-26

## Brief
This program uses a CFG to evaluate simple arithmetic expressions.

### Context-Free Grammar (CFG) Rules
- `sim_exp → md_exp`
- `sim_exp → sim_exp l_op md_exp`
- `md_exp → num`
- `md_exp → md_exp h_op num`
- `l_op → + | -`
- `h_op → * | /`
- `num → 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9`

The code defines four functions to evaluate arithmetic expressions recursively: `get_op()`, `get_num()`, `sim_sub_exp()`, and `md_sub_exp()`. The main function is `sim_exp()`, which evaluates a simple arithmetic expression by calling `md_exp()` to evaluate the first multiplicative/divisive expression, and then calling `sim_sub_exp()` to evaluate the rest of the expression recursively.

The main function also includes a loop that prompts the user to enter a simple arithmetic expression, evaluates it, prints the result, and then asks if the user wants to continue. If the user enters 'Y', the loop continues; if the user enters 'N' or any other character, the program exits.

## Compilation and Execution
A CMake file is provided to compile and run the program. Feel free to use this or your preferred compiler, like gcc, to run the program.

```bash
make main
./main
```

Or

```bash
gcc -o expression_evaluator main.c
./expression_evaluator
```

## License

MIT
