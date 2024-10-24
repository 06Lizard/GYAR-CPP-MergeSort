#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool {
public:
    // Constructor initializes the thread pool with one thread, then gradually adds more threads until thread_limit is reached.
    ThreadPool(size_t thread_limit)
        : stop(false), current_threads(0), max_threads(thread_limit) {

        // Start by creating one thread.
        addThread();

        // Gradually create threads until we reach the thread limit.
        for (size_t i = 1; i < max_threads; ++i) {
            addThread();
        }
    }

    // Destructor ensures proper cleanup of threads.
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }

        condition.notify_all();

        for (std::thread& worker : workers) {
            worker.join();  // Wait for all threads to finish.
        }
    }

    // Add a new task to the queue.
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = task->get_future();

        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            // Don't allow enqueueing after stopping the pool.
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }

            tasks.emplace([task]() { (*task)(); });
        }

        condition.notify_one();
        return result;
    }

private:
    // Vector of worker threads.
    std::vector<std::thread> workers;

    // Task queue.
    std::queue<std::function<void()>> tasks;

    // Synchronization.
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
    size_t current_threads;
    size_t max_threads;

    // Worker thread function.
    void workerThread() {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(this->queue_mutex);

                // Wait for a task or stop signal.
                this->condition.wait(lock, [this] {
                    return this->stop || !this->tasks.empty();
                    });

                // Exit if stopping and no tasks left.
                if (this->stop && this->tasks.empty()) {
                    return;
                }

                // Get the next task from the queue.
                task = std::move(this->tasks.front());
                this->tasks.pop();
            }

            // Execute the task.
            task();
        }
    }

    // Adds a new worker thread.
    void addThread() {
        workers.emplace_back([this] { this->workerThread(); });
        ++current_threads;
    }
};