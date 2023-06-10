EURO ELEVATOR Simulator
___________________________________________________________

This is indended to be a clicker type video game with classic look and feel resembling Pong. Gameplay would focus on managing elevators, that carry virtual passengers back and forth. 
Player would recieve points based on number and satisfaction of the passengers and then be able to use it for upgrading elevators (or increasing their number).

It is currently under development.

The game is implemented using my own GuI engine based on OpenGL and Winx library (tha latter one for easy window opening and handling).
At some point I am planning to release it as a separate library. Probably DLL.


Progress
________________________________

Currently only sandbox mode is implemented in the game.
It enables the player to play with any number of elevators and infinite number of floors.
Passengers can be created by the player, instead of being randomly generated.
All elevators are maxed up with maximum speed and intelligence.

Campaign Mode is to be developed, when player would start with one elevator with no logic at all (it would need to be manually sent to floors to take passengers).
Passengers will be generated randomly. For transporting them player will recieve points allowing to upgrade the elevator. Player will also recieve minus points if a passenger waits too long for an elevator.
Upgrades would include: more elevators, faster elevators, elevator logic (so no manual clicking will be necesarry after a while).


Sandbox Mode Controls
_______________________________

By clicking on an elevator, typing the floor number and pressing enter (or clicking the downward-pointing arrow), you can send a specific elevator to a specific floor.

By clicking on the arrows in upper right corner of the screen, you can call an elevator to a specific floor. Game logic will determine which elevator is the most optimal. Clicking the arrow pointing upwards will indicate you intend to go up from the chosen floor. Clicking the arrow pointing downwards will indicate you intend to go down. Game engine will optimize based on this as well.

By clicking on ,,Create Passenger" button you can add a new passenger and tell him where (and from where) he is supposed to go. He will automatically call an elevator and after boarding it, send it to the destination floor.


Campaign Mode Controls
_______________________________

To be implemented in the future.


Final notes
_______________________________

All textures in the game are made by me, except for the font. 
Special thanks to https://github.com/magistermaks for Winx library. It is truly a masterpiece. 
