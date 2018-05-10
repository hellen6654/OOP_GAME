
namespace game_framework
{
	
	class Cabin
	{
	public:
		Cabin();
		Cabin(int,int,int,int,int);
		~Cabin();
		void SetXY(int, int);
		void SetVelocity(int);
		void SetMovingCabin(string,int);
		void SetIsShow(bool);
		void SetRGB(int, int, int);
		void SetGoingDirection(string);
		void SetMovingDirection(string);
		void SetLinePoint(vector<int>, vector<int>);
		int  GetX();
		int  GetY();
		int  GetVelocity();
		bool IsShow();
		void OnMove();
		void OnShow();
	private:
		//���[�j�p 42*28 �C�ӭ��Ȫ���t�U2px
		int nextPoint=1;
		int prePoint=0;
		string movingDirection = "";
		string goingDirection="";
		int leftTopX, leftTopY;			//���[�����W����m
		int rightDownX, rightDownY;		//���[���k�U����m
		int velocity;					//�t��
		int color[3];					//���[�C��
		bool isShow;
		vector<int> linePointX;
		vector<int> linePointY;
		//int passenagerNum; //�̦h����
		//vector<Passenger*> passengerList;
		
	};
}


