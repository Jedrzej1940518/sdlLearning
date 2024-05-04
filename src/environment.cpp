
#include "environment.hpp"

Environment::Environment(int maxEpisodeSteps, int videoRecordInterval, int frameSkip) : maxEpisodeSteps{maxEpisodeSteps}, videoRecordInterval{videoRecordInterval}, frameSkip{frameSkip}, arena{fakeLevel}
{
}

void Environment::initHumanRender() { initRendering(); }

void Environment::draw() { arena.draw(); }

bool make_info()
{
    return false;
}

py::array_t<float> make_obs(const levels::Arena::Observations &obs)
{
    auto result = py::array_t<float>(obs.size() * ObservationFactory::totalObsSize);
    auto buf = result.request();
    float *ptr = (float *)buf.ptr;

    for (int i = 0; i < obs.size(); ++i)
        for (int j = 0; j < ObservationFactory::totalObsSize; ++j)
            ptr[i * ObservationFactory::totalObsSize + j] = obs[i][j];

    result.resize({obs.size(), (std::size_t)ObservationFactory::totalObsSize});
    return result;
}

py::array_t<float> make_rewards(const levels::Arena::Rewards &obs)
{
    auto result = py::array_t<float>(obs.size(), obs.data());
    result.resize({obs.size(), 1ul});
    return result;
}

py::array_t<int> make_dones(const levels::Arena::Dones &dones)
{
    auto result = py::array_t<int>(dones.size(), dones.data());
    result.resize({dones.size(), 1ul});
    return result;
}

levels::Arena::Tactics make_tactics(py::array_t<float> actions)
{
    levels::Arena::Tactics tactics{};
    auto buf = actions.request();
    float *ptr = (float *)buf.ptr;

    for (int i = 0; i < buf.shape[0]; ++i)
    {
        int offset = buf.shape[1] * i;
        auto tactic = ships::Tactic::TacticOutcome{ptr[0 + offset], {ptr[1 + offset], ptr[2 + offset]}, ptr[3 + offset] > 0.5};
        tactics.push_back(tactic);
    }
    return tactics;
}

py::tuple Environment::step(py::array_t<float> actions)
{
    ++currentStep;
    auto tactics = make_tactics(actions);
    auto [obs, rewards, dones] = arena.step(tactics, frameSkip);

    bool trunc = currentStep > maxEpisodeSteps;
    return py::make_tuple(make_obs(obs), make_rewards(rewards), make_dones(dones), trunc, make_info());
}
py::tuple Environment::reset()
{
    ++currentEpsiode;
    currentStep = 0;
    bool recordEpisode = videoRecordInterval and (currentEpsiode % videoRecordInterval == 0);

    auto obs = arena.reset(recordEpisode);

    return py::make_tuple(make_obs(obs), make_info());
}
