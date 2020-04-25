class Window{
  public:
    Window();//default
    ~Window();//destructor

    int getTimeFree();//get the time that the window is free
    int getTimeArrived();//get time arrived

    void setTimeFree(int timeFree);
    void setTimeArrived(int timeArrived);
  private:
    //member variables 
    int m_timeFree;
    int m_timeArrived;
};
