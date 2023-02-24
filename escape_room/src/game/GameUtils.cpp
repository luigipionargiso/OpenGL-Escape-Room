#include <sstream>
#include <iomanip>
#include "GameUtils.h"
#include "engine/text_rendering/Text.h"

bool CheckDistanceLimit(GameObject& ob1, GameObject& ob2)
{
    if (glm::distance(ob1.GetPosition(), ob2.GetPosition()) <= MAX_PICK_DIST)
        return true;
    return false;
}

void DrawTime()
{
    Game& game = Game::GetInstance();

    /* draw current time */
    int min = game.current_time_ / 60;
    int sec = game.current_time_ % 60;
    std::string time = "Time: " + TwoDigitsFormat(min) + ":" + TwoDigitsFormat(sec);
    Text::Render(time.c_str(), -0.5f, 0.9f, 16.0f);

    /* draw last record */
    if (game.last_record_ != 0)
    {
        min = game.last_record_ / 60;
        sec = game.last_record_ % 60;
        std::string record = "Last record: " + TwoDigitsFormat(min) + ":" + TwoDigitsFormat(sec);
        Text::Render(record.c_str(), 0.25f, 0.9f, 16.0f);
    }
}

std::string TwoDigitsFormat(unsigned int n)
{
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << n;
    return oss.str();
}

