Real Time Tactics

Coding by: Kevin Weber, Bennett Schalich, Olin Olmstead

README Author: Bennett Schalich

Real Time Tactics is a RTS style game built from the ground up using openGL
and C++. The player controls multiple combatants to attempt to destroy the AI controlled
combatants on the other side of the map. There are three warrior types: the Warrior, a melee
juggernaut, the Archer, a single target sniper, and the Mage, a powerful area of effect 
spell caster. 

NOTE: Unfortunately some of the code has deprecated since this game was made and our team
	had to move on to other projects. The project cannot be build without specific 
	settings on our schools lab computers (a portability problem we should have avoided). 
	I am posting this because it gives a good idea of the project scale and some good
	example C++ code.
	
Feel free to browse around the source code, but what I want to focus primarily on are six
classes: Combatant, Archer, Warrior, Mage, and StateMachine, and part of GameController

Combatant:
	The Combatant class is the super class to the Archer, Warrior, and Mage. There is 
	generic data that applies to any type of combatant, such as velocity. 
	You may notice sound data from all types of combatants at the top. I was 
	not responsible for that :). Sound data should only be loaded depending on the 
	Combatant_Type. You will notice that this code is very raw, as
    initial positions are set and the bounding boxes are created upon creating
	a combatant. Next data is initialized depending on the type specified in the Combatant 
	constructor. This way we are able to determine aspects of the Combatant like color once 
	in one place in the code instead of in three different classes. 
	
	In this specific project we didn't want to hassle with too much inheritance, so we 
	instead created a type enum for Warrior, Mage, and Archer. You will see that certain 
	functions in Combatant have switch statements that execute different code depending 
	on the type of the combatant. In this project we use inheritance to give each 
	Combatant distinct types of attacks that are defined within each subclass of 
	Combatant, but Combatant handles most other functionality.
	
    In the constructor AI is given to the Combatant depending on whether the Combatant is
    a hero (a player controlled character) or an enemy (computer controlled character)
    
    The way a Combatant acquires a target is through a variable named "enemy". The "enemy" 
    variable initially set to null and when an enemy enters the range of the Combatant 
    it is set to an enemy. The Combatant then attacks that enemy until it is given another 
    instruction or until the enemy is dead. When a new instruction is given or the enemy 
    dies the "enemy" variable is set back to NULL. In the StateMachine if "enemy" is NULL 
    the character does not aggress.
    
    Much of this code is tedious due to how close we were working with our graphics engine.
    This was a graphics based project and we were not allowed to abstract it away too much.   

Archer:
	A subclass of Combatant. It has its own specific way it attacks and a unique attack
	animation. The archer is checking every frame to see if there is an enemy in range. If
	there is it attacks the target. The archers attack speed is based off a clock created 
	when the archer is. A projectile is created upon attacking and moves toward the 
	calculated direction of the enemy. Projectiles can get stuck on trees or miss.
	
Warrior:
	A subclass of Combatant. The warrior can only attack enemies close to himself. He 
	has the most health out of all the combatants. 
	
Mage:
	A subclass of Combatant. The mage is the weakest physically of the combatants, but has
	a devastating AOE attack. The mage attacks the center of his target, causing sparks 
	to fly at the enemies current location. If other enemies are caught in the blast they
	take damage as well.
	
StateMachine:
	All combatants that are not heros (player controlled) are controlled by StateMachine.
	Depending on the combatants surroundings they are moved into certain states. When in
	a particular state they take particular actions. Take a look at the code to get an 
	idea of what state does what.

GameController:
	The game controller initializes the map with players and is responsible for setting 
	the state of the computer controlled combatants by traversing the combatant list. Every
	time a new combatant is created it is added to the combatant list. Also whenever
	a hero is added to the map it is put in the hero list which is referenced to allow
	the player to control there combatants. There is a lot of commented code at the bottom
	which are remnants of an older method of controlling the game. It was there for us to 
	reference as we created our new method.

Working with such raw code is good practice, but can be quite messy. We did our best to 
keep it as neat as possible.
	
	
	