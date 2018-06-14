
namespace game_framework
{
	class Passenger;
	class Station;
	class Cabin
	{
	public:
		Cabin();
		Cabin(int,int,int,int,int);
		~Cabin();
		void SetXY(int, int);
		void SetVelocity(int);
		void SetMovingCabin(string,int);
		void SetRGB(int, int, int);
		void SetGoingDirection(string);
		void SetMovingDirection(string);
		void SetLinePoint(vector<int>, vector<int>);
		void SetPassedStation(vector<int>);
		int  GetX();
		int  GetY();
		int  GetVelocity();
		int  GetNextPoint();
		void GetRGB(int& R, int& G, int& B);
		void OnMove(vector<Station> totalStationList);
		void OnShow();
		bool IsInStation(int endX, int endY, vector<Station> totalStationList);
		void GetNextPrePoint(int&, int&);
		int	 GetNextStation();
		void SetLineStationNum(int num[6]);
		void GetLineStationNum(int (&num)[6]);
		void SetPassengerPosition();
		int  GetPassengerNum();
		void SetPassengerNum(int);
		void AddPassengerNum(int);
		bool IsCabinColorRepeat(vector<Cabin> cabinList, int R, int G, int B);
		int GetCabinPointer(vector<Cabin> cabinList, int R, int G, int B);
		bool IsCabinFull();
		void PassengerGetOn(Passenger* p, int nowStation);
		int  PassengerGetOut(int);
		bool IsStop();
		void SetIsStop(bool);
		void SetAddCounter(int n);
		void SetCounter(int n);
		int GetCounter();
	private:
		//車廂大小 42*28 每個乘客的邊緣各2px
		const int CABIN_STOP_IN_STATION_TIME = 30 / 2; //車廂停留在車站的時間
		const int BASIC_VELOCITY = 2;
		int nextPoint;
		int prePoint;
		int leftTopX, leftTopY;			//車廂的左上角位置
		int rightDownX, rightDownY;		//車廂的右下角位置
		int velocity;					//速度
		int color[3];					//車廂顏色
		int lineStationNum[6] = { 0 };
		int nextStation;				//下一個車站在totalStation裡的編號
		int passengerNum=0;
		int counter_cabin_stop;
		string movingDirection = "";
		string goingDirection="";
		vector<int> linePointX;
		vector<int> linePointY;

		vector<int> updatelinePointX;
		vector<int> updatelinePointY;

		vector<int> passedStation;

		const int PASSENGERPOSITIONX_UPDOWN[6] = {2,16, 2,16, 2,16};
		const int PASSENGERPOSITIONY_UPDOWN[6] = {2, 2,16,16,30,30};
		const int PASSENGERPOSITIONX_RIGHTLEFT[6] = { 2, 2,16,16,30,30 };
		const int PASSENGERPOSITIONY_RIGHTLEFT[6] = { 2,16, 2,16, 2,16 };
		const int MAX_PASSENGER_NUM = 6; //最多六個乘客
		bool isStop;
		bool isStopOnceInStation;
		vector<Passenger*> passengerOnCabinList;		//在車廂的乘客
	};
}


