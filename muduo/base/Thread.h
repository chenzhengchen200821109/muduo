// Use of this source code is governed by a BSD-style license
// that can be found in the License file.
//
// Author: Shuo Chen (chenshuo at chenshuo dot com)

#ifndef MUDUO_BASE_THREAD_H
#define MUDUO_BASE_THREAD_H

#include <muduo/base/CountDownLatch.h>
#include <muduo/base/Types.h>
#include <functional>
#include <muduo/base/NonCopyable.h>
#include <atomic>
#include <pthread.h>

namespace muduo
{

class Thread : muduo::noncopyable
{
 public:
  typedef std::function<void ()> ThreadFunc;

  explicit Thread(const ThreadFunc&, const string& name = string());
  explicit Thread(ThreadFunc&&, const string& name = string());
  ~Thread();

  void start();
  int join(); // return pthread_join()

  bool started() const { return started_; }
  // pthread_t pthreadId() const { return pthreadId_; }
  pid_t tid() const { return tid_; }
  const string& name() const { return name_; }

  static int numCreated() { return numCreated_.load(); }

 private:
  void setDefaultName();
 private:
  bool       started_;
  bool       joined_;
  pthread_t  pthreadId_;
  pid_t      tid_;
  ThreadFunc func_;
  string     name_;
  CountDownLatch latch_;
  static std::atomic<int> numCreated_;
};

} //namespace muduo
#endif
