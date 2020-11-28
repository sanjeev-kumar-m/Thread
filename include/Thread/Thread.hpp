#pragma once 
/**
 * @file Thread.hpp
 * @author Sanjeev Kumar M
 * @date 28/09/2020 12::00
 * 
 * This module defines Thread::Thread class
 */

#include <signal.h>

namespace Thread {
  enum class ThreadStatus {
    ThreadStatusOk,
    ThreadStatusFailed,
    ThreadStatusAlreadyStarted,
  };

  class Thread {
   public:
    //Life cycle management
    ~Thread() {
      if (_m_thread_id != -1) {
        pthread_kill(_m_thread_id, SIGUSR1);
      }
    }
    Thread(const Thread&) noexcept = delete;
    Thread(Thread&&) noexcept = delete;
    Thread& operator=(const Thread&) = delete;
    Thread& operator=(Thread&&) = delete;
   public:
    //This is the constructor
    Thread()
      : _m_thread_id(-1)
      {}

    /**
     * This function used to start the thread execution
     */
    ThreadStatus run() {
      if (_m_thread_id != -1) return ThreadStatus::ThreadStatusAlreadyStarted;
      if (pthread_create(&_m_thread_id, nullptr,
          &start_thread, this) == -1) return ThreadStatus::ThreadStatusFailed;
      return ThreadStatus::ThreadStatusOk;
    }

   protected:
    /**
     * The function must be implemented by the child classes 
     * the main thread execution code goes in this function
       */
    virtual void thread_main() = 0;

    /**
     * This function is used to stop the thread 
     * execution
     */


   private:
    /**
     * This function actually calls the thread_main
     * function on the calling object
     * 
     * @param[in]
     *    __thread_addr - address of the calling object
     */
      static void* start_thread(void* __thread_addr) {
        static_cast<Thread*>(__thread_addr)->thread_main();
      }

    /**
     * This holds the if of the created 
     * pthread
     */
    pthread_t _m_thread_id;
  };
}