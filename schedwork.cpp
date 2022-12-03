

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    AvailabilityMatrix& avail, 
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    int row,
    int col);

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




}

bool scheduleHelper(
    AvailabilityMatrix& avail, 
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    int currDay,
    int col
)
{
    size_t nDays = avail.size();
    size_t kWorkers = avail.at(0).size();
    const unsigned CANWORK = 1;
    const unsigned CANNOTWORK = 0;
    // we have finished the matrix
    if (currDay == nDays - 1 && col == dailyNeed)
    {
        return true;
    }

    // add more pseudobase cases

    if (col == dailyNeed)
    {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, currDay + 1, 0);
    }

    // iteration part
    // iterate over the availabilities for a given day
    
    for (size_t workerPos = 0; workerPos < avail[currDay].size(); ++workerPos)
    {
        if (avail[currDay][workerPos] == CANWORK)
        {
            sched[currDay][col] = workerPos;

            if (isValid(avail, dailyNeed, maxShifts, sched))
            {
                bool status = false;
                status = scheduleHelper(avail, dailyNeed, maxShifts, sched, currDay, col + 1);

                if (status)
                {
                    return true;
                }
            }
            else
            {
                sched[currDay][col] = INVALID_ID;
            }
            
        }
    }
    
    return false;
    
}

bool isValid(AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched)
{
    // make sure the nurses aren't overbooked

    std::map<Worker_T, unsigned> nurseCounts;

    for (size_t i = 0; i < sched.size(); ++i)
    {
        for (size_t j = 0; j < sched[i].size(); ++i)
        {
            Worker_T nurse1 = static_cast<Worker_T>(sched[i][j]);
            std::map<Worker_T, unsigned>::iterator it = nurseCounts.find(nurse1);
            if (it != nurseCounts.end())
            {
                it->second++; 
                // increment the count of that nurse's shifts
            }
            else
            {
                // insert the nurse with a count of 0
                nurseCounts.insert(std::make_pair(nurse1, 0));
            }
        }
    }

    for (const std::pair<Worker_T, unsigned>& nurse: nurseCounts)
    {
        if (nurse.second > maxShifts)
        {
            return false;
        }
    }

    return true;
}