// Green Team - Robert Squires, Christian Hinkle


#include "GTaskBenchmarker.h"

#include "GTask.h"
#include "GTaskProcessor.h"
#include <iostream>



namespace GTaskBenchmarker
{
	// Private space
	namespace
	{
		float TotalTurnaroundTime = 0.f;
		float TotalWaitingTime = 0.f;
		float TotalResponseTime = 0.f;
		int NumberOfTasksProcessed = 0;
		int TotalProcessTime = 0;

		void OnTaskPreProcess(const GTask& InTask, const GTaskProcessor& InTaskProcessor, const int InTimeSlice)
		{
			std::printf("Processing task id [%d]. Task name: [%s]. Task priority: [%d]. Task current burst: [%d]. Processing with time slice [%d].\n", InTask.Id, InTask.Name.c_str(), InTask.Priority, InTask.Burst, InTimeSlice);
			std::cout.flush();

			TotalWaitingTime += GetTotalProcessTime();

			int ArrivalTime = 0; // we do not have an arrival time because there is no varying enter time into the ready queue
			TotalResponseTime += (GetTotalProcessTime() - ArrivalTime);
		}

		void OnTaskPostProcess(const GTask& InTask, const GTaskProcessor& InTaskProcessor, const int InTimeSlice)
		{
			++NumberOfTasksProcessed;
			TotalProcessTime += InTimeSlice;

			TotalTurnaroundTime += GetTotalProcessTime();
		}
	}

	void GTaskBenchmarker::StartBenchmarking()
	{
		// Bind to task process delegates
		GTask::OnPreProcessDelegate.AddStatic(OnTaskPreProcess);
		GTask::OnPostProcessDelegate.AddStatic(OnTaskPostProcess);
	}
	void GTaskBenchmarker::StopBenchmarking()
	{
		// Unbind from task process delegates
		GTask::OnPreProcessDelegate.RemoveStatic(OnTaskPreProcess);
		GTask::OnPostProcessDelegate.RemoveStatic(OnTaskPostProcess);
	}

	float GetTotalTurnaroundTime() { return TotalTurnaroundTime; }
	float GetTotalWaitingTime() { return TotalWaitingTime; }
	float GetTotalResponseTime() { return TotalResponseTime; }
	int GetNumberOfTasksProcessed() { return NumberOfTasksProcessed; }

	int GetTotalProcessTime() { return TotalProcessTime; }

	float GetAverageTurnaroundTime()
	{
		return (GetTotalTurnaroundTime() / GetNumberOfTasksProcessed());
	}
	float GetAverageWaitingTime()
	{
		return (GetTotalWaitingTime() / GetNumberOfTasksProcessed());
	}
	float GetAverageResponseTime()
	{
		return (GetTotalResponseTime() / GetNumberOfTasksProcessed());
	}
}
