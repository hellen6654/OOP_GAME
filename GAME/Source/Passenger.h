namespace game_framework
{
	class Passenger
	{
	public:
		Passenger();
		void LoadBitmap();			//載入圖形
		void SetType(int);
		void SetXY(int,int);

		int GetStartStation();
		void RandomMadePassenger(vector<Passenger>&,int,int);
		void RandomMadePassenger(int);
		void OnShow();				//將圖形貼到畫面
		~Passenger();
	private:
		CMovingBitmap passengerAnimation;					//利用動畫作圖形
		const int MAXIUM_PASSENGER_TYPE = 1;				//乘客樣式個數
		const int MAXIUM_PASSANGER = 20;
		int finalStation;									//目的地
		int startStation;									//起點
		int x, y;											//圖形座標
		int passengerType;									//乘客類型
		vector<Passenger> passengerList;
	};
}

