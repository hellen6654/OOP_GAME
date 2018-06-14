
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
		//���[�j�p 42*28 �C�ӭ��Ȫ���t�U2px
		const int CABIN_STOP_IN_STATION_TIME = 30 / 2; //���[���d�b�������ɶ�
		const int BASIC_VELOCITY = 2;
		int nextPoint;
		int prePoint;
		int leftTopX, leftTopY;			//���[�����W����m
		int rightDownX, rightDownY;		//���[���k�U����m
		int velocity;					//�t��
		int color[3];					//���[�C��
		int lineStationNum[6] = { 0 };
		int nextStation;				//�U�@�Ө����btotalStation�̪��s��
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
		const int MAX_PASSENGER_NUM = 6; //�̦h���ӭ���
		bool isStop;
		bool isStopOnceInStation;
		vector<Passenger*> passengerOnCabinList;		//�b���[������
	};
}


