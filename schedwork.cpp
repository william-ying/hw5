#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

void perms(int index, int dailyNeed, vector<Worker_T> &data, vector<vector<Worker_T>> &ret, vector<Worker_T> rowavail) {
    if (data.size() == dailyNeed) {
        ret.push_back(data);
        return;
    }
    for (int i = index; i < rowavail.size(); i++) {
        data.push_back(rowavail[i]);
        perms(i + 1, dailyNeed, data, ret, rowavail);
        data.pop_back();
    }
}


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    // sched.clear();
    // Add your code below
    vector<Worker_T> rowavail;
    for (int i = 0; i < avail[sched.size()].size(); i++) {
        if (avail[sched.size()][i]) {
            bool add = 0;
            for (int j = 0; j < sched.size(); j++) {
                if (find(sched[j].begin(), sched[j].end(), i) != sched[j].end) add += 1;
            }
            if (add < maxShifts) {
                rowavail.push_back(i);
            }
        }
    }
    if (rowavail.size() < dailyNeed) return false;
    vector<vector<Worker_T>> schedrows;
    vector<Worker_T> data;
    perms(0, dailyNeed, data, schedrows, rowavail);
    if (schedrows.size() > 0 && avail.size() == 1) {
        sched.push_back(schedrows[0]);
        return true;
    }
    for (int i = 0; i < schedrows.size(); i++) {
        sched.push_back(schedrows[i]);
        if (schedule(avail, dailyNeed, maxShifts, sched)) return true;
        sched.pop_back();
    }
    return false;
}

