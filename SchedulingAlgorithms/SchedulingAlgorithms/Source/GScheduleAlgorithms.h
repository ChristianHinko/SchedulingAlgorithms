// Green Team - Robert Squires, Christian Hinkle

#pragma once

#include <string>
#include <map>
#include <vector>


class GTask;
class GTaskProcessor;
template <class TReturnType, class... TParameterTypes>
class GDelegate;



/**
 * Central container of all task scheduling algorithms. Maps from algorithm name to function.
 * 
 * See G_REGISTER_SCHEDULE_ALGORITHM() for adding scheduling algorithms to this.
 */
extern std::map<std::string, GDelegate<void, GTaskProcessor&, std::vector<GTask>&>> GScheduleAlgorithms;

/**
 * Statically registers a given function to the GScheduleAlgorithms.
 * Use this next to the definition of your function (not the declaration because this
 * code has definitions).
 */
#define G_REGISTER_SCHEDULE_ALGORITHM(NameString, Function) \
namespace\
{\
	class GRegisterScheduleAlgorithm_##Function\
	{\
	public:\
		GRegisterScheduleAlgorithm_##Function()\
		{\
			GScheduleAlgorithms.emplace(NameString, Function);\
		}\
	};\
\
	GRegisterScheduleAlgorithm_##Function RegisterScheduleAlgorithm_##Function;\
}


/** First-come first-serve algorithm */
void ScheduleAlgorithmFirstComeFirstServe(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue);

/** Shortest-job-first algorithm */
void ScheduleAlgorithmShortestJobFirst(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue);

/** Priority algorithm */
void ScheduleAlgorithmPriority(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue);

/** Round-robin algorithm */
void ScheduleAlgorithmRoundRobin(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue);

/** Priority with round-robin algorithm */
void ScheduleAlgorithmPriorityRoundRobin(GTaskProcessor& InOutTaskProcessor, std::vector<GTask>& InOutReadyQueue);
