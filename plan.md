# push_swap: worksheets

> **What changed in this version:** the plan now matches the code. Types are `t_node` and `t_stack` (with `head` and `size`), not `t_stack_node` with no wrapper. The bag is `t_context`, not `t_ctx`. `emit` takes the operation first. `stack_size` is gone because `size` is kept in `t_stack`. `assign_indexes` is `assign_index`. Owners and the timetable are unchanged.

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

### Names we use (they match `push_swap.h`)

| Name | What it is |
|---|---|
| `t_node` | one number in a pile: `value`, `index`, the Turk fields, `next` (the node below) and `prev` (the node above) |
| `t_stack` | one pile: `head` (pointer to the top node) and `size` |
| `t_config` | which flags were given: `strategy`, `bench` |
| `t_stats` | the counters: `ops[11]` and `total` (disorder and complexity class are added later) |
| `t_context` | everything in one bag: `a`, `b` (both `t_stack`), `config`, `stats` |
| `t_operation` | the 11 moves, `OP_SA` to `OP_RRR` |
| `t_strategy` | `ADAPTIVE`, `SIMPLE`, `MEDIUM`, `COMPLEX` |

```
context
 |-- a  (t_stack)   head --> [3] <--> [2] <--> [1]     size = 3
 |-- b  (t_stack)   head --> NULL                      size = 0
 |-- config
 |-- stats          ops[11], total
```

How functions are called:
- `emit(OP_SA, context)`: the operation comes first.
- Moves take the whole bag: `sa(context)`, `pb(context)`. Their silent cores take piles: `swap_top(t_stack *stack)`, `push_top(t_stack *from, t_stack *to)`.
- Helpers take piles: `stack_is_sorted(t_stack *stack)`, `assign_index(t_stack *stack)`.
- There is no wrapper around the node and no pointer-to-pointer: a function changes the top of a pile through `stack->head`.

### The decisions

1. **One `t_context` travels everywhere.** It holds pile A, pile B, the config (which flags were given) and the stats (how many of each move were used). The subject forbids global variables, so this is how everything shares data.
2. **Every move has a silent core and a printing wrapper.** The core (`swap_top`, `push_top`, `rotate_top`, `rrotate_top`) only changes piles. The wrapper (`sa`, `pb`, `rra`...) calls the core, then calls `emit`. Two reasons: `sa` and `sb` share one core, so there's less code, and the bonus `checker` can reuse the silent cores.
3. **Sorts never print.** They only call `ra(context)`, `pb(context)` and so on.
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

**Fits in the project:** it's the contract between both parts. If both of you build to the same header, the pieces fit when you put them together.

**Comes from:** #1.
**Leads to:** everything.

**Build (write it together, on one screen):**
1. Include guards, then the includes you need (`stdlib.h`, `unistd.h`, `limits.h`, `stdbool.h`, your libft header).
2. An enum for the 11 moves, in this order: `sa sb ss pa pb ra rb rr rra rrb rrr`. This is also the order the bench report prints them.
3. An enum for the strategy: adaptive, simple, medium, complex.
4. `t_node` with `value`, `index`, `push_cost`, `above_median` (bool), `cheapest` (bool), `*target_node`, `*next`, `*prev`. This is a doubly-linked list node: `next` points to the node below, `prev` points to the node above.
5. `t_stack` with `head` (a pointer to the top node) and `size` (how many nodes). A pile is a `t_stack`, and every move takes a pointer to one.
6. `t_config` with the chosen strategy and a bench on/off flag.
7. `t_stats` with one counter per move (an array of 11 ints indexed by the move enum), a total, and later the disorder and the complexity class that was used.
8. `t_context` with `a` and `b` (both `t_stack`), `config` and `stats`.
9. Prototypes for every function in the plan, grouped by folder. Every move takes a `t_context *`, and `emit` takes the operation first: `emit(operation, context)`.

**Done when:**
- both of you can explain every line
- an empty `main.c` that includes it compiles
- `norminette include/` is clean

**Watch out:** no function bodies in the header, don't forget the include guard, and keep the typedefs aligned the way the Norm wants.

**Be able to explain:** why moves take the whole context instead of just a pile, and why there are no global variables.

---

# Sheet 3: `emit.c`

**Owner:** Nami
**Files:** `src/stack/emit.c`

**Goal:** one function that prints a move and counts it.

**Fits in the project:** every move calls it, and it's the only place that writes moves to stdout. The `--bench` report reads the counters it updates. If a flag ever changes how moves are printed, this is the one place you change.

**Comes from:** #2.
**Leads to:** #5 and #8 (the moves call it), #15 (the report reads its counters), #21 (the drill).

**Build:**
1. A small function that turns a move from the enum into its text (`"sa"`, `"pb"`...). The Norm bans `switch`, so use a chain of `if` lines. It fits in 25 lines.
2. `emit(operation, context)`: write the text and a newline to stdout, add 1 to that move's counter, add 1 to the total.

**Done when:** `emit(OP_SA, context)` prints `sa` followed by a newline, and the counter for `sa` and the total are both 1.

**Watch out:** nothing else may ever go to stdout, and only `\n` separates moves (no spaces, no extra blank lines).

**Be able to explain:** why printing and counting are in the same function, and which lines you'd change to add a `--verbose` flag.

---

# Sheet 4: `stack.c`

**Owner:** John
**Files:** `src/stack/stack.c`, optionally `src/stack/stack_utils.c`

**Goal:** a pile that you can create, add to, take from and free.

**Fits in the project:** piles A and B are the only data in the whole project. Every move, every sort and the parser use these functions.

**Comes from:** #2 (the types).
**Leads to:** #5 and #8 (moves), #9 (parser fills pile A).

**Build:**
1. `node_new(value)`: allocate a node, set the value, set `next` and `prev` to nothing. The Turk fields (`push_cost`, `above_median`, `cheapest`, `target_node`) start at zero/false/nothing — the sort sets them later.
2. `stack_push_top(stack, node)`: put the node on top. Set `prev` of the old top to the new node (only if there is an old top), `next` of the new node to the old top, `prev` of the new node to nothing, and add 1 to `size`.
3. `stack_pop_top(stack)`: detach and return the top node. Clear the `prev` pointer of the new top (only if there is one), clear `next` and `prev` of the node you hand back, subtract 1 from `size`, and return NULL if the pile is empty.
4. `stack_last(stack)`: walk `next` to return the bottom node (or keep a tail pointer if you prefer).
5. `stack_free(stack)`: free every node and set `size` to 0.
6. In a second file `stack_utils.c`, add helpers: `stack_is_sorted(stack)` (1 for sorted, empty and one-node piles, 0 otherwise) and `find_min`/`find_max` (return the node with the smallest/largest index). Others will need all of these. There is no `stack_size` helper, because push and pop keep `size` up to date.

**Done when:** in a small test, you build a pile of 3 numbers, print them top to bottom, free it, and valgrind reports no leaks.

**Watch out:** forgetting to set `prev` pointers when pushing or popping — a broken `prev` chain will silently break rotations later. Test by walking both directions.

**Be able to explain:** why the top of the pile is the first node of the list, and what changes when you push or pop.

---

# Sheet 5: Swap and push moves

**Owner:** John
**Files:** `src/stack/ops_swap.c`, `src/stack/ops_push.c`

**Goal:** `sa sb ss pa pb`.

**Fits in the project:** these are the first moves the sorts will use. They are also what the program prints.

**Comes from:** #4 (piles), #3 (`emit`; until it exists, print with `write`).
**Leads to:** #7 and every sort.

**Build:**
1. `ops_swap.c` gets the silent core `swap_top(stack)` (a `t_stack *`): do nothing if the pile has fewer than 2 numbers, otherwise swap the top two. Update `prev` and `next` on both nodes (and the third node below, if it exists). All fields (`index`, `push_cost`, etc.) travel with the node.
2. Then the wrappers: `sa` swaps A, `sb` swaps B, and `ss` swaps both and prints once.
3. `ops_push.c` gets the silent core `push_top(from, to)` (both `t_stack *`): do nothing if `from` is empty, otherwise pop from one and push on the other. `stack_pop_top` and `stack_push_top` already keep `size` and `prev` correct.
4. Then the wrappers: `pa` moves B to A, `pb` moves A to B.
5. Each wrapper calls its core, then `emit(OP_..., context)`. If the move did nothing, don't emit. Tip: let the core return 1 if it changed something and 0 if not, so the wrapper knows.

**Done when:** with pile A as `2 1 3 6 5 8` (top first), `sa` gives `1 2 3 6 5 8`, and then `pb pb pb` leaves A as `6 5 8` and B as `3 2 1`. This matches page 13 of the subject.

**Watch out:** `ss` must print `ss`, not `sa` and `sb`. Keep `prev` pointers correct after every push — push is the operation most likely to break the doubly-linked chain.

**Be able to explain:** why `sa` and `sb` can share one core, and what `pb` does to both piles' `prev`/`next` chains.

---

# Sheet 6: `index.c` (ranks)

**Owner:** Nami
**Files:** `src/sort/index.c`

**Goal:** replace each value by its rank: the smallest number gets 0, the next 1, and so on up to n-1.

**Fits in the project:** every big sort works on ranks instead of raw values. Ranks are always 0 to n-1 with no gaps, and negatives stop being a problem. The Turk sort needs this, and chunks are easier with it.

**Comes from:** #4 (nodes with an `index` field), #9 (real input; until then build a pile by hand).
**Leads to:** #7, #12, #13, #17, #18.

**Build:**
1. A helper that counts how many nodes in the pile have a smaller value than a given node.
2. `assign_index(stack)`: for each node, store that count in its `index`.
3. It runs once, before any move. The index stays with the node as it moves between piles. The Turk fields (`push_cost`, `above_median`, `cheapest`, `target_node`) are set later by the sort, not here.

**Done when:**
- `5 -2 9` becomes the indexes `1 0 2`
- with 500 random numbers, each index from 0 to 499 appears exactly once

**Watch out:** the double loop is slow, but 500 numbers is fine. Don't change `value`.

**Be able to explain:** why ranks are easier to work with than raw values.

---

# Sheet 7: `sort_three`

**Owner:** John
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

**Owner:** Nami
**Files:** `src/stack/ops_rotate.c`, `src/stack/ops_rrotate.c`

**Goal:** `ra rb rr rra rrb rrr`.

**Fits in the project:** rotating is how the sorts bring a number to the top. It's the most used family of moves, and `rr` and `rrr` save moves because they do both piles at once.

**Comes from:** #4, #3.
**Leads to:** #7 and every sort.

**Build:**
1. Silent core `rotate_top(stack)`: the top node goes to the bottom. Do nothing if the pile has fewer than 2 numbers.
2. Wrappers `ra`, `rb`, and `rr` (rotates both, prints once).
3. Silent core `rrotate_top(stack)`: the bottom node goes to the top. With a doubly-linked list, the second-to-last node is `stack_last(stack)->prev` — no need to walk the whole list.
4. Wrappers `rra`, `rrb`, and `rrr` (prints once).

**Done when:** the whole example on page 13 of the subject matches, state by state:
- `sa`, then `pb pb pb`
- then `rr`: A is `5 8 6`, B is `2 1 3`
- then `rrr`: back to A `6 5 8`, B `3 2 1`
- then `sa`, then `pa pa pa`: A is `1 2 3 5 6 8`

**Watch out:** relink both `next` and `prev` pointers in the right order. The old bottom's `prev` must be cleared, and the new bottom's `next` must be cleared.

**Be able to explain:** why `rr` counts as 1 move, and how the doubly-linked list makes reverse rotation simpler than a singly-linked one.

---

# Sheet 9: `parse.c` (numbers and errors)

**Owner:** Nami
**Files:** `src/input/parse.c`, `src/input/error.c`

**Goal:** turn the number arguments into pile A, or print `Error` and stop.

**Fits in the project:** it's where all bad input is caught, so the sorts can trust that pile A holds valid, unique numbers.

**Comes from:** #4.
**Leads to:** #11 (`main`).

**Build:**
1. `parse_args(argc, argv, context)`: go through the arguments and skip any that start with `--`, because those are flags and belong to `flags.c`. The first number argument ends up on top of the pile.
2. For each number argument check three things: it's only an optional sign followed by digits (and not empty), it fits in an `int` (build it in a `long` and stop as soon as it's too big), and it's not already in the pile.
3. `error_exit(context)` in `error.c`: free both piles, write `Error` and a newline to stderr, exit. `flags.c` will call it too.
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

**Owner:** Nami
**Files:** `src/input/flags.c`

**Goal:** read the options and store them in `t_config`.

**Fits in the project:** this is the path every flag follows: flag, then config, then behavior. The live coding task will almost certainly start here.

**Comes from:** #2 (`t_config`), #9 (`error_exit`; use a temporary exit until it exists).
**Leads to:** #11 (`main` reads the config), #15 (bench flag), #17, #18, #19.

**Build:**
1. `parse_flags(argc, argv, context)`: set the defaults first (adaptive strategy, bench off).
2. Go through the arguments. If one starts with `--`, compare it with the known names: `--simple`, `--medium`, `--complex`, `--adaptive`, `--bench`. A `--` argument that isn't known is an error.
3. Each flag is its own `if` line that calls a tiny helper. Split into a strategy helper and an options helper so every function stays within 25 lines.
4. A small `is_flag(str)` helper that `parse.c` can also use.
5. If two strategy flags are given, decide which wins (for example, the last one) and write it in the README.

**Done when:** flags and numbers can appear in any order, `--bench` alone sets only the bench option, and a bad flag prints `Error`.

**Watch out:** `-5` has one dash, so it is a number. Don't store flag state in a global.

**Be able to explain:** the exact edits to add a new flag `--foo`. This is the one you must know cold.

---

# Sheet 11: `dispatch.c` and `main.c`

**Owner:** Nami (`main.c` together)
**Files:** `src/sort/dispatch.c`, `src/main.c`

**Goal:** make the whole program run from start to finish.

**Fits in the project:** `main` is the conductor and `dispatch` is the switchboard. After this part, both halves of the project meet for the first time.

**Comes from:** #4, #9, #10, #6.
**Leads to:** every sort (the dispatcher calls them), #15.

**Build:**
1. `run_strategy(context)`: if the pile has 0 or 1 numbers, or is already sorted, do nothing. Otherwise look at the configured strategy and call the matching sort. Adaptive calls the adaptive picker. Each strategy is one `if` line.
2. For now, use a placeholder for sorts that don't exist yet: a function that compiles and returns.
3. `main`: zero the context, read flags, read the numbers, return quietly if there are none, measure the disorder (placeholder 0 until #14), assign the ranks, call `run_strategy`, print the bench report if asked, free everything.

**Done when:** the program parses, dispatches and frees without leaks, and the error cases behave correctly. The sort itself can still be fake.

**Watch out:** the disorder must be measured before any move. Free both piles on every path.

**Be able to explain:** the order of the steps in `main`, and which file you'd change to add a new strategy.

---

# Sheet 12: `sort_five` (sorting 2 to 5 numbers)

**Owner:** John
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

# Sheet 13: Turk sort (the complex strategy)

**Owner:** John
**Files:** `src/sort/sort_complex.c`

**Goal:** sort any size with roughly n log n moves.

**Fits in the project:** this is your first big sort and the milestone of the project. After it, you have a real working program. It's also the high-disorder method in the adaptive picker.

**Comes from:** #3, #5, #6, #8.
**Leads to:** #19.

**Build:**
1. Push the first two numbers from A to B.
2. **Set targets:** for each node in A, find its `target_node` in B — the node in B where this value should land next to (the closest smaller rank in B; if none, the node with the largest rank).
3. **Set costs:** for each node in A, set `above_median` (is it in the top half of A?), then compute `push_cost` — how many rotations of A and B it takes to bring this node and its target to their tops, counting `rr`/`rrr` as single moves when both rotate the same way.
4. **Mark cheapest:** set the `cheapest` flag on the node in A with the lowest `push_cost`.
5. **Execute:** move the cheapest node — rotate A and B (using `rr`/`rrr` where both go the same direction), then `pb`. Repeat from step 2 until 3 nodes remain in A.
6. Sort the remaining 3 with `sort_three`.
7. **Push back:** for each node in B, find its target in A (the closest larger rank; if none, the node with the smallest rank), rotate A to bring the target to the top, then `pa`. Finally rotate A so the smallest is on top.

**Done when:** `--complex` sorts 100 and 500 random numbers (check with the test scripts). Turk typically gets under 700 for 100 numbers and under 5500 for 500. Write down your real counts and tune.

**Watch out:** use ranks, not raw values. The cost calculation is the trickiest part — get the combined rotation logic (`rr`/`rrr`) right. Stay under 5 variables per function by splitting the cost calculation, the move execution and the final rotation into separate helpers.

**Be able to explain:** why the greedy cheapest-move approach works, how combined rotations save moves, and why the move count grows roughly like n log n.

---

# Sheet 14: `disorder.c`

**Owner:** Nami
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

**Owner:** Nami
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

**Owner:** Nami
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

**Owner:** John
**Files:** `src/sort/sort_simple.c`

**Goal:** the O(n²) strategy, behind `--simple`.

**Fits in the project:** it's one of the four required strategies. It's also the method you already invented by hand with 5 numbers, so it's the same idea John already used in sort_five, scaled up to any size.

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

**Owner:** John
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

**Owner:** John
**Files:** `src/sort/sort_adaptive.c`

**Goal:** choose the method based on how messy the input is.

**Fits in the project:** it's the default mode, and it's what the evaluators will run most. The README must explain its thresholds.

**Comes from:** #13, #14, #17, #18, #11 (`main` measures the disorder).
**Leads to:** #15 (report shows the chosen class), #20.

**Build:**
1. Read the disorder that `main` stored (before any move).
2. Under 0.2 (stored as 2000): use an O(n²) method. From 0.2 up to 0.5 (2000 to 4999): the chunk sort. At 0.5 or more (5000+): Turk.
3. Save which class was used in the stats so `--bench` can print `Adaptive / <class>`.
4. The subject only fixes the complexity per regime, so inside each regime the internals are yours. For example, a nearly sorted input could use a smarter method than the plain simple sort.
5. Decide how tiny inputs (2 to 5 numbers) are handled, and write it down.

**Done when:** the default mode picks a different regime for a nearly sorted list, a medium mess and a random list, and `--bench` shows which one.

**Watch out:** a random list has disorder around 50%, so it lands in the Turk regime. Turk should already hit the "good" tier or better for 500 numbers. Tuning the cost calculation and combined rotations can push it toward "excellent".

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

**Owner:** Together
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

Then invent surprise flags for each other and time those too.

**Done when:** you can add each of the three flags in under 5 minutes without looking at notes.

**Be able to explain:** the path of a flag from the command line to its effect.

---

# Sheet 22: The bonus `checker`

**Owner:** Nami
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

---

# Timetable (31.10. – 14.11.)

Five phases across 14 days. Each phase has a hard end date — if a sheet isn't done by then, flag it and move on so the next phase doesn't slip.

## Phase 1 — Foundations (Nov 1–3)

| Sheet | Owner | Deadline |
| --- | --- | --- |
| 7 sort_three | John | Nov 1 (in progress) |
| 8 Rotate moves | Nami | Nov 2 |
| 9 parse.c | Nami | Nov 3 |
| 10 flags.c | Nami | Nov 3 |

Both start in parallel. No dependencies between these. By end of Nov 3, the full move set, input handling and first sort are done.

## Phase 2 — Wire it up (Nov 4–6)

| Sheet | Owner | Deadline |
| --- | --- | --- |
| 11 dispatch + main.c | Nami | Nov 4 |
| 12 sort_five | John | Nov 6 |
| 14 disorder.c | Nami | Nov 5 |

**Sync point on Nov 4:** sit together briefly to merge main.c (parser + flags + dispatch). After that, both go independent again. John builds sort_five while Nami finishes disorder.

## Phase 3 — Big sorts (Nov 7–10)

| Sheet | Owner | Deadline |
| --- | --- | --- |
| 13 Turk sort (complex) | John | Nov 10 |
| 15 bench.c | Nami | Nov 8 |
| 16 Test scripts | Nami | Nov 9 |

The heaviest phase. John has 4 days for the Turk algorithm — the biggest single piece. Nami builds bench first (so both can verify move counts), then the test scripts.

## Phase 4 — Remaining strategies + adaptive (Nov 11–12)

| Sheet | Owner | Deadline |
| --- | --- | --- |
| 17 Simple sort | John | Nov 11 |
| 18 Medium sort (chunks) | John | Nov 12 |
| 19 Adaptive picker | John | Nov 12 |

John builds the two remaining strategies and the adaptive picker that ties them together. He already has sort_five's helpers and the Turk sort done, so simple and medium build on that foundation.

## Phase 5 — Polish + drill (Nov 13–14)

| Sheet | Owner | Deadline |
| --- | --- | --- |
| 20 README, leaks, norm | Together | Nov 13 |
| 21 Flag drill | Together | Nov 14 |
| 22 Bonus checker | Nami | Nov 14 |

**Sync point on Nov 13:** final review together — norminette, valgrind, edge cases. Then Nami finishes the bonus checker on Nov 14 while both practise the flag drill together.

---

# Dependencies and sync points

Most work is independent. These are the only places where one person blocks the other or you need to meet:

1. **Nov 4 — merge main.c.** Nami's parser (9) + Nami's flags (10) meet in main. Sit together for 30 minutes, wire them up, make sure `make` builds and the error paths work. After this, both go back to independent work.
2. **John needs sort_five helpers for sheets 17 and 18.** John finishes sort_five (12) by Nov 6 and reuses those helpers in sheets 17 and 18. No dependency on Nami here — John owns the whole sort chain.
3. **Nami needs a working program before test scripts (16).** dispatch + main (11) should be done Nov 4 with placeholder sorts. That's enough for the test scripts to run against.
4. **Adaptive (19) needs all three sorts done.** John writes all three sorts and the adaptive picker himself, so no cross-dependency here — just his own sequencing.
5. **Nov 13 — final review together.** Norminette, valgrind, edge cases, README. Plan 2–3 hours.

If anything is running late, tell the other person by the phase deadline — not the project deadline. A phase that slips 1 day is fine; 3 days means the plan needs adjusting.
