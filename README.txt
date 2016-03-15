I started with a minimax algorithm using a heuristic function which assigned
varying scores to different squares, with corners being weighted the highest.
I then changed the minimax part to alpha-beta pruning, which allowed me to check
the game tree to greater depths. 

I spent a lot of time trying to pick a better heuristic function. Picking what
to optimize for is one of the trickiest parts of othello becuase one's "lead" over
the opponent could be reversed in one move, so it's unclear that this is a good
metric for success. I tried to optimize for things like coin stability: having
coins whose value could not be flipped; as well as mobility: having a large 
number of options for moves, while keeping the opponents number of moves small.

However, I found that these methods were computationally intensive, and it took me
too much time to implement them. Eventually, I ended up using a monte carlo approach
where I simulated random games from a given configuration as a way of determining it's 
desirablity.

This might help me win because my AI optimizes for things like stability and mobility,
which means it keeps a very small group of coins as it slowly moves towards the edges
and corners. Player who have niave evaluation functions may be tricked into thinking that
they are doing well, but will succumb to the Loser Machine.
