# Project Proposal - puzzle battle

## Summary

My project will be a puzzle game where players compete with each other to see 
who can get the most points in a certain amount of turns. The players play on
a 6 x 6 board. Players earn points by erasing orbs. Orbs are erased when 3 or 
more of the same color are touching. Each orb erased grants 1 point each. If 
the player gets more than 6 matches, their points for that turn are multiplied 
by 1.5. Players play a turn by selecting an orb and dragging it; when the orb 
passes over another orb, they swap places. When the player releases the orb, 
their turn is over. At the end of all the turns, if the players are tied, the 
game goes on until one player has more points at the end of the turn. At the 
end of the game, the player with the most points is the winner.

## Development Checklist

### Core Goals
- [x] Set up libraries
- [ ] Gamestates (player 1 turn, player 2 turn, game over, menu, etc.)
	- [ ] detect winner
	- [ ] board 
- [ ] Playing turn
	- [ ] detect picking up starting orb
	- [ ] drag orbs
	- [ ] track orb position/swap orbs
- [ ] Analyze board
	- [ ] detect matches
	- [ ] count orbs in match
	- [ ] calculate points
- [ ] Graphics
	- [ ] orb movement animations
	- [ ] orb graphics
- [ ] networking
	- [ ] animate other player's movements
	- [ ] send over score info
- [ ] GUI
	- [ ] game settings
	- [ ] buttons (start game, etc.)

### Stretch Goals
- [ ] detect matches from orbs falling
- [ ] allow for more than 2 players
- [ ] improve/add more graphics
- [ ] add sounds

## Resources

- Libraries
	- GUI
		- [ofxGUI](https://openframeworks.cc/documentation/ofxGui/)
	- Networking
		- [ofxNetwork](https://openframeworks.cc/documentation/ofxNetwork/)
	- Graphics
		- [open frameworks graphics module](https://openframeworks.cc/documentation/graphics/)