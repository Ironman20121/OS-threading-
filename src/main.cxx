#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <stdexcept>

#define MAX_WAITING 2 // Maximum number of students waiting
#define HELP_TIME 5   // Time TA helps a student (in seconds)
#define TA_GOING_TIME 10 // Time TA will wait before going to sleep (in seconds)

using namespace std;

mutex mtx; // Mutex for mutual exclusion
condition_variable cv; // Condition variable for signaling
int waiting_students = 0; // Tracking number of students
bool ta_sleeping = true; // TA's state
int ta_sleeping_counter = 0; // Counter for TA's sleeping time

void student(int student_id);
void sleeping_ta();

int main(int argc, char *argv[]) {
    // Student thread tracker
    vector<thread> student_threads; 
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation
    int num_students;

    if (argc < 2) {
        cout << "Enter the number of students: ";
        cin >> num_students;
    } else {
        num_students = std::stoi(argv[1]);
    }

try  
{
    thread ta_thread(sleeping_ta); // Create TA thread

    // Create student threads
    for (int i = 0; i < num_students; i++) {
        student_threads.emplace_back(student, i + 1); 
        this_thread::sleep_for(chrono::seconds(rand() % 2)); // Random wait time before next student arrives
    }

    // Join all student threads
    for (auto& s : student_threads) {
        if (s.joinable()) {
            s.detach();
        }
    }

    // Join TA thread
    if (ta_thread.joinable()) {
        ta_thread.join();
    }

}

catch(exception &e){
cerr<< "An exception occurred :" << e.what()<<endl;
}
    return 0;
}

void sleeping_ta() {
    while (true) {
        // Decrease waiting students count
        unique_lock<mutex> lock(mtx);
        auto start_idle_time = chrono::steady_clock::now();
        cv.wait_for(lock,10s,[] { return !ta_sleeping; }); // Wait until TA is woken until some student call in 10 secounds or else bye
        // TA is helping a student
        if (waiting_students == 0) {
            cout << "[TA THREAD] No students waiting. TA goes back to sleep." << endl;
            auto end_idle_time = chrono::steady_clock::now();
            auto idle_duration = chrono::duration_cast<chrono::seconds>(end_idle_time - start_idle_time);
            //cout<< "count :::" << idle_duration.count() ;
            if (idle_duration.count() >= 10) {
                cout << "[TA THREAD] No students for 10 seconds. TA is exiting." << endl;
                return; // Exit the TA thread
            }
            ta_sleeping = true; // TA goes back to sleep
        }
        else{
        cout << "[TA THREAD] TA is helping a student..." << endl;
        this_thread::sleep_for(chrono::seconds(HELP_TIME)); // Simulate helping time
        cout << "[TA THREAD] TA is done helping a student!" << endl;
        if (waiting_students > 0) {

        this_thread::sleep_for(chrono::seconds(HELP_TIME)); // Simulate helping time
        cout << "[TA THREAD] TA is done helping a student!" << endl;
            waiting_students--;
            cout << "[TA THREAD] Waiting students = " << waiting_students << endl;
        }


        }
        }       
    }


void student(int student_id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cout << "[STUDENT THREAD] Student " << student_id << " is coming!" << endl;

        if (ta_sleeping) {
            cout << "[STUDENT THREAD] Student " << student_id << " wakes up TA!" << endl;
            ta_sleeping = false; // TA is awake
            cv.notify_one(); // Signal the TA to help
            cout << "[STUDENT THREAD] student "<< student_id <<" done with work going bye"<<endl; 
            return; // Student is helped, exit the function
        } 
        if (waiting_students < MAX_WAITING) {
            waiting_students++;
            cout << "[STUDENT THREAD] Student " << student_id << " is seated on a waiting chair. Waiting students = " << waiting_students << endl;
            return; // Student is seated, exit the function
        }
        else {
            cout << "[STUDENT THREAD] Student " << student_id << " finds no chairs available and will come back later." << endl;
            // this is for degbuging
            //cout << "TA :::: "<< ta_sleeping<< "waiting_student_counter :::: " << waiting_students << endl ;
            lock.unlock(); // Unlock the mutex before sleeping

            // Wait for a random time before trying again
            this_thread::sleep_for(chrono::seconds(rand() % 8)); // Random wait between 1 to 3 seconds

            // Re-lock the mutex for the next attempt
            continue; //will  start of the while loop to so it go to if condition
        }

}

}
