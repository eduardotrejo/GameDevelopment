#Invader

<p>Implements a simplified invader game. In the game, there are two invaders at the level 1 and four invaders at the level 2. And also, there’s one barricade to protect the defender. The barricade will not be broken by the defender’s weapon, while it can be broken and disappear from the invaders’ weapon.</p>

<b>Initial Screen</b>
<p>Note that there are two imaginary front lines. At the beginning, the invaders are behind the front line 1 and move to right. When they reach to the right boundary, they come closer to the defender (= between front line 1 and 2) and keep moving to the left side. If they reach to the left boundary again, you lose the game.</p>
<p>However, if you break the two invaders before reaching the left boundary, you will move to the level 2. </p>
<p align="center">
<img src="https://github.com/eduardotrejo/GameDevelopment/blob/master/Invader/invader.png>
</p>

<b>Ongoing game</b>
<p>During the game, the defender can shoot its missile. If the defender breaks all three invaders at the level 2, you win the game. Meanwhile, the invaders can shoot their missiles as well. Note that there only one defender in the game. If invader’s missile hits the defender before the end of level 2, you lose the game. To make the game simple, the defender can’t shoot maximum three missiles at a single screen. However, the invaders can have only one missile per invader.</p>

<b>End of game</b>
* Win
* Lose
