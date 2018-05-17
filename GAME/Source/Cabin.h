
namespace game_framework
{
	class Passenger;
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
		int  GetX();
		int  GetY();
		int  GetVelocity();
		void OnMove();
		void OnShow();

		void SetPassengerPosition();
		bool IsCabinFull();
		void PassengerGetOn(vector<Passenger>,int);
		bool IsPassengerGetOut(int);
		int  PassengerGetOut(int);
		bool GetIsStop();
		void SetIsStop(bool);
		
	private:
		//���[�j�p 42*28 �C�ӭ��Ȫ���t�U2px
		const int BASIC_VELOCITY = 2;
		int nextPoint=1;
		int prePoint=0;
		string movingDirection = "";
		string goingDirection="";
		int leftTopX, leftTopY;			//���[�����W����m
		int rightDownX, rightDownY;		//���[���k�U����m
		int velocity;					//�t��
		int color[3];					//���[�C��
		vector<int> linePointX;
		vector<int> linePointY;

		const int PASSENGERPOSITIONX_UPDOWN[6] = {2,16, 2,16, 2,16};
		const int PASSENGERPOSITIONY_UPDOWN[6] = {2, 2,16,16,30,30};
		const int PASSENGERPOSITIONX_RIGHTLEFT[6] = { 2, 2,16,16,30,30 };
		const int PASSENGERPOSITIONY_RIGHTLEFT[6] = { 2,16, 2,16, 2,16 };
		const int MAXPASSENGERNUM = 6; //�̦h���ӭ���
		bool isStop;
		vector<Passenger> passengerOnCabinList;
	};
}


