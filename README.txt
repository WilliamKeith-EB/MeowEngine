
MEOW

This is the meow engine.
Ewout Buyck 2DAE01
git repo: https://github.com/WilliamKeith-EB/MeowEngine

Sadly it is not complete but these are the features currently implemented:

- Locator
	There is one big locator class which holds all the data that should be globally available
	for the whole project. All those have a define which makes it easier to get to them.
	e.g. instead of having to write Locator::GetTime() you can just write TIME to get the same result.

- Game
	When the engine is created and run it expects a "Game" pointer. "Game" is an abstract class with one pure virtual method:
	LoadGame(). This is the method in which the scenes should be created and the starting scene needs to be set active.

- Debugging
	Debugging in the engine has been made easier and cleaner. There is a logger (that can be obtained
	through the LOGGER macro) which can log info, warnings and errors (which all have a different
	color and print a time stamp to now when it was printed)
	There is also a debugrenderer, for now this can only draw the colliders that are added to it
	when creating a collider component, you can add it to the debugrenderer so it also gets shown in the window.

- Optimized renderer
	The renderer in this engine is quite optimized, the rendercomponent does not inherit from the base component
	and is stored in a separate array (next to eachother in memory), when the rendering phase is started, all rendercomponents
	get sorted according to their render depth and then are looped over and drawn.

- Frame Allocator
	The engine includes a frame allocator which is a stack allocator that can be used to temporarily store some data
	that is to big and would otherwise overflow the base stack. It gets cleansed every frame and taken away at the end.
	It is also used as a temporary storage for the rendercomponents that are moved to the scene's array when the object
	it is attached to gets added to a scene. e.g. GameObject obj = new (FRAMEALLOC) GameObject("Object on the frameAllocator");

- Scene Management
	"Scene" is a baseclass that can be inherited from to create a level or a menu scene. It has two pure virtual methods
	(Sandbox methods) "Initialize" and "Update". In intialize the general structure of the objects and components can be created.
	(They need to be added to the scene as well), they get updated and drawn automatically but if anything else wants to be done
	in the update that isn't written in a component, the update method can be used to do that.
	There's also a scenemanager that can be used to set a different scene as active, when that is done the rendercomponents of that
	scene are set in the renderer.

- Resource Manager
	The resource manager is a classic manager that holds a map of textures and only creates a new one if the same file is not already loaded.
	It is accessible through the RESOURCEMANAGER Macro.

- Config Loader
	The config loader is a small extra I wrote before I even had an engine because I love it. It loads an ini-file before the window gets initialized.
	For the moment only the window width, window height, window title and vsync can be changed in the Engine.ini.
	Also some memory numbers can be adjusted in the file, like the size of the frame allocator and the number of rendercomponents that can max be in the game.

- COMPONENTS
	RenderComponent:
		Even though this component doesn't inherit from the Component base class, it mimics the main behaviour. It has a reference to the
		gameobject it is attached to and a pointer to the texture it displays. Something special about this component is the overload of the new and delete operator.
		When a rendercomponent is created, it is always put on the frameallocator. It is copied to the array in the scene whenever it gets added to the scene.
		Whenever the Render() method is called, the component forwards the rendering to the texture and gets the transform from the gameobject to let the renderer
		where to render the texture.

	TransformComponent:
		The transformComponent holds the information about where and how the texture of the object should be rendered. It has a position, rotation, scale, size,
		anchor and renderdepth (this depth decides if it should be rendered in front of or behind another object). The transform matrix only gets calculated when
		it is needed, but it is also stored so it doesn't need to be calculated if it didn't change since last frame (Dirty flag pattern).

	CameraComponent:
		This component can be added to an object to make it a camera. Then the transform of that object will decide the position, scale, rotation, etc. of a camera.
		To set the main camera to be a certain camera component, the locator provides a CAMERA macro.	
	
	ColliderComponent:
		The collider is the latest addition to the engine and as such it is not completely finished. It provides a constructor to make a rectangular box around
		an object (This rect can as of now not yet be rotated). This component is also where I implemented the Observer pattern. Whenever you create a 
		ColliderComponent, you can choose to give with it a CollisionListener pointer, this is an interface that can be implemented by a scene or component to
		react on collision that has been triggered. As of now, all collision boxes are seen as triggers and there is no actual pushing back of objects.

This is what my engine has right now. I know it isn't much and my main reason for that is the course "Game Projects". One of our team members decided this assignment was
more important than our group work, so I had to take up a lot of tasks that he didn't want to do anymore. I mainly dropped this assignment because I can still pas the
course if I fail this project. I know I don't have too much content in my engine, but I hope the quality is at least enough to make me pass this course.

Thank you for your attention,
Ewout Buyck