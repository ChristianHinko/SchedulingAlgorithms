// Green Team - Robert Squires, Christian Hinkle

#pragma once

#include <string>
#include "GMulticastDelegate.h"
#include <atomic>


class GTaskProcessor;



/**
 * A task that can be processed by a task processor.
 */
class GTask
{
public:
	GTask();


	/** Unique ID for this task. */
	unsigned int Id;

	/** Name of this task. */
	std::string Name;

	/** Priority of this task. From 0 to 10. Higher value means higher priority. */
	int Priority;

	/** The current burst time. The remaining amount of processor time that we want. */
	int Burst;


	/** Process tick function */
	virtual void Process(const float InDeltaSeconds);


	/** Broadcasted before the task is processed by the processor. */
	static GMulticastDelegate<const GTask&, const GTaskProcessor&, const int> OnPreProcessDelegate;

	/** Broadcasted afterthe task is processed by the processor. */
	static GMulticastDelegate<const GTask&, const GTaskProcessor&, const int> OnPostProcessDelegate;

private:
	/** Static thread-safe counter for the next unique ID to use for the next task. */
	static std::atomic<unsigned int> NextId;
};
