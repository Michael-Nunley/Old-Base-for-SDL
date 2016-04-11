class Frame
{
    public:
        Frame();
        ~Frame();

        int getFPmS();
    private:
        int mTicksSinceStart;
        LTimer fpsTimer;
};

Frame::Frame()              {fpsTimer.start();}
Frame::~Frame()             {fpsTimer.stop();}

int Frame::getFPmS()
{
    mTicksSinceStart = fpsTimer.getTicks();
    return (mTicksSinceStart);
}
