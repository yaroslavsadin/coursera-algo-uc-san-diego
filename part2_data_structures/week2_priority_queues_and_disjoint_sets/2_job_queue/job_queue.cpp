#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using std::vector;
using std::cin;
using std::cout;

class JobQueue {
 private:
  struct JobInProgress {
    int worker;
    long long finish_time;
  };

  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.reserve(jobs_.size());
    start_times_.reserve(jobs_.size());
    std::priority_queue<int,std::vector<int>,std::greater<int>> free_workers;
    auto job_comp = [](JobInProgress lhs, JobInProgress rhs) { return lhs.finish_time > rhs.finish_time; };
    std::priority_queue<JobInProgress,std::vector<JobInProgress>,decltype(job_comp)> jobs_in_progress(job_comp);
    while(num_workers_--) {
      free_workers.push(num_workers_);
    }
    std::queue<int> jobs_queue;
    for(auto job : jobs_) {
      jobs_queue.push(job);
    }
    
    long long current_time = 0;
    while(!jobs_queue.empty()) {
      while(!jobs_in_progress.empty() && jobs_in_progress.top().finish_time <= current_time) {
        auto job = jobs_in_progress.top(); jobs_in_progress.pop();
        free_workers.push(job.worker);
      }
      long long next_time = (!jobs_in_progress.empty()) ? jobs_in_progress.top().finish_time : jobs_queue.front();
      while(!free_workers.empty() && !jobs_queue.empty()) {
        auto job_time = jobs_queue.front(); jobs_queue.pop();
        auto worker = free_workers.top(); free_workers.pop();
        assigned_workers_.push_back(worker);
        start_times_.push_back(current_time);
        jobs_in_progress.push({worker,current_time + job_time});
        next_time = std::min(next_time, current_time + job_time);
      }
      current_time = next_time;
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
