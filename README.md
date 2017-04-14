
# Mandelbrot

This repository contains a code that calculates
a [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) --
which is interesting mathematically, and pretty to look at.

After compiling and running the code, it produces a data file called
`mandelbrot.asc`. There's a script included that can be used with
gnuplot to convert those data into an image:
```sh
$ gnuplot mandelbrot.gpl
```

will generate the image `mandelbrot.png`:

![Mandelbrot](mandelbrot.png)

(Or you can use your own favorite plotting tool -- the data is in
ASCII format.)

## Assignment

* Add timing code, so that you can measure how long the actual
  calculation of the Mandelbrot set takes (as opposed to writing the
  calculated data to the file). If you don't get repeatable numbers,
  you may have to choose a larger resolution (change `MX` and `MY`). 
  
* If you double the resolution in both x and y direction, how much
  slower to you expect the calculation to run? Try it out, present
  your results, and discuss.
  
* Parallelize the code using OpenMP. We have only learned out to
  parallelize one loop at a time in a situation where there are nested
  loops, so you're limited to doing that. Which loops are good / not
  so good candidates for parallelization?
  
  Make sure that the code still works correctly after parallelization.
  
  Note; "nested loops" is the situation where one is nested within
  another (hence the name), e.g.:
  ```c
  for (int iy = 0; iy < MY; iy++) {
    for (int ix = 0; ix < MX; ix++) {
	  // ...
    }
  }
  ```
  If you're interested in how to parallelize both loops at the same
  time, you can google "openmp for collapse".
  
* Perform a scaling study of your parallelized code. You should go up
  from 1 to 8 threads, and in order to get meaningful results, you'll
  need a machine that has at least 8 cores, which might mean that you
  have to run on fishercat (you can still do the development on your
  local machine, then, once things are working, commit and push to
  your github repo, then clone, compile and run on fishercat).
  
  Present a plot with the scaling results, and compare to what you'd
  expect for perfect scalability. Discuss -- in particular, can you
  explain the reason why your results deviate from perfect
  scalability?
  
* This assignment requires some amount of coding, but also making
  plots and explaining results. The coding part obviously should be
  checked into git. For the rest, you can either include the written
  parts and plots in the repo (e.g., by editing this README file), or
  you can do the discussion in your pull request on github, which will
  allow you to include images as well. It is quite feasible for you to
  open the pull request early and then add comments to it addressing
  the steps laid out above. Once you're ready for submission of your
  work, request me as reviewer.
  
  
