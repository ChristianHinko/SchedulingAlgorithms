// Green Team - Robert Squires, Christian Hinkle


#include "GScheduleAlgorithms.h"

#include "GTask.h"
#include "GTaskProcessor.h"
#include "GDelegate.h"
#include <algorithm>



std::map<std::string, GDelegate<void, GTaskProcessor&, std::vector<GTask>&>> GScheduleAlgorithms;


G_REGISTER_SCHEDULE_ALGORITHM(std::string("FCFS"), ScheduleAlgorithmFirstComeFirstServe)
void ScheduleAlgorithmFirstComeFirstServe(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue)
{
	// Process these tasks in the given order
	for (std::size_t i = 0; i < InOutReadyQueue.size(); ++i)
	{
		const int ProcessTimeSlice = InOutReadyQueue.at(i).Burst; // process for as long as the burst time is
		InOutTaskProcessor.ProcessTask(InOutReadyQueue[i], ProcessTimeSlice);

		// Erase it
		{
			InOutReadyQueue.erase(InOutReadyQueue.begin() + i);
			--i;
		}
	}
}

G_REGISTER_SCHEDULE_ALGORITHM(std::string("SJF"), ScheduleAlgorithmShortestJobFirst)
void ScheduleAlgorithmShortestJobFirst(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue)
{
	// Sort by shortest burst to highest burst
	std::sort(InOutReadyQueue.begin(), InOutReadyQueue.end(),
		[](const GTask& InTaskA, const GTask& InTaskB)
		{
			return (InTaskA.Burst < InTaskB.Burst);
		}
	);

	ScheduleAlgorithmFirstComeFirstServe(InOutTaskProcessor, InOutReadyQueue);
}

G_REGISTER_SCHEDULE_ALGORITHM(std::string("PRI"), ScheduleAlgorithmPriority)
void ScheduleAlgorithmPriority(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue)
{
	// Sort by highest priority to lowest priority
	std::sort(InOutReadyQueue.begin(), InOutReadyQueue.end(),
		[](const GTask& InTaskA, const GTask& InTaskB)
		{
			return (InTaskA.Priority > InTaskB.Priority);
		}
	);

	ScheduleAlgorithmFirstComeFirstServe(InOutTaskProcessor, InOutReadyQueue);
}

G_REGISTER_SCHEDULE_ALGORITHM(std::string("RR"), ScheduleAlgorithmRoundRobin)
void ScheduleAlgorithmRoundRobin(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue)
{
	while (InOutReadyQueue.empty() == false)
	{
		// Process these tasks in the given order
		for (std::size_t i = 0; i < InOutReadyQueue.size(); ++i)
		{
			const int ProcessTimeSlice = std::min(InOutReadyQueue.at(i).Burst, InOutTaskProcessor.TimeQuantum); // upper-bound the time slice by the time quantum
			InOutTaskProcessor.ProcessTask(InOutReadyQueue[i], ProcessTimeSlice);

			if (InOutReadyQueue.at(i).Burst <= 0)
			{
				// Erase it
				InOutReadyQueue.erase(InOutReadyQueue.begin() + i);
				--i;
			}
		}
	}
}

G_REGISTER_SCHEDULE_ALGORITHM(std::string("PRI-RR"), ScheduleAlgorithmPriorityRoundRobin)
void ScheduleAlgorithmPriorityRoundRobin(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue)
{
	// Sort by highest priority to lowest priority
	std::sort(InOutReadyQueue.begin(), InOutReadyQueue.end(),
		[](const GTask& InTaskA, const GTask& InTaskB)
		{
			return (InTaskA.Priority > InTaskB.Priority);
		}
	);

	ScheduleAlgorithmRoundRobin(InOutTaskProcessor, InOutReadyQueue);
}
