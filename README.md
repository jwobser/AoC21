# AoC21
Advent of Code 2021

I will be trying to hone my programming skill by working through the advent of code challenges. Sometimes I will shoe-horn in a concept, even if it isn't the most efficient way.


## Day 1
### Part 1
This one was pretty straight forward: ingest the 2000 depth readings and count how many are deeper than the previous.
### Part 2
For part 2, a boxcar filter was applied to the depth readings. Then the windows were compared to see if they were deeper. In order to prevent seeking all over the file, a circular buffer was used to keep track of the readings. The oldest value was subtracted out from the sum, then the new value overwrites it and is added to the sum. 

## Day 2
### Part 1
Another pretty straight forward one. Read the direction and magnitude, then increment a sum for the depth or distance.
### Part 2
A minor tweak to part 1. Rather than translate up/down, the submarine points itself up/down, then moves horizontally and vertically at the same time.

## Day 3
### Part 1
This was a fun one, and allowed me to learn about `std::bitset<int>` for managing binary numbers.
### Part 2
This part involved filtering the list. In order to make more efficient removal, a linked list was used. A `forward_list` could not be used becuase it has no emplace_front method(), so the list ended up in reverse order when read in from the file. A possible solution could be to read the file in backwards.
  
Additionally, I believe the node is freed when removed. This necessitates reading the file in twice: once for the oxygen system status, then again for the CO2 scrubber. It might be possible to subclass `list` to keep the original next/prev node pointers and provide a restore function.
  
## Day 4
### Part 1
Another fun one! Having multiple bingo boards felt like an obvious use case for OOP. Structured the class with some private methods that the user would never need to call (e.g. checking just the rows or just the columns), as well as the board numbers and whether or not they have been drawn.
### Part 2
Borrowed an idea from Day 3, and made a forward list of all the boards that had not won yet. As numbers are drawn and boards win, they get removed from the list. This means checking for winners gets faster towards the end, as fewer and fewer boards are in play.

## Day 5
### Part 1
First test to see if it's diagonal, and if it is skip it.
The just update an array with how many times a line has been drawn over a pixel.
### Part 2
Adding the diagonals wasn't too hard.


## Day 6
### Part 1
Vectors! I still want to go back and benchmark my original brute force implementation, which tracked each fish individually, decrementing their counters and appending lanternfish to the vector as they were born. Despite being brute force, I honestly didn't notice how slow it was. I wonder how much slower it would have been in Python for example.
### Part 2
Linux killed the logic bomb I had written after about 5minutes and 11GB of memory usage.
Then I implemented two circular buffers; one to track the newborns, and another to track the adults. The only write to the adult buffer is when the newborns grow up, so it's very fast! Definitely want to compare this to the brute force method.

## Day 7
### Part 1
"Oh, this will be easy. Just average their position!"
I still need to do some googling to see if their is an efficient algorithm to calculate this.
I also terminate early, but I think if the distribution was bimodal there could probably a local minimum that would hang up my logic.
### Part 2
A little scribbling on paper yielded a formula for the sum of first n numbers. Then it was trivial to add this fuel cost function to the existing search code.


## Day 8
### Part 1
Switched to python becuase I didn't want to write a big old parser in Cpp.
The problem practically gave you the logic for part 1 of this problem. Just look for characters in the output with a specific number of segments.
### Part 2
This took a little bit of time to work out logically. Once I had the seven segment sodoku figured out, I just had to string together the logic so that it would look at each line, determine which digits where which, then sum the output. I didn't actually determine the output/display matchup, but it would be pretty straight foward from here.


## Day 9
### Part 1
Off by one errors really bit me here. Rather than providing a generalized function to check the whole field, I wrote ones to check the edges, the corners, and finally the main field.

I also realized that the field could be checked completely independently, so I wanted to try some `async` programming. Definitely want to come back and check out how much faster this is than a single threaded version.

I also used a mutex to control access to the vector listing all the minimum points, as well as an atomic long to keep track of the risk level. 
### Part 2


## Day 10
For this one I used some unit testing to make sure the scoring and detection functions were working correctly. It also forced me to do more separation of concerns to make the functions unit-testable.
### Part 1
I set this up with a stack to track which chunks have been opened. If an opening character is detected, a new chuck is added to the stack. If not, it is assumed to be a closing character and is compared against the stack. If they do not match, this is a corrupted line.
### Part 2
Due to setting up the stack from part 1, this one was pretty straight forward. Just look at all the remaining unclosed chunks and score them.
