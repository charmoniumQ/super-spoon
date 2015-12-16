#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <cstdint>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>
#include <tuple>

template<typename Iterator, typename K, typename V>
class ThreadFunc {
public:
  ThreadFunc(
			 std::function<std::tuple<K, bool>(V, uint8_t)> worker_m, 
        std::mutex* input_lock_m,
		std::mutex* output_lock_m,
		Iterator& work_chunks_m,
		Iterator& end_m,
		K& output_value_m,
		bool& terminated_m,
		bool& success_m) : 
	    worker(worker_m),
		input_lock(input_lock_m),
		output_lock(output_lock_m),
		work_chunks(work_chunks_m),
		end(end_m),
		output_value(output_value_m),
		terminated(terminated_m),
		success(success_m) {}
  void operator()(uint8_t i) {
	uint8_t pid (i);
	K local_output_value;
	bool local_terminated;
	V input;
	while (true) {
	  input_lock->lock();
	  {
		if (work_chunks == end) {
		  // End of input data
		  // Signal that to other threads
		  terminated = true;
		}
		// See if other threads signaled to terminate
		local_terminated = terminated;
		if (! terminated) {
		  // If nobody else says to stop, get the next input chunk
		  input = *work_chunks++;
		}
	  }
	  input_lock->unlock();

	  if (local_terminated) {
		return;
	  }

	  std::tie(local_output_value, local_terminated) = worker(input, pid);
	  if (local_terminated) {
		// I found the end!!!
		output_lock->unlock();
		{
		  // This signals other threads to stop
		  terminated = local_terminated;
		  // This stores the end answer
		  output_value = local_output_value;
		  // This signals that I got an answer
		  success = true;
		}
		output_lock->lock();
		return;
	  }
	}
  };
private:
  std::function<std::tuple<K, bool>(V, uint8_t)> worker;
  std::mutex* input_lock;
  std::mutex* output_lock;
  Iterator& work_chunks;
  Iterator& end;
  K& output_value;
  bool& terminated;
  bool& success;
};

template<typename Iterator, typename K, typename V>
std::tuple<K, bool> mrd(
						std::function<std::tuple<K, bool>(V, uint8_t)> worker,
    Iterator work_chunks, Iterator end,
    uint8_t thread_count
) {
  std::mutex output_lock, input_lock;
  K output_value;
  bool terminated = false, success = false;

  std::vector<std::thread*> threadss (thread_count);
  ThreadFunc<Iterator, K, V> thread_func (worker, &input_lock, &output_lock, work_chunks, end, output_value, terminated, success);
  for (int i = 0; i < thread_count; ++i) {
	//std::function<void(void)> f = std::bind(&thread_func.run_func, &input_lock, &output_lock, work_chunks, end, output_value, terminated, success);
	threadss[i] = new std::thread(thread_func, i);
  }

  for (int i = 0; i < thread_count; ++i) {
	threadss[i]->join();
	delete threadss[i];
  }

  return std::make_tuple(output_value, success);
}

#endif
