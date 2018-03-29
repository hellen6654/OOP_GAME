namespace game_framework
{
	class Timer
	{
	public:
		Timer();
		void StartCount();
		void CountPassTime();
		void ResetCount();
		int GetTime();
		~Timer();

	private:
		time_t start_time;
		time_t end_time;
		int time;
	};

}

