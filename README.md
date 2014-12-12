Development status: alpha (sdli::Device breaking overhauls are unlikely to happen.)


**Goals of the library**
* Easy integration
* Clear, self-explaining interface
* Multiplayer input handling in mind
* Extensible interfaces


**Compiler support**
* Clang (Requirement for 'master' and 'develop' branch)
* gcc (Requirement for 'master' branch)
* MinGW-w64 (untested)
* VS13 MSVC (planned - untested)

**Branches**
* master: stable build, will contain flags once first working release is out
* develop: contains the latest compile-able version, mostly untested by other people or lacking test code


**Conceptual (move to wiki later)**
* Processor: represent an interface used by your game engine to get devices and create new contexts. Also handles sdl events. (You can use callbacks to add new functionality to events)
* Device: a handle for the user to interact with the interface, allows disconnected/reconnected devices to work properly
* Interface: represents a single input device (controller/gamepad, mouse+keyboard)
* Context: represents a contextual mapping of a input device
* A device requires an active context (default is no context - as no mapping)
* It is highly advised to use enums (or enum class) as arguments for InputAction, InputAxis, ContextId


**Implementation statistics**
* Keyboard support [30%] - Key Polling
* Gamecontroller support [20%] - Axis and button polling
* Joystick support [0%]
* Mouse support [0%]


See samples/ for intended usage.


If you find anything lacking tickets, patches and contribution are welcome. (Especially once I start optimization phase.)

Multiple library support may be added if concepts are not broken by doing so. (glfw, sfml)
