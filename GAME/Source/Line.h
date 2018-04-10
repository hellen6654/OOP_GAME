

namespace game_framework
{
	class Line
	{
	public:
		Line();
		~Line();
		void SetmouseClickedPointA(int, int);
		void SetisStation_A_Clicked(bool);
		void SetisStation_B_Clicked(bool);
		void SetclickedStationNumA(int);
		void SetclickedStationNumB(int);
		int	 GetclickedStationNumA();
		int	 GetclickedStationNumB();
		int	 GetmouseClickedPoint_X();
		int	 GetmouseClickedPoint_Y();
		bool IsStation_A_Clicked();
		bool IsStation_B_Clicked();
		bool IsClickedOnStation(int,int,vector<Station>,int); //檢查是否有點到車站
	private:
		const int stationSize = 25;					// 每張車站的大小為25*25
		int		mouseClickedPoint_X;				// 存放滑鼠點擊位置
		int		mouseClickedPoint_Y;				// 存放滑鼠點擊位置
		int		clickedStationNumA;					// 哪個是起點車站
		int		clickedStationNumB;					// 哪個是終點車站
		bool	isStation_A_Clicked;				// 是否選出起點車站
		bool	isStation_B_Clicked;				// 是否選出終點車站
	};

	
}