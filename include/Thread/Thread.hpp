#pragma once
/**
 * @file Thread.hpp
 * @author Sanjeev Kumar M
 * @date 28/09/2020 12:00
 * 
 * @brief Defines the Thread::Thread class, which provides a base class for managing threads.
 */

#include <signal.h>
#include <pthread.h>
#include <cstdint>

namespace Thread {

  /**
   * @enum ThreadStatus
   * @brief Represents the possible states of a thread operation.
   */
  enum class ThreadStatus : uint8_t {
    Ok,              ///< Thread started successfully.
    Failed,          ///< Thread creation failed.
    AlreadyStarted,  ///< Thread is already running.
  };

  /**
   * @class Thread
   * @brief A base class for creating and managing threads.
   */
  class Thread {
   public:
    /**
     * @brief Destructor that ensures the thread is terminated before destruction.
     */
    ~Thread() {
      if (_m_thread_id != -1) {
        pthread_kill(_m_thread_id, SIGUSR1);
        pthread_join(_m_thread_id, nullptr); // Ensure proper cleanup
        _m_thread_id = -1;
      }
    }

    // Delete copy and move constructors to prevent unintended copying/moving.
    Thread(const Thread&) noexcept = delete;
    Thread(Thread&&) noexcept = delete;
    Thread& operator=(const Thread&) = delete;
    Thread& operator=(Thread&&) = delete;
   
   public:
    /**
     * @brief Default constructor initializes the thread ID.
     */
    Thread() : _m_thread_id(-1) {}

    /**
     * @brief Starts the thread execution.
     * @return ThreadStatus indicating the result of thread creation.
     */
    ThreadStatus run() {
      if (_m_thread_id != -1) return ThreadStatus::AlreadyStarted;
      if (pthread_create(&_m_thread_id, nullptr, &start_thread, this) != 0) return ThreadStatus::Failed;
      return ThreadStatus::Ok;
    }

   protected:
    /**
     * @brief The main function that must be implemented by derived classes.
     *        This function contains the main execution logic of the thread.
     */
    virtual void thread_main() = 0;

    /**
     * @brief Stops the thread execution.
     */
    virtual void stop() = 0;

   private:
    /**
     * @brief Static function that serves as an entry point for the pthread.
     *        Calls `thread_main()` on the calling object.
     *
     * @param[in] __thread_addr Pointer to the calling object.
     * @return Always returns nullptr.
     */
    static void* start_thread(void* __thread_addr) {
      Thread* threadObj = static_cast<Thread*>(__thread_addr);
      threadObj->thread_main();
      threadObj->_m_thread_id = -1;
      pthread_exit(nullptr); // Ensure the thread exits cleanly
      return nullptr;
    }

    /**
     * @brief Holds the thread ID of the created pthread.
     */
    pthread_t _m_thread_id;
  };
}
