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
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftCount,
    size_t day,
    size_t slot);

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
    sched.clear();
    // Add your code below
    
    size_t n = avail.size();
    size_t k = avail[0].size();

    for (size_t i = 0; i < n; i++) {
        sched.push_back(std::vector<Worker_T>(dailyNeed, INVALID_ID));
    }
    
    std::vector<size_t> shiftCount(k, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftCount,
    size_t day,
    size_t slot)
{
    size_t n = avail.size();
    size_t k = avail[0].size();

    if (day == n) {
        return true;
    }

    if (slot == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day + 1, 0);
    }

    for (Worker_T w = 0; w < k; w++) {
        if (!avail[day][w]) continue;
        if (shiftCount[w] >= maxShifts) continue;
        if (std::find(sched[day].begin(), sched[day].begin() + slot, w)
            != sched[day].begin() + slot) continue;

        // Choose
        sched[day][slot] = w;
        shiftCount[w]++;

        // Explore
        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day, slot + 1)) {
            return true;
        }

        // Un-choose (backtrack)
        sched[day][slot] = INVALID_ID;
        shiftCount[w]--;
    }
    return false;
}



}

