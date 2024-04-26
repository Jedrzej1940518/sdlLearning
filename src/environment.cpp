
#include "environment.hpp"

Environment::Environment(int maxEpisodeSteps, int videoRecordInterval) : maxEpisodeSteps{maxEpisodeSteps}, videoRecordInterval{videoRecordInterval}, arena{fakeLevel}
{
    if (videoRecordInterval != 0)
        initHumanRender();
}

void Environment::initHumanRender() { initRendering(); }

void Environment::draw() { arena.draw(); }

bool make_info()
{
    return false;
}

py::array_t<float> make_obs(const levels::Arena::ObservationType &obs)
{
    return py::array_t<float>(obs.max_size(), obs.data());
}

py::tuple Environment::step(py::array_t<float> action)
{
    ++currentStep;
    auto r = action.unchecked<1>(); // add more dims l8ter sk8ter

    float targetAngle;
    sf::Vector2f targetVelocity;
    bool shoot;
    ships::Tactic::TacticOutcome tactic{};
    tactic.targetAngle = r(0);
    tactic.targetVelocity = {r(1), r(2)};
    tactic.shoot = {r(3) > 0.5};

    auto [obs, reward, done] = arena.step(tactic);

    bool trunc = currentStep > maxEpisodeSteps;

    return py::make_tuple(make_obs(obs), reward, done, trunc, make_info());
}
py::tuple Environment::reset()
{
    ++currentEpsiode;
    currentStep = 0;
    bool recordEpisode = videoRecordInterval and (videoRecordInterval % currentEpsiode == 0);

    auto obs = arena.reset(recordEpisode);

    return py::make_tuple(make_obs(obs), make_info());
}
