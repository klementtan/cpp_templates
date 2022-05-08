# New Handler with CRTP

Notes:
* Credits: Code copied from the book "Effective C++" Item 49 from Scott Meyers.
* New Handler:
  * C++ allows us to specify an error handler (aka `std::new_handler`) when there is a bad alloc.
  * Limitation: there can only be one global new handler.
* Why CRTP:
  * A benefit of CRTP is that it allows for a easily reusable base class with separate base static
  variable for each derived class.
  * Traditionally, different derived class that inherits from the same base class with share the 
  same static variable. However, with CRTP each derived class inherits from a different synthesized
  of the same base class template. This will allow the static variable in the synthesized base
  class to be different.
  * Using the benefit of separate static variable in CRTP, we can have the base class store the
  different new handlers and each operator new of the base class will set different handlers.
* Control Flow:
  1. Register the class specific `std::new_handler` with `Foo::set_hanlder`.
      * Stores the custom new handler in the base class static variable `NewHandlerSupport::current_handler`
  2. Calling `new Foo`
      * Calls the class defined operator new - implemented by `NewHandlerSupport`
      * `NewHandlerSupport::operator new`:
        1. Replaces the global operator new with `std::set_new_handler` with the
        class specific new handler stored in `NewHandlerSupport::current_handler`
        2. `std::set_new_handler` will return the previous `std::new_handler` which
        will be stored in the RAII'ed `NewHandlerHolder`
            * Calls `std::set_new_handler` in destructor to reset the global new handler
        3. Calls the global `::operator new`
  3. Global `::operator new` throws exception:
      1. Infinitely calls the new global new handler - which was set to `NewHandlerSupport::current_handler`
      2. New handler throws an error
  4. Destructor of `NewHandlerHolder` will be called
  5. Reset the global `new_handler` to the original `new_handler` (not the custom supplied one)
