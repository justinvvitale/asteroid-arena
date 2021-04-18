Interactive 3D Graphics and Animation (2110) – S1 2021

Justin Vitale (s3718796)

<Building & Running>
	Source files are in vs/src, whereas the sln is located in /vs
	Everything else is as provided by canvas (Example VS files), it should run.
	Note: There are no folder filters since I was using CLion and merely moved it over for submission. 
	However, for a cleaner view, in VS, change the hierarchy to folder view, this is much neater.
	Ignore the warnings about casting, that is intended.

<Controls>
	W A S D – movement
	Left mouse button - shoot
	
<Implementation Information>
	Just a quick run down on how everything fits together, I am using a ECS architecture approach. There are Entities, which have multiple Components, these components add functionality to Entities, such as a mesh or a script (e.g PlayerControllerScript). The components are managed by systems (e.g MeshRendererSystem) whose job is to process each component of its respective type of each game cycle. 
	
	I have tried my best to keep the core game engine and the assignment specification separate, as you can probably tell by the A1 and core folder in 
	the src folder. The only purpose of the A1 folder is providing data for the core (engine) and scripts (for entities).
	
	Majority of the bounce functionality works well, there are slight hiccups but nothing game breaking, 
	mostly related to interactions between the wall and asteroids bouncing around, ah the R&G, I tried to fix majority of the quirks 
	but not sure if any more will arise 😊.
	
	Config files are located vs/src/core/ENGINECONFIG.h and vs/src/A1/GAMECONFIG.h respectively
	
<Milestones>
	I have completed/attempted the following:
		Level 1
			Everything
		Level 2
			Everything
		Level 3
			Everything
		Level 4
			4.1 – Bouncies
			4.2 - Bouncies 2
			4.3 - Do The Splits 
								(Instead of left/right, it picks a random position inside circle and spawns two opposite each other, 
								then they’re repelled from the asteroid centre at half the speed of the parent. I think it looks better; 
								the spec-obeying code is commented out in AsteroidWaveScript.cpp)
			4.4 - Earth Shattering Kaboom
		Bonus
			B.1 - Better Ship Movement
