Submission for assignment 9: Distributed Random Numbers.
Mostly followed the instructions. I don't think I implemented the batching as described. In the assignment we want to trade numbers all over the place.
Instead, I did a batch and generated histograms, then recombined the histograms. This seemed a lot simpler, and probably faster because I think I'm
trading memory fewer times.

I'm not sure if it's expected. As I increase the number of processes past 16, the runtime jumps longer then starts decreasing again. The problem is that
user time goes from a few seconds to a couple minutes. I think this indicates that I either messed something up with SLURM, or in my implementation.
Passing things around too much?

teachsetup should hold the modules needed to run on Teach.
jobscript.sh should tell Teach to load the modules.
