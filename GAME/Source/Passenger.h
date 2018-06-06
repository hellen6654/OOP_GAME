namespace game_framework
{
	class Station;
	class Passenger
	{
	public:
		Passenger();
		Passenger(int,int,int,int,int);
		void LoadBitmap();									//載入圖形
		void SetType(int);
		void SetXY(int,int);
		int GetStartStation();
		int GetFinalStation();
		void RandomMadePassenger(vector<Passenger>& passengerList,vector<Station> stationList, int stationMaxium, int stationTypeNum,int passenagerNum);
		void OnShow();										//將圖形貼到畫面
		~Passenger();
	private:
		CMovingBitmap passengerAnimation;					//乘客圖形 
		int finalStation;									//終點
		int startStation;									//起點
		int x, y;											//圖形座標
		int passengerType;									//乘客類型
	};
}

