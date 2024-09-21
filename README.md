# The Project 
A long time ago I 3d printed a few parts for a quadraped. I never finished the project.

Until now... if now is sometime in the future. I mean let's finish it!

# Things we probably need to do
1. ~~Create a repo to track the work~~
1. Build a development environment
1. Write some code (tm)
1. Test that code
1. Design new boards? Maybe?
1. Move the code to the final boards

# The Development Environment
We'll be using a stock VM published in hashicorp, like Ubuntu, built and configured using vagrant & maybe ansible. If I recall correctly this VM really just needs to have:
- build-essential
- gcc-msp430 (or something like this)
- mspdebug for programming the dev boards

We'll be using Virtual Box & passing an MSP430 launchpad through to it via USB.

We'll need to test the build toolchain too. Probably with the typically blinky lights built onto the dev boards. Though an interesting thing I was thinking about earlier too is that we could do some types of tests using the built-in simulator too. Could be good for building tests like ensuring the watchdog timer is correctly disabled on a project, or that a specific function is executing within a set number of cycles. This would make the process of deving for a project more CI/CD like giving us software verification prior to cutting anything on actual hardware. Food for thought.
