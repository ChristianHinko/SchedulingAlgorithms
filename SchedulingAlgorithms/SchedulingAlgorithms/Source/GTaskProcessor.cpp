// Green Team - Robert Squires, Christian Hinkle


#include "GTaskProcessor.h"

#include "GTask.h"
#include <algorithm>
#include <chrono>
#include <conio.h>



GTaskProcessor::GTaskProcessor()
	: TimeQuantum(0)
	, TotalProcessTime(0)
	, TimeScale(1)
{

}


void GTaskProcessor::ProcessTask(GTask& InOutTask, const int InTimeSlice)
{
	const int TimeSlice = std::min(InTimeSlice, InOutTask.Burst);

	GTask::OnPreProcessDelegate.Broadcast(InOutTask, *this, TimeSlice);

	// Process the task for the specified time slice
	std::chrono::time_point<std::chrono::steady_clock> TimePointStart = std::chrono::steady_clock::now();
	while ((std::chrono::steady_clock::now() - TimePointStart) < std::chrono::milliseconds(static_cast<int>(1000 * TimeSlice / TimeScale)))
	{
		InOutTask.Process(0); // TODO: give it a proper delta time value
	}

	// Apply the process time to the task
	InOutTask.Burst -= TimeSlice;

	// Track our total process time
	TotalProcessTime += TimeSlice;

	GTask::OnPostProcessDelegate.Broadcast(InOutTask, *this, TimeSlice);
}
