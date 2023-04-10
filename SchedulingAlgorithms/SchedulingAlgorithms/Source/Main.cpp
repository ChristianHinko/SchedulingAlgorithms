// Green Team - Robert Squires, Christian Hinkle


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "GTask.h"
#include "GScheduleAlgorithms.h"
#include "GTaskProcessor.h"
#include "GTaskBenchmarker.h"



// Exit codes
const int GExitCodeErrorBadArguments = 1;
const int GExitCodeErrorNoInputFile = 2;
const int GExitCodeErrorBadScheduleAlgorithmName = 3;

/**
 * Fill out a task array given an input format that defines
 * a task on each line defined by: [TaskName], [TaskPriority], [TaskBurst]
 */
void BuildTaskScheduleFromInputStream(std::istream& InOutInputStream, std::vector<GTask>& OutTaskSchedule);


/**
 * Entry point of application
 */
int main(const int argc, const char* const argv[])
{
	if (argc <= 2)
	{
		std::cout << "Invalid arguments given." << '\n';
		std::cout << "Expected arguments format: [TaskScheduleFileName] [SchedulingAlgorithmName]" << '\n';

		std::cout << '\n';

		std::cout << "Availible schedule algorithms: " << '\n';
		for (std::pair<std::string, GDelegate<void, GTaskProcessor&, std::vector<GTask>&>> ScheduleAlgorithm : GScheduleAlgorithms)
		{
			std::cout << '\"' << ScheduleAlgorithm.first << '\"' << '\n';
		}

		std::cout.flush();
		return GExitCodeErrorBadArguments;
	}

	std::vector<GTask> ReadyQueue;

	// Build ready queue
	{
		const std::string InputFileName = argv[1];
		std::ifstream InputFileStream = std::ifstream(InputFileName);
		if (InputFileStream.is_open() == false)
		{
			std::cout << "No \"" << InputFileName << "\" file present. Exiting." << '\n';
			std::cout.flush();
			return GExitCodeErrorNoInputFile;
		}

		BuildTaskScheduleFromInputStream(InputFileStream, ReadyQueue);

		InputFileStream.close();
	}

	// Get the schedule algorithm
	const std::string AlgorithmName = argv[2];
	std::map<std::string, GDelegate<void, GTaskProcessor&, std::vector<GTask>&>>::iterator ScheduleAlgorithm = GScheduleAlgorithms.find(AlgorithmName);
	if (ScheduleAlgorithm == GScheduleAlgorithms.end())
	{
		std::cout << "No \"" << AlgorithmName << "\" scheduling algorithm exists. Exiting." << '\n';
		std::cout.flush();
		return GExitCodeErrorBadScheduleAlgorithmName;
	}

	// Create and configure our task processor
	GTaskProcessor TaskProcessor;
	TaskProcessor.TimeQuantum = 10;
	TaskProcessor.TimeScale = 100;
	std::printf("Task processor created with time quantum [%d].\n", TaskProcessor.TimeQuantum);

	std::cout << '\n';

	// Invoke the algorithm with our task processor and ready queue
	std::printf("Processing tasks with scheduling algorithm [%s].\n", AlgorithmName.c_str());
	std::cout << '\n';
	std::cout.flush();

	GTaskBenchmarker::StartBenchmarking();
	ScheduleAlgorithm->second.Execute(TaskProcessor, ReadyQueue);
	GTaskBenchmarker::StopBenchmarking();

	std::cout << '\n';

	// Print benchmarking results
	std::printf("Finished processing tasks with total process time of [%d].\n", GTaskBenchmarker::GetTotalProcessTime());
	std::printf("Average turnaround time: [%.2f].\n", GTaskBenchmarker::GetAverageTurnaroundTime());
	std::printf("Average waiting time: [%.2f].\n", GTaskBenchmarker::GetAverageWaitingTime());
	std::printf("Average response time: [%.2f].\n", GTaskBenchmarker::GetAverageResponseTime());


	std::cout.flush();

	return 0; // exit with success status
}

void BuildTaskScheduleFromInputStream(std::istream& InOutInputStream, std::vector<GTask>& OutTaskSchedule)
{
	std::string Line;
	while (std::getline(InOutInputStream, Line))
	{
		std::stringstream LineStream = std::stringstream(Line);

		GTask Task;

		// Get task name
		{
			std::string TaskNameString;
			std::getline(LineStream, TaskNameString, ',');
			std::stringstream TaskNameStringStream = std::stringstream(TaskNameString);
			TaskNameStringStream >> Task.Name;
		}

		// Get task priority
		{
			std::string TaskPriorityString;
			std::getline(LineStream, TaskPriorityString, ',');
			std::stringstream TaskPriorityStringStream = std::stringstream(TaskPriorityString);
			TaskPriorityStringStream >> Task.Priority;
		}

		// Get task burst
		{
			std::string TaskBurstString;
			std::getline(LineStream, TaskBurstString, ',');
			std::stringstream TaskBurstStringStream = std::stringstream(TaskBurstString);
			TaskBurstStringStream >> Task.Burst;
		}

		OutTaskSchedule.push_back(Task);
	}
}
