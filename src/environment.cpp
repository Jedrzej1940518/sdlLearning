
#include "environment.hpp"

Environment::Environment() : arena{fakeLevel}
{
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

    return py::make_tuple(make_obs(obs), reward, done, trunc);
}
py::array_t<float> Environment::reset()
{
    auto obs = arena.reset();
    return make_obs(obs);
}
