// Green Team - Robert Squires, Christian Hinkle

#pragma once



/**
 * Static tools for recording task processing data.
 * 
 * TODO: Make this a class that can be instantiated. To achieve this, we
 * would have to make our delegates support invoking member functions on objects.
 */
namespace GTaskBenchmarker
{
	/** Begin recording statistics from tasks processing. */
	void StartBenchmarking();
	/** End recording of statistics. */
	void StopBenchmarking();

	int GetTotalProcessTime();

	float GetTotalTurnaroundTime();
	float GetTotalWaitingTime();
	float GetTotalResponseTime();

	int GetNumberOfTasksProcessed();

	float GetAverageTurnaroundTime();
	float GetAverageWaitingTime();
	float GetAverageResponseTime();
};
