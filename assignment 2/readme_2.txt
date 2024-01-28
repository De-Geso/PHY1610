The original game of life code has been modularized. initlife now holds constants
and initialization functions. updatelife now holds update steps in order to update
the state of the system. outputlife now holds outputs for the game of life.

I am running Fedora 39. Compile everything by using the makefile. Compilation details
are in the makefile. I'm handing in a .tar.gz, which I hope is approximately the
same as a .tar.

I think I successfully modularized everything to an appropriate degree. I had some
confusion on how to declare and pass around the "cell" variable because it was a
smart pointer. I settled on making the variable in main, then passing it by reference
to whatever function needed it. I'm not sure if that's the best way to do things,
but it seemed to work. For the evolution loop, I think it's modular enough, but
maybe I should have put "newcell" into the updatelife module as well.
