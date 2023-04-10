// Green Team - Robert Squires, Christian Hinkle

#pragma once

class GTask;



/**
 * Processes tasks.
 */
class GTaskProcessor
{
public:
	GTaskProcessor();

	/**
	 * The max time that a task is allowed to be processed.
	 * TODO: Make a value of -1 mean infinite.
	 */
	int TimeQuantum;

	/** Process a given task. */
	virtual void ProcessTask(GTask& InOutTask, const int InTimeSlice);

	int GetTotalProcessTime() const { return TotalProcessTime; }

	/** Time dilation multiplier. */
	float TimeScale;

protected:
	int TotalProcessTime;
};
