# push_swap: worksheets

One sheet per part of `PLAN.md`. Each sheet says what the part is, where it fits in the whole project, what it connects to, what to build, how to know it's done, and what you should be able to explain afterwards.

The sheets describe the idea and the steps. They don't contain finished code: you write it, because at the evaluation you have to explain every line.

## How to read a sheet

- **Goal:** the part in one sentence.
- **Fits in the project:** why this part exists.
- **Comes from / Leads to:** what it needs before it, and what uses it afterwards.
- **Build:** the steps.
- **Done when:** a test you can run to prove it works.
- **Watch out:** the usual mistakes.
- **Be able to explain:** questions the other person (or an evaluator) can ask.

## How the pieces connect

```
terminal args
   |
   v
 flags.c (#10) --> config        parse.c (#9) --> pile A (#4)
                        \            /
                         v          v
                  main.c (#11) computes disorder (#14), ranks (#6)
                              |
                              v
                       dispatch.c (#11)
            /        /         |          \
      simple (#17) medium (#18) complex (#13) adaptive (#19)
            \        \         |          /
                       the 11 moves (#5, #8)
                              |
                              v
                       emit.c (#3): prints + counts
                              |
                  +-----------+-----------+
                  v                       v
         moves on stdout          bench.c (#15) on stderr
```

## Shared design decisions (read before sheet 2)

1. **One `t_ctx` travels everywhere.** It holds pile A, pile B, the config (which flags were given) and the stats (how many of each move were used). The subject forbids global variables, so this is how everything shares data.
2. **Every move has a silent core and a printing wrapper.** The core (`swap_top`, `push_top`, `rotate_top`, `rrotate_top`) only changes piles. The wrapper (`sa`, `pb`, `rra`...) calls the core, then calls `emit`. Two reasons: `sa` and `sb` share one core, so there's less code, and the bonus `checker` can reuse the silent cores.
3. **Sorts never print.** They only call `ra(ctx)`, `pb(ctx)` and so on.
4. **Disorder is a whole number.** C has no easy decimals here, so disorder is stored in hundredths of a percent: 0 means sorted, 10000 means worst case, 4000 means 40.00%.
5. **Norm reminders:** max 25 lines per function, 5 functions per file, 4 parameters, 5 variables per function. No `for`, no `switch`, no ternary `?:`, no global variables. Use `while` and `if`. Run `norminette` after every file.

---

# Sheet 1: Repo, folders, Makefile skeleton

**Owner:** Together
**Files:** `Makefile`, `.gitignore`, empty folders, minimal `src/main.c`

**Goal:** a place to put code that compiles from day one.

**Fits in the project:** everything else is added to this skeleton.

**Comes from:** nothing.
**Leads to:** #2 (the header goes in `include/`), and every later file gets added to the Makefile.

**Build:**
1. Create the git repository and add both of you as contributors. The subject requires both logins to appear.
2. Create the folders: `include/`, `src/input/`, `src/stack/`, `src/sort/`, `src/bench/`, `tests/`, `libft/`.
3. Copy your libft sources and its Makefile into `libft/`.
4. Write the Makefile with the rules `NAME`, `all`, `clean`, `fclean`, `re`. It compiles with `cc -Wall -Wextra -Werror`, builds libft through libft's own Makefile first, and puts `.o` files in an `obj/` folder.
5. List the source files by name. Evaluators often dislike wildcards.
6. Write a `main.c` that only returns 0.
7. Add the binary and `obj/` to `.gitignore`.

**Done when:**
- `make` builds `push_swap`
- running `make` again says nothing to do (no relinking)
- `make fclean && make` works from scratch

**Watch out:** relinking on every `make`, forgetting `-Werror`, forgetting that headers changing should trigger a rebuild.

**Be able to explain:** why `make` doesn't rebuild the second time, and the difference between `clean` and `fclean`.

---

# Sheet 2: The header

**Owner:** Together
**Files:** `include/push_swap.h`

**Goal:** one shared file that lists every type and function, so you can work in parallel.

**Fits in the project:** it's the contract between your parts and hers. If both of you build to the same header, the pieces fit when you put them together.

**Comes from:** #1.
**Leads to:** everything.

**Build (write it together, on one screen):**
1. Include guards, then the includes you need (`stdlib.h`, `unistd.h`, `limits.h`, your libft header).
2. An enum for the 11 moves, in this order: `sa sb ss pa pb ra rb rr rra rrb rrr`. This is also the order the bench report prints them.
3. An enum for the strategy: adaptive, simple, medium, complex.
4. `t_node` with `value`, `index`, `next`. `t_stack` with `head` and `size`.
5. `t_config` with the chosen strategy and a bench on/off flag.
6. `t_stats` with one counter per move (an array indexed by the move enum), a total, the disorder, and the complexity class that was used.
7. `t_ctx` with pile `a`, pile `b`, the config and the stats.
8. Prototypes for every function in the plan, grouped by folder. Every move takes a `t_ctx *`.

**Done when:**
- both of you can explain every line
- an empty `main.c` that includes it compiles
- `norminette include/` is clean

**Watch out:** no function bodies in the header, don't forget the include guard, and keep the typedefs aligned the way the Norm wants.

**Be able to explain:** why moves take the whole context instead of just a pile, and why there are no global variables.

---

# Sheet 3: `emit.c`

**Owner:** You
**Files:** `src/stack/emit.c`

**Goal:** one function that prints a move and counts it.

**Fits in the project:** every move calls it, and it's the only place that writes moves to stdout. The `--bench` report reads the counters it updates. If a flag ever changes how moves are printed, this is the one place you change.

**Comes from:** #2.
**Leads to:** #5 and #8 (the moves call it), #15 (the report reads its counters), #21 (the drill).

**Build:**
1. A small function that turns a move from the enum into its text (`"sa"`, `"pb"`...). The Norm bans `switch`, so use a chain of `if` lines. It fits in 25 lines.
2. `emit(ctx, op)`: write the text and a newline to stdout, add 1 to that move's counter, add 1 to the total.

**Done when:** `emit(ctx, OP_SA)` prints `sa` followed by a newline, and the counter for `sa` and the total are both 1.

**Watch out:** nothing else may ever go to stdout, and only `\n` separates moves (no spaces, no extra blank lines).

**Be able to explain:** why printing and counting are in the same function, and which lines you'd change to add a `--verbose` flag.

---

# Sheet 4: `stack.c`

**Owner:** Partner
**Files:** `src/stack/stack.c`, optionally `src/stack/stack_utils.c`

**Goal:** a pile that you can create, add to, take from and free.

**Fits in the project:** piles A and B are the only data in the whole project. Every move, every sort and the parser use these functions.

**Comes from:** #2 (the types).
**Leads to:** #5 and #8 (moves), #9 (parser fills pile A).

**Build:**
1. `node_new(value)`: allocate a node, set the value, set `next` to nothing.
2. `stack_push_top(stack, node)`: put the node on top and add 1 to `size`.
3. `stack_pop_top(stack)`: detach and return the top node, subtract 1 from `size`. Return nothing if the pile is empty.
4. `stack_last(stack)`: return the bottom node.
5. `stack_free(stack)`: free every node.
6. In a second file `stack_utils.c`, a small helper `stack_is_sorted(stack)`. Others will want it.

**Done when:** in a small test, you build a pile of 3 numbers, print them top to bottom, free it, and valgrind reports no leaks.

**Watch out:** forgetting to update `size`, losing the rest of the list when popping, and breaking on an empty pile.

**Be able to explain:** why the top of the pile is the first node of the list, and what changes when you push or pop.

---

# Sheet 5: Swap and push moves

**Owner:** Partner
**Files:** `src/stack/ops_swap.c`, `src/stack/ops_push.c`

**Goal:** `sa sb ss pa pb`.

**Fits in the project:** these are the first moves the sorts will use. They are also what the program prints.

**Comes from:** #4 (piles), #3 (`emit`; until it exists, print with `write`).
**Leads to:** #7 and every sort.

**Build:**
1. `ops_swap.c` gets the silent core `swap_top(pile)`: do nothing if the pile has fewer than 2 numbers, otherwise swap the top two. Remember that `index` has to move together with `value`.
2. Then the wrappers: `sa` swaps A, `sb` swaps B, and `ss` swaps both and prints once.
3. `ops_push.c` gets the silent core `push_top(from, to)`: do nothing if `from` is empty, otherwise pop from one and push on the other.
4. Then the wrappers: `pa` moves B to A, `pb` moves A to B.
5. Each wrapper calls its core, then `emit(ctx, OP_...)`. If the move did nothing, don't emit.

**Done when:** with pile A as `2 1 3 6 5 8` (top first), `sa` gives `1 2 3 6 5 8`, and then `pb pb pb` leaves A as `6 5 8` and B as `3 2 1`. This matches page 13 of the subject.

**Watch out:** `ss` must print `ss`, not `sa` and `sb`. Keep `size` correct after every push.

**Be able to explain:** why `sa` and `sb` can share one core, and what `pb` does to both sizes.

---

# Sheet 6: `index.c` (ranks)

**Owner:** You
**Files:** `src/sort/index.c`

**Goal:** replace each value by its rank: the smallest number gets 0, the next 1, and so on up to n-1.

**Fits in the project:** every big sort works on ranks instead of raw values. Ranks are always 0 to n-1 with no gaps, and negatives stop being a problem. Radix needs this, and chunks are easier with it.

**Comes from:** #4 (nodes with an `index` field), #9 (real input; until then build a pile by hand).
**Leads to:** #7, #12, #13, #17, #18.

**Build:**
1. A helper that counts how many nodes in the pile have a smaller value than a given node.
2. `assign_indexes(pile)`: for each node, store that count in its `index`.
3. It runs once, before any move. The index stays with the node as it moves between piles, and the value never changes.

**Done when:**
- `5 -2 9` becomes the indexes `1 0 2`
- with 500 random numbers, each index from 0 to 499 appears exactly once

**Watch out:** the double loop is slow, but 500 numbers is fine. Don't change `value`.

**Be able to explain:** why ranks are easier to work with than raw values.

---

# Sheet 7: `sort_three`

**Owner:** You
**Files:** `src/sort/sort_small.c`

**Goal:** sort a pile of exactly 3 numbers with at most 2 moves.

**Fits in the project:** it's the smallest sorting method, and bigger sorts finish with it (`sort_five` and the simple sort both leave 3 numbers in A).

**Comes from:** #3, #5, #6, and the rotate moves from #8 (you can write it now and run it once #8 exists).
**Leads to:** #12, #17.

**Build:**
1. Compare the indexes of the three top nodes. Don't assume they are 0, 1, 2, because later this function runs on the 3 numbers that are left in a bigger pile.
2. Handle the 6 possible orders with `if` checks. We already solved three by hand (top to bottom):

| Order | Moves |
|---|---|
| `1 2 3` | none |
| `2 1 3` | `sa` |
| `3 2 1` | `sa`, `rra` |
| `3 1 2` | `ra` |
| `2 3 1` | you find it |
| `1 3 2` | you find it |

3. Keep each function short: one helper that finds the case, one that applies the moves.

**Done when:** a test that tries all 6 orders ends with sorted piles, using at most 2 moves each.

**Watch out:** the 25-line limit. Split the checks into helpers.

**Be able to explain:** why there are only 6 cases, and how you found the moves for `2 3 1` and `1 3 2`.

---

# Sheet 8: Rotate moves

**Owner:** Partner
**Files:** `src/stack/ops_rotate.c`, `src/stack/ops_rrotate.c`

**Goal:** `ra rb rr rra rrb rrr`.

**Fits in the project:** rotating is how the sorts bring a number to the top. It's the most used family of moves, and `rr` and `rrr` save moves because they do both piles at once.

**Comes from:** #4, #3.
**Leads to:** #7 and every sort.

**Build:**
1. Silent core `rotate_top(pile)`: the top node goes to the bottom. Do nothing if the pile has fewer than 2 numbers.
2. Wrappers `ra`, `rb`, and `rr` (rotates both, prints once).
3. Silent core `rrotate_top(pile)`: the bottom node goes to the top. You need the second to last node, so walk the list.
4. Wrappers `rra`, `rrb`, and `rrr` (prints once).

**Done when:** the whole example on page 13 of the subject matches, state by state:
- `sa`, then `pb pb pb`
- then `rr`: A is `5 8 6`, B is `2 1 3`
- then `rrr`: back to A `6 5 8`, B `3 2 1`
- then `sa`, then `pa pa pa`: A is `1 2 3 5 6 8`

**Watch out:** relink pointers in the right order so you don't lose the list. Make sure the last node's `next` is cleared.

**Be able to explain:** why `rr` counts as 1 move, and how `rra` finds the node before the last.

---

# Sheet 9: `parse.c` (numbers and errors)

**Owner:** Partner
**Files:** `src/input/parse.c`, `src/input/error.c`

**Goal:** turn the number arguments into pile A, or print `Error` and stop.

**Fits in the project:** it's where all bad input is caught, so the sorts can trust that pile A holds valid, unique numbers.

**Comes from:** #4.
**Leads to:** #11 (`main`).

**Build:**
1. `parse_args(argc, argv, ctx)`: go through the arguments and skip any that start with `--`, because those are flags and belong to `flags.c`. The first number argument ends up on top of the pile.
2. For each number argument check three things: it's only an optional sign followed by digits (and not empty), it fits in an `int` (build it in a `long` and stop as soon as it's too big), and it's not already in the pile.
3. `error_exit(ctx)` in `error.c`: free both piles, write `Error` and a newline to stderr, exit. `flags.c` will call it too.
4. If there are no numbers at all, print nothing and return normally.
5. Don't use `atoi`. It can't tell you about errors.

**Done when:**
- `./push_swap 0 one 2 3` and `./push_swap 3 2 3` print `Error` on stderr
- `-2147483648` is accepted
- `2147483648` is an error
- an empty string `""` is an error
- valgrind is clean on every error path

**Watch out:** leaks when the error happens after some nodes were already created, and a lone `-` or `+` with no digits.

**Be able to explain:** how you detect overflow, and why `-5` is a number but `--bench` is a flag.

---

# Sheet 10: `flags.c` and the config

**Owner:** You
**Files:** `src/input/flags.c`

**Goal:** read the options and store them in `t_config`.

**Fits in the project:** this is the path every flag follows: flag, then config, then behavior. The live coding task will almost certainly start here.

**Comes from:** #2 (`t_config`), #9 (`error_exit`; use a temporary exit until it exists).
**Leads to:** #11 (`main` reads the config), #15 (bench flag), #17, #18, #19.

**Build:**
1. `parse_flags(argc, argv, ctx)`: set the defaults first (adaptive strategy, bench off).
2. Go through the arguments. If one starts with `--`, compare it with the known names: `--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`. A `--` argument that isn't known is an error.
3. Each flag is its own `if` line that calls a tiny helper. Split into a strategy helper and an options helper so every function stays within 25 lines.
4. A small `is_flag(str)` helper that `parse.c` can also use.
5. If two strategy flags are given, decide which wins (for example, the last one) and write it in the README.

**Done when:** flags and numbers can appear in any order, `--bench` alone sets only the bench option, and a bad flag prints `Error`.

**Watch out:** `-5` has one dash, so it is a number. Don't store flag state in a global.

**Be able to explain:** the exact edits to add a new flag `--foo`. This is the one you must know cold.

---

# Sheet 11: `dispatch.c` and `main.c`

**Owner:** You (`main.c` together)
**Files:** `src/sort/dispatch.c`, `src/main.c`

**Goal:** make the whole program run from start to finish.

**Fits in the project:** `main` is the conductor and `dispatch` is the switchboard. After this part, both halves of the project meet for the first time.

**Comes from:** #4, #9, #10, #6.
**Leads to:** every sort (the dispatcher calls them), #15.

**Build:**
1. `run_strategy(ctx)`: if the pile has 0 or 1 numbers, or is already sorted, do nothing. Otherwise look at the configured strategy and call the matching sort. Adaptive calls the adaptive picker. Each strategy is one `if` line.
2. For now, use a placeholder for sorts that don't exist yet: a function that compiles and returns.
3. `main`: zero the context, read flags, read the numbers, return quietly if there are none, measure the disorder (placeholder 0 until #14), assign the ranks, call `run_strategy`, print the bench report if asked, free everything.

**Done when:** the program parses, dispatches and frees without leaks, and the error cases behave correctly. The sort itself can still be fake.

**Watch out:** the disorder must be measured before any move. Free both piles on every path.

**Be able to explain:** the order of the steps in `main`, and which file you'd change to add a new strategy.

---

# Sheet 12: `sort_five` (sorting 2 to 5 numbers)

**Owner:** You
**Files:** `src/sort/sort_small.c`

**Goal:** sort piles of 2, 3, 4 or 5 numbers.

**Fits in the project:** small inputs are valid inputs, and the strategies must not break on them. This part is also the idea behind the simple sort in #17.

**Comes from:** #3, #5, #6, #7, #8.
**Leads to:** #17 (the same idea for any size), and optionally #19 (adaptive can use it for tiny inputs).

**Build:**
1. Size 2: `sa` if it's not sorted.
2. Size 3: call `sort_three`.
3. Size 4 or 5: repeat "push the smallest number to B" until 3 remain. To reach the smallest, find its position and choose `ra` or `rra`, whichever is shorter. Then call `sort_three` and `pa` everything back.
4. Because you push the smallest first and the next smallest second, B ends with the bigger one on top, so the `pa` moves come back in the right order. This is what you traced by hand with `4 2 5 1 3`.

**Done when:** a test over all 120 orders of 5 numbers ends sorted with B empty. Test 4 numbers too.

**Watch out:** finding "the smallest" with ranks: use the lowest index in A, and don't assume it's 0 once numbers have been pushed.

**Be able to explain:** how you decide between `ra` and `rra`, and why the pushes come back in the right order.

---

# Sheet 13: Radix sort (the complex strategy)

**Owner:** You
**Files:** `src/sort/sort_complex.c`

**Goal:** sort any size with roughly n log n moves.

**Fits in the project:** this is your first big sort and the milestone of the project. After it, you have a real working program. It's also the high-disorder method in the adaptive picker.

**Comes from:** #3, #5, #6, #8.
**Leads to:** #19.

**Build:**
1. Find how many bits the largest rank needs (the largest rank is size minus 1).
2. For each bit, from the lowest to the highest: go through all numbers in A once. If the number's rank has a 0 in this bit, `pb` it, otherwise `ra` it. Then `pa` everything from B back to A.
3. After the last bit, A is sorted.
4. Why it works: each pass sorts numbers by one more bit, and the order from the previous passes is kept (the passes are stable).

**Done when:** `--complex` sorts 100 and 500 random numbers (check with the test scripts). Expect roughly 1000 moves for 100 numbers and roughly 6800 for 500. These are estimates, so write down your real counts.

**Watch out:** use ranks, not raw values (negatives break bit tricks). Use `while` loops with counters. Stay under 5 variables per function by splitting into helpers.

**Be able to explain:** why the sorted order appears after the last bit, and why the move count grows like n log n.

---

# Sheet 14: `disorder.c`

**Owner:** Partner
**Files:** `src/bench/disorder.c`

**Goal:** compute how messy pile A is, from 0 (sorted) to the worst case (reversed).

**Fits in the project:** the adaptive strategy uses it to choose a method, and `--bench` prints it.

**Comes from:** #4.
**Leads to:** #15 and #19.

**Build:**
1. Look at every pair of numbers where one comes before the other in the pile. Count the total pairs, and count the "mistakes" (the earlier number is bigger).
2. Result is mistakes divided by total pairs. To avoid decimals, return it in hundredths of a percent: mistakes times 10000 divided by total pairs. Use `long` for the multiplication, because the number gets big.
3. Pairs: nested `while` loops with two pointers walking the list.
4. If the pile has fewer than 2 numbers, return 0.

**Done when:**
- a sorted pile gives 0
- a reversed pile gives 10000
- `2 1 3` gives 3333
- `4 67 3 87 23` gives 4000, which matches the 40.00% in the subject's example

**Watch out:** this must be measured before any move is made.

**Be able to explain:** why `4 67 3 87 23` has 10 pairs and 4 mistakes.

---

# Sheet 15: `bench.c` (the report)

**Owner:** You
**Files:** `src/bench/bench.c`

**Goal:** print the `--bench` report on stderr.

**Fits in the project:** it reads the stats that `emit` collects and the disorder that `main` measured. It's another place a live flag might touch (a new line in the report).

**Comes from:** #3 (counters), #10 (the bench flag), #14 (disorder).
**Leads to:** #21 (the drill).

**Build:**
1. Print 5 lines in the exact format of page 16 of the subject:

```
[bench] disorder: 40.00%
[bench] strategy: Adaptive / O(n√n)
[bench] total_ops: 13
[bench] sa: 0 sb: 0 ss: 0 pa: 5 pb: 5
[bench] ra: 2 rb: 1 rr: 0 rra: 0 rrb: 0 rrr: 0
```

2. Disorder: whole part is the stored value divided by 100, then a dot, then the remainder as two digits (pad with a leading zero, so 4005 prints as `40.05`).
3. Strategy: for forced flags print the name with its class (`Simple / O(n²)`, `Medium / O(n√n)`, `Complex / O(n log n)`). For adaptive print `Adaptive` and the class it chose.
4. Write everything to stderr (fd 2). Use libft functions or `write`.
5. Only call it when `--bench` was given.

**Done when:** the output matches the subject's examples, and `./push_swap --bench ... 2> bench.txt | ./checker_linux ...` shows `OK` with the report in the file.

**Watch out:** stdout must stay clean, with only moves on it. Copy the spacing from the subject exactly.

**Be able to explain:** why the report goes to stderr, and how you'd add a new stat line.

---

# Sheet 16: Test scripts

**Owner:** Partner
**Files:** `tests/*.sh` (not graded)

**Goal:** one command that shows how many moves the program used for N numbers.

**Fits in the project:** all the tuning and checking in the later parts depends on these.

**Comes from:** nothing to write them, but they need a working program (#11 or #13) to be useful.
**Leads to:** #13, #17, #18, #19, #20.

**Build:**
1. `gen.sh N`: print N random unique numbers, including some negatives. The subject uses `shuf -i 0-9999 -n 500` for positives. For negatives, generate positives and subtract an offset with `awk`.
2. `count.sh N`: run `./push_swap $(./gen.sh N) | wc -l`.
3. `check.sh N`: pipe the moves into `./checker_linux` with the same numbers and show `OK` or `KO`.
4. `stress.sh N RUNS`: repeat many times and show the smallest, average and largest move count, and stop if any run gives `KO`.
5. `errors.sh`: run a list of bad inputs and confirm each prints `Error`.

**Done when:** one command prints the move count for 100 numbers and for 500 numbers.

**Watch out:** the numbers must be unique. The same numbers have to go to both `push_swap` and the checker, so store them in a variable first.

**Be able to explain:** what each script checks, and what the worst-case number from `stress.sh` tells you.

---

# Sheet 17: The simple sort

**Owner:** Together (she types, you explain)
**Files:** `src/sort/sort_simple.c`

**Goal:** the O(n²) strategy, behind `--simple`.

**Fits in the project:** it's one of the four required strategies. It's also the method you already invented by hand with 5 numbers, so it's the best part for the two of you to build side by side.

**Comes from:** #12 (the same idea and helpers), #7, #5, #8.
**Leads to:** #19 (low disorder regime).

**Build:**
1. Repeat "push the smallest number to B using the shorter rotation" until 3 numbers remain in A.
2. Sort the 3 with `sort_three`.
3. `pa` everything back. The pushes come back in the right order, as in #12.
4. Reuse the helpers from #12 (finding the smallest, rotating it to the top).

**Done when:** `--simple` sorts 3, 5, 100 and 500 numbers. For 500 numbers expect tens of thousands of moves, which is much more than the benchmark limits. That's normal for an O(n²) method, because the benchmark is judged on the default strategy.

**Watch out:** don't copy-paste #12. Share the helpers.

**Be able to explain (both of you):** why the number of moves grows with n squared, and what the README should say about it.

---

# Sheet 18: The medium sort (chunks)

**Owner:** You
**Files:** `src/sort/sort_medium.c`

**Goal:** the O(n√n) strategy, behind `--medium`.

**Fits in the project:** it's the second required strategy, and the middle regime of the adaptive picker.

**Comes from:** #3, #5, #6, #8.
**Leads to:** #19.

**Build:**
1. Write your own integer square root. `math.h` isn't in the allowed functions list.
2. Cut the ranks into chunks of about √n numbers each (you can tune the size later).
3. Phase 1: go chunk by chunk. For the current chunk, rotate A until the top belongs to it, then `pb`. Optionally rotate B a little for the smaller half of the chunk, so B is loosely ordered.
4. Phase 2: while B isn't empty, find the largest rank in B, rotate B the shorter way (`rb` or `rrb`) to bring it to the top, then `pa`. Since the biggest goes first, A ends up ascending with the smallest on top.
5. Why O(n√n): each number only travels about √n positions to reach its chunk.

**Done when:** `--medium` sorts 100 and 500 numbers. Write down the move counts for a few chunk sizes and keep the best.

**Watch out:** the 25-line limit again. Split phase 1 and phase 2 into separate functions.

**Be able to explain:** why chunks cut the rotation cost, and how you chose the chunk size.

---

# Sheet 19: The adaptive picker

**Owner:** You
**Files:** `src/sort/sort_adaptive.c`

**Goal:** choose the method based on how messy the input is.

**Fits in the project:** it's the default mode, and it's what the evaluators will run most. The README must explain its thresholds.

**Comes from:** #13, #14, #17, #18, #11 (`main` measures the disorder).
**Leads to:** #15 (report shows the chosen class), #20.

**Build:**
1. Read the disorder that `main` stored (before any move).
2. Under 0.2 (stored as 2000): use an O(n²) method. From 0.2 up to 0.5 (2000 to 4999): the chunk sort. At 0.5 or more (5000+): radix.
3. Save which class was used in the stats so `--bench` can print `Adaptive / <class>`.
4. The subject only fixes the complexity per regime, so inside each regime the internals are yours. For example, a nearly sorted input could use a smarter method than the plain simple sort.
5. Decide how tiny inputs (2 to 5 numbers) are handled, and write it down.

**Done when:** the default mode picks a different regime for a nearly sorted list, a medium mess and a random list, and `--bench` shows which one.

**Watch out:** a random list has disorder around 50%, so it lands in the radix regime. That gives the "good" tier at best. Getting to "excellent" needs better methods, which we can look at once everything works.

**Be able to explain:** why those thresholds, and the complexity argument for each regime. The README needs both.

---

# Sheet 20: README, leaks, norm, Makefile check

**Owner:** Together
**Files:** `README.md`, plus fixes anywhere

**Goal:** everything the evaluators check that isn't the algorithm itself.

**Fits in the project:** a project with a leak, a norm error or a missing README line gets a 0 or fails, no matter how good the sorts are.

**Comes from:** all parts.
**Leads to:** #21, #22.

**Checklist:**
1. README first line, in italics: `This project has been created as part of the 42 curriculum by <login1>, <login2>.`
2. README sections: Description, Instructions, Resources (including exactly how AI was used and for which parts), each person's contributions, the justification and complexity argument for every algorithm, and the adaptive thresholds with their rationale.
3. `norminette` clean on every file.
4. Valgrind or `-fsanitize=address` clean on normal runs and on every error path.
5. `make` twice says nothing to do.
6. Benchmark runs with the test scripts: 100 and 500 random numbers, several runs, compare to the table in the subject.
7. Edge inputs: no arguments, one number, two numbers, already sorted, `-2147483648`, `2147483647`, duplicates.

**Done when:** all items are ticked, and both of you have answered "why?" about every file.

**Watch out:** the AI description in the README should be honest and specific.

**Be able to explain:** every file, to each other, without notes.

---

# Sheet 21: The flag drill

**Owner:** You (she can invent the flags)
**Files:** whichever the flag needs

**Goal:** be ready for the live coding at the evaluation.

**Fits in the project:** the evaluation may ask you to add a new flag within a few minutes. This is practice for exactly that.

**Comes from:** #3, #10, #11, #15.
**Leads to:** nothing, it's the final skill.

**Drill:** time yourself with 5 minutes per flag.
1. **An output flag**, like `--count`: print only the number of moves instead of the moves. Touches the config, `flags.c`, `emit.c` and `main.c`.
2. **A strategy flag**, like `--insertion`: a new sort chosen by a flag. Touches the enum, `flags.c`, `dispatch.c` and one new sort file.
3. **A bench line**, like `max size of B`: a new stat. Touches `t_stats`, the place it's updated, and `bench.c`.

If a flag takes more than about 4 small edits or touches files you didn't expect, the structure needs to be simplified. Tell me and we'll fix it.

Then let your partner invent a surprise flag and time that one too.

**Done when:** you can add each of the three flags in under 5 minutes without looking at notes.

**Be able to explain:** the path of a flag from the command line to its effect.

---

# Sheet 22: The bonus `checker`

**Owner:** Partner
**Files:** bonus files named `*_bonus.c` and `*_bonus.h`, and a `bonus` rule in the Makefile

**Goal:** a program that reads moves and says whether they sort the pile.

**Fits in the project:** it's only graded if the mandatory part is perfect. It reuses your piles, the silent move cores and the parser.

**Comes from:** #4, #5, #8, #9, #20.
**Leads to:** nothing.

**Build:**
1. `checker` takes the numbers as arguments, with the first on top. No arguments means it does nothing.
2. Read moves from stdin, one per line. Unknown or badly formatted moves print `Error` on stderr.
3. Apply them with the silent cores (no printing).
4. At the end, if pile A is sorted and B is empty, print `OK`, otherwise `KO` (both on stdout).
5. Bad numbers print `Error` on stderr, the same checks as the parser.
6. Bonus files must be named `*_bonus.c` and `*_bonus.h`, so check the subject's rule about that before reusing the mandatory files.

**Done when:** it gives the same answers as the examples on page 20 of the subject.

**Watch out:** the subject says it's only evaluated if the mandatory part is perfect, including the benchmarks.

**Be able to explain:** how the checker reuses the same stack code as `push_swap`.
