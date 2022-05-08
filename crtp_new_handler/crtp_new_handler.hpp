/**
 * Credits: Adopted from "Effective C++" (Scott Meyers) Item 49
 *
 * The purpose of a new handler is to allow for custom error handling for OOM
 * exceptions when allocating new memory. This file contains an implementation
 * reference on how you can have class specific new handler and is achieved by
 * having a CRTP base class.
 *
 * Challenge: C++ only allow for a single global new handler, thus we need to
 * find a way set the new handler before we call new for each class new operator
 * and reset it once it is successful.
 */


#include <cassert>
#include <new>

/** RAII class that stores the temporarily replaced global handler and resets it once
 * it is destroyed.
 */
class NewHandlerHolder {
public:
  explicit NewHandlerHolder(std::new_handler nh) : handler{nh} {}
  ~NewHandlerHolder() {
    // reset global handler
    std::set_new_handler(handler);
  }
private:
  std::new_handler handler;
  NewHandlerHolder(const NewHandlerHolder&); // prevent copying
  NewHandlerHolder& operator=(const NewHandlerHolder&); 
};


template<typename T>
class NewHandlerSupport {
public:
  static std::new_handler set_hanlder(std::new_handler p) throw();
  static void* operator new(std::size_t size);
  static void* operator new[](std::size_t size);
private:
  static std::new_handler current_handler;
};

template<typename T>
std::new_handler NewHandlerSupport<T>::set_hanlder(std::new_handler p) throw()
{
  std::new_handler older_handler = current_handler;
  current_handler = p;
  return older_handler;
}

template<typename T>
void* NewHandlerSupport<T>::operator new(std::size_t size)
{
  // set current_handler as the global new_handler and store the
  // previous global new_handler in the RAII h
  NewHandlerHolder h(std::set_new_handler(current_handler));
  return ::operator new(size);
}
template<typename T>
void* NewHandlerSupport<T>::operator new[](std::size_t size)
{
  // set current_handler as the global new_handler and store the
  // previous global new_handler in the RAII h
  NewHandlerHolder h(std::set_new_handler(current_handler));
  return ::operator new[](size);
}

template<typename T>
std::new_handler NewHandlerSupport<T>::current_handler = nullptr;
