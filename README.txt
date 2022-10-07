Name: Kandarp Solanki
Roll No. : 210260026
Topic : CS101-Project-Bubble_Trouble

The following features were implemented in the project to make it functional:





1. bubble.h

~ The parabolic trajectory of the bubbles was introduced by manipulating the velocity of the bubbles after each STEP_TIME by adding an additional factor of (acceleration x time) to the velocity.

~ The new y-position of bubble was determined by using the "Newton's Laws of Motion" ; S = ut + 0.5at^2

~ The bubble movement was confined along the y-coordinates between the floor (blue line) and 40 px below the top-margin.





2. shooter.h

~ A new 'if condition' was added to check if the shooter was in contact with any of the existing bubbles and thus change the colour when the bubble collides or else keep the default colour. This was made possible using the boolean value of the function (bubble_contact).





3. bullet.h

~ No Changes





4. main.cpp

The following functions are mentioned in the order of their appearance in the code.

~ A void function named 'create_bubbles_small' was created with parameters as the vector bubbles, x_pos(x-position), y_pos(y-position), radius(radius of the bubble), lev_num(level number) to create smaller bubbles.


The level number was used to randomise the color of bubbles.


This function creates two bubbles splitting from the main bubble and moving in opposite directions and starting with a default y-velocity of 100px/STEP_TIME.


~ An int function named 'collide_bullets_bubbles' was created to check the collision between all the pairs of bubbles and bullets.


The way it works is that it checks the distance between centres of each pair of bubbles and bullets and if it is lesser than a certain value (dependent on radius of bubble) it collides and the function moves ahead.


It checks if the bubble radius is greater than threshold radius and if that returns to be 'true' it splits the bubbles and destroys the old bubble and the bullet and if 'false' it just destroys the bullet and bubble without splitting.


~ A function with vector type return named 'create_bubbles' which was already present and was modified by adding a parameter of level number.


This was done so as to ensure that when new level comes the color of bubbles change and also to randomise the bubble speed.


To move half of bubbles in one direction and half in other a variable 'j' was used.


~ A Boolean function named 'shooter_dead' was used to check whether the shooter is in the contact with any of the bubbles of the existing bubbles on screen and returns a bool value 'True' if yes and 'False' if no.


The parameters passed in this function are the 'vector-bubbles' and 'Shooter class - shooter'.


~ std::stringstream & std:: string was used to convert a number to a string.


~ Some basic variables like timer (in milliseconds), level_num (Level No.), health_left (Health Left), score (Score Counter) were created.


~ Two lines were created making the lower and upper bounds of the game area (represented by blue lines).


~ Some basic variables as mentioned earlier were stored in a variable 'temp' and then it was transferred to temp2 and utilised as a string to print it on the screen. The statement temp.clear() was used to flush out all the stuff from temp variable before entering any new information.


~ Initialisation of 'shooter', 'bubbles', 'bullets' & Xevent 'event'.


~ The main game loop starts with a 'while' loop which basically checks if time is left AND health_left is greater than zero, then only the user is allowed to enter the loop and play the game. Else, it quits and completes the other formalities (as mentioned later).


~ Inside the 'while' Loop
	
	Once the bool value is checked before movement of bubble using 'bool check_before' whether it is in contact with shooter or not using shooter_dead function and once after movement using using 'bool check_after'.

The health is reduced only and only if the bool was before movement 'false' and after movement was 'true' i.e when it was approaching i.e it reduces redundancy of bubble hitting the shooter.

	It checks the pending events and does it as usual given in the starter_code. Just that I have added the status of shooter_dead as 'True' or 'False' to change/retain the color of shooter to give a realistic look of collision of bubble to shooter.

~ If all bubbles vanish i.e level is finished, do the following things:

	- Clear all bullets
	- Increment level_num
	- Give a pop-up on screen for next level for 2 secs.
	- Create next level bubbles
	- Increment timer speed so as to match with more elements on screen

~ Move the bubbles & bullets using move_bubbles() and move_bullets() functions respectively passing the parameter as vector bubbles and bullets respectively.

~ Decrease 'health' if it satisfies the condition as mentioned earlier.

~ Wait for STEP_TIME.
	
~ End the game by writing either 'You ran out of lifes!' if health = 0 or 'You ran out of time!' if timer goes to zero.

Wait for the user to read and then prompt to click the screen to exit the game!

GAME OVER! :)



The complete video of the project output can be viewed at the following link using any IITB LDAP account:

https://drive.google.com/file/d/16sxcLrM2aBUdFfizVEhoC_zRdugbmig5/view?usp=sharing


