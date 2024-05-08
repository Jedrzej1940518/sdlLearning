
#include "environment.hpp"

Environment::Environment(int maxEpisodeSteps, int videoRecordInterval, int frameSkip) : maxEpisodeSteps{maxEpisodeSteps}, videoRecordInterval{videoRecordInterval}, frameSkip{frameSkip}, arena{fakeLevel}
{
}

bool make_info()
{
    return false;
}

py::array_t<float> make_obs(const levels::Arena::ObservationType &obs)
{
    return py::array_t<float>(obs.size(), obs.data());
}

ships::Tactic::TacticOutcome make_tactic(py::array_t<float> action)
{
    auto buf = action.request();
    float *ptr = (float *)buf.ptr;

    return ships::Tactic::TacticOutcome{ptr[0], {ptr[1], ptr[2]}, ptr[3] > 0.5};
}

py::tuple Environment::step(py::array_t<float> action)
{
    ++currentStep;
    auto tactic = make_tactic(action);
    auto [obs, reward, done] = arena.step(tactic, frameSkip);

    bool trunc = currentStep > maxEpisodeSteps;
    return py::make_tuple(make_obs(obs), reward, done, trunc, make_info());
}
py::tuple Environment::reset()
{
    ++currentEpsiode;
    currentStep = 0;
    bool recordEpisode = videoRecordInterval and (currentEpsiode % videoRecordInterval == 0);

    auto obs = arena.reset(recordEpisode);

    return py::make_tuple(make_obs(obs), make_info());
}
