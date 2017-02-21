#Battleship

<p>Battleship is played on a 10x10 grid which is stored internally as a 2-dimensional array.The user can enter a location using two integers (row and column) separated by a space. The user can enter 0-9 (you can assume they know that arrays in CS Battleship start at 0)
The board once at the beginning and after each guess. At the beginning of the game, the board should be all Os.</p>

<p align="center">
<img src=""/>
</p>
* Each hit should be marked by an '*'
* Each miss should be marked by an 'X'
* Prints an error message if the user double-guesses a spot
* Prints an error message if the user guesses a spot with invalid indexes

<b>The boats</b>
<p>The program has a global constant BOATS that holds the number of boats on the board.Each boat takes up two consecutive spaces on the board (up, down, right or left).</p>

<b>Winning</b>
<p>The player wins when they sink all of the battleships and displays how many turns it took to accomplish.</p>
