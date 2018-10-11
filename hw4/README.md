# CS 104 Student Repository

- **Name**: Julia Wisnia
- **USC ID**: 2096592657
- **Email**: wisnia@usc.edu

In order to implement Scrabble, I used a 2D vector implementation.  The program
is not complete, and when I try to exchange tiles is does not print the hand
correctly, and causes a seg-fault.  In all of my error checking, the user is
required to re-enter the whole part of the command except what move they are
making, because they cannot change what they are doing.

The bulk of this assignment is in my board.  This is where the PlaceMove
is mostly implemented.  Each of the move's execute functions only call their
specific validity checkers, and then calls execute of their own.  For place
move, it calls the execute function on the board, and then changes the player's
hand.  This also happens in ExchangeMove.

In order to implement this, I friended all three move classes from player so 
that it could have access to its members, and perform the bulk of the work.