
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
		int GetNextPoint();
		void OnMove(vector<Station>);
		void OnShow();

		void SetPassengerPosition();
		bool IsCabinFull();
		void PassengerGetOn(vector<Passenger>&,int);
		bool IsPassengerGetOut(int);
		int  PassengerGetOut(int);
		bool IsStop();
		void SetIsStop(bool);
		
	private:
		//車廂大小 42*28 每個乘客的邊緣各2px
		
		const int BASIC_VELOCITY = 2;
		int nextPoint=1;
		int prePoint=0;
		int leftTopX, leftTopY;			//車廂的左上角位置
		int rightDownX, rightDownY;		//車廂的右下角位置
		int velocity;					//速度
		int color[3];					//車廂顏色
		string movingDirection = "";
		string goingDirection="";
		vector<int> linePointX;
		vector<int> linePointY;
		vector<int> updateLinePointX;
		vector<int> updateLinePointY;

		vector<int> passedStation;

		const int PASSENGERPOSITIONX_UPDOWN[6] = {2,16, 2,16, 2,16};
		const int PASSENGERPOSITIONY_UPDOWN[6] = {2, 2,16,16,30,30};
		const int PASSENGERPOSITIONX_RIGHTLEFT[6] = { 2, 2,16,16,30,30 };
		const int PASSENGERPOSITIONY_RIGHTLEFT[6] = { 2,16, 2,16, 2,16 };
		const int MAXPASSENGERNUM = 6; //最多六個乘客
		bool isStop;
		vector<Passenger> passengerOnCabinList;
	};
}


