
#include "environment.hpp"

Environment::Environment(int maxEpisodeSteps, int videoRecordInterval, int frameSkip, int scenario, std::string logPath) : maxEpisodeSteps{maxEpisodeSteps}, videoRecordInterval{videoRecordInterval}, frameSkip{frameSkip}, scenario{scenario}, logPath{logPath}, arena{fakeLevel, logPath}
{
    initTimer();
}

bool make_info()
{
    return false;
}

ships::Tactic::TacticOutcome make_tactic(py::array_t<float> action)
{
    auto buf = action.request();
    float *ptr = (float *)buf.ptr;

    return ships::Tactic::TacticOutcome{ptr[0], {ptr[1], ptr[2]}, ptr[3] > 0};
}

py::tuple Environment::step(py::array_t<float> action)
{
    ++currentStep;
    auto tactic = make_tactic(action);
    auto [obs, reward, done] = arena.step(tactic, frameSkip);

    bool trunc = currentStep > maxEpisodeSteps;
    auto convertedObs = py::array_t<float>(obs.size(), obs.data());

    return py::make_tuple(convertedObs, reward, done, trunc, make_info());
}
py::tuple Environment::reset()
{
    globals::TIMER->startTimer(__FUNCTION__);

    ++currentEpsiode;
    currentStep = 0;
    bool recordEpisode = videoRecordInterval and (currentEpsiode % videoRecordInterval == 0);

    auto obs = arena.reset(scenario, recordEpisode);
    auto convertedObs = py::array_t<float>(obs.size(), obs.data());

    globals::TIMER->endTimer(__FUNCTION__);

    return py::make_tuple(convertedObs, make_info());
}

void Environment::writeTimerResults()
{
    globals::TIMER->writeResults(logPath + std::string{"timer.csv"});
}