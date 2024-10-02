#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

#define MAX_WAITING 10 // Maximum number of waiting students
#define HELP_TIME 10 // Time TA helps a student

using namespace std;

mutex mtx; // Mutex for mutual exclusion
condition_variable cv; // Condition variable for signaling
int waiting_students = 0; // Number of waiting students
bool ta_sleeping = true; // TA's state

void student(int student_id);
void sleeping_ta();


int main() {
    // this make sure each time random number generates randomly for each run
    srand(static_cast<unsigned int>(time(0))); // Seed 
    int num_students;

    cout << "Enter the number of students: ";
    cin >> num_students;

    thread ta_thread(sleeping_ta); // Create TA thread

    //student thread arr
    vector<thread> student_threads;
    for (int i = 0; i < num_students; i++) {
        student_threads.emplace_back(student, i + 1); 
	// randomly waiting time 0.....8 Sec
        this_thread::sleep_for(chrono::seconds(rand() % 8)); 
    }

    // Join all student threads main thread ||  will be waiting completion for student thread
    for (auto& s : student_threads) {
        s.join();
    }
    
    // main does not need completition of ta thread
    ta_thread.detach(); 

    return 0;
}

void sleeping_ta() {
    while (true) {
        // Wait for a student to wake up the TA
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !ta_sleeping; }); // Wait until TA is woken up

        // TA is helping a student
        cout << "[TA THREAD] TA is helping a student..." << endl;
        this_thread::sleep_for(chrono::seconds(HELP_TIME)); // Simulate helping time
        cout << "[TA THREAD] TA is done helping a student!" << endl;

        if (waiting_students > 0) {
            waiting_students--;
            cout << "[TA THREAD] Waiting students = " << waiting_students << endl;
        } else {
            cout << "[TA THREAD] No students waiting. TA goes back to sleep." << endl;
            ta_sleeping = true; // TA goes back to sleep
        }
    }
}

void student(int student_id) {
    // Lock the mutex
    unique_lock<mutex> lock(mtx);
    cout << "[STUDENT THREAD] Student " << student_id << " is coming!" << endl;

    if (ta_sleeping) {
        cout << "[STUDENT THREAD] Student " << student_id << " wakes up TA!" << endl;
        ta_sleeping = false; // TA is awake
        cv.notify_one(); // Signal the TA to help
    } else if (waiting_students < MAX_WAITING) {
        waiting_students++;
        cout << "[STUDENT THREAD] Student " << student_id << " is seating on a waiting chair. Waiting students = " << waiting_students << endl;
    } else {
        cout << "[STUDENT THREAD] Student " << student_id << " finds no chairs available and will come back later." << endl;
        return; // End thread
    }
}

