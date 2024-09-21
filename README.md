# The Project 
A long time ago I 3d printed a few parts for a quadraped. I never finished the project.

Until now... if now is sometime in the future. I mean let's finish it!

# Things we probably need to do
1. ~~Create a repo to track the work~~
1. ~~Build a development environment~~
1. Write some code (tm)
    1. Set the CPU clock
    1. PWM using Timer_A (probably) & built-in DCO
    1. 74HC595 serialization
    1. Distributing 74HC595 at PWM resolution for all 8x servos
1. Test that code
    1. Use DSO for analysis
1. Design new boards? Maybe?
1. Move the code to the final boards
1. Battery-ize the whole thing

# The Development Environment
We'll be using a stock VM published in hashicorp, like Ubuntu, built and configured using vagrant & maybe ansible. If I recall correctly this VM really just needs to have:
- build-essential
- gcc-msp430 (or something like this)
- mspdebug for programming the dev boards

We'll be using Virtual Box & passing an MSP430 launchpad through to it via USB.

We'll need to test the build toolchain too. Probably with the typically blinky lights built onto the dev boards. Though an interesting thing I was thinking about earlier too is that we could do some types of tests using the built-in simulator too. Could be good for building tests like ensuring the watchdog timer is correctly disabled on a project, or that a specific function is executing within a set number of cycles. This would make the process of deving for a project more CI/CD like giving us software verification prior to cutting anything on actual hardware. Food for thought.

## Building with msp430-gcc
To generate an ELF from source do the following:

```bash
cd /src
msp430-gcc -ggdb -mmcu=msp430g2553 main.c
```
To program this binary to the target board first pass the USB device to the VM and then use mspdebug:
```bash
cd /src
printf "prog a.out\nexit\n" |  sudo mspdebug rf2500
```
**TODO:** I think mspdebug can be run without sudo if the user is in the correct group.