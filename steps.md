# push_swap: project plan

Work through the table from top to bottom. The two of us work on different rows at the same time and meet at the "Together" rows. After each part, swap for 15 minutes: the author explains the code line by line, the other asks "why?". Both of us must be able to defend any part at the evaluation.

## Ownership

- **You (flag path owner):** `emit.c`, `index.c`, `flags.c` and config, `dispatch.c`, `bench.c`, and the sorting methods (three, five, radix, medium, adaptive).
- **Partner:** the stack, the 11 moves, number parsing, the disorder score, the test scripts, and the bonus checker if we get there.
- **Together:** repo and Makefile, the header, `main.c`, the simple sort, and the README.
## Parts

| # | Part | Who | Done when |
|---|------|-----|-----------|
| 1 | Repo, folders, Makefile skeleton | Together | Empty `main.c` compiles with the flags |
| 2 | Header: stack, config, stats, ctx structs | Together | Both of us can explain every line |
| 3 | `emit.c`: print a move and count it | You | Calling it prints one line and bumps a counter |
| 4 | `stack.c`: create, push, pop, last, free | Partner | Build a 3-number pile, print it, free it, no leaks |
| 5 | Swap and push moves (`sa sb ss pa pb`) | Partner | Matches the subject example on page 13 so far |
| 6 | `index.c`: values become ranks 0 to n-1 | You | `5 -2 9` becomes `1 0 2` |
| 7 | `sort_three` | You | All 6 orders of 3 numbers get sorted |
| 8 | Rotate moves (`ra rb rr rra rrb rrr`) | Partner | The full example on page 13 now matches |
| 9 | `parse.c`: numbers and errors | Partner | Letters, overflow and duplicates print `Error` |
| 10 | `flags.c` and config | You | Flags and numbers mix in any order, adaptive is the default |
| 11 | `dispatch.c` and `main.c` | You (`main.c` together) | The program runs start to finish with a placeholder sort |
| 12 | `sort_five` | You | All orders of 5 numbers get sorted |
| 13 | Radix sort (complex) | You | 100 random numbers get sorted |
| 14 | `disorder.c` | Partner | Sorted gives 0, reversed gives 100% |
| 15 | `bench.c`: the report | You | Output matches the subject's examples |
| 16 | Test scripts: random numbers, move counter | Partner | One command shows the move count for N numbers |
| 17 | Simple sort | Together | Selection-style sort works with `--simple` |
| 18 | Medium sort (chunks) | You | Works with `--medium` |
| 19 | Adaptive picker | You | Default mode chooses by disorder |
| 20 | README, leaks, norm, Makefile check | Together | Valgrind clean, norminette clean, README complete |
| 21 | Flag drill | You | 3 invented flags, 5 minutes each |
| 22 | Bonus `checker` | Partner | Only if the mandatory part is perfect |

## Milestones

- **After part 11:** the program runs end to end, even with a fake sort. First time both halves meet.
- **After part 13:** a real working project. Everything after adds features or improves the score.
- **After part 19:** all four strategies and all flags work.
## Notes

- Part 3 comes before the moves (parts 5 and 8), because each move calls `emit`. If the partner is ready first, print with `write` for now and switch later.
- Sorts never print. They only call moves through `ctx`.
- No global variables. Everything travels in `t_ctx`.
- A new flag follows one path: parser, then `t_config`, then dispatcher (or `emit` for output flags, `bench.c` for report lines).
- Walk the partner through parts 3, 10 and 11 once they're done, so she understands the flag path too.
## Benchmarks to hit (from the subject)

| Numbers | Pass | Good | Excellent |
|---------|------|------|-----------|
| 100 | under 2000 ops | under 1500 | under 700 |
| 500 | under 12000 ops | under 8000 | under 5500 |

## Rules for all code

- Norm: max 25 lines per function, 5 functions per file, 4 parameters per function, no `for` loops. Run `norminette` often.
- Free everything, including on error paths.
- Allowed functions: `read`, `write`, `malloc`, `free`, `exit`, plus our libft.
- Compile with `-Wall -Wextra -Werror`, and the Makefile must not relink.
