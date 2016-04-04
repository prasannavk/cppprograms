class Buffer {
 public:
  void add(int num) {
    while (true) {
      std::unique_lock<std::mutex> locker(mu);
      cond.wait(locker, [this](){return buffer_size() < size_;});
      buffer_.push_back(num);
      locker.unlock();
      cond.notify_all();
      return;
    }
  }

  int remove() {
    while (true) {
      std::unique_lock<std::mutex> locker(mu);
      cond.wait(locker, [this](){return buffer_.size() > 0;});
      int back = buffer_.back();
      buffer_.pop_back();
      locker.unlock();
      cond.notify_all();
      return back;
    }
  }
  Buffer() {}
 private:
  // sychronization variables
  std::mutex mu;
  std::condition_variable cond;

  // Normal variables here
  deque<int> buffer_;
  const unsigned int size_ = 10;
};

class Producer {
 public:
  Producer(Buffer& buffer) : buffer_(buffer) {}
  void run() {
    while (true) {
      int num = std::rand() % 100;
      buffer_->add(num);
      {
        std::unique_lock<std::mutex> locker(cout_mu);
        // Prefer \n over std::endl
        std::cout << "Produced: " << num << "\n";
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }
 private:
  Buffer &buffer_;
};

class Consumer {
  public:
   Consumer(Buffer& buffer) : buffer_(buffer);

   void run() {
     while (true) {
       int num = buffer_->remove();
       {
         std::unique_lock<std::mutex> locker(cout_mu);
         std::cout << "Consumed: " << num << "\n";
       }
       std::this_thread::sleep_for(std::chrono::milliseconds(50));
     }
   }
  private:
   Buffer &buffer_;
};

int main() {
  Buffer b;
  Producer p(&b);
  Consumer c(&b);

  std::thread producer_thread(&Producer::run, &p);
  std::thread consumer_thread(&Consumer::run, &c);

  producer_thread.join();
  consumer_thread.join();
  getchar();
  return 0;
}
