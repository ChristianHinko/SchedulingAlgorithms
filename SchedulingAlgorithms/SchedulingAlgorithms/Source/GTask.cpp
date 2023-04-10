// Green Team - Robert Squires, Christian Hinkle


#include "GTask.h"
#include "GTaskProcessor.h"
#include "GMulticastDelegate.h"



std::atomic<unsigned int> GTask::NextId = 0;
GMulticastDelegate<const GTask&, const GTaskProcessor&, const int> GTask::OnPreProcessDelegate;
GMulticastDelegate<const GTask&, const GTaskProcessor&, const int> GTask::OnPostProcessDelegate;


GTask::GTask()
	: Id(0)
	, Name(std::string())
	, Priority(0)
	, Burst(0)
{
	Id = NextId;
	++NextId;
}

void GTask::Process(const float InDeltaSeconds)
{

}
