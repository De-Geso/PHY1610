The problem could be solved analytically, but I thought that the point of the
assignment was to stay away from that. In this spirit, I used Runge-Kutte 4 with
constant step size to integrate the ODEs for the x and y position of the ball.
I then used a golden section search to find the maximum range of the ball.

I am running Fedora 39, and used "g++ -std=c++17 assignment1.cpp" to compile the
program, and "./a.out" to run it. I tested it with reasonably small velocities
on the order of 1~100. For larger velocities, the time step may need to be
adjusted for good performance.

I'm a little bit disappointed in the precision of the program, but if the time
step is made too small then it takes too long to run. It could probably be
greatly improved if I implemented some adaptive time step for RK4,or used a
fancier integrating scheme. I also probably should have put the golden section
search in a function of its own.
