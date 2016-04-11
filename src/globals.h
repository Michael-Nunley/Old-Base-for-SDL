TTF_Font *gFont = NULL;
SDL_Renderer* gRenderer = NULL;
Mix_Music *gMusic = NULL;

bool quit = false;
bool escapeOpen = false;

std::string int64ToString(uint64_t i)
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
std::string int32ToString(uint32_t i)
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
std::string int16ToString(uint16_t i)
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
std::string doubleToString(double i)
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
std::string floatToString(float i)
{
    std::stringstream ss;
    ss<<i;
    return ss.str();
}
