class Student{
  public:
    Student();
    Student(int arrivalTime, int windowTime);
    ~Student();

    int getArrivalTime();
    int getWindowTime();
  private:
    int m_arrivalTime;
    int m_windowTime;
};
