# push_swap
push_swap is a 42 curriculum project with the goal to sort a stack, with restricted instructions, in the least instructions possible and with only one other stack.

## Instructions
- `sa`: swap a - swap the first 2 elements at the top of stack a. Do nothing if there is only one or no elements).
- `sb`: swap b - swap the first 2 elements at the top of stack b. Do nothing if there is only one or no elements).
- `ss`: `sa` and `sb` at the same time.
- `pa`: push a - take the first element at the top of b and put it at the top of a. Do nothing if b is empty.
- `pb`: push b - take the first element at the top of a and put it at the top of b. Do nothing if a is empty.
- `ra`: rotate a - shift up all elements of stack a by 1. The first element becomes the last one.
- `rb`: rotate b - shift up all elements of stack b by 1. The first element becomes the last one.
- `rr`: `ra` and `rb` at the same time.
- `rra`: reverse rotate a - shift down all elements of stack a by 1. The last element becomes the first one.
- `rrb`: reverse rotate b - shift down all elements of stack b by 1. The last element becomes the first one.
- `rrr`: `rra` and `rrb` at the same time.

## Arguments
The program must accept a list of signed integers, with no duplicates. The arguments towards the left will be towards the front/top of the stack, and the arguments towards the right will be towards the back/bottom of the stack.
Some examples of valid arguments:

`./push_swap 3 2 1 0`

`./push_swap 1`

`./push_swap -5 -2 3`

For the bonus, you had to make a checker which would read from standard input the instructions and took as arguments the same as the push_swap program. It's usage:

`./push_swap 3 2 1 0 | ./checker 3 2 1 0`

`./push_swap 1 | ./checker 1`

`./push_swap -5 -2 3 | ./checker -5 -2 3`

It would print out one of the following:
- "OK" If the instructions sorted stack A
- "KO" If the instructions didn't sort stack A
- "Error" If wrong arguments were given, an unkown instruction was used or if something else went wrong like `malloc` or `read`

# My goals
For this project, I wanted to make a pretty fast solver, fast as in less instructions, not as in execution time. I also wanted to focus more on how readable my code is for others. Lastly I wanted to make my code modular, so that I can more easily change a system if I wanted.

# My approach
I already quickly realized that instructions such as `ss`, `rr` and `rrr` would become very important in ensuring less instruction count. With this in mind, I created my first version of the solver which would evaluate for each number in stack a how many instructions it would take to put it into the right position in B. I would keep the "closest" number and put that at the right spot and start over again. At the end I would put everything back in stack A. This already created a pretty fast solver. It would take on average about 5500 instructions to sort a shuffled list of 500 numbers. However, while it was quite fast for large lists of numbers, this on its was terrible at sorting small lists (0~8 numbers). I already chose at this point to add a brute forcer to try up to ~6 instructions to see if it could find a solution. If it couldn't it would go to the other algorithm

While I was quite happy with 5500 instructions for ~500 numbers, I wanted to make it faster. In an article by a fellow 42 student I read that partioning the stack into smaller stacks helps with the speed. In this method you, for example for 500 numbers, first dump the numbers 0-100 into stack B, then 101-200, then 201-300 etc. Until you have all the numbers partioned in stack B. Now you use the same algorithm as in the paragraph above to push the numbers back to stack A instead of to B. This would avoid a lot of jumping around placing the next number at the right spot. When I implemented this my average instruction count for 500 numbers went to ~4500.

# Results
Average instruction count for range of numbers (tested on 2000 random lists of numbers):
|Number count|Average instructions|
|---|---|
|3|1.1715|
|4|2.9695|
|5|5.646|
|6|14.4075|
|7|21.3375|
|8|25.9315|
|9|29.9795|
|10|34.22|
|20|73.7255|
|50|249.1315|
|100|587.1415|
|200|1399.59|
|300|2345.059|
|400|3388.5575|
|500|4545.255|

# Can it go faster?
If I gave myself more time I think I could've made it faster by applying the following:
- Keeping the longest sorted series in stack A
- Optimizing afterwards. Some combinations of instructions can be replaced by one `ss`
- Evaluating multiple layers deep. Like a chess AI, looking deeper to check if a move that on first sight doesn't seem so good, might pay off more in the end.

# My takeaways
I wanted to make my code look more readable and modular for this project. And while I'm pretty proud of some pieces of code, I'm still not so happy of the others (quick_solver*.c sorter*.c). If I would do this project again I definitely would want to spend more time on those making it more clear. I'd like to think that I learned at least a bit how to make my code look cleaner in the next project.

Unit testing seems like a really smart idea. I've spent way more time than I wanted on debugging some very silly bugs, which could've easily been spotted I think if I had made unit tests for them. I'm definitely planning on using unit tests in my next projects.