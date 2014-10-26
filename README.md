This is supposed as a wrapper around SDL2's input api.

Development status: Getting interface done (Do use for prod code with caution - overhauls happen)

Goals of the library:
* Easy integration
* Clear, self-explaining interface
* Multiplayer input handling in mind
* Extensible interfaces


Compiler support:
* Clang
* gcc (untested)
* MinGW-w64 (untested)

Conceptual (move to wiki later):
* Processor: represent an interface used by your game engine to get devices and create new contexts. Also handles sdl events. (You can use callbacks to add new functionality to events)
* Device: a handle for the user to interact with the interface, allows disconnected/reconnected devices to work properly
* Interface: represents a single input device (controller/gamepad, mouse+keyboard)
* InputContext: represents a contextual mapping of a input device
* A device requires an active context (default is no context - as no mapping)
* It is highly advised to use enum or enum class as arguments for InputAction, InputAxis, ContextId

See samples for intended usage.

If you find anything lacking tickets and contribution are welcome.

Multiple library support may be added if concepts are not broken by doing so.
