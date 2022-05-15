#include <atomic>
#include <cstdint>
#include <type_traits>

namespace k {

class control_block {
private:
  std::atomic<std::size_t> m_count;
public:
  control_block() : m_count{1} {}
  control_block(const control_block& other) = delete;
  control_block& operator=(const control_block& other) = delete;
  control_block(control_block&& other) = delete;
  control_block& operator=(control_block&& other) = delete;
  ~control_block() {}
  
  control_block* acquire() {
    m_count++;
    return this;
  }
  /** return true if resource should be release */
  bool release() {
    m_count--;
    return m_count == 0;
  }
};

template <typename T> 
class shared_ptr {
private:
  T* m_data;
  control_block* m_cb;
public:

  shared_ptr(T* data) 
  try: 
    m_data{data}, 
    m_cb{new control_block{}} 
  {} 
  catch(...){
    delete data;
    throw;
  }

  shared_ptr(const shared_ptr& other): m_data{other.m_data}, m_cb{other.m_cb->acquire()} {
  }

  shared_ptr& operator=(const shared_ptr& other) {
    shared_ptr tmp{other};
    this->swap(tmp);
    return *this;
  }

  shared_ptr(shared_ptr&& other) noexcept : m_data{std::move(other.m_data)}, m_cb{std::move(other.m_cb)} {
    other.m_data = nullptr;
    other.m_cb = nullptr;
  }

  shared_ptr& operator=(shared_ptr&& other) noexcept {
    swap(other);
    return *this;
  }

  ~shared_ptr() {
    if (!m_cb) {
      delete m_cb;
      return;
    }
    if (m_cb->release()) {
      delete m_cb;
      if (m_data) delete m_data;
    }
  }

  void swap(shared_ptr& other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_cb, other.m_cb);
  }

};

} // namespace k
