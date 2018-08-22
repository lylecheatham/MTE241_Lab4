# MTE241 Lab 4

This project was created for Lab Number 4 of MTE241 - Introduction to Computer Structures & Real-Time Systems

Creating a game to run on an LPC1768 dev board, which as an LCD screen, a joystick, 8 user-controlled LEDs and a button.

[Specification Document (written for pandoc formatting, not github formatting)](specification/specification.md)

[Specification Document (PDF)](specification/specification.pdf)

# Building

The project is meant to be built in Keil uVision 4.

However, because I was more comfortable developing on my own computer, I set up
a basic makefile that allowed for remote development.

The makefile can check for obvious compilation errors using `clang
-fsyntax-only` and also format the code using `clang-format`.

The commands to do that are `make check` and `make format`.

## Things We Would Change

This project has been left in it's 'as turned in' form, but there are
definitely some things that we would have changed if we did it again.

1.  First, the display had many tearing problems because of the way that the
    updating was done. It's definitely an area that could be improved. One easy
    solution would be to double buffer the screen, maybe only tracking the
    deltas (i.e. only update the pixels that change colors). Another approach
    would be to make all of the sprites larger than they actually are, with
    black space all around them.  This way it would effectively erase where it
    previously was when being updated.

2.  The file organization was sub-optimal. We aimed to have each task have it's
    own folder, but of course the game-loop task was the bulk of the code, and
    therefore became a disorganized sprawl very fast. I no longer think it
    makes sense to organize by task in an embedded system.

3.  It would have been nice for the game to get harder instead of just ending.
    We did not have time to give the game a proper ending screen if the player
    destroyed all of the enemy ships. Ideally, it would put the player on a new
    level with harder (either faster moving or faster shooting) ships.
